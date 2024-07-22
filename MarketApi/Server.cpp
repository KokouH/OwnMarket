#include <Server.hpp>

Server::Server()
{
}

void Server::on_accept(pSession session)
{
    std::lock_guard _lock(m_mut_sessions);

    m_sessions.push(session);
}