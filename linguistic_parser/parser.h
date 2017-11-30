//
//  parser.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/15/17.
//
//

#ifndef parser_h
#define parser_h

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <chris/json.h>
#include <chris/json_serialize.h>
#include "word_stats.h"

using namespace std;

class Parser {
public:
    Parser(string input);
    vector<string> words;
    libchris::json serialize();
private:
};

#endif /* parser_h */
