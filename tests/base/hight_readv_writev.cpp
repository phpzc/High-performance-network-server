//
// Created by zhangcheng on 2019-05-02.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/uio.h>

#define BUFFER_SIZE 1024
static const char* status_line[2] = {"200 OK", "500 Internal server error" };

/**
 * writev 一次写出多个缓冲区的内容到socket中去 发送给客户端
 * @return
 */
int main(int argc, char* argv[])
{
    if( argc == 3){
        printf("usage: %s ip_address port_number filename\n", ( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    const char* file_name = argv[3];

    struct sockaddr_in address;
    bzero( &address, sizeof(address) );

    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr); //转为2进制 地址
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address) );
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);

    int connfd = accept( sock, (struct sockaddr*)&client, &client_addrlength);
    if(connfd < 0) {
        printf("errno is : %d\n", errno);
    }else{
        char header_buf[BUFFER_SIZE];
        memset(header_buf,'\0', BUFFER_SIZE);
        char* file_buf;
        struct stat file_stat;
        bool valid = true;
        int len = 0;
        if( stat(file_name, &file_stat) < 0){ //文件不存在
            valid = false;
        }else{
            if( S_ISDIR(file_stat.st_mode)){ //是目录 也为不存在
                valid = false;
            }else if(file_stat.st_mode & S_IROTH ) { //其他人可读
                int fd = open(file_name, O_RDONLY);
                file_buf = new char[file_stat.st_size + 1];
                memset(file_buf,'\0', file_stat.st_size + 1);
                if( read(fd, file_buf, file_stat.st_size) < 0){
                    valid = false;
                }

            }else{
                valid = false;
            }
        }


        if(valid){
            //格式化 并复制到指定内存处
            ret = snprintf( header_buf, BUFFER_SIZE -1,"%s %s\r\n", "HTTP/1.1", status_line[0]  );
            len += ret;

            ret = snprintf( header_buf + len, BUFFER_SIZE-1-len,  "Content-Length: %d\r\n", file_stat.st_size );
            len += ret;

            ret = snprintf( header_buf + len, BUFFER_SIZE-1- len, "%s", "\r\n"  );

            struct iovec iv[2];//缓冲区结构定义
            iv[0].iov_base = header_buf;
            iv[0].iov_len = strlen(header_buf);
            iv[1].iov_base = file_buf;
            iv[1].iov_len = file_stat.st_size;

            ret = writev( connfd, iv, 2);
        }else{
            //失败 写入的信息
            ret = snprintf( header_buf, BUFFER_SIZE - 1,"%s %s\r\n", "HTTP/1.1", status_line[1]);
            len += ret;
            ret = snprintf(header_buf + len, BUFFER_SIZE-1 -len, "%s", "\r\n"  );

            send(connfd, header_buf, strlen(header_buf), 0);
        }

        close( connfd );
        if(valid){
            delete [] file_buf;
        }

    }

    close(sock);


    return 0;
}
