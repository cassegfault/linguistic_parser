//
//  word_stats.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#include "word_stats.h"
#include <string>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <chris/json.h>
#include <vector>
#include <cstdint>

enum cache_markers {
    CACHE_WORD_START    = 's',
    CACHE_WORD_END      = 'e',
    CACHE_FILE_END      = 'Z',
    CACHE_SEPARATOR     = '-',
    CACHE_PARTS_END     = 'P',
    CACHE_BIGRAM_START  = 'B'
};


static std::unordered_map<string, word_stats> _global_word_stats;
unordered_map<string,unordered_map<short, int> > word_pos_counts;
unordered_map< string, float> bigram_probabilities;
unordered_map< string, int> bigram_counts;
int total_bigrams = 0;

unordered_map<string, vector<vector<short> > > current_chunk_patterns;
unordered_map<string, vector<short> > chunk_patterns;
/*
 NP = 2 256 128 0
 unordered_map<string,vector<short> > chunk_patterns
*/

unordered_map<short, vector<chunk_model> > mapped_chunks;

const unordered_map<string, word_stats> & global_word_stats(){
    return _global_word_stats;
}
const unordered_map<string, float> & global_bigram_probabilities(){
    return bigram_probabilities;
}
const unordered_map<string, vector<short> > & global_chunk_patterns(){
    return chunk_patterns;
}
const unordered_map<short, vector<chunk_model> > & global_mapped_chunks(){
    return mapped_chunks;
}


// char - word start marker
//    uint16 - probability (between 1-65536)
//    char   - separator
//    uint16 - probability (between 1-65536)
//    char   - separator
void save_cache(){
    ofstream cachefile("caches.dat",std::ios::binary);
    int idx = 0;
    int skipped = 0;
    for(auto word : global_word_stats()){
        if(word.second.probabilities.size() < 1 || word.first.size() < 1){
            skipped++;
            continue;
        }
        cachefile << (char)CACHE_WORD_START;
        idx = 0;
        for(auto p : word.second.probabilities){
            uint16_t probability = (uint16_t)(p.second * 65535.0);
            cachefile << (uint16_t)p.first;
            cachefile << (char)CACHE_SEPARATOR;
            cachefile << probability;
            if (idx == word.second.probabilities.size() - 1){
                cachefile << (char)CACHE_PARTS_END;
            } else {
                cachefile << (char)CACHE_SEPARATOR;
            }
            idx++;
        }
        cachefile << word.first << '\0';
    }
    for(auto bigram : global_bigram_probabilities()){
        cachefile << (char)CACHE_BIGRAM_START;
        cachefile << (uint16_t)(bigram.second * 65535.0);
        cachefile << (char)CACHE_SEPARATOR;
        cachefile << bigram.first << '\0';
    }
    cachefile << (char)CACHE_FILE_END;
    cachefile.close();
    cout << "Skipped " << skipped << " words" << endl;
}


