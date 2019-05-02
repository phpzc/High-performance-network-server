//
// Created by zhangcheng on 2019-04-23.
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

//管道
//pipe 创建单向管道
//socketpair 创建双向管道


//系统 fd
// 0	STDIN	标准输入
// 1	STDOUT	标准输出
// 2	STDERR	标准错误输出

//dup dup2
//dup dup总是返回系统中最小的可用文件描述符
// 那么比如我们先关闭 标准输出 在使用dup复制socketfd
// 那么此时 标准输出fd就指向了当前复制的socketfd上
// 往标准输出写入信息 就发送给当前socketfd上了

//dup2
//int dup2(int oldfd, int newfd);
//dup2与dup区别是dup2可以用参数newfd指定新文件描述符的数值。
// 若参数newfd已经被程序使用，则系统就会将newfd所指的文件关闭，
// 若newfd等于oldfd，则返回newfd,而不关闭newfd所指的文件。

//readv
//writev 发送多块分散的数据 一起发送

//sendfile 在两个文件描述符之间拷贝数据
//int sendfile(int out_fd,int in_fd,off_t *offset,size_t count)
//out_fd必须是socket
//in_fd 必须是真实文件描述符

//mmap  -- 如何实现进程间 共享内存
//   权限
//   状态标志
//munmap

//splice
//两个文件描述符之间 移动数据 零拷贝

//tee
//两个管道 之间 移动数据

//fcntl 控制文件描述符的属性

int main()
{

    return 0;
}