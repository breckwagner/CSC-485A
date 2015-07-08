#include<netinet/in.h>    
#include<stdio.h>    
#include<stdlib.h>    
#include<sys/socket.h>    
#include<sys/stat.h>    
#include<sys/types.h>    
#include<unistd.h>    
	 
int create_socket, new_socket;    
socklen_t addrlen;    
int bufsize = 1024;    
char *buffer;    
struct sockaddr_in address;    

void init_server()
{
	buffer = malloc(bufsize);       
	if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0)
	{    
		printf("The socket was created\n");
	}
	address.sin_family = AF_INET;    
	address.sin_addr.s_addr = INADDR_ANY;    
	address.sin_port = htons(15000);    
	if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0)
	{    
		printf("Binding Socket\n");
	}
}

void managed_element_control_cycle()
{
	//Server control cycle
		if (listen(create_socket, 10) < 0) {    
		perror("server: listen");    
		exit(1);    
		}    
	 
		if ((new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen)) < 0) {    
			perror("server: accept");    
			exit(1);    
		}    
	 
		if (new_socket > 0){    
			printf("The Client is connected...\n");
		}
		  
		recv(new_socket, buffer, bufsize, 0);    
		printf("%s\n", buffer);    
		write(new_socket, "HTTP/1.1 200 OK\n", 16);
		write(new_socket, "Content-length: 46\n", 19);
		write(new_socket, "Content-Type: text/html\n\n", 25);
		write(new_socket, "<html><body><H1>Hello world</H1></body></html>",46);   
		close(new_socket);
}

void am_monitor()
{
	
}

void am_plan()
{

}

void am_analyze()
{

}

void am_execute()
{

}

void autonomic_manager_control_cycle()
{
	am_monitor();
	am_analyze();
	am_plan();
	am_execute();
}

int main() {   
	init_server(); 
	while (1) 
	{    
		managed_element_control_cycle();
		autonomic_manager_control_cycle();
	}    
	close(create_socket);    
	return 0;    
}