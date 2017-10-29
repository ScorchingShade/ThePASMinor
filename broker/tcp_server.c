#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

typedef enum {
    RESERVED = 0//forbidden
    CONNECT = 1,//client request to connect to server
    CONNACK = 2,//connection acknowledged, server to client
    PUBLISH = 3,
    PUBACK = 4,
    PUBREC = 5,
    PUBREL = 6,
    PUBCOMP = 7,
    SUBSCRIBE = 8,
    SUBACK = 9,
    UNSUBSCRIBE = 10,
    UNSUBACK = 11,
    PINGREQ = 12,
    PINGRESP = 13,
    DISCONNECT = 14 
} connect_msg_t;

int main(){
	char server_message[256]="ankush sharma created this server\nSending this message from broker socket";
        int server_socket;
        server_socket=socket(AF_INET,SOCK_STREAM,0);

        struct sockaddr_in server_address;
        server_address.sin_family=AF_INET;
        server_address.sin_port=htons(9002);
        server_address.sin_addr.s_addr=INADDR_ANY;

	bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
	
    while(1){
	listen(server_socket,5);
	
	int client_socket;
	
	client_socket=accept(server_socket,NULL,NULL);
	
	send(client_socket,server_message,sizeof(server_message),0);
    }cd br
	close(server_socket);
	return 0;
}
