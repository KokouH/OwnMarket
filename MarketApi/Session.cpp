#include <Session.hpp>

Session::Session(int serverSocket)
{
    m_fd = accept(serverSocket, nullptr, nullptr);
    m_bad_session = false;
    if (m_fd < 0)
        m_bad_session = true;
}

Session::~Session()
{
    if (!m_bad_session)
        close(m_fd);
}

void Session::handle(
    InventoryCollector& collector,
    JsonConverter& convertor,
    std::vector<EndPoint>& m_endPoints
)
{
    m_read();
    m_request_parse();
    m_create_response(collector, convertor, m_endPoints);
    m_send();
}

void Session::m_read()
{
    /*
    TODO
    Добавить ограничения для чтения
    Максимальное время
    Максимальный размер
    */
    size_t readed;
    char buffer[2048] = {0};

    std::memset(buffer, 0, 2048);
    recv(m_fd, buffer, sizeof(buffer), 0);
    request.append(buffer);
}

void Session::m_create_response(
    InventoryCollector& collector,
    JsonConverter& convertor,
    std::vector<EndPoint>& m_endPoints
)
{
    std::stringstream ss;
    pInventory inv = collector.getInventoryById(0);
    std::string temp = convertor.getJson(inv);

    // TODO
    // Заглушка статуса ответа, отсутсвие заголовков в ответе
    ss << "HTTP/1.0 200 OK\r\nContent-Length: ";
    ss << m_req.uri.size() << "\r\n\r\n";
    ss << m_req.uri;
    response = ss.str();

    // EndPointArgs argsEndPoint = {collector, convertor};

    // for (auto endPoint: m_endPoints)
    // {
    //     if (endPoint == m_req.uri)
    //     {
    //         std::string cont_text = std::string(m_req.content.begin(), m_req.content.end());
    //         endPoint(
    //             cont_text,
    //             argsEndPoint,
    //             response
    //         );
    //     }
    // }

}

void Session::m_send()
{
    send(m_fd, response.c_str(), response.size(), 0);
}

bool Session::m_request_parse()
{
    char* c_requests = (char *)request.c_str();

    httpparser::HttpRequestParser::ParseResult res = parser.parse(
        m_req,
        c_requests,
        c_requests + request.size()
    );

    if (res != httpparser::HttpRequestParser::ParsingCompleted)
        return false;
    return true;
}