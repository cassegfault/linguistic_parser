//
//  response.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#include <unistd.h>
#include <unordered_map>
#include <cppconn/driver.h>

#include "response.h"

std::unordered_map<int, std::string> code_strings = {
    {200, "OKIE-DOKIE"},
    {404, "NOTHING HERE"},
    {500, "SHITS BROKE"},
    {405, "FUCK OFF"},
    {400, "FIX YO SHIT"}
};

Response::Response(){
    this->code = 200;
    this->headers["Connection"] = "close";
    this->headers["Content-Type"] = "application/json";
    this->headers["Access-Control-Allow-Origin"] = "http://chat.local";
    this->headers["Access-Control-Allow-Methods"] = "GET,POST,PUT,OPTIONS,DELETE";
    this->headers["Access-Control-Allow-Headers"] = "Authorization,Content-Type,Accept,Origin,User-Agent,DNT,Cache-Control,X-Mx-ReqToken,Keep-Alive,X-Requested-With,If-Modified-Since,Session-Key";
}
Response::~Response(){
}

std::string Response::build_response_string() {
    std::string resp = "HTTP/1.1 ";
    resp += std::to_string(this->code);
    resp += ' ';
    
    if (code_strings.find(this->code) != code_strings.end())
        resp += code_strings[this->code];
    else
        resp += "IDK";
    
    resp += "\r\n";
    for (auto h : this->headers) {
        resp += h.first;
        resp += ": ";
        resp += h.second;
        resp += "\r\n";
    }
    resp += "\r\n";
    
    resp += this->body;
    return resp;
}

void Response::error(int code, std::string error_message){
    this->code = code;
    this->body = "{\"status\":\"error\",\"message\":\"";
    this->body += error_message;
    this->body += "\"}";
    this->did_error = true;
}
