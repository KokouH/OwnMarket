#if !defined(SERVER_SESSION_HPP)
#define SERVER_SESSION_HPP

#include <Server.hpp>
#include <chrono>

namespace MarketServer
{

void handle_request();

class session : public std::enable_shared_from_this<session>
{
private:
    beast::tcp_stream m_stream;
    beast::flat_buffer m_buffer;
    http::request<http::string_body> m_req;
    http::response<http::string_body> m_res;

public:
    // Take ownership of the stream
    session(tcp::socket&&);

    // Start the asynchronous operation
    void run();
    void do_read();
    void on_read( beast::error_code, std::size_t );
    void send_response();
    void on_write( beast::error_code, std::size_t );
    void do_close();
};

}

#endif