//
//  request.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#include "request.h"
Request::Request(){
}
Request::Request(struct mg_connection *_conn): conn(_conn){
    
}
