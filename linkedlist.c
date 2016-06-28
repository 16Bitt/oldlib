#include "stdlib.h"
#include "oldlib.h"

linkedlist_node_t* linkedlist_get_internal(linkedlist_t* list, size_t index){
	linkedlist_node_t* current = list->value;
	for(size_t i = 0; i < index; i++){
		if(current == NULL){
			OLDLIB_WARN("Index out of bound in list");
			break;
		}

		current = current->next;
	}

	if(current == NULL)
		OLDLIB_WARN("Index out of bound at end of list");

	return current;
}

linkedlist_t* mk_linkedlist(){
	linkedlist_t* list = (linkedlist_t*) malloc(sizeof(linkedlist_t));
	list->length = 0;
	list->value = NULL;

	return list;
}

void rm_linkedlist(linkedlist_t* list){
	for(size_t i = 0; i < list->length; i++){
		linkedlist_node_t* node = linkedlist_get_internal(list, list->length - i - 1);
		if(node == NULL){
			OLDLIB_WARN("Can't free NULL node in list cleanup code");
			continue;
		}
		free(node);
	}
	free(list);
}

size_t linkedlist_length(linkedlist_t* list){
	if(list == NULL){
		OLDLIB_WARN("Can't get length of NULL list");
		return 0;
	}

	return list->length;
}

void* linkedlist_get(linkedlist_t* list, size_t index){
	linkedlist_node_t* node = linkedlist_get_internal(list, index);
	if(node == NULL){
		OLDLIB_WARN("Invalid NULL get() from linkedlist");
		return NULL;
	}
	return node->value;
}

void linkedlist_set(linkedlist_t* list, size_t index, void* value){
	linkedlist_node_t* node = linkedlist_get_internal(list, index);
	if(node == NULL){
		OLDLIB_WARN("Invalid NULL set() from linkedlist");
		return;
	}
	node->value = value;
}

void linkedlist_insert(linkedlist_t* list, size_t index, void* value){
	if(index > list->length){
		OLDLIB_WARN("Out of bounds insert() in linkedlist");
		return;
	}

	linkedlist_node_t* node = (linkedlist_node_t*) malloc(sizeof(linkedlist_node_t));
	node->value = value;
	node->next = NULL;

	if(index == 0){
		node->next = list->value;
		list->value = node;
		list->length++;
		return;
	}

	linkedlist_node_t* ahead = linkedlist_get_internal(list, index - 1);
	node->next = ahead->next;
	ahead->next = node;
	list->length++;
}

void linkedlist_delete(linkedlist_t* list, size_t index){
	if(index >= list->length){
		OLDLIB_WARN("Out of bounds delete() in linkedlist");
		return;
	}

	linkedlist_node_t* node;
	if(index == 0){
		node = list->value->next;
		free(list->value);
		list->value = node;
		list->length--;
		return;
	}

	linkedlist_node_t* ahead = linkedlist_get_internal(list, index - 1);
	linkedlist_node_t* current = linkedlist_get_internal(list, index);
	ahead->next = current->next;
	free(current);
	list->length--;
}

void* linkedlist_pop(linkedlist_t* list){
	if(list->length == 0){
		OLDLIB_WARN("Underflow in list during pop()");
		return NULL;
	}

	void* value = linkedlist_get(list, list->length - 1);
	linkedlist_delete(list, list->length - 1);
	return value;
}

void linkedlist_push(linkedlist_t* list, void* value){
	linkedlist_insert(list, list->length, value);
}
