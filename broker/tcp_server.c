#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>

#include<netinet/in.h>

#include "mqtt.h"

typedef enum {
    RESERVED = 0,//forbidden
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
} connect_broker;


struct mqtt_broker_handle
{
	int                 socket;
	struct sockaddr_in  socket_address;
	uint16_t            port;
	char                hostname[16];  // based on xxx.xxx.xxx.xxx format
	char                clientid[24];  // max 23 charaters long
	bool                connected;
    size_t              topic;
    uint16_t            pubMsgID;
    uint16_t            subMsgID;
};


int main(){
	
	mqtt_broker_handle_t *broker = (mqtt_broker_handle_t *)malloc(sizeof(mqtt_broker_handle_t)) ;

	char server_message[256]="ankush sharma created this server\nSending this message from broker socket";
       // int server_socket;
        broker->socket=socket(AF_INET,SOCK_STREAM,0);

        struct sockaddr_in server_address;
        server_address.sin_family=AF_INET;
        server_address.sin_port=htons(9002);
        server_address.sin_addr.s_addr=INADDR_ANY;

	bind(broker->socket,(struct sockaddr*)&server_address,sizeof(server_address));
	
    while(1){
	listen(broker->socket,5);
	
	int client_socket;
	
	client_socket=accept(broker->socket,NULL,NULL);
	
	send(client_socket,server_message,sizeof(server_message),0);
    }
	close(broker->socket);
	return 0;
}
