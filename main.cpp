//
// Created by Titanlbr520 on 2018/11/25.
//
#include <iostream>
#include <conio.h>
#include <iomanip>                  //格式控制
#include <pcap.h>
#include "HeaderFile/Log.h"
#include "HeaderFile/Network_Card.h"
#include "HeaderFile/Get_Package.h"
#include "HeaderFile/header.h"

using namespace std;

void packet_handler(u_char *, const struct pcap_pkthdr *, const u_char *);

int main() {
    //定义变量
    int ch = 0;//按键字符
    char *Card_Selected = nullptr;//
    char *Description_Selected = nullptr;//
    struct pcap_addr *Card_Addresses_Selected = nullptr;//

    pcap_t *adhandle = nullptr;

    //定义需要的类变量
    Log New_Log;
    NetWork_Card New_NetWork_Card;
    Get_Package New_Get_Package;

    //设置窗口大小
    system("mode con cols=110 lines=22");

    //设置文字颜色及背景
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

    //写日志文件
    New_Log.Make_Log_Access();
    New_Log.Write_Empty_line();
    New_Log.Write_Time("System begin to run;");

    //读网卡
    if (New_NetWork_Card.Get_NetWork_Card()) {
        New_Log.Write_String("Network card get succeed;");
        New_Log.Write_Empty_line();
    } else {
        cout << "Network Card Get Failure !" << endl;
        New_Log.Write_Time("Network card get failure and exit;");
        system("pause");
        exit(-1);
    }

    //日志
    New_NetWork_Card.Write_NetWork_Card_Log();

    //输出显示
    New_NetWork_Card.Output_NetWork_Card();

    //循环选择网卡
    while ((ch = getch()) != 13) {//Enter的ASCII码为13
        if (ch == 224)//方向键区的ASCII码为224
            New_NetWork_Card.Change_Number(getch());
        if (ch < '9' && ch >= '0')
            New_NetWork_Card.Make_It_To_Number(ch);
        system("cls");
        New_NetWork_Card.Output_NetWork_Card();
    }

    //检查所选择是否合理
    New_NetWork_Card.Is_Right();

    //获得所选
    Card_Selected = New_NetWork_Card.Get_Card_Name();
    Description_Selected = New_NetWork_Card.Get_Card_Description();
    Card_Addresses_Selected = New_NetWork_Card.Get_Card_Addresses();
    cout << endl << "listening on " << Description_Selected << "..." << endl << endl;

    //打开适配器
    adhandle = New_NetWork_Card.Open_Adapter(Card_Selected);

    //写日志文件
    New_Log.Write_String("Open Adapter ");
    New_Log.Write_String(Description_Selected);
    New_Log.Write_Empty_line();

    //检查数据链路层，只考虑以太网
    New_Get_Package.Track_Datalink(adhandle);

    //获得接口第一个地址的掩码
    New_Get_Package.Get_NetMask(Card_Addresses_Selected);

    //编译过滤器，默认抓IP和UDP数据包
    New_Get_Package.Pcap_Compile(adhandle);

    //设置过滤器
    New_Get_Package.Pcap_Setfilter(adhandle);

    //释放列表
    New_NetWork_Card.Free_NetWork_Card();

    //开始捕捉，默认捕捉20个包
    New_Log.Write_String("Begin to Sniffer...");
    New_Log.Write_Empty_line();
    pcap_loop(adhandle, 20, packet_handler, nullptr);

    system("pause");

    //The end
    system("cls");
    cout
            << "------------------------------------------------------------------------------------------------------\n"
            << "------------------------------------------------------------------------------------------------------\n"
            << "------------------------------------------------------------------------------------------------------\n"
            << "---------------------------------- Thank You For Using The System ! ----------------------------------\n"
            << "------------------------------------------------------------------------------------------------------\n"
            << "-------------------------------------Copyright 2018 By Titanlbr520 -----------------------------------\n"
            << "------------------------------------------------------------------------------------------------------\n"
            << "------------------------------------------------------------------------------------------------------\n"
            << "------------------------------------------------------------------------------------------------------\n"
            << endl;
    system("pause");

    //日志
    New_Log.Write_Time("System safely exit;");

    return 0;
}

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    Log Ip_Log;
//回调函数，当收到每一个数据包时会被libpcap所调用
    struct tm *ltime;
    char timestr[16];
    ip_header *ih;
    udp_header *uh;
    int ip_len;
    u_short sport, dport;
    time_t local_tv_sec;

    //将时间戳转换成可识别的格式
    local_tv_sec = header->ts.tv_sec;
    ltime = localtime(&local_tv_sec);
    strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

    //打印数据包的时间戳和长度
    printf("%s.%.6ld len:%-4d ", timestr, header->ts.tv_usec, header->len);
    char str[100];
    sprintf(str, "%s.%.6ld len:%-4d ", timestr, header->ts.tv_usec, header->len);
    Ip_Log.Write_String(str);
    //获得IP数据包头部的位置
    ih = (ip_header *) (pkt_data + 14); //以太网头部长度

    //获得UDP首部的位置
    ip_len = (ih->ver_ihl & 0xf) * 4;
    uh = (udp_header *) ((u_char *) ih + ip_len);

    //将网络字节序列转换成主机字节序列
    sport = ntohs(uh->sport);
    dport = ntohs(uh->dport);

    //打印IP地址和UDP端口
    printf("ip: %3d.%3d.%3d.%3d port: %-5d -> ip: %3d.%3d.%3d.%3d port: %-5d\n",
           ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4, sport,
           ih->daddr.byte1, ih->daddr.byte2, ih->daddr.byte3, ih->daddr.byte4, dport);
    sprintf(str,
            "ip: %3d.%3d.%3d.%3d port: %-5d -> ip: %3d.%3d.%3d.%3d port: %-5d\n",
            ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4, sport,
            ih->daddr.byte1, ih->daddr.byte2, ih->daddr.byte3, ih->daddr.byte4, dport);
    Ip_Log.Write_String(str);
}
