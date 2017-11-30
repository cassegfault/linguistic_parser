//
//  string_utils.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/2/17.
//
//

#include "string_utils.h"

void to_lowercase(string &input){
    for(size_t idx = 0; idx < input.length(); idx++){
        input[idx] = (char)tolower(input[idx]);
    }
}
void to_uppercase(string &input){
    for(size_t idx = 0; idx < input.length(); idx++){
        input[idx] = (char)toupper(input[idx]);
    }
}
