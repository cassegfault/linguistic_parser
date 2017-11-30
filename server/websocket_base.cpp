//
//  websocket_base.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#include "websocket_base.h"


bool WebSocketHandler::has_param(struct mg_connection * conn, std::string param){
    std::string out;
    out = this->get_param(conn, param);
    if(out.size() > 0){
        return true;
    }
    return false;
}

bool WebSocketHandler::has_header(struct mg_connection * conn, std::string header){
    std::string out;
    out = this->get_header(conn, header);
    if(out.size() > 0){
        return true;
    }
    return false;
}

std::string WebSocketHandler::get_header(struct mg_connection * conn, std::string param){
    std::string out;
    if(CivetServer::getHeader(conn, param) != NULL){
        out = CivetServer::getHeader(conn, param);
    }
    return out;
}

std::string WebSocketHandler::get_param(struct mg_connection * conn, std::string param){
    std::string out;
    CivetServer::getParam(conn, param.c_str(), out);
    return out;
}
std::string WebSocketHandler::get_param(struct mg_connection * conn, std::string param, std::string fallback){
    if(this->has_param(conn, param)) {
        return this->get_param(conn, param);
    } else {
        return fallback;
    }
}
