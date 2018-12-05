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
    void Track_Datalink(pcap_t *);//���������·�㣬ֻ������̫��

    void Get_NetMask(struct pcap_addr *);//��ýӿڵ�һ����ַ������

    void Pcap_Compile(pcap_t *); //�����������Ĭ��ץIP��UDP���ݰ�

    void Pcap_Setfilter(pcap_t *);

private:
    u_int netmask = 0;
    struct bpf_program fcode = {0, nullptr};
    char packet_filter[200] = "ip and udp";//Ĭ��ץIP��UDP���ݰ�

    NetWork_Card Delate_Card;
    Log Package_Log;
};


#endif //TCP_IP_GET_PACKAGE_H
