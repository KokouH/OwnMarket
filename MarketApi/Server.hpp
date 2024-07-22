#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <queue>
#include <Session.hpp>
#include <mutex>
#include <memory>

using pSession = std::shared_ptr<Session>;

class Server
{
public:
    Server();

    void start_session_handler();
    void start_acceptor();
    void on_accept(pSession session);

private:
    std::mutex m_mut_sessions;
    std::queue<pSession> m_sessions;

};

#endif