//
//  bitcoin.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 6/24/17.
//
//

#include "bitcoin.h"

void::bitcoin_handler::get(){
    auto query = this->db->prepareStatement("SELECT price,sell FROM bitcoin_prices ORDER BY `timestamp` DESC LIMIT 1 ");
    auto dbres = query->executeQuery();
    libchris::json d;
    
    while(dbres->next()){
        d["buy"] = dbres->getString("price");
        d["sell"] = dbres->getString("sell");
    }
    this->res.body = d.dump();
}
