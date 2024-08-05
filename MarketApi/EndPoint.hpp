#if !defined(ENDPOINT_HPP)
#define ENDPOINT_HPP

#include <string>
#include <InventoryCollector.hpp>
#include <Logger.hpp>
#include <Json.hpp>

#include <iostream>

struct EndPointArgs
{
    InventoryCollector &m_collector;
    JsonConverter &m_converter;
    BaseLogger &m_logger;
};

class EndPoint
{
public:
    EndPoint(std::string uri, void (*f)(std::string&, EndPointArgs&, std::string&))
        : m_f(f)
    {
        m_uri = uri;
        m_size = m_uri.size();
    };

    inline bool operator==(std::string &str) const
    {
        return str.compare(0, m_size, m_uri) == 0;
    };

    void operator()(std::string &content, EndPointArgs& args, std::string& response)
    {
        m_f(content, args, response);
    };

private:
    std::string m_uri;
    size_t m_size;
    
    void (*m_f)(std::string&, EndPointArgs&, std::string&);

};

#endif