//
//  notifications.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/22/17.
//
//

#include "notifications.h"
#include <chris/json.h>

void notifications_handler::get(){
    auto location_query = this->db->prepareStatement("SELECT name FROM known_locations, (SELECT latitude, longitude FROM location ORDER BY id DESC LIMIT 1) AS cur WHERE geodist(cur.latitude, cur.longitude,  known_locations.latitude, known_locations.longitude) < 0.2 LIMIT 1");
    auto locres = location_query->executeQuery();
    string location_name = "Unknown Location";
    if(locres->next()){
        location_name = locres->getString("name");
    }
    
    libchris::json doc;
    doc["notifications"] = libchris::json::array();
    auto notif = libchris::json::object();
    notif["type"] = "sticky";
    notif["body"] = location_name;
    doc["notifications"].push_back(notif);
    this->res.body = doc.dump();
}
