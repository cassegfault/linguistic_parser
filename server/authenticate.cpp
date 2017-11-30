//
//  authenticate.cpp
//  linguistic_parser
//
//  Created by Chris Pauley on 5/18/17.
//
//

#include "authenticate.h"

using namespace std;



void user_info_handler::get() {
    sql::PreparedStatement *stmt;
    sql::ResultSet *dbres;
    
    
    stmt = this->db->prepareStatement("SELECT username, is_active FROM users WHERE `id` = ?");
    cout << "Requesting ID:" << req.user_id << endl;
    stmt->setInt(1, req.user_id);
    dbres = stmt->executeQuery();
    
    if(dbres->rowsCount() > 0){
        res.code = 200;
        dbres->next();
        this->res.body = json_string(unordered_map<string, string>({
            { "id", std::to_string(req.user_id) },
            { "session_key", req.session_key },
            { "username", dbres->getString("username") },
            { "is_active", dbres->getString("is_active") }
        }));
    } else {
        res.error(400, "Not Authorized");
    }
}

void login_handler::post() {
    if(!this->has_param("username") || !this->has_param("password")){
        this->res.error(400,"Username and password must be present to log in");
        return;
    }
    
    sql::PreparedStatement *stmt;
    sql::ResultSet *dbres;
    
    stmt = this->db->prepareStatement("SELECT id,password FROM users WHERE  username = ?");
    stmt->setString(1,this->get_param("username"));
    dbres = stmt->executeQuery();
    dbres->next();
    
    string session_key = generate_session_key();
    
    if(check_hash_against_pass(dbres->getString("password"), this->get_param("password"))) {
        stmt = this->db->prepareStatement("INSERT INTO sessions (user_id,`key`) VALUES (?, ?)");
        stmt->setInt(1,dbres->getInt("id"));
        stmt->setString(2,session_key);
        stmt->executeQuery();
        
        this->res.headers["Session-Key"] = session_key;
        //this->res.body = "{ \"session_key\":\"" + session_key + "\" }";
        this->res.code = 200;
        this->res.headers["Content-Type"] = "applicaion/json";
        this->res.body = json_string(unordered_map<string, string>({
            { "id", to_string(dbres->getInt("id")) },
            { "session_key", session_key }
        }));
    } else {
        this->res.error(405,"Not Authorized");
    }
    
}

void logout_handler::get() {
    auto stmt = db->prepareStatement("DELETE FROM sessions WHERE user_id=? AND `key`=?");
    stmt->setInt(1,req.user_id);
    stmt->setString(2,req.session_key);
    stmt->executeQuery();
    
    res.code = 200;
    res.body ="{\"message\":\"success\"}";
}

void signup_handler::post() {
    if(!this->has_param("username") || !this->has_param("password")){
        this->res.error(400,"Username and password must be present to sign up");
        return;
    }
    sql::PreparedStatement *stmt;
    std::string username = this->get_param("username");
    stmt = this->db->prepareStatement("INSERT INTO users (username,password) VALUES (?, ?)");
    stmt->setString(1,username);
    stmt->setString(2,sha512(this->get_param("password")));
    stmt->executeQuery();
    
    cout << "returning\n" << endl;
    
    this->res.body = "{ \"next\":\"login\" }";
}
