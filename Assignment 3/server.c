#include<netinet/in.h>    
#include<stdio.h>    
#include<stdlib.h>  
#include<string.h>  
#include<sys/socket.h>    
#include<sys/stat.h>    
#include<sys/types.h>    
#include<unistd.h>    
	 
int create_socket, new_socket;    
socklen_t addrlen;    
int bufsize = 1024;    
char *buffer;    
struct sockaddr_in address; 

// typedef enum {
// 	"request_job";
// 	"cancel_job";
// 	"return_status";
// 	"change_policy";
// }request_types;

//Request types
//	job request_job;
//	user_id ip;
//	

//Job types
//	char[] name;
//	uint64_t id;
//	

typedef struct {
	// Knowledge "database" (in main memory)
	// Event types:
	// 	user_request
	// 		user_id
	// 		request_made
	// 		time
}user_request;

//Event data types
typedef struct {
    char *sourceComponentId;
    char *situation;
}event;

//Symptom data types
typedef enum {
	created=0,
	building=1, 
	analyzed=2,
	planning=3, 
	executing=4, 
	scheduled=5, 
	completed=6, 
	expired=7, 
	fault=8
} lifecycle_type;

typedef struct {
    char *identification;
    float versioning;
    char *annotation;
    char *location;
    char *scope;
    char *lifecycle;
}symptom_metadata;

typedef struct {
	// definitions can vary so much that we'll only pre-define a key. This may be redundant.
    char *definition_key;
}symptom_definition;

typedef struct {
    char *description;
    char *example;
    char *solution;
    char *reference;
    char *type;
    double probability;
    int priority;
}symptom_schema;

typedef struct {
    symptom_metadata *symptom_metadata;
    symptom_schema *schema;
    symptom_definition *definition;
}symptom;

//Policy data types
typedef struct {
	//Whatever is in here, it has to be amenable to our policy type.
	//It may be action-, goal-, or utility function-based
	char *temp;
}policy;

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

event managed_element_control_cycle()
{
	event component_state;
	component_state = (event) {.sourceComponentId="server_0001",.situation="listening"};
	//Server control cycle
	if (listen(create_socket, 10) < 0) {    
	perror("server: listen");
	return component_state;    
	//exit(1);    
	}    
 
	if ((new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen)) < 0) {    
		perror("server: accept");  
		return component_state;  
		//exit(1);    
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
	component_state= (event){.sourceComponentId="server_0001",.situation="website successfully sent"};

	return component_state;
}

event retrieve_state()
{
	event component_state = managed_element_control_cycle();
	return component_state;
}

//Store each event in an event log

//Knowledge manager: 
//	-event log
//	-symptom catalogue
//	-policies
//	-scripts

void write_event_to_event_log_buffer()
{
	//turn event struct into XML text, add text to array
}

void flush_event_log_buffer()
{
	//Print all events in log buffer to log file; clear log buffer
}

void symptom_engine()
{
	// Check event log and/or recent event for symptom
}

void am_monitor(event element_state)
{
	//Search for symptoms from symptom database using respective symptom engines
}


void am_analyze()
{

}

void am_plan()
{

}

void am_execute()
{

}

policy get_policy()
{
	policy input;
	input = (policy){"nothing"};
	return input;
}

void am_update_policy()
{
	policy temp_policy;
	temp_policy = get_policy();
	if (strncmp(temp_policy.temp,"nothing",7))
	{
		//Add policy to policy database 
	}
}

void autonomic_manager_control_cycle(event element_state)
{
	am_update_policy();
	//Control loop
	am_monitor(element_state);
	am_analyze();
	am_plan();
	am_execute();
}

int main() {   
	init_server(); 
	while (1) 
	{    
		event element_state = retrieve_state();
		autonomic_manager_control_cycle(element_state);
	}    
	close(create_socket);    
	return 0;    
}