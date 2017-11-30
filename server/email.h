//
//  email.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/22/17.
//
//

#ifndef email_hpp
#define email_hpp

#include <stdio.h>
#include <unordered_map>
#include <chris/json.h>
#include "http_base.h"
using namespace std;

// provides individual channel information (users, etc)
class email_handler : public BaseHandler {
    void get() override;
};


#endif /* email_hpp */
