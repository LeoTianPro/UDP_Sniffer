//
// Created by Titanlbr520 on 2018/11/25.
//

#ifndef TCP_IP_NET_WORK_CARD_H
#define TCP_IP_NET_WORK_CARD_H

#include <pcap.h>
#include "Log.h"

class NetWork_Card {
public:
    bool Get_NetWork_Card();//�õ����������б���ʾ

    void Free_NetWork_Card();//�ͷ�������ռ�ڴ���Դ

    void Output_NetWork_Card();//���������Ϣ

    void Change_Number(int Change);//�������¼��ı�������ţ�ѡ������

    void Make_It_To_Number(int Change);//����ǰ��ѡ������ASCII��ת��Ϊʮ����������Ϊ��ǰ��ѡ�������

    void Is_Right();//�ж��Ƿ����쳣�������

    char *Get_Card_Name();//�õ���ǰ��ѡ��������

    char *Get_Card_Description();//�õ���ǰ��ѡ��������

    pcap_addr *Get_Card_Addresses();//�õ���ǰ��ѡ����IP��ַ

    void Write_NetWork_Card_Log();//д��������־�ļ�

    pcap_t *Open_Adapter(char *);//����������׼���������ݰ�

private:
    int Number_Choose_Now = 1;//Ŀǰѡ�������
    int Card_Number_All = 0;//��������

    char *Card_Name[11] = {nullptr};//��������
    char *Card_Description[11] = {nullptr};//����������
    struct pcap_addr *Card_Addresses[11] = {nullptr};//������ַ
    char errbuf[PCAP_ERRBUF_SIZE] = "";//������Ϣ

    pcap_if_t *alldevs = nullptr;
    pcap_if_t *d = nullptr;
    pcap_t *adhandle = nullptr;

    Log Card_Log;
};


#endif //TCP_IP_NET_WORK_CARD_H
