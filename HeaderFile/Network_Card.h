//
// Created by Titanlbr520 on 2018/11/25.
//

#ifndef TCP_IP_NET_WORK_CARD_H
#define TCP_IP_NET_WORK_CARD_H

#include <pcap.h>
#include "Log.h"

class NetWork_Card {
public:
    bool Get_NetWork_Card();//得到本地网卡列表并显示

    void Free_NetWork_Card();//释放网卡所占内存资源

    void Output_NetWork_Card();//输出网卡信息

    void Change_Number(int Change);//控制上下键改变网卡编号，选择网卡

    void Make_It_To_Number(int Change);//将当前所选网卡的ASCII码转化为十进制数，作为当前所选网卡编号

    void Is_Right();//判断是否有异常情况发生

    char *Get_Card_Name();//得到当前所选网卡名字

    char *Get_Card_Description();//得到当前所选网卡描述

    pcap_addr *Get_Card_Addresses();//得到当前所选网卡IP地址

    void Write_NetWork_Card_Log();//写网卡的日志文件

    pcap_t *Open_Adapter(char *);//打开适配器，准备发送数据包

private:
    int Number_Choose_Now = 1;//目前选择的网卡
    int Card_Number_All = 0;//网卡数量

    char *Card_Name[11] = {nullptr};//网卡名字
    char *Card_Description[11] = {nullptr};//网卡的描述
    struct pcap_addr *Card_Addresses[11] = {nullptr};//网卡地址
    char errbuf[PCAP_ERRBUF_SIZE] = "";//错误信息

    pcap_if_t *alldevs = nullptr;
    pcap_if_t *d = nullptr;
    pcap_t *adhandle = nullptr;

    Log Card_Log;
};


#endif //TCP_IP_NET_WORK_CARD_H