void load_brown_data(){
    ifstream mapfile("/usr/local/texts/universal_tagset/en-brown.map");
    std::unordered_map<string, short> intermediary_map {
        { "VERB", pos_verb },
        { "NOUN", pos_noun },
        { "PRON", pos_pronoun },
        { "ADJ", pos_adjective },
        { "ADV", pos_adverb },
        { "ADP", pos_preposition },
        { "CONJ", pos_conjunction },
        { "DET", pos_determiner },
        { "NUM", pos_number },
        { "PRT", pos_particle },
        { "X", pos_none },
        { ".", pos_punctuation }
    };
    std::unordered_map<string, short> pos_map;
    string line, token;
    bool in_key = true;
    cout << intermediary_map["DET"] << " : " << pos_determiner << endl;
    while(std::getline(mapfile,line)){
        in_key = true;
        auto split = line.find("\t");
        auto _pos = line.substr(0,split);
        auto _pos2 = line.substr(split + 1);
        to_uppercase(_pos);
        to_uppercase(_pos2);
        short mapped = intermediary_map[_pos2];
        pos_map[_pos] = mapped;
    }
    size_t split;
    vector<string> files({ "ca01", "ca02", "ca03", "ca04", "ca05", "ca06", "ca07", "ca08", "ca09", "ca10", "ca11", "ca12", "ca13", "ca14", "ca15", "ca16", "ca17", "ca18", "ca19", "ca20", "ca21", "ca22", "ca23", "ca24", "ca25", "ca26", "ca27", "ca28", "ca29", "ca30", "ca31", "ca32", "ca33", "ca34", "ca35", "ca36", "ca37", "ca38", "ca39", "ca40", "ca41", "ca42", "ca43", "ca44", "cb01", "cb02", "cb03", "cb04", "cb05", "cb06", "cb07", "cb08", "cb09", "cb10", "cb11", "cb12", "cb13", "cb14", "cb15", "cb16", "cb17", "cb18", "cb19", "cb20", "cb21", "cb22", "cb23", "cb24", "cb25", "cb26", "cb27", "cc01", "cc02", "cc03", "cc04", "cc05", "cc06", "cc07", "cc08", "cc09", "cc10", "cc11", "cc12", "cc13", "cc14", "cc15", "cc16", "cc17", "cd01", "cd02", "cd03", "cd04", "cd05", "cd06", "cd07", "cd08", "cd09", "cd10", "cd11", "cd12", "cd13", "cd14", "cd15", "cd16", "cd17", "ce01", "ce02", "ce03", "ce04", "ce05", "ce06", "ce07", "ce08", "ce09", "ce10", "ce11", "ce12", "ce13", "ce14", "ce15", "ce16", "ce17", "ce18", "ce19", "ce20", "ce21", "ce22", "ce23", "ce24", "ce25", "ce26", "ce27", "ce28", "ce29", "ce30", "ce31", "ce32", "ce33", "ce34", "ce35", "ce36", "cf01", "cf02", "cf03", "cf04", "cf05", "cf06", "cf07", "cf08", "cf09", "cf10", "cf11", "cf12", "cf13", "cf14", "cf15", "cf16", "cf17", "cf18", "cf19", "cf20", "cf21", "cf22", "cf23", "cf24", "cf25", "cf26", "cf27", "cf28", "cf29", "cf30", "cf31", "cf32", "cf33", "cf34", "cf35", "cf36", "cf37", "cf38", "cf39", "cf40", "cf41", "cf42", "cf43", "cf44", "cf45", "cf46", "cf47", "cf48", "cg01", "cg02", "cg03", "cg04", "cg05", "cg06", "cg07", "cg08", "cg09", "cg10", "cg11", "cg12", "cg13", "cg14", "cg15", "cg16", "cg17", "cg18", "cg19", "cg20", "cg21", "cg22", "cg23", "cg24", "cg25", "cg26", "cg27", "cg28", "cg29", "cg30", "cg31", "cg32", "cg33", "cg34", "cg35", "cg36", "cg37", "cg38", "cg39", "cg40", "cg41", "cg42", "cg43", "cg44", "cg45", "cg46", "cg47", "cg48", "cg49", "cg50", "cg51", "cg52", "cg53", "cg54", "cg55", "cg56", "cg57", "cg58", "cg59", "cg60", "cg61", "cg62", "cg63", "cg64", "cg65", "cg66", "cg67", "cg68", "cg69", "cg70", "cg71", "cg72", "cg73", "cg74", "cg75", "ch01", "ch02", "ch03", "ch04", "ch05", "ch06", "ch07", "ch08", "ch09", "ch10", "ch11", "ch12", "ch13", "ch14", "ch15", "ch16", "ch17", "ch18", "ch19", "ch20", "ch21", "ch22", "ch23", "ch24", "ch25", "ch26", "ch27", "ch28", "ch29", "ch30", "cj01", "cj02", "cj03", "cj04", "cj05", "cj06", "cj07", "cj08", "cj09", "cj10", "cj11", "cj12", "cj13", "cj14", "cj15", "cj16", "cj17", "cj18", "cj19", "cj20", "cj21", "cj22", "cj23", "cj24", "cj25", "cj26", "cj27", "cj28", "cj29", "cj30", "cj31", "cj32", "cj33", "cj34", "cj35", "cj36", "cj37", "cj38", "cj39", "cj40", "cj41", "cj42", "cj43", "cj44", "cj45", "cj46", "cj47", "cj48", "cj49", "cj50", "cj51", "cj52", "cj53", "cj54", "cj55", "cj56", "cj57", "cj58", "cj59", "cj60", "cj61", "cj62", "cj63", "cj64", "cj65", "cj66", "cj67", "cj68", "cj69", "cj70", "cj71", "cj72", "cj73", "cj74", "cj75", "cj76", "cj77", "cj78", "cj79", "cj80", "ck01", "ck02", "ck03", "ck04", "ck05", "ck06", "ck07", "ck08", "ck09", "ck10", "ck11", "ck12", "ck13", "ck14", "ck15", "ck16", "ck17", "ck18", "ck19", "ck20", "ck21", "ck22", "ck23", "ck24", "ck25", "ck26", "ck27", "ck28", "ck29", "cl01", "cl02", "cl03", "cl04", "cl05", "cl06", "cl07", "cl08", "cl09", "cl10", "cl11", "cl12", "cl13", "cl14", "cl15", "cl16", "cl17", "cl18", "cl19", "cl20", "cl21", "cl22", "cl23", "cl24", "cm01", "cm02", "cm03", "cm04", "cm05", "cm06", "cn01", "cn02", "cn03", "cn04", "cn05", "cn06", "cn07", "cn08", "cn09", "cn10", "cn11", "cn12", "cn13", "cn14", "cn15", "cn16", "cn17", "cn18", "cn19", "cn20", "cn21", "cn22", "cn23", "cn24", "cn25", "cn26", "cn27", "cn28", "cn29", "cp01", "cp02", "cp03", "cp04", "cp05", "cp06", "cp07", "cp08", "cp09", "cp10", "cp11", "cp12", "cp13", "cp14", "cp15", "cp16", "cp17", "cp18", "cp19", "cp20", "cp21", "cp22", "cp23", "cp24", "cp25", "cp26", "cp27", "cp28", "cp29", "cr01", "cr02", "cr03", "cr04", "cr05", "cr06", "cr07", "cr08", "cr09" });
    short previous_pos = 0;
    for(auto filename : files){
        ifstream tagfile("/usr/local/texts/brown/"+filename);
        while(!tagfile.eof()){
            tagfile >> token;
            split = token.find("/");
            if (split != string::npos){
                string word =token.substr(0,split);
                to_lowercase(word);
                string _pos = token.substr(split + 1);
                to_uppercase(_pos);
                short _pos2 = pos_map[_pos];
                if(_pos2 > 0){
                    word_pos_counts[word][_pos2]++;
                    if(previous_pos > 0){
                        bigram_counts[ ( pos_strings.at(previous_pos) + pos_strings.at(_pos2) ) ]++;
                        total_bigrams++;
                    }
                    previous_pos = _pos2;
                }
            }
        }
    }
}
void load_chunk_file(){
    std::ifstream chunkfile("/usr/local/texts/chunks.txt");
    string line;
    string current_pos;
    string current_pattern;
    short combined_pattern = 0;
    while(std::getline(chunkfile,line)){
        chunk_model current_chunk;
        string type;
        auto split = line.find('\t');
        if(split != std::string::npos){
            auto type = line.substr(0,split);
            if(chunk_bits.find(type) != chunk_bits.end()){
                current_chunk.chunk_type =  chunk_bits.at(type);
                for(int idx = (int)split + 1; idx < line.length(); idx++){
                    // Iterate the line after the chunk type
                    char cmp = line.at(idx);
                    if(cmp == ' '){
                        // if we're at a space, log out the type we've just iterated over
                        to_lowercase(current_pos);
                        if(current_pos.size() > 0){
                            // append the POS
                            // add the pos to the pattern
                            current_pattern += current_pos;
                            combined_pattern |= pos_bits.at(current_pos);
                        }
                        current_pos.clear();
                    } else {
                        // append the char to the pos
                        current_pos += line[idx];
                    }
                }
                if(current_pattern.size() > 1){
                    if(current_pos.size() > 0){
                        to_lowercase(current_pos);
                        current_pattern += current_pos;
                        combined_pattern |= pos_bits.at(current_pos);
                    }
                    //chunk_patterns[current_pattern] = type;
                    current_chunk.parts.push_back(pos_bits.at(current_pos));
                }
                
                //mapped_chunks[combined_pattern] = pattern_parts;
                mapped_chunks[combined_pattern].push_back(current_chunk);
                current_pos.clear();
                current_pattern.clear();
                combined_pattern = 0;
            }
            
        }
    }
    cout << mapped_chunks.size() << " mapped chunks" << endl;
}

