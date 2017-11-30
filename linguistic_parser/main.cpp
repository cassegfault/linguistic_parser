//
//  main.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/15/17.
//
//

#include <iostream>
#include <istream>
#include <string>
#include <thread>
#include <unordered_map>
#include <chris/json_serialize.h>
#include <chris/json.h>
#include "word_stats.h"
#include "parser.h"
#include "routes.h"
#include <fstream>
#include <cstdint>

using namespace std;

int main(int argc, const char * argv[]) {
    /*cout << "Loading global word stats" << endl;
    load_global_word_stats();
     cout << "Finished" << endl;
    auto gg = global_word_stats();
    auto bg = global_bigram_probabilities();
    cout << "Words loaded: " << gg.size() << endl;
    cout << "Bigrams loaded: " << bg.size() << endl;*/
    bool is_running = true;
    
    /*
    string word;
    while(is_running){
        cin >> word;
        if (word.find("quit") != string::npos){
            is_running = false;
        }
        cout << '\t' << word << '\t' << gg[word].probabilities.size() << endl;
    }
    
    return 0;
    */
     
    thread api_thread([&is_running](){
        const char *options[] = { "document_root", ".", "listening_ports", "9095", 0 };
        
        std::vector<std::string> cpp_options;
        for (int i=0; i<(sizeof(options)/sizeof(options[0])-1); i++) {
            cpp_options.push_back(options[i]);
        }
        CivetServer api_server(cpp_options);
        for(auto route : routes){
            api_server.addHandler(route.first, route.second());
        }/*
        for(auto route : websocket_routes){
            api_server.addWebSocketHandler(route.first, route.second());
        }*/
        while(is_running){
            this_thread::sleep_for(chrono::milliseconds(1));
        }
    });
    while(is_running){
        this_thread::sleep_for(chrono::milliseconds(1));
    }
    api_thread.join();
    return 0;
}
