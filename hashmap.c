#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "oldlib.h"

//This is the Jenkin's "One at a time" hashing algorithm
size_t generic_hash(char* key, size_t size){
	size_t len = strlen(key);
	size_t index = 0;
	for(size_t i = 0; i < len; i++){
		index += key[i];
		index += index << 10;
		index ^= index >> 6;
	}

	return index % size;
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

void rm_hashmap(hashmap_t* hashmap){
    for(size_t i = 0; i < hashmap->length; i++)
        if(hashmap->map[i].bucketed)
            rm_linkedlist(hashmap->map[i].bucket);

    free(hashmap->map);
    free(hashmap);
}

void* hashmap_get(hashmap_t* hashmap, char* key){
    size_t index = hashmap->hashfunction(key, hashmap->length);

    if(index >= hashmap->length){
        OLDLIB_WARN("hashmap index out of bounds-- check your hashing function");
        return NULL;
    }

    //The key doesn't exist
    if(hashmap->map[index].value.value == NULL)
        return NULL;

    //Check the primary key
    if(strcmp(key, hashmap->map[index].value.key) == 0)
        return hashmap->map[index].value.value;

    //Search the bucket, if applicable
    if(hashmap->map[index].bucketed){
        size_t len = linkedlist_length(hashmap->map[index].bucket);
        for(size_t i = 0; i < len; i++){
            hashmap_value_t* value = linkedlist_get(hashmap->map[index].bucket, i);
            if(strcmp(key, value->key) == 0)
                return value->value;
        }
    }

    //It wasn't found
    return NULL;
}

bool hashmap_exists(hashmap_t* hashmap, char* key){
    size_t index = hashmap->hashfunction(key, hashmap->length);

    if(index >= hashmap->length){
        OLDLIB_WARN("hashmap index out of bounds-- check your hashing function");
        return false;
    }

    //The key doesn't exist
    if(hashmap->map[index].value.value == NULL)
        return false;

    //Check the primary key
    if(strcmp(key, hashmap->map[index].value.key) == 0)
        return true;

    //Search the bucket, if applicable
    if(hashmap->map[index].bucketed){
        size_t len = linkedlist_length(hashmap->map[index].bucket);
        for(size_t i = 0; i < len; i++){
            hashmap_value_t* value = linkedlist_get(hashmap->map[index].bucket, i);
            if(strcmp(key, value->key) == 0)
                return true;
        }
    }

    //It wasn't found
    return false;
}

void hashmap_set(hashmap_t* hashmap, char* key, void* value){
    size_t index = hashmap->hashfunction(key, hashmap->length);

    if(index >= hashmap->length){
        OLDLIB_WARN("hashmap index out of bounds-- check your hashing function");
        return;
    }

    //If the primary key is empty, we can just set it
    if(hashmap->map[index].value.key == NULL){
        hashmap->map[index].value.value = value;
        hashmap->map[index].value.key = key;
        return;
    }

    //If the primary key matches, we can just set it
    if(hashmap->map[index].value.key != NULL && strcmp(hashmap->map[index].value.key, key) == 0){
        hashmap->map[index].value.value = value;
        hashmap->map[index].value.key = key;
        return;
    }

    //Initialize a new value_t so we have something to put in the bucket
    hashmap_value_t* node = (hashmap_value_t*) malloc(sizeof(hashmap_value_t));
    node->key = key;
    node->value = value;

    //Make the bucket if it doesn't already exist
    if(!hashmap->map[index].bucketed){
        hashmap->map[index].bucketed = true;
        hashmap->map[index].bucket = mk_linkedlist();
        linkedlist_push(hashmap->map[index].bucket, node);
        return;
    }

    //See if it already exists in the bucket
    size_t len = linkedlist_length(hashmap->map[index].bucket);
    for(size_t i = 0; i < len; i++){
        hashmap_value_t* current = linkedlist_get(hashmap->map[index].bucket, i);
        //Replace the index in the list if the key was found
        if(strcmp(current->key, key) == 0){
            linkedlist_set(hashmap->map[index].bucket, i, node);
            free(current);
            return;
        }
    }

    //Finally, push the value into the bucket since it wasn't already there
    linkedlist_push(hashmap->map[index].bucket, node);
}
