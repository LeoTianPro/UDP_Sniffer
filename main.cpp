//
// Created by Titanlbr520 on 2018/11/25.
//
#include <iostream>
#include <conio.h>
#include <iomanip>                  //��ʽ����
#include <pcap.h>
#include "HeaderFile/Log.h"
#include "HeaderFile/Network_Card.h"
#include "HeaderFile/Get_Package.h"
#include "HeaderFile/header.h"

using namespace std;

void packet_handler(u_char *, const struct pcap_pkthdr *, const u_char *);

int main() {
    //�������
    int ch = 0;//�����ַ�
    char *Card_Selected = nullptr;//
    char *Description_Selected = nullptr;//
    struct pcap_addr *Card_Addresses_Selected = nullptr;//

    pcap_t *adhandle = nullptr;

    //������Ҫ�������
    Log New_Log;
    NetWork_Card New_NetWork_Card;
    Get_Package New_Get_Package;

    //���ô��ڴ�С
    system("mode con cols=110 lines=22");

    //����������ɫ������
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

    //д��־�ļ�
    New_Log.Make_Log_Access();
    New_Log.Write_Empty_line();
    New_Log.Write_Time("System begin to run;");

    //������
    if (New_NetWork_Card.Get_NetWork_Card()) {
        New_Log.Write_String("Network card get succeed;");
        New_Log.Write_Empty_line();
    } else {
        cout << "Network Card Get Failure !" << endl;
        New_Log.Write_Time("Network card get failure and exit;");
        system("pause");
        exit(-1);
    }

    //��־
    New_NetWork_Card.Write_NetWork_Card_Log();

    //�����ʾ
    New_NetWork_Card.Output_NetWork_Card();

    //ѭ��ѡ������
    while ((ch = getch()) != 13) {//Enter��ASCII��Ϊ13
        if (ch == 224)//���������ASCII��Ϊ224
            New_NetWork_Card.Change_Number(getch());
        if (ch < '9' && ch >= '0')
            New_NetWork_Card.Make_It_To_Number(ch);
        system("cls");
        New_NetWork_Card.Output_NetWork_Card();
    }

    //�����ѡ���Ƿ����
    New_NetWork_Card.Is_Right();

    //�����ѡ
    Card_Selected = New_NetWork_Card.Get_Card_Name();
    Description_Selected = New_NetWork_Card.Get_Card_Description();
    Card_Addresses_Selected = New_NetWork_Card.Get_Card_Addresses();
    cout << endl << "listening on " << Description_Selected << "..." << endl << endl;

    //��������
    adhandle = New_NetWork_Card.Open_Adapter(Card_Selected);

    //д��־�ļ�
    New_Log.Write_String("Open Adapter ");
    New_Log.Write_String(Description_Selected);
    New_Log.Write_Empty_line();

    //���������·�㣬ֻ������̫��
    New_Get_Package.Track_Datalink(adhandle);

    //��ýӿڵ�һ����ַ������
    New_Get_Package.Get_NetMask(Card_Addresses_Selected);

    //�����������Ĭ��ץIP��UDP���ݰ�
    New_Get_Package.Pcap_Compile(adhandle);

    //���ù�����
    New_Get_Package.Pcap_Setfilter(adhandle);

    //�ͷ��б�
    New_NetWork_Card.Free_NetWork_Card();

    //��ʼ��׽��Ĭ�ϲ�׽20����
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

    //��־
    New_Log.Write_Time("System safely exit;");

    return 0;
}

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    Log Ip_Log;
//�ص����������յ�ÿһ�����ݰ�ʱ�ᱻlibpcap������
    struct tm *ltime;
    char timestr[16];
    ip_header *ih;
    udp_header *uh;
    int ip_len;
    u_short sport, dport;
    time_t local_tv_sec;

    //��ʱ���ת���ɿ�ʶ��ĸ�ʽ
    local_tv_sec = header->ts.tv_sec;
    ltime = localtime(&local_tv_sec);
    strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

    //��ӡ���ݰ���ʱ����ͳ���
    printf("%s.%.6ld len:%-4d ", timestr, header->ts.tv_usec, header->len);
    char str[100];
    sprintf(str, "%s.%.6ld len:%-4d ", timestr, header->ts.tv_usec, header->len);
    Ip_Log.Write_String(str);
    //���IP���ݰ�ͷ����λ��
    ih = (ip_header *) (pkt_data + 14); //��̫��ͷ������

    //���UDP�ײ���λ��
    ip_len = (ih->ver_ihl & 0xf) * 4;
    uh = (udp_header *) ((u_char *) ih + ip_len);

    //�������ֽ�����ת���������ֽ�����
    sport = ntohs(uh->sport);
    dport = ntohs(uh->dport);

    //��ӡIP��ַ��UDP�˿�
    printf("ip: %3d.%3d.%3d.%3d port: %-5d -> ip: %3d.%3d.%3d.%3d port: %-5d\n",
           ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4, sport,
           ih->daddr.byte1, ih->daddr.byte2, ih->daddr.byte3, ih->daddr.byte4, dport);
    sprintf(str,
            "ip: %3d.%3d.%3d.%3d port: %-5d -> ip: %3d.%3d.%3d.%3d port: %-5d\n",
            ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4, sport,
            ih->daddr.byte1, ih->daddr.byte2, ih->daddr.byte3, ih->daddr.byte4, dport);
    Ip_Log.Write_String(str);
}
