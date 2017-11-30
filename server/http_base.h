//
//  http_base.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#ifndef http_base_h
#define http_base_h

#include <stdio.h>
#include <mutex>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include "CivetServer.h"
#include "request.h"
#include "response.h"

class BaseHandler : public CivetHandler {
public:
    BaseHandler();
    BaseHandler(std::string host, std::string user, std::string pass, std::string db);
    ~BaseHandler();
    Request req;
    Response res;
    sql::Connection *db;
    CivetServer *server;
    struct mg_connection *conn;
    bool handleAll(int method, CivetServer *server, struct mg_connection *conn);
    bool handleGet(CivetServer *server, struct mg_connection *conn);
    bool handlePost(CivetServer *server, struct mg_connection *conn);
    bool handleHead(CivetServer *server, struct mg_connection *conn);
    bool handlePut(CivetServer *server, struct mg_connection *conn);
    bool handlePatch(CivetServer *server, struct mg_connection *conn);
    bool handleDelete(CivetServer *server, struct mg_connection *conn);
    bool handleOptions(CivetServer *server, struct mg_connection *conn);
    
    virtual void get();
    virtual void post();
    virtual void head();
    virtual void put();
    virtual void patch();
    virtual void del();
    virtual void options();
    
    bool authenticate();
    virtual bool requires_auth();
    
    bool has_param(std::string param);
    std::string get_param(std::string param);
    std::string get_param(std::string param, std::string fallback);
    
    bool has_header(std::string param);
    std::string get_header(std::string param);
    
    std::string get_body();
private:
};

class AuthenticatedHandler : public BaseHandler {
public:
    bool requires_auth() override;
};

#endif /* http_base_h */