void load_stats_from_file(){
    load_brown_data();
    cout << word_pos_counts.size() << " words from brown corpus\n";
    string line;
    /*
    std::ifstream infile("wiktionary-english.json");
    libchris::json d;
    unordered_map<string, word_stats> word_parts;
    while (std::getline(infile, line))
    {
        
        auto j = d.parse(line);
        word_stats stats;
        
        stats.parts_of_speech = pos_none;
        
        for(string part : j["parts"]){
            if(pos_bits.find(part) != pos_bits.end()){
                stats.parts_of_speech |= pos_bits.at(part);
            }
        }
        _global_word_stats[j["word"]] = stats;
    }
     */
    std::ifstream twfile("/usr/local/texts/twpos/full_data/daily547.supertsv");
    std::ifstream twfile2("/usr/local/texts/twpos/full_data/oct27.supertsv");
    char pos;
    std::string word;
    std::unordered_map<char, short> pos_map({
        { 'V', pos_verb },
        { 'N', pos_noun },
        { '^', pos_noun },
        { 'Z', pos_noun },
        { 'O', pos_pronoun },
        { 'P', pos_preposition },
        { 'A', pos_adjective },
        { 'R', pos_adverb },
        { '!', pos_interjection },
        { 'D', pos_determiner },
        { 'T', pos_particle },
        { '$', pos_number },
        { ',', pos_punctuation },
        { 'G', pos_none },
        { 'E', pos_none },
        { 'U', pos_none },
        { 'X', pos_none },
        { '#', pos_number },
        { '@', pos_none },
        { '~', pos_none },
        { '&', pos_none },
        { 'S', -1 },
        { 'Z', -1 },
        { 'L', -1 },
        { 'M', -1 },
        { 'N', -1 },
    });
    
    short previous_pos = 0;
    while(std::getline(twfile, line)){
        auto first_bit = line.substr(0,5).c_str();
        if(line.size() > 0 && strcmp("TWEET", first_bit) != 0 && strcmp("TOKEN", first_bit) != 0){
            pos = line.c_str()[0];
            word =line.substr(2);
            to_lowercase(word);
            word_pos_counts[word][pos_map[pos]]++;
            if(pos_map[pos] > 0 && previous_pos > 0){
                total_bigrams++;
                bigram_counts[ (pos_strings.at(previous_pos) + pos_strings.at(pos_map[pos])) ]++;
            }
            previous_pos = pos_map[pos];
        }
    }
    previous_pos = 0;
    while(std::getline(twfile2, line)){
        auto first_bit = line.substr(0,5).c_str();
        if(line.size() > 0 && strcmp("TWEET", first_bit) != 0 && strcmp("TOKEN", first_bit) != 0){
            pos = line.c_str()[0];
            word = line.substr(2);
            to_lowercase(word);
            word_pos_counts[word][pos_map[pos]]++;
            if(pos_map[pos] > 0 && previous_pos > 0){
                total_bigrams++;
                bigram_counts[ (pos_strings.at(previous_pos) + pos_strings.at(pos_map[pos])) ]++;
            }
            previous_pos = pos_map[pos];
        }
    }
    
    int total_count = 0;
    for(auto word : word_pos_counts){
        total_count = 0;
        for(auto pos : word.second){
            total_count += pos.second;
        }
        for(auto pos : word.second){
            uint16_t prob = (uint16_t)(((float)pos.second / (float)total_count) * 65535.0);
            if(prob > 0){
                _global_word_stats[word.first].probabilities[pos.first] = (float)pos.second / (float)total_count;
                _global_word_stats[word.first].parts_of_speech |= pos.first;
            }
        }
    }
    for (auto bigram : bigram_counts){
        bigram_probabilities[bigram.first] = (float)bigram.second / (float)total_bigrams;
    }
    save_cache();
}


