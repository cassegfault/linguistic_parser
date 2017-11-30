//
//  sms.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/21/17.
//
//

#include "sms.h"
#include <chris/json.h>

void sms_handler::get(){
    cout <<"SMS handler"<<endl;
    this->db->setSchema("v3x");
    
    auto number = this->get_param("number","");
    string query_str = "SELECT sender, body, time_received FROM sms ";
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
        tempObject["from"] = dbres->getString("sender");
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
void sms_handler::post(){
    auto body = this->get_param("body","");
    auto from = this->get_param("from","");
    auto index = this->get_param("index","");
    auto timestamp = this->get_param("timestamp","0");
    bool isEmail = strcmp(this->get_param("isEmail","").c_str(), "true") == 0;
    
    auto query = this->db->prepareStatement("INSERT IGNORE INTO sms (sender, body, sim_index, time_received, isEmail) VALUES (?, ?, ?, FROM_UNIXTIME(?), ?)");
    
    cout <<(int64_t)stoll(timestamp) / 1000 << endl;
    
    query->setString(1, from);
    query->setString(2, body);
    query->setInt(3, stoi(index));
    query->setInt64(4, (int64_t)stoll(timestamp) / 1000);
    query->setBoolean(5, isEmail);
    
    query->executeQuery();
}
void sms_handler::put(){
    libchris::json d;
    /*
    try{
        auto s = this->req.req_info->;
        d.parse(s);
    } catch(exception e) {
        this->res.body = "Failed to parse input";
        this->res.code = 400;
        return;
    }*/
    
    
    
}
