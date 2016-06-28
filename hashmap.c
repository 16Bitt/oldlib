#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "oldlib.h"

size_t generic_hash(char* key, size_t size){
	return 0;
}

hashmap_t* mk_hashmap(size_t size){
	hashmap_t* hashmap = (hashmap_t*) malloc(sizeof(hashmap_t));
	hashmap->length = size;
	hashmap->hashfunction = generic_hash;
	hashmap->map = (hashmap_container_t*) malloc(sizeof(hashmap_container_t) * size);
	memset(hashmap->map, 0, sizeof(hashmap_container_t) * size);
	return hashmap;
}

hashmap_t* mk_hashmap_custom(size_t size, hashfunction_t fn){
	hashmap_t* hashmap = mk_hashmap(size);
	hashmap->hashfunction = fn;
	return hashmap;
}
