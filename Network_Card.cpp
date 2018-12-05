//
// Created by Titanlbr520 on 2018/11/25.
//

#include <iostream>
#include "windows.h"
#include "HeaderFile/Network_Card.h"

using namespace std;

bool NetWork_Card::Get_NetWork_Card() {//得到本地网卡列表并显示
    //获取网卡列表
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Error in pcap_findalldevs_ex: %s\n", errbuf);
        return false;
    }

    //显示列表的响应字段的内容
    Card_Number_All = 0;
    for (d = alldevs; d != nullptr; d = d->next) {
        Card_Number_All++;
        Card_Name[Card_Number_All] = d->name;

        if (d->description)
            Card_Description[Card_Number_All] = d->description;
        else
            Card_Description[Card_Number_All] = const_cast<char *>("(No description available)");
    }

    //检测是否成功生成
    if (!Card_Number_All) {
        cout << endl << "No interfaces found! Make sure WinPcap is installed." << endl;
        return false;
    }

    return true;
}

void NetWork_Card::Free_NetWork_Card() {//释放网卡所占内存资源
    //不再需要设备列表了，释放它
    pcap_freealldevs(alldevs);
}

void NetWork_Card::Output_NetWork_Card() {//输出网卡信息
    cout << "----------------------------------     WinPcap Special Edition     ----------------------------------"
         << endl;
    cout
            << "----------------------------------      Design By Titanlbr520      ----------------------------------"
            << endl;
    cout << endl
         << "System finds " << Card_Number_All << " network cards as follows :"
         << endl;
    for (int i = 1; i <= Card_Number_All; i++) {
        if (i == Number_Choose_Now) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                    BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
        } else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                    FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
        }
        cout << i << "." << Card_Name[i] << "----" << Card_Description[i] << endl;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    cout << endl
         << R"(Please choose one network card ! (Use "The number key" or "The direction key" to move and "Enter" to choose))"
         << endl;
}

void NetWork_Card::Change_Number(int Change) {//控制上下键改变网卡编号，选择网卡
    //方向键区的ASCII码：上 72，下 80，左 75，右 77
    if (Change == 72) {//上
        if (Number_Choose_Now > 1)
            Number_Choose_Now--;
    } else if (Change == 80) {//下
        if (Number_Choose_Now < Card_Number_All)
            Number_Choose_Now++;
    }
}

void NetWork_Card::Make_It_To_Number(int Change) {//将当前所选网卡的ASCII码转化为十进制数，作为当前所选网卡编号
    if (Change > '0' && Change <= Card_Number_All + '0')
        Number_Choose_Now = Change - '0';
}

void NetWork_Card::Is_Right() {//判断是否有异常情况发生
    if (Number_Choose_Now < 1 && Number_Choose_Now > Card_Number_All) {
        cout << "System May Get Something Wrong !" << endl;//正常是不会出现这种情况的
        Card_Log.Write_Time("System May Get Something Wrong And Exit !");
        system("pause");
        //出错，释放网卡列表
        Free_NetWork_Card();
        //程序非正常退出
        exit(-1);
    }
}

void NetWork_Card::Write_NetWork_Card_Log() {//写网卡的日志文件
    for (int i = 1; i <= Card_Number_All; i++) {
        Card_Log.Write_String(Card_Name[i]);
        Card_Log.Write_String(Card_Description[i]);
        Card_Log.Write_Empty_line();
    }
}

char *NetWork_Card::Get_Card_Name() {//得到当前所选网卡名字
    return Card_Name[Number_Choose_Now];
}

char *NetWork_Card::Get_Card_Description() {//得到当前所选网卡描述
    return Card_Description[Number_Choose_Now];
}

pcap_addr *NetWork_Card::Get_Card_Addresses() {//得到当前所选网卡IP地址
    return Card_Addresses[Number_Choose_Now];
}

pcap_t *NetWork_Card::Open_Adapter(char *Card_Selected) {//打开适配器，准备发送数据包
    if ((adhandle = pcap_open(Card_Selected, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1000, nullptr, errbuf)) == nullptr) {
        fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap!\n", Card_Selected);
        //日志
        Card_Log.Write_String("Unable to open the adapter. ");
        Card_Log.Write_String(Card_Selected);
        Card_Log.Write_String(" is not supported by WinPcap");
        Card_Log.Write_Empty_line();

        //错误，释放网卡所占内存资源
        pcap_freealldevs(alldevs);
    }
    return adhandle;
}
