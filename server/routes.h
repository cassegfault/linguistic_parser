//
//  routes.h
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#ifndef routes_h
#define routes_h

#include "http_base.h"
#include "websocket_base.h"
#include "authenticate.h"
#include "channels.h"
#include "sms.h"
#include "email.h"
#include "location.h"
#include "notifications.h"
#include "bitcoin.h"

class index_handler : public BaseHandler {
    void get() override;
};
class broken_handler : public BaseHandler {
    void get() override;
};

void index_handler::get(){
    this->res.body = "index route\n";
    if(this->has_param("what")){
        this->res.body += this->get_param("what");
    }
}
void broken_handler::get(){
    this->res.body = "index route\n";
    if(this->has_param("what")){
        this->res.body += this->get_param("what");
    }
}

const static std::unordered_map<std::string, std::function<BaseHandler *(void)> > routes = {
    {"/",                   []() { return new index_handler; } },
    {"/signup",             []() { return new signup_handler;} },
    {"/login",              []() { return new login_handler;} },
    {"/logout",             []() { return new logout_handler;} },
    {"/user_info",          []() { return new user_info_handler;} },
    
    {"/channel",            []() { return new channel_handler; } },
    {"/channels",           []() { return new channels_handler; } },
    {"/channel/logs",       []() { return new channel_logs_handler; } },
    {"/channel/users",      []() { return new channel_users_handler; } },
    
    {"/bitcoin",                []() { return new bitcoin_handler; } },
    {"/sms",                []() { return new sms_handler; } },
    {"/notifications",      []() { return new notifications_handler; } },
    {"/emails",             []() { return new email_handler; } },
    {"/location",             []() { return new location_handler; } },
    
};
const static std::unordered_map<std::string, std::function<CivetWebSocketHandler *(void)> > websocket_routes = {
    {"/notifications",       []() { return new WebSocketHandler; } }
};
#endif /* routes_h */
