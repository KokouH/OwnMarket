#if !defined(ENDPOINT_HPP)
#define ENDPOINT_HPP

#include <string>

class EndPoint
{
public:
    EndPoint(std::string& uri, void (*f)(std::string&, std::string&))
        : m_uri(uri),
        m_f(f)
    {};

    bool operator==(std::string &str) const
    {
        return str == m_uri;
    };

    void operator()(std::string &content, std::string& response)
    {
        m_f(content, response);
    };

private:
    std::string m_uri;
    void (*m_f)(std::string&, std::string&);

};

#endif