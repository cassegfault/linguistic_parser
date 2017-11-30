//
//  word_stats.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#ifndef word_stats_h
#define word_stats_h

#include <stdio.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "string_utils.h"

enum pos {
    pos_none        = 0b0000000000000000,
    pos_verb        = 0b0000000000000001,
    pos_noun        = 0b0000000000000010,
    pos_adjective   = 0b0000000000000100,
    pos_adverb      = 0b0000000000001000,
    pos_conjunction = 0b0000000000010000,
    pos_determiner  = 0b0000000000100000,
    pos_number      = 0b0000000001000000,
    pos_preposition = 0b0000000010000000,
    pos_pronoun     = 0b0000000100000000,
    pos_particle    = 0b0000001000000000,
    pos_interjection= 0b0000010000000000,
    pos_punctuation = 0b0000100000000000,
    pos_all         = 0b1111111111111111
};
enum chunk_types {
    chunk_verb        = 0b0000000000000001,
    chunk_noun        = 0b0000000000000010,
    chunk_adjective   = 0b0000000000000100,
    chunk_adverb      = 0b0000000000001000,
    chunk_particle    = 0b0000000000010000,
    chunk_interjection= 0b0000000000100000,
    chunk_preposition = 0b0000000001000000,
    chunk_conjunction = 0b0000000010000000
};

struct word_stats{
    short parts_of_speech;
    std::unordered_map<short,float> probabilities;
};
struct chunk_model {
    vector<short> parts;
    short chunk_type;
};


void load_global_word_stats();
const std::unordered_map<std::string,word_stats> & global_word_stats();
const std::unordered_map<std::string,float> & global_bigram_probabilities();
const std::unordered_map<std::string, vector<short> > & global_chunk_patterns();
const std::unordered_map<short, std::vector<chunk_model> > & global_mapped_chunks();

const std::unordered_map<short, std::string> pos_strings {
    { pos_none, "none" },
    { pos_punctuation, "." },
    { pos_verb, "verb" },
    { pos_noun, "noun" },
    { pos_adjective, "adj" },
    { pos_adverb, "adv" },
    { pos_conjunction, "conj" },
    { pos_determiner, "det" },
    { pos_number, "number" },
    { pos_preposition, "prep" },
    { pos_pronoun, "prn" },
    { pos_particle, "part" },
    { pos_interjection, "int" },
    { pos_all, "all" }
};
const std::unordered_map<std::string, short> pos_bits ({
    { "none", pos_none },
    { "verb", pos_verb },
    { "noun", pos_noun },
    { "adj", pos_adjective },
    { "adv", pos_adverb },
    { "conj", pos_conjunction },
    { "det", pos_determiner },
    { "number", pos_number },
    { "prep", pos_preposition },
    { "prn", pos_pronoun },
    { "part", pos_particle },
    { "int", pos_interjection },
    { ".", pos_punctuation },
    { "x", pos_none },
    { "all", pos_all }
});

const std::unordered_map<std::string, short> chunk_bits {
    { "PP", chunk_preposition },
    { "ADJP", chunk_adjective },
    { "INTJ", chunk_interjection },
    { "VP", chunk_verb },
    { "NP", chunk_noun },
    { "CONJP", chunk_conjunction },
    { "ADVP", chunk_adverb },
};

const std::unordered_map<short, std::string> chunk_strings {
    { chunk_preposition, "PP" },
    { chunk_adjective, "ADJP" },
    { chunk_interjection, "INTJ" },
    { chunk_verb, "VP" },
    { chunk_noun, "NP" },
    { chunk_conjunction, "CONJP" },
    { chunk_adverb, "ADVP" },
};

#endif /* word_stats_h */
