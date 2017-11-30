//
//  channels.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/30/17.
//
//

#ifndef channels_h
#define channels_h

#include <stdio.h>
#include <unordered_map>
#include "http_base.h"
using namespace std;

// provides individual channel information (users, etc)
class channel_handler : public AuthenticatedHandler {
    void get() override;
};
class channel_users_handler : public AuthenticatedHandler {
    void get() override;
};
class channel_logs_handler : public AuthenticatedHandler {
    void get() override;
};
// lists channels
class channels_handler : public AuthenticatedHandler {
    void get() override;
};

#endif /* channels_h */
