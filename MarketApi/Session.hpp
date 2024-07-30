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
#include <unordered_map>

enum RequestType: int
{
    POST,
    GET
};

class Request
{
public:
    Request() = default;
    ~Request() = default;

private:
    std::string m_url;
    RequestType m_type;
    std::unordered_map<std::string, std::string> m_headers;
    std::string m_content;

};

class Session
{
public:
    Session(int);
    ~Session();
    void handle(InventoryCollector&, JsonConverter&);

private:
    int m_fd;
    std::string request;
    std::string response;
    Request m_req;

    bool m_bad_session;

    void m_read();
    // void m_parse();
    void m_create_response(InventoryCollector&, JsonConverter&);
    void m_send();
    bool m_request_parse();
};

#endif