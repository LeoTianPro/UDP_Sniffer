//
// Created by Titanlbr520 on 2018/11/25.
//

#include <iostream>
#include <pcap.h>
#include "HeaderFile/Get_Package.h"

using namespace std;

void Get_Package::Track_Datalink(pcap_t *adhandle) {//检查数据链路层，只考虑以太网
    if (pcap_datalink(adhandle) != DLT_EN10MB) {
        fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
        //日志
        Package_Log.Write_Time("Error for not on Ethernet networks");
        //释放列表
        Delate_Card.Free_NetWork_Card();
        system("pause");
        exit(-1);
    }
}

void Get_Package::Get_NetMask(struct pcap_addr *addresses) {//获得接口第一个地址的掩码
    if (addresses != nullptr)
        netmask = ((struct sockaddr_in *) (addresses->netmask))->sin_addr.S_un.S_addr;
    else
        //如果接口没有地址，那么我们假设一个C类的掩码
        netmask = 0xffffff;
}

void Get_Package::Pcap_Compile(pcap_t *adhandle) {
    //编译过滤器，默认抓IP和UDP数据包
    if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0) {
        fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
        //日志
        Package_Log.Write_Time("Error for unable to compile the packet filter.");
        // 释放列表
        Delate_Card.Free_NetWork_Card();
        system("pause");
        exit(-1);
    }
}

void Get_Package::Pcap_Setfilter(pcap_t *adhandle) {
    if (pcap_setfilter(adhandle, &fcode) < 0) {
        fprintf(stderr, "\nError setting the filter.\n");
        //日志
        Package_Log.Write_Time("Error setting the filter.");
        // 释放列表
        Delate_Card.Free_NetWork_Card();
        system("pause");
        exit(-1);
    }
}
