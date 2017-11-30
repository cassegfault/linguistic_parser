//
//  websocket_base.hpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/16/17.
//
//

#ifndef websocket_base_h
#define websocket_base_h

#include <stdio.h>
#include <string>
#include <cppconn/driver.h>
#include <chris/json_serialize.h>
#include "CivetServer.h"
#include "http_base.h"
#include "parser.h"

using namespace std;
using namespace libchris;

struct connectionInfo {
    string username;
    int user_id;
    string channel;
    int channel_id;
};

class WebSocketHandler : public CivetWebSocketHandler {
public:
    unordered_map<struct mg_connection *, struct connectionInfo> connection_users;
    unordered_map<string, vector<struct mg_connection *> > channel_connections;
    sql::Connection *db;
    
    WebSocketHandler(){
        sql::Driver *driver;
        driver = get_driver_instance();
        this->db = driver->connect("tcp://127.0.0.1:3306", "chat", "sup3rs3cur3");
        this->db->setSchema("chat");
    }
    
    virtual bool has_param(struct mg_connection * conn, std::string param);
    virtual std::string get_param(struct mg_connection * conn, std::string param);
    virtual std::string get_param(struct mg_connection * conn, std::string param, std::string fallback);
    
    virtual bool has_header(struct mg_connection * conn, std::string param);
    virtual std::string get_header(struct mg_connection * conn, std::string param);
    
    virtual bool handleConnection(CivetServer *server, struct mg_connection *conn) {
        
        return true;
    }
    
    virtual void handleReadyState(CivetServer *server, struct mg_connection *conn) {
        string key;
        server->getParam(conn, "session-token", key);
        bool did_authenticate = false;
        
        //Check the key, get username from that
        if(key.size() > 0){
            sql::PreparedStatement *stmt;
            sql::ResultSet *dbres;
            stmt = this->db->prepareStatement("SELECT user_id, username FROM sessions JOIN users ON users.id=sessions.user_id WHERE `key`=?");
            stmt->setString(1,key);
            dbres = stmt->executeQuery();
            stmt->close();
            dbres->next();
            if(dbres->rowsCount() > 0){
                connection_users[conn].username = dbres->getString("username");
                connection_users[conn].user_id = dbres->getInt("user_id");
                did_authenticate = true;
            } else {
                //Failed connection
                cout << "Authentication Failed DB" << endl;
                mg_websocket_write(conn, WEBSOCKET_OPCODE_CONNECTION_CLOSE, "", 0);
                
            }
        } else {
            // Failed Auth
            cout << "Authentication Failed" << endl;
            mg_websocket_write(conn, WEBSOCKET_OPCODE_CONNECTION_CLOSE, "", 0);
        }
        if(did_authenticate == false)
            return;
        string channel;
        channel = this->get_param(conn, "channel", "all");
        connection_users[conn].channel = channel;
        channel_connections[channel].push_back(conn);
        cout << connection_users[conn].username << " connected to " << connection_users[conn].channel << " with key: " << key << endl;
        
        auto channel_query = this->db->prepareStatement("INSERT IGNORE INTO chat.channels_users (channel, user_id) VALUES (?, ?)");
        channel_query->setString(1, channel);
        channel_query->setInt(2, connection_users[conn].user_id);
        channel_query->executeQuery();
        auto channel_insert = this->db->prepareStatement("INSERT IGNORE INTO chat.channels (name) VALUES (?)");
        channel_insert->setString(1, channel);
        channel_insert->executeQuery();
        
    }
    
    virtual bool handleData(CivetServer *server,
                            struct mg_connection *conn,
                            int bits,
                            char *data,
                            size_t data_len) {
        if(connection_users[conn].username.size() < 1) {
            cout << "Trying to write to closed connection" << endl;
            return false;
        }
        if(bits == 136){
            this->handleClose(server, conn);
            return false;
        }
        
        string data_str (data,data_len);
        Parser p(data_str);
        libchris::json output = p.serialize();
        output["raw"] = data_str;
        output["user"] = connection_users[conn].username;
        cout << connection_users[conn].username << ": " << connection_users[conn].channel << ": " << data_str << endl;
        string response = output.dump();
        for(auto c : channel_connections[connection_users[conn].channel]){
            mg_websocket_write(c, WEBSOCKET_OPCODE_TEXT, response.c_str(), response.size());
        }
        auto stmt = this->db->prepareStatement("INSERT INTO chat.logs (channel, sender, body, `time`) VALUES (?, ?, COMPRESS(?), CURRENT_TIMESTAMP)");
        stmt->setString(1,connection_users[conn].channel);
        stmt->setInt(2,connection_users[conn].user_id);
        stmt->setString(3,data_str);
        stmt->executeQuery();
        return true;
    }
    
    virtual void handleClose(CivetServer *server, struct mg_connection *conn) {
        auto channel_query = this->db->prepareStatement("DELETE FROM chat.channels_users WHERE user_id=? AND channel=?");
        channel_query->setInt(1, connection_users[conn].user_id);
        channel_query->setString(2, connection_users[conn].channel);
        channel_query->executeQuery();
        cout << connection_users[conn].username << " disconnected" << endl;
    }
};

#endif /* websocket_base_h */
