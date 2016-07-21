#ifndef OLDLIB_H
#define OLDLIB_H

#include "stddef.h"
#include "stdbool.h"

/* oldlib common functions */

enum errorlevels{
	OLDLIB_STRICT,
	OLDLIB_LOUD,
	OLDLIB_QUIET,
};

//Set the strictness of the warnings and errors
extern void oldlib_error_level(int level);

//Print out where these happen
extern void oldlib_warning_msg(const char* file, const char* function, int line, char* message);
extern void oldlib_error_msg(const char* file, const char* function, int line, char* message);
#define OLDLIB_WARN(msg) oldlib_warning_msg(__FILE__, __func__, __LINE__, msg)
#define OLDLIB_ERR(msg) oldlib_error_msg(__FILE__, __func__, __LINE__, msg)
#define OLDLIB_ASSERT(xpr) if(!(xpr))oldlib_warning_msg(__FILE__, __func__, __LINE__, "Assertion failed: '" #xpr "'");


/* Linked Lists */

typedef struct linkedlist_node{
	void* value;
	struct linkedlist_node* next;
} linkedlist_node_t;

typedef struct linkedlist{
	size_t length;
	linkedlist_node_t* value;
} linkedlist_t;

//Constructor and destructor
extern linkedlist_t* mk_linkedlist();
extern void rm_linkedlist(linkedlist_t* list);

//Length
extern size_t linkedlist_length(linkedlist_t* list);

//Getters and setters
extern void* linkedlist_get(linkedlist_t* list, size_t index);
extern void linkedlist_set(linkedlist_t* list, size_t index, void* value);

//Other operations
extern void linkedlist_insert(linkedlist_t* list, size_t index, void* value);
extern void linkedlist_delete(linkedlist_t* list, size_t index);
extern void* linkedlist_pop(linkedlist_t* list);
extern void linkedlist_push(linkedlist_t* list, void* value);


/* Hashmaps */

//Function for hashing a string into an index
typedef size_t (*hashfunction_t) (char*, size_t);

//Format of data stored in hashmap
typedef struct hashmap_value{
	char* key;
	void* value;
} hashmap_value_t;

//The meta-container for the data-- used to determine bucketing
typedef struct hashmap_container{
	hashmap_value_t value;
	bool bucketed;
	linkedlist_t* bucket;
} hashmap_container_t;

//Outer container-- this is the user-facing structure
typedef struct hashmap{
	size_t length;
	hashmap_container_t* map;
	hashfunction_t hashfunction;
} hashmap_t;

//Constructors and destructors
extern hashmap_t* mk_hashmap(size_t size);
extern hashmap_t* mk_hashmap_custom(size_t size, hashfunction_t fn);
extern void rm_hashmap(hashmap_t* hashmap);

//Accessors
extern void* hashmap_get(hashmap_t* hashmap, char* key);
extern bool hashmap_exists(hashmap_t* hashmap, char* key);
extern void hashmap_set(hashmap_t* hashmap, char* key, void* value);

#endif
