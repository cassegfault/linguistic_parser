    //
//  parser.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/15/17.
//
//

#include "parser.h"

#include <ctype.h>
#include <locale>
#include <set>
#include <chris/json_serialize.h>



Parser::Parser(string input){
    string current_word;
    locale loc;
    for(int idx = 0; idx < input.size(); idx++){
        
        input[idx] = tolower(input[idx], loc);
        switch(input[idx]){
            case '.':
            case ',':
            case ':':
            case '"':
            case ' ':
                input[idx] = ' ';
                words.push_back(current_word);
                current_word.clear();
                break;
            default:
                current_word += input[idx];
                break;
        }
    }
    
    // last of the characters
    words.push_back(current_word);
    
}

set<string> cfg ({
    "nounnoun", "adjadj", "adjnoun"
});
set<string> np ({
    "noun", "adj", "det", "prn"
});
set<string> vp ({
    "verb", "adv"
});

libchris::json Parser::serialize(){
    const unordered_map<std::string,word_stats> & word_stats = global_word_stats();
    auto bigram_probabilities = global_bigram_probabilities();
    vector<unordered_map<string,string>> output_words;
    string previous_pos;
    string current_np;
    string current_vp;
    vector<string> vps, nps;
    libchris::json output;
    output["output"] = libchris::json::array();
    for(auto word : words){
        libchris::json doc = libchris::json::object();
        doc["parts"] = libchris::json::array();
        unordered_map<string,string> current_word;
        if(word.size() == 0){
            continue;
        }
        if(word_stats.find(word) != word_stats.end()){
            short parts = word_stats.at(word).parts_of_speech;
            if(parts & pos_noun){
                doc["parts"].push_back("noun");
            }
            if(parts & pos_noun){
                doc["parts"].push_back("verb");
            }
            if(parts & pos_verb){
                doc["parts"].push_back("adj");
            }
            if(parts & pos_adjective){
                doc["parts"].push_back("adv");
            }
            if(parts & pos_adverb){
                doc["parts"].push_back("conj");
            }
            if(parts & pos_conjunction){
                doc["parts"].push_back("det");
            }
            if(parts & pos_determiner){
                doc["parts"].push_back("number");
            }
            if(parts & pos_number){
                doc["parts"].push_back("prep");
            }
            if(parts & pos_pronoun){
                doc["parts"].push_back("prn");
            }
            unordered_map<string,float> probabilities;
            float max_prob = -1.0;
            string max_prob_string;
            for(auto p : word_stats.at(word).probabilities){
                probabilities[pos_strings.at(p.first)] = p.second;
                if(p.second > max_prob){
                    string pos_string = pos_strings.at(p.first);
                    doc["pos"] = pos_string;
                    max_prob = p.second;
                }
            }
            doc["probabilities"] = probabilities;
        }
        doc["word"] = word;
        
        output["output"].push_back(doc);
    }
    /*
     As we iterate through keep a noun phrase
     wait for a verb phrase
     reset on hard punctuation (.?!)
     after verb phrase
     */
    
    
    
    
    /*
     ALL OTHER IDEAS SUCK USE THIS ONE
     
     sort chunks by length, iterate longest to smallest
        match each chunk using something like strncmp
        keep an array of parts, starting with one, split based on matches
     
     
     ALSO MAYBE THIS IDEA -- Definitely faster
     
     start with first POS, see if first + second match any chunks, if so move on to 1+2+3. the first not to match identifies the longest match at n-1, restart
     
     quick match patterns with the short system. short identifies noun+adj+verb on phrase, if pattern contains that as well, check the order. This could actually just be a map to look up possibilities
     */
    
    
    
    
    vector<short> current_pos_set;
    short combined_pos = 0;
    short current_chunk = 0;
    short prev_chunk = 0;
    auto chunks = global_chunk_patterns();
    auto mapped_chunks = global_mapped_chunks();
    string current_phrase;
    output["chunks"] = libchris::json::array();
    // for every word
    for (auto word : output["output"]) {
        string word_str = word["word"];
        string pos_string;
        if (word["pos"].is_string()) {
            pos_string = word["pos"];
        } else {
            pos_string = "";
        }
        
        // Append to the combined POS
        if(pos_string.size() > 0){
            combined_pos |= pos_bits.at(pos_string);
            current_pos_set.push_back(pos_bits.at(pos_string));
        }
        
        // if a chunk exists with our current pattern
        if(pos_string.size() > 0 && mapped_chunks.find(combined_pos) != mapped_chunks.end()){
            // Iterate the chunks that match the pattern we've found
            for(auto chunk : mapped_chunks.at(combined_pos)){
                // If they number of POS in the chunk match the number in our set
                if(chunk.parts.size() == current_pos_set.size()){
                    //check if they are the same
                    bool are_same = true;
                    for(int idx=0; idx < current_pos_set.size();idx++){
                        if(chunk.parts.at(idx) != current_pos_set.at(idx)){
                            are_same = false;
                            break;
                        }
                    }
                    //If they match
                    if(are_same){
                        //set our chunk type
                        current_chunk = chunk.chunk_type;
                        
                        break;
                    }
                }
            }
            current_phrase += " ";
            current_phrase += word_str;
        } else {
            // No chunk found, use what we had before appending
            //if we had a chunk already
            if(current_chunk > 0){
                //append it
                cout << "we found: " << current_phrase << "(" << current_pos_set.size() << ")" << endl;
                auto chunk_json = libchris::json::object();
                chunk_json["content"] = current_phrase;
                chunk_json["type"] = chunk_strings.at(current_chunk);
                if(pos_string.size() > 0){
                    current_pos_set.push_back(pos_bits.at(pos_string));
                }
                output["chunks"].push_back(chunk_json);
            }
            // reset for the next chunk
            combined_pos = 0;
            current_chunk = 0;
            current_pos_set.clear();
            current_phrase.clear();
        }
        
        ///
        ////
    }
    
    return output;
}
