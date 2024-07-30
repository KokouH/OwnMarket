#if !defined(SESSION_HPP)
#define SESSION_HPP

/*
Session

Можно сделать сокетом, но хочется что=то более высокое
start -> read -> create_answer -> write -> close
*/
#include <string>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <InventoryCollector.hpp>
#include <Json.hpp>
#include <EndPoint.hpp>
#include <httpparser/request.h>
#include <httpparser/httprequestparser.h>
#include <unordered_map>

class Session
{
public:
    Session(int);
    ~Session();
    
    void handle(
        InventoryCollector&,
        JsonConverter&,
        std::vector<EndPoint>&
    );

private:
    int m_fd;
    std::string request;
    std::string response;
    httpparser::HttpRequestParser parser;
    httpparser::Request m_req;

    bool m_bad_session;

    void m_read();
    // void m_parse();
    void m_create_response(
        InventoryCollector&,
        JsonConverter&,
        std::vector<EndPoint>&
    );
    void m_send();
    bool m_request_parse();
};

#endif