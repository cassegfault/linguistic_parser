//
//  notifications.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/22/17.
//
//

#ifndef notifications_hpp
#define notifications_hpp

#include <stdio.h>
#include "http_base.h"
using namespace std;

// provides individual channel information (users, etc)
class notifications_handler : public BaseHandler {
    void get() override;
};

#endif /* notifications_hpp */
