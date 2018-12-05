//
// Created by Titanlbr520 on 2018/11/25.
//

#include <iostream>
#include <fstream>                  //文件读写
#include <sstream>                  //格式转换
#include <iomanip>                  //格式控制
#include <direct.h>                 //目录遍历
#include "HeaderFile/Log.h"

using namespace std;

void Log::Write_Time(const string &str) {
    Time_Get = time(nullptr);
    current_time = localtime(&Time_Get);
    stringstream ss;
    ss << R"(../Log/)" << current_time->tm_year + 1900 << '_' << setw(2) << setfill('0') << current_time->tm_mon + 1
       << '_' << setw(2) << setfill('0') << current_time->tm_mday << ".txt";

    ofstream Logfile(ss.str(), ofstream::app);

    Logfile << setw(2) << setfill('0') << current_time->tm_hour << ':' << setw(2) << setfill('0')
            << current_time->tm_min << ':' << setw(2) << setfill('0') << current_time->tm_sec << '\t';
    Logfile << str << endl;
    Logfile.close();
}

void Log::Write_Empty_line() {
    Time_Get = time(nullptr);
    current_time = localtime(&Time_Get);
    stringstream ss;
    ss << R"(../Log/)" << current_time->tm_year + 1900 << '_' << setw(2) << setfill('0') << current_time->tm_mon + 1
       << '_' << setw(2) << setfill('0') << current_time->tm_mday << ".txt";

    ofstream Logfile(ss.str(), ofstream::app);

    Logfile << endl;
    Logfile.close();
}

void Log::Write_String(const string &msg) {
    Time_Get = time(nullptr);
    current_time = localtime(&Time_Get);
    stringstream ss;
    ss << R"(../Log/)" << current_time->tm_year + 1900 << '_' << setw(2) << setfill('0') << current_time->tm_mon + 1
       << '_' << setw(2) << setfill('0') << current_time->tm_mday << ".txt";

    ofstream Logfile(ss.str(), ofstream::app);

    Logfile << msg;
    Logfile.close();
}

void Log::Make_Log_Access() {
    if (access("../Log/", 0) == -1) {
        int flag = mkdir("../Log/");
        if (flag == -1)
            cout << "Do Not Have A Folder Named \"Log\" And Can Not Make It !" << endl;
    }
}
