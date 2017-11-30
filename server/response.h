//
//  response.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#ifndef response_h
#define response_h

#include<string>
#include <unordered_map>

class Response {
public:
    int code;
    std::unordered_map<std::string,std::string> headers;
    std::string body;
    void error(int code, std::string error_message);
    Response();
    ~Response();
    std::string build_response_string();
    bool did_error;
    bool requires_auth;
    
};

#endif /* response_h */
