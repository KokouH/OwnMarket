#if !defined(LOGGER_HPP)
#define LOGGER_HPP

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

enum MessageTypes : int
{
    ERROR,
    INFO
};

struct LogMessage
{
    MessageTypes type;
    std::string msg;
};

using tLogMessage = struct LogMessage;

class BaseLogger
{
protected:
    std::vector<tLogMessage> m_logs;

public:
    virtual void popAllMessages() = 0;
    virtual void popMessage() = 0;
    virtual void putMessage(tLogMessage) = 0;
};

class ConsoleLogger : public BaseLogger
{
public:
    ConsoleLogger() = default;

    void putMessage(tLogMessage);
    void popAllMessages();
    void popMessage();
};

#endif