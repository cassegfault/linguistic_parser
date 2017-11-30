//
//  location.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/23/17.
//
//

#include "location.h"


void location_handler::post(){
    
    string latitude = this->get_param("latitude","");
    string longitude  = this->get_param("longitude","");
    string accuracy = this->get_param("accuracy","");
    string altitude = this->get_param("altitude","");
    string bearing = this->get_param("bearing","");
    string speed = this->get_param("speed","");
    string time = this->get_param("time","");
    
    auto query = this->db->prepareStatement("INSERT IGNORE INTO location (latitude, longitude, accuracy, altitude, bearing, speed, `timestamp`) VALUES (?, ?, ?, ?, ?, ?, FROM_UNIXTIME(?))");
    
    query->setString(1, latitude);
    query->setString(2, longitude);
    query->setString(3, accuracy);
    query->setString(4, altitude);
    query->setString(5, bearing);
    query->setString(6, speed);
    query->setInt64 (7, (int64_t)stoll(time) / 1000);
    
    auto dbres = query->executeQuery();

    query->close();
    dbres->close();
    delete query;
    delete dbres;
    
}

void::location_handler::get(){
    auto query = this->db->prepareStatement("SELECT latitude, longitude, accuracy, altitude, bearing, speed, `timestamp` FROM location ");
    auto dbres = query->executeQuery();
    libchris::json d;
    d["entries"] = libchris::json::array();
    
    while(dbres->next()){
        auto tempObject = libchris::json::object();
        tempObject["latitude"] = dbres->getString("latitude");
        tempObject["longitude"] = dbres->getString("longitude");
        tempObject["accuracy"] = dbres->getString("accuracy");
        tempObject["altitude"] = dbres->getString("altitude");
        tempObject["bearing"] = dbres->getString("bearing");
        tempObject["speed"] = dbres->getString("speed");
        tempObject["timestamp"] = dbres->getString("timestamp");
        d["entries"].push_back(tempObject);
    }
    this->res.body = d.dump();
}
