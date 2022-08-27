//
//  main.cpp
//  rdomainsocket
//
//  Created by 郑琳 on 2022/7/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE] = {0};
char path[] = "./namo_amitabha";
void handleError(char *msg) { //错误处理函数
    perror(msg);
    exit(-1);
}
int main(void) {
    int clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        handleError("创建socket失败");
    }
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path));

    if (connect(clientSocket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        handleError("连接服务端失败");
    }
    while(true) {
        fgets(buffer, BUFFER_SIZE, stdin);
        if(send(clientSocket, buffer, strlen(buffer), 0)==-1) {
            handleError("发送失败");
        }
        int numOfReaded = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if(numOfReaded==-1) {
            handleError("对端已经关闭");
        }
        buffer[numOfReaded]=0;
        printf("%s", buffer);
    }
}
