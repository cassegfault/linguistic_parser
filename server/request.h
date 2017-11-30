//
//  request.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#ifndef request_h
#define request_h

#include <string>

class Request {
public:
    Request();
    Request(struct mg_connection *_conn);
    const struct mg_request_info *req_info;
    std::string session_key;
    int user_id;
private:
    struct mg_connection *conn;
    
};

#endif /* request_h */
