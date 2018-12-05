//
// Created by Titanlbr520 on 2018/11/25.
//

#ifndef TCP_IP_LOG_H
#define TCP_IP_LOG_H

#include <ctime>
#include <string>

using namespace std;

class Log{
public:
    void Write_Time(const string &);

    void Write_Empty_line();

    void Write_String(const string &);

    void Make_Log_Access();

private:
    time_t Time_Get = time(nullptr);

    struct tm *current_time = localtime(&Time_Get);
};


#endif //TCP_IP_LOG_H
