#if !defined(ENDPOINT_HPP)
#define ENDPOINT_HPP

#include <string>
#include <InventoryCollector.hpp>
#include <Logger.hpp>
#include <Json.hpp>

struct EndPointArgs
{
    InventoryCollector &m_collector;
    JsonConverter &m_converter;
    // BaseLogger &m_logger;
};

class EndPoint
{
public:
    EndPoint(std::string uri, void (*f)(std::string&, EndPointArgs&, std::string&))
        : m_uri(uri),
        m_f(f)
    {};

    bool operator==(std::string &str) const
    {
        // return str == m_uri;
        return str.compare(0, m_uri.size(), m_uri.c_str()) == 0;
    };

    void operator()(std::string &content, EndPointArgs& args, std::string& response)
    {
        m_f(content, args, response);
    };

private:
    std::string m_uri;
    void (*m_f)(std::string&, EndPointArgs&, std::string&);

};

#endif