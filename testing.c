//This will be used for playing around with C and linked lists.#include "fs.h"
#include <stdlib.h>
#include <stdio.h>
#define HEAP_SIZE 15 	//how many total memory spots in linked list?
#define ALLOCATE 11		//how many objects in heap?
#define NUM_ROOTS 4		//how many roots?
//type: 0 = null, 1 = IND, 2 = INT

struct node {
	int address;
	int val2;
	int val1;
	const char *type;
	const char *color;
	struct node *next;
	struct node *prev;
};

struct node2{
	int address;
	const char *type;
	const char *color;
	struct node *next;
	struct node *prev;
	struct heap_cell *contents;
};

struct heap_cell{

};

struct pointr{
	const char *name;
	struct node *points_to;
};
	

struct node *head = NULL;
struct node * curr = NULL;
struct pointr *grey_ptr = NULL;
struct pointr *black_ptr = NULL;
struct pointr *free_ptr = NULL;
struct pointr *white_ptr = NULL;

struct node2 *head2 = NULL;
struct node2 * curr2 = NULL;

void new_print(){
	curr2 = head2;
	int i;
	for (i=0; i<HEAP_SIZE+1; i++){
		printf("%d | %s | %s\n", curr2->address, curr2->type, curr2->color);
		curr2 = curr2->next;
	}
}

void new_init(int length){
	printf("Hi new init %d\n", length);
	char *types[] = {"INT","NULL","CONS","CONS","CONS","CONS","IND","CONS","INT","NULL","IND"};
	if (head2==NULL){
		head2 = malloc(sizeof(struct node2));
		head2->address = 0;
		head2->next = NULL;
		head2->prev = NULL;
	}
	curr2 = malloc(sizeof(struct node2));
	curr2 = head2;
	int i;
	for (i=0; i<length; i++){
		struct node2 * ptr2 = malloc(sizeof(struct node2));
		ptr2->address = -1;
		ptr2->type = NULL;
		ptr2->color = "ecru";
		ptr2->next = NULL;
		ptr2->prev = curr2;
		curr2->next = ptr2;
		curr2 = ptr2;
	}
	curr2->next = head2;
	head2->prev = curr2;
	curr2 = head2;
	int j;
	for (j=0; j<ALLOCATE; j++){
		curr2->address = j*3;
		curr2->type = types[j];
		curr2->color = "white";
		curr2 = curr2->next;	
	}
	new_print();
}
/*
void init_heap(int length){
	printf("Init heap of size %d\n", HEAP_SIZE);
	//add heap objects
	int val1s[ALLOCATE] = {0,0,0,18,6,9,0,9,4,0,15};
	int val2s[ALLOCATE] = {0,0,21,21,7,3,0,3,0,0,0};
	char *types[] = {"INT","NULL","CONS","CONS","CONS","CONS","IND","CONS","INT","NULL","IND"};
	white_ptr = malloc(sizeof(struct pointr));
	black_ptr = malloc(sizeof(struct pointr));
	grey_ptr = malloc(sizeof(struct pointr));
	free_ptr = malloc(sizeof(struct pointr));
	if (head==NULL){
		head = malloc(sizeof(struct node));
		head->address = 0;
		head->next = NULL;
		head->prev = NULL;
	}
	curr = malloc(sizeof(struct node));
	curr = head;
	int i;
	for (i=0; i<length; i++){
		struct node * ptr = malloc(sizeof(struct node));
		ptr->address = -1;
		ptr->type = NULL;
		ptr->val1 = 0;
		ptr->val2 = 0;
		ptr->type = NULL;
		ptr->color = "ecru";
		ptr->next = NULL;
		ptr->prev = curr;
		curr->next = ptr;
		curr = ptr;
	}
	curr->next = head;
	head->prev = curr;
	curr = head;
	int j;
	for (j=0; j<ALLOCATE; j++){
		curr->address = j*3;
		curr->val1 = val1s[j];
		curr->val2 = val2s[j];
		curr->type = types[j];
		curr->color = "white";
		curr = curr->next;	
	}
	free_ptr->name = "FREE";
	free_ptr->points_to = curr;
	curr = head;
	white_ptr->name = "WHITE";
	white_ptr->points_to = head;
	black_ptr->name = "BLACK";
	black_ptr->points_to = head;
	grey_ptr->name = "GREY";
	grey_ptr->points_to = head;
}
*/




void find_node(int addr){
	curr2 = head2;
	int i;
	for (i=0; i<HEAP_SIZE; i++){
		if (curr2->address == addr){
			return;
		}else{
			curr2 = curr2->next;}}}




int main(int argc, char** argv){
	int roots[] = {21,0,3,12};
	//init_heap(HEAP_SIZE);	//parameter is total space in memory (# of links in LL)
	//print_list();
	new_init(HEAP_SIZE);
    //start_gc(roots);
	return 0;
}










