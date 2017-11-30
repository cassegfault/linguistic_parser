//
//  bitcoin.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/24/17.
//
//

#ifndef bitcoin_hpp
#define bitcoin_hpp

#include <unordered_map>
#include <chris/json.h>
#include "http_base.h"
using namespace std;

// provides individual channel information (users, etc)
class bitcoin_handler : public BaseHandler {
    void get() override;
};

#endif /* bitcoin_hpp */
