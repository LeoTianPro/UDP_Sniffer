//
// Created by Titanlbr520 on 2018/11/25.
//

#ifndef TCP_IP_GET_PACKAGE_H
#define TCP_IP_GET_PACKAGE_H

#include <pcap.h>
#include "Network_Card.h"
#include "Log.h"

class Get_Package{
public:
    void Track_Datalink(pcap_t *);//检查数据链路层，只考虑以太网

    void Get_NetMask(struct pcap_addr *);//获得接口第一个地址的掩码

    void Pcap_Compile(pcap_t *); //编译过滤器，默认抓IP和UDP数据包

    void Pcap_Setfilter(pcap_t *);

private:
    u_int netmask = 0;
    struct bpf_program fcode = {0, nullptr};
    char packet_filter[200] = "ip and udp";//默认抓IP和UDP数据包

    NetWork_Card Delate_Card;
    Log Package_Log;
};


#endif //TCP_IP_GET_PACKAGE_H
