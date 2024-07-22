#include <Logger.hpp>

static void print_msg(tLogMessage log_msg)
{
    if (log_msg.type == MessageTypes::ERROR)
        std::cout << "Error :";
    if (log_msg.type == MessageTypes::INFO)
        std::cout << "Info :";

    std::cout << log_msg.msg << '\n';
}

void ConsoleLogger::popAllMessages()
{
    std::for_each(m_logs.begin(), m_logs.end(), [](tLogMessage log){
        print_msg(log);
    });
}

void ConsoleLogger::popMessage()
{
    tLogMessage log = m_logs.back();
    
    m_logs.pop_back();
    print_msg(log);
}

void ConsoleLogger::putMessage(tLogMessage new_log)
{
    m_logs.push_back(new_log);
}