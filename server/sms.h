//
//  sms.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/21/17.
//
//

#ifndef sms_hpp
#define sms_hpp

#include <stdio.h>
#include <unordered_map>
#include "http_base.h"
using namespace std;

// provides individual channel information (users, etc)
class sms_handler : public BaseHandler {
    void get() override;
    void post() override;
    void put() override;
};

#endif /* sms_hpp */
