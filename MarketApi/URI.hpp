#include <string>
#include <vector>
#include <algorithm>

#define OK_HTTP_STRING "HTTP/1.0 200 OK\r\n"

struct param
{
    std::string key;
    std::string value;
};

class URI
{
public:
    std::string root;
    std::vector<param> params;

    void Parse(std::string uri)
    {
        typedef std::string::iterator iterator_t;
        
        if (uri.length() == 0)
            return ;

        iterator_t uriEnd = uri.end();
        iterator_t queryStart = std::find(uri.begin(), uriEnd, L'?');
        queryStart++;
        
    }
};