void load_global_word_stats(){
    //*
    load_stats_from_file();
    // */
    load_chunk_file();
    /*
    ifstream cachefile("caches.dat", std::ios::binary);
    char cmd = '\0';
    char cur = '\0';
    string word;
    uint16_t current_part = 0;
    uint16_t current_probability = 0;
    short parts = 0;
    unordered_map<short, float> probabilities;
    cachefile >> cmd;
    while(cmd == CACHE_WORD_START){
        current_part = 0;
        parts = 0;
        probabilities.clear();
        while (cur != CACHE_PARTS_END){
            cachefile >> current_part;
            parts |= current_part;
            cachefile >> cur;
            cachefile >> current_probability;
            probabilities[current_part] = (float)((float)current_probability / 65536.0);
            cachefile >> cur;
        }
        word.clear();
        cachefile >> cur;
        while (cur != '\0'){
            word += cur;
            cachefile >> cur;
        }
        _global_word_stats[word].probabilities = probabilities;
        _global_word_stats[word].parts_of_speech = parts;
        cachefile >> cmd;
    }
    while(cmd == CACHE_BIGRAM_START){
        word.clear();
        cachefile >> current_probability;
        cachefile >> cur;
        while (cur != '\0'){
            word += cur;
            cachefile >> cur;
        }
        bigram_probabilities[word] = (float)((float)current_probability / 65536.0);
        cachefile >> cmd;
    }
        
    cachefile.close();
    //*/
}




