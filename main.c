#include<stdio.h>
#include<stdlib.h>
#include <errno.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include"cJSON.h"

int main(int agrc, char *agrv[])
{
	struct sockaddr_in srv_addr;
	bzero(&srv_addr, sizeof(struct sockaddr_in));
 
	srv_addr.sin_family = AF_INET ; /* 主机字节顺序 */
	srv_addr.sin_port = htons(61886); /* 网络字节顺序，短整型 */
	srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1") ;

	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	int ret = bind(listen_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));		
	if (ret < 0)
	{
		printf("bind 127.0.0.1 61886 fail\n");
		return 0;
	}
	
	listen(listen_fd, 5);
	struct sockaddr addr;
	int len = sizeof(addr);
	bzero(&addr, len);
	int task = accept(listen_fd, &addr, &(len));	
	while(1){
		printf("task=%d\n", task);
		break;
	}
	

	cJSON * person = NULL, *event = NULL;
	
	person = cJSON_CreateObject();
	cJSON_AddItemToObject(person, "name", cJSON_CreateString("Lelouch"));
	cJSON_AddNumberToObject(person, "age", 17);
	
	event = cJSON_CreateObject();
	cJSON_AddItemToObject(person, "event", event);
	cJSON_AddStringToObject(event, "year", "2011");	
	cJSON_AddStringToObject(event, "item", "black rebellion");	
	cJSON_AddStringToObject(event, "palce", "area 11");

	char *out =  cJSON_Print(person);
	char data[1024] = {0};
	char *new = strcpy(data, out);
	printf("data:%s\n", data);
	int byte = send(task, data, strlen(data), 0); 
	perror("send:");
	printf("send byte:%d\n", byte);
	cJSON_Delete(person);
	printf("JSON:%s\n", out)	;	
	
	free(out);
	close(task);
}
