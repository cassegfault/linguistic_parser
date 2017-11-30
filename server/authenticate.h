//
//  authenticate.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/18/17.
//
//

#ifndef authenticate_h
#define authenticate_h

#include "http_base.h"
#include "crypto.h"
#include <chris/json.h>

class user_info_handler : public AuthenticatedHandler {
    void get() override;
};
class login_handler : public BaseHandler {
    void post() override;
};
class logout_handler : public AuthenticatedHandler {
    void get() override;
};
class signup_handler : public BaseHandler {
    void post() override;
};

#endif /* authenticate_h */
