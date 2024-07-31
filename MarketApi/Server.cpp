#include <Server.hpp>

Server::Server(BaseLogger &l, InventoryCollector& coll)
    : m_logger(l),
    m_collector(coll)
{
    const int opt = 1;

    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(m_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(m_serverSocket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(
        m_serverSocket,
        (struct sockaddr*)&serverAddress,
        sizeof(serverAddress)
    );
    if (listen(m_serverSocket, 10000) < 0 && m_logger_inited)
    {
        m_logger.putMessage(
            tLogMessage{
                MessageTypes::ERROR,
                "can't start listen"
            }
        );
    }

    m_acceptor_working = false;
    m_session_handle = false;
}

Server::~Server()
{
    close(m_serverSocket); 
}

void Server::start_acceptor()
{
    m_acceptor_working = true;
    std::thread accept_thread(&Server::m_acceptor, this);
    std::swap(accept_thread, m_threads[0]);
    m_logger.putMessage(
        LogMessage{
            MessageTypes::INFO,
            "Acceptor started."
        }
    );
}

void Server::start_session_handler()
{
    m_session_handle = true;
    for (int i = 0; i < THREAD_HANDLE_COUNT; i++)
    {
        m_threads[i + 1] = std::thread(&Server::m_session_handler, this);
    }
    m_logger.putMessage(
        LogMessage{
            MessageTypes::INFO,
            "Session handler started."
        }
    );
}

void Server::m_on_accept(pSession session)
{
    std::lock_guard _lock(m_mut_sessions);

    m_sessions.push(session);
}

void Server::m_acceptor()
{
    pSession cur_session;
    
    while (m_acceptor_working)
    {
        cur_session = std::make_shared<Session>(m_serverSocket);
        {
            std::lock_guard _lock(m_mut_sessions);
            m_sessions.push( std::move(cur_session) );
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}

void Server::m_session_handler()
{
    pSession cur_session;

    while (m_session_handle)
    {
        if (m_sessions.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        while (!m_sessions.empty())
        {
            {
            std::lock_guard _lock(m_mut_sessions);
            if (m_sessions.empty())
                break;
            cur_session = std::move(m_sessions.front());
            m_sessions.pop();
            }
            if (cur_session.get() == nullptr)
                break;
            cur_session->handle(m_collector, m_converter, m_endPoints);
            cur_session.reset();

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }   
}

void Server::add_end_point(std::string uri, void (*f)(std::string&, EndPointArgs&, std::string&))
{
    EndPoint endPoint(uri, f);

    m_endPoints.push_back(endPoint);
}

void Server::join()
{
    m_threads[0].join();
    for (int i = 0; i < THREAD_HANDLE_COUNT; i++)
    {
        m_threads[i + 1].join();
    }
}