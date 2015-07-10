typedef struct {
	// Knowledge "database" (in main memory)
	// Event types:
	// 	user_request
	// 		user_id
	// 		request_made
	// 		time
}user_request;
//Job structure
typedef struct {
	char *name;
	int id;
	long time_to_run;
	int priority;
}job;

//Event data types
typedef struct {
	//There are more kinds of possible situations than user requests, but those are the only ones
	//Our model takes into account and so for simplicity we'll assume that situations contain user requests. 
	user_request request;
}situation;

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