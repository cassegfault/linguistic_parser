//
//  email.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/22/17.
//
//

#include "email.h"


void email_handler::get(){
    
    auto number = this->get_param("number","");
    string query_str = "SELECT sender, body, time_received FROM email ";
    if(number.size() > 0){
        query_str += "WHERE from = ?";
    }
    auto query = this->db->prepareStatement(query_str);
    if(number.size() > 0){
        query->setString(1, number);
    }
    auto dbres = query->executeQuery();
    
    libchris::json d;
    d["messages"] = libchris::json::array();
    
    while(dbres->next()){
        auto tempObject = libchris::json::object();
        tempObject["from"] = dbres->getString("from");
        tempObject["to"] = dbres->getString("to");
        tempObject["body"] = dbres->getString("body");
        tempObject["time_received"] = dbres->getString("time_received");
        d["messages"].push_back(tempObject);
    }
    this->res.body = d.dump();
    query->close();
    dbres->close();
    delete query;
    delete dbres;
    
}
