#include <Server.hpp>

namespace MarketServer
{

ServerAPI::ServerAPI()
    : m_acceptor( net::make_strand(m_ioc) )
{
    beast::error_code ec;

    // Open the acceptor
    m_acceptor.open(m_endpoint.protocol(), ec);

    // Allow address reuse
    m_acceptor.set_option(net::socket_base::reuse_address(true), ec);

    // Bind to the server address
    m_acceptor.bind(m_endpoint, ec);

    // Start listening for connections
    m_acceptor.listen(
        net::socket_base::max_listen_connections, ec
    );
}

void ServerAPI::do_accept()
{
    m_acceptor.async_accept(
        net::make_strand(m_ioc),
        beast::bind_front_handler(
            &ServerAPI::on_accept,
            shared_from_this()
        )
    );
}

void ServerAPI::on_accept(beast::error_code ec, tcp::socket socket)
{
    if(ec)
    {
        // TODO 
        // Создать логгер и записать ошибку
        return ;
    }
    else
    {
        // Create the session and run it
        std::make_shared<session>(
            std::move(socket)
        )->run();
    }

    // Accept another connection
    do_accept();
}

}
