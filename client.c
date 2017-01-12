#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "cJSON.h"
int main(int argc, char *agrv[])
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); /* 在你自己的程序中 */
	
	struct sockaddr_in dest_addr ;
	bzero(&(dest_addr), sizeof(dest_addr)); /* 将整个结构剩余*/
	dest_addr.sin_family = AF_INET ; /* 主机字节顺序 */
	dest_addr.sin_port = htons(61886); /* 网络字节顺序，短整型 */
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1") ;
	
	int res = connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
	printf("connect:%d", res);
	char recData[1024] = {0};

	int ret = recv(sockfd, recData, 255, 0); 
	printf("byte:%d",ret);

	cJSON *json = cJSON_Parse(recData);
	char *out = cJSON_Print(json);
	cJSON_Delete(json);
	printf("recv:\n%s\n", out);
	free(out);

	close(sockfd);
}
