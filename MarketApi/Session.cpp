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
    BaseLogger& logger,
    std::vector<EndPoint>& m_endPoints
)
{
    m_read();

    if (m_request_parse())
    {
        m_create_response(collector, convertor, logger, m_endPoints);
    }
    else
    {
        std::cout << "UI";
    }
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
    BaseLogger& logger,
    std::vector<EndPoint>& endPoints
)
{
    std::stringstream ss;
    std::string cont_text;

    // TODO
    // Заглушка статуса ответа, отсутсвие заголовков в ответе
    ss << "HTTP/1.0 200 OK\r\nContent-Length: ";
    ss << m_req.uri.size() << "\r\n\r\n";
    ss << m_req.uri;
    response = ss.str();

    EndPointArgs argsEndPoint = {collector, convertor, logger};
    if (m_req.method == "POST")
        cont_text = std::string(m_req.content.begin(), m_req.content.end());
    if (m_req.method == "GET")
        cont_text = m_req.uri;

    for (auto endPoint: endPoints)
    {
        if (endPoint == m_req.uri)
        {
            endPoint(
                cont_text,
                argsEndPoint,
                response
            );
        }
    }
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