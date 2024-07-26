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
    if (m_logs.size() == 0)
        return ;

    std::lock_guard lock(m_mut);
    std::for_each(m_logs.begin(), m_logs.end(), [](tLogMessage log){
        print_msg(log);
    });

    m_logs.clear();
}

void ConsoleLogger::popMessage()
{
    if (m_logs.size() == 0)
        return ;

    std::lock_guard lock(m_mut);
    tLogMessage log = m_logs.front();
    
    print_msg(log);
    m_logs.erase(m_logs.begin());
}

void ConsoleLogger::putMessage(tLogMessage new_log)
{
    std::lock_guard lock(m_mut);
    m_logs.push_back(new_log);
}