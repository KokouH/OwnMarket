#if !defined(SERVER_HPP)
#define SERVER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <memory>

#include <ServerSession.hpp>

namespace MarketServer
{

#define THREAD_COUNT 10
#define IP_ADDRESS "127.0.0.1"
#define USING_PORT 5555

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

auto const address = net::ip::make_address(IP_ADDRESS);

class ServerAPI : public std::enable_shared_from_this<ServerAPI>
{
public:
    ServerAPI();
    // ~ServerAPI();

private:
    net::io_context m_ioc {THREAD_COUNT};
    tcp::acceptor m_acceptor;
    tcp::endpoint m_endpoint{address, USING_PORT};

    void do_accept();
    void on_accept(beast::error_code, tcp::socket);

};

}

#endif