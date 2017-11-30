//
//  http_base.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#include "http_base.h"
using namespace std;
std::mutex m;

BaseHandler::BaseHandler(){
    m.lock();
    sql::Driver *driver;
    driver = get_driver_instance();
    this->db = driver->connect("tcp://v3x.pw:3306", "v3x_external", "");
    this->db->setSchema("v3x");
    m.unlock();
}

BaseHandler::~BaseHandler(){
}

bool BaseHandler::requires_auth(){ return false; }
bool AuthenticatedHandler::requires_auth(){ return true; }

bool BaseHandler::has_param(std::string param){
    std::string out;
    out = this->get_param(param);
    if(out.size() > 0){
        return true;
    }
    return false;
}

bool BaseHandler::has_header(std::string header){
    std::string out;
    out = this->get_header(header);
    if(out.size() > 0){
        return true;
    }
    return false;
}

std::string BaseHandler::get_header(std::string param){
    std::string out;
    if(CivetServer::getHeader(this->conn, param) != NULL){
        out = CivetServer::getHeader(this->conn, param);
    }
    return out;
}

std::string BaseHandler::get_param(std::string param){
    std::string out;
    CivetServer::getParam(this->conn, param.c_str(), out);
    return out;
}
std::string BaseHandler::get_param(std::string param, std::string fallback){
    if(this->has_param(param)) {
        return this->get_param(param);
    } else {
        return fallback;
    }
}

bool BaseHandler::authenticate(){

    if(this->has_header("Session-Key") || this->has_param("session_key")){
        sql::PreparedStatement *stmt;
        sql::ResultSet *dbres;
        std::string session_key = "";
        if(this->has_param("session_key")){
            session_key = this->get_param("session_key");
        } else {
            session_key = this->get_header("Session-Key");
        }
        stmt = this->db->prepareStatement("SELECT `user_id` FROM `chat`.`sessions` WHERE `key`=?");
        stmt->setString(1,session_key);
        dbres = stmt->executeQuery();
        stmt->close();
        dbres->next();
        if(dbres->rowsCount() > 0){
            
            this->req.user_id = dbres->getInt("user_id");
            this->req.session_key = session_key;
            return true;
        }
        
    }
    return false;
}

bool BaseHandler::handleAll(int method, CivetServer *_server, struct mg_connection *_conn){
    server = _server;
    conn = _conn;
    
    bool needs_auth = requires_auth();
    if(needs_auth){
        bool is_auth = this->authenticate();
        if(is_auth != true){
            this->res.code = 404;
            this->res.body = "{ \"status\":\"error\", \"message\":\"Route not found\" }";
            mg_printf(this->conn, "%s", this->res.build_response_string().c_str());
            return true;
        }
    }
    
    switch(method){
        default:
        case 1:
            get();
            break;
        case 2:
            post();
            break;
        case 3:
            head();
            break;
        case 4:
            put();
            break;
        case 5:
            patch();
            break;
        case 6:
            del();
            break;
        case 7:
            options();
            break;
    }
    
    mg_printf(this->conn, "%s", this->res.build_response_string().c_str());
    return true;
}

bool BaseHandler::handleGet(CivetServer *_server, struct mg_connection *_conn) {
    return this->handleAll(1, _server, _conn);
}

bool BaseHandler::handlePost(CivetServer *_server, struct mg_connection *_conn) {
    return this->handleAll(2, _server, _conn);
}

bool BaseHandler::handleHead(CivetServer *_server, struct mg_connection *_conn) {
    return this->handleAll(3, _server, _conn);
}

bool BaseHandler::handlePut(CivetServer *_server, struct mg_connection *_conn) {
    return this->handleAll(4, _server, _conn);
}

bool BaseHandler::handlePatch(CivetServer *_server, struct mg_connection *_conn) {
    return this->handleAll(5, _server, _conn);
}

bool BaseHandler::handleDelete(CivetServer *_server, struct mg_connection *_conn) {
    return this->handleAll(6, _server, _conn);
}

bool BaseHandler::handleOptions(CivetServer *_server, struct mg_connection *_conn) {
    return this->handleAll(7, _server, _conn);
}

// Default routes
void BaseHandler::get(){
    this->res.code = 404;
    this->res.body = "{ \"status\":\"error\", message:\"Route not found\" }";
}

void BaseHandler::post(){
    this->res.code = 404;
    this->res.body = "{ \"status\":\"error\", message:\"Route not found\" }";
}

void BaseHandler::head(){
    this->res.code = 404;
    this->res.body = "{ \"status\":\"error\", message:\"Route not found\" }";
}

void BaseHandler::put(){
    this->res.code = 404;
    this->res.body = "{ \"status\":\"error\", message:\"Route not found\" }";
}

void BaseHandler::patch(){
    this->res.code = 404;
    this->res.body = "{ \"status\":\"error\", message:\"Route not found\" }";
}

void BaseHandler::del(){
    this->res.code = 404;
    this->res.body = "{ \"status\":\"error\", message:\"Route not found\" }";
}

void BaseHandler::options(){
    this->res.code = 204;
}
