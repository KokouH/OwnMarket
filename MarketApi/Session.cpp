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

void Session::handle(InventoryCollector& collector, JsonConverter& convertor)
{
    m_read();
    if (!m_request_parse())
        return ;
    m_create_response(collector, convertor);
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

void Session::m_create_response(InventoryCollector& collector, JsonConverter& convertor)
{
    std::stringstream ss;
    pInventory inv = collector.getInventoryById(0);
    std::string temp = convertor.getJson(inv);

    // TODO
    // Заглушка статуса ответа, отсутсвие заголовков в ответе
    ss << "HTTP/1.0 200 OK\r\nContent-Length: ";
    ss << temp.size() << "\r\n\r\n";
    ss << temp;

    response = ss.str();
}

void Session::m_send()
{
    send(m_fd, response.c_str(), response.size(), 0);
}

static inline void split(std::string str, std::string splitBy, std::vector<std::string>& tokens)
{
    size_t splitAt;
    size_t splitLen = splitBy.size();
    std::string frag;
    while(true)
    {
        frag = tokens.back();
        splitAt = frag.find(splitBy);
        if(splitAt == std::string::npos)
            break;
        tokens.back() = frag.substr(0, splitAt);
        tokens.push_back(frag.substr(splitAt+splitLen, frag.size()-(splitAt+splitLen)));
    }
}

bool Session::m_request_parse()
{
    std::vector<std::string> splt_req;

    split(request, "\r\n", splt_req);


    return true;
}