#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <Session.hpp>
#include <Logger.hpp>
#include <InventoryCollector.hpp>
#include <EndPoint.hpp>
#include <Json.hpp>
#include <chrono>
#include <queue>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream> 
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 8484
#define THREAD_HANDLE_COUNT 10

// Server -> Session -> Endpoint

using pSession = std::shared_ptr<Session>;

class Server
{
public:
    // Server();
    Server(BaseLogger&, InventoryCollector&);
    ~Server();

    void join();
    void start_session_handler();
    void start_acceptor();
    void add_end_point(std::string uri, void (*f)(std::string&, EndPointArgs&, std::string&));
    // bool joinable();

private:
    bool m_acceptor_working;
    bool m_session_handle;
    int m_serverSocket;
    bool m_logger_inited;
    BaseLogger &m_logger;
    InventoryCollector &m_collector;
    JsonConverter m_converter;
    std::vector<EndPoint> m_endPoints;
    std::thread m_threads[1 + THREAD_HANDLE_COUNT];
    std::mutex m_mut_sessions;
    std::queue<pSession> m_sessions;

    void m_acceptor();
    void m_session_handler();
    void m_on_accept(pSession session);

};

#endif