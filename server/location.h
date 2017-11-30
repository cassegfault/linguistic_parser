//
//  location.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/23/17.
//
//

#ifndef location_hpp
#define location_hpp

#include <stdio.h>
#include <unordered_map>
#include <chris/json.h>
#include "http_base.h"
using namespace std;

// provides individual channel information (users, etc)
class location_handler : public BaseHandler {
    void get() override;
    void post() override;
};

#endif /* location_hpp */
