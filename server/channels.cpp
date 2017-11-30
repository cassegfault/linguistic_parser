//
//  channels.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/30/17.
//
//

#include "channels.h"
#include "chris/json_serialize.h"
#include "parser.h"

void channel_handler::get(){
    auto channel = this->get_param("channel","all");
    auto query = this->db->prepareStatement("SELECT id,name FROM channels JOIN logs ON logs.channel=channels.name WHERE channels.name=?");
    query->setString(1, channel);
}

void channel_logs_handler::get(){
    auto channel = this->get_param("channel","all");
    auto query = this->db->prepareStatement("SELECT users.username AS username, UNCOMPRESS(body) AS body, time FROM logs JOIN users ON logs.sender=users.id WHERE logs.channel=? LIMIT 100");
    query->setString(1, channel);
    auto dbres = query->executeQuery();
    
    libchris::json d;
    d["logs"] = libchris::json::array();
    while(dbres->next()){
        auto tempObject = libchris::json::object();
        tempObject["user"] = dbres->getString("username");
        tempObject["text"] = dbres->getString("body");
        tempObject["time"] = dbres->getString("time");
        Parser p(dbres->getString("body"));
        auto pd = p.serialize();
        tempObject["words"] = pd["output"];
        tempObject["subject"] = pd["subject"];
        tempObject["chunks"] = pd["chunks"];
        d["logs"].push_back(tempObject);
    }
    this->res.body = d.dump();
    query->close();
    dbres->close();
    delete query;
    delete dbres;
}

void channel_users_handler::get(){
    auto channel = this->get_param("channel","all");
    auto query = this->db->prepareStatement("SELECT users.id AS id, users.username AS username FROM channels_users JOIN users ON channels_users.user_id=users.id WHERE channels_users.channel=?");
    query->setString(1, channel);
    auto dbres = query->executeQuery();
    
    libchris::json d;
    d["users"] = libchris::json::array();
    cout << "Returning " << dbres->rowsCount() << " users\n";
    while(dbres->next()){
        auto tempObject = libchris::json::object();
        tempObject["username"] = dbres->getString("username");
        tempObject["id"] = dbres->getString("id");
        d["users"].push_back(tempObject);
    }
    this->res.body = d.dump();
    query->close();
    dbres->close();
    delete query;
    delete dbres;
    
}

void channels_handler::get(){
    auto query = this->db->prepareStatement("SELECT channels.name, COUNT(user_id) AS user_count FROM channels LEFT JOIN channels_users ON channels_users.channel=channels.name GROUP BY channels.name LIMIT 100");
    auto dbres = query->executeQuery();
    
    cout << "Returning " << dbres->rowsCount() << " channels\n";
    libchris::json d;
    d["channels"] = libchris::json::array();
    while(dbres->next()){
        auto tempObject = libchris::json::object();
        tempObject["channel"] = dbres->getString("name");
        tempObject["users"] = dbres->getString("user_count");
        d["channels"].push_back(tempObject);
    }
    
    this->res.body = d.dump();
    query->close();
    dbres->close();
    delete query;
    delete dbres;
}
