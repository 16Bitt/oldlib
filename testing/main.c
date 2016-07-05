#include "stdio.h"
#include "stdlib.h"
#include "oldlib.h"
#include "math.h"

char* randstr();

int main(int argc, char** argv){
	printf("Starting tests for %s\n", argv[0]);

	//Test the warning macro
	oldlib_error_level(OLDLIB_LOUD);
	OLDLIB_WARN("Testing the warning macro-- if you're seeing this, it works");

	//Crank up pickiness and test the initializer
	//oldlib_error_level(OLDLIB_STRICT);
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
	#define TESTBUCKET_SZ 100000

	hashmap_t* hashmap = mk_hashmap(TESTBUCKET_SZ);
	for(size_t i = 0; i < TESTBUCKET_SZ; i++){
		char* rng = randstr();
		hashmap_set(hashmap, rng, NULL);
	}

	int num_collisions = 0;
	for(size_t i = 0; i < TESTBUCKET_SZ; i++){
		if(hashmap->map[i].bucketed)
			num_collisions += linkedlist_length(hashmap->map[i].bucket);
	}

	printf("Out of %d indeces and elements, there were %d collisions.\n",
		TESTBUCKET_SZ, num_collisions);

	return 0;
}

//Make a random string between 1 and 16 characters
char* randstr(){
	size_t sz = rand() % 15 + 1;
	char* str = (char*) malloc(sizeof(char) * (sz + 1));
	for(size_t i = 0; i < sz; i++){
		str[i] = (rand() % (126 - 33)) + 33;
	}
	str[sz] = '\0';
	return str;
}
