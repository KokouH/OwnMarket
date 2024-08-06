#if !defined(S_URI_HPP)
#define S_URI_HPP

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

#define OK_HTTP_STRING "HTTP/1.0 200 OK\r\n"

struct URIParam
{
    std::string key;
    std::string value;
};

class URI
{
using URI_IT = std::string::iterator;
public:
    std::map<std::string, std::string> params;

    void Parse(std::string& uri)
    {
        URIParam temp;
        URI_IT startParam, endParam, eqChar;
        URI_IT argsStart = std::find(uri.begin(), uri.end() + uri.size(), '?');
        
        if (argsStart == uri.end())
            return ;

        startParam = argsStart;
        endParam = std::find(argsStart, uri.end(), '&');
        while (startParam != uri.end())
        {
            eqChar = std::find(startParam, endParam, '=');
            if (eqChar != endParam)
            {
                if (eqChar + 1 != endParam)
                    params[std::string(startParam + 1, eqChar)] =
                        std::string(eqChar + 1, endParam);
            }
            startParam = endParam;
            endParam = std::find(startParam, uri.end(), '&');
        }
    }
};

#endif