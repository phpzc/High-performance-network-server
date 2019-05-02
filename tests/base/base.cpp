//
// Created by zhangcheng on 2019-04-22.
//


#include <stdio.h>

#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "../common/tests_common.h"

void byteorder()
{
    //联合体 测试value数据布局
    union{
        short value;
        char union_bytes[ sizeof(short)];
    } test;
    test.value = 0x0102;
    printf("short 大小 %d \n",sizeof(short));

    if( (test.union_bytes[0] == 1) && (test.union_bytes[1] == 2))
    {
        printf("big 大端字节序\n");//主机字节序 大端字节序  网络传输一般用大端字节序
    }
    else if( (test.union_bytes[0] == 2) &&  (test.union_bytes[1] == 1))
    {
        printf("little 小端字节序\n");//主机字节序 小端字节序
    }else
    {
        printf("unkown\n");
    }

    //主机字节序与网络字节序转换
    unsigned long int hostlong = 1000;

    hostlong = htonl(hostlong);

    printf("net word sort -> %lu\n",hostlong);
}
//通用地址
sockaddr sa1;

//专用socket地址
//unitx本地域协议族
sockaddr_un s1;
//tcp ipv4 ipv6
sockaddr_in ipv4addr;
sockaddr_in ipv6addr;

//ip地址转换函数
void test_1(){
    in_addr_t a1 = inet_addr("127.0.0.1");//转为网络字节序整数
    printf("%d \n", a1);
    in_addr s;
    s.s_addr = a1;
    printf("%s \n", inet_ntoa(s));//将网络字节序整数 转化为 点分十进制IPV4地址

    int addr;
    int res = inet_pton(AF_INET,"127.0.0.1",(void*)&addr);//转换ipv4或ipv6地址到 网络字节序数值 转换结果存储于 指向的内存
    if(res == 1){
        //转换成功
        printf("转换成功 %d\n",addr);
    }else{
        printf("转换失败\n");
    }
}

int main()
{
    TESTS_PRINT("主机字节序与网络字节序")
    byteorder();

    test_1();

    hostent* host = gethostbyname("localhost");
    printf("%s \n",host->h_name);
    return 0;
}
