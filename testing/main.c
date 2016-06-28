#include "stdio.h"
#include "oldlib.h"

int main(int argc, char** argv){
	printf("Starting tests for %s\n", argv[0]);
	
	//Test the warning macro
	oldlib_error_level(OLDLIB_LOUD);
	OLDLIB_WARN("Testing the warning macro-- if you're seeing this, it works");
	
	//Crank up pickiness and test the initializer
	oldlib_error_level(OLDLIB_STRICT);
	linkedlist_t* list = mk_linkedlist();
	OLDLIB_ASSERT(linkedlist_length(list) == 0);
	
	//Make some test values
	int test_a = 1;
	int test_b = 2;
	int test_c = 3;
	
	//Test the push routine
	linkedlist_push(list, &test_a);
	OLDLIB_ASSERT(linkedlist_length(list) == 1);
	linkedlist_push(list, &test_b);
	OLDLIB_ASSERT(linkedlist_length(list) == 2);
	linkedlist_push(list, &test_c);
	OLDLIB_ASSERT(linkedlist_length(list) == 3);
	//Test the pop routine
	OLDLIB_ASSERT(*((int*) linkedlist_pop(list)) == test_c);
	OLDLIB_ASSERT(*((int*) linkedlist_pop(list)) == test_b);
	OLDLIB_ASSERT(*((int*) linkedlist_pop(list)) == test_a);
	OLDLIB_ASSERT(linkedlist_length(list) == 0);
	
	//Cleanup
	rm_linkedlist(list);

	puts("Tests of the linkedlist portion successful");

	return 0;
}
