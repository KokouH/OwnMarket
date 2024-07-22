#if !defined(SESSION_HPP)
#define SESSION_HPP

/*
Session

Можно сделать сокетом, но хочется что=то более высокое
start -> read -> create_answer -> write -> close
*/

class Session
{
public:
    void handle();

private:
    void _read();
};

#endif