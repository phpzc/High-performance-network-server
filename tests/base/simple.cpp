//
// Created by zhangcheng on 2019-04-23.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static bool stop = false;

static void handle_term(int sig )
{
    printf("get signal SIGTERM !\n");
    stop = true;
}


int main(int argc, char* argv[])
{
    //注册信号事件
    signal( SIGTERM, handle_term);

    if( argc <= 3)
    {
        printf( "usage: %s ip_address port_number backlog\n", ( argv[0] ) );
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi( argv[3]);//监听的队列长度设置   可以类比nginx中的listen设置的数量

    //创建socket fd
    int sock = socket( PF_INET, SOCK_STREAM, 0);

    assert(sock >= 0);

    //设置监听的地址
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr); //转换到网路字节序 并放入指定内存区域
    address.sin_port = htons( port);//转为网络字节序

    //绑定socket fd到这个地址上
    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert( ret != -1);

    //监听
    ret = listen(sock, backlog);//
    assert( ret != -1);


    while( !stop)
    {
        sleep(1);
    }

    close( sock);


    return 0;
}
