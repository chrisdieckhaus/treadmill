//This will be used for playing around with C and linked lists.#include "fs.h"
#include <stdlib.h>
#include <stdio.h>
#define HEAP_SIZE 10
#define ALLOCATE 6
#define NUM_ROOTS 2
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

void init_heap(int length){
	//add heap objects
	int allocate = 6;
	int val1s[ALLOCATE] = {3,2,0,0,9,0};
	int val2s[ALLOCATE] = {0,0,9,9,15,0};
	char *types[] = {"IND","INT","CONS","CONS","CONS","NULL"};
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
	for (j=0; j<allocate; j++){
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
	//print_list();
	//print_pointers();
}

void print_pointers(){
	printf("%s points to %d | %s | %d | %d\n", white_ptr->name, white_ptr->points_to->address, white_ptr->points_to->type, white_ptr->points_to->val1, white_ptr->points_to->val2);
	printf("%s points to %d | %s | %d | %d\n", black_ptr->name, black_ptr->points_to->address, black_ptr->points_to->type, black_ptr->points_to->val1, black_ptr->points_to->val2);
	printf("%s points to %d | %s | %d | %d\n", grey_ptr->name, grey_ptr->points_to->address, grey_ptr->points_to->type, grey_ptr->points_to->val1, grey_ptr->points_to->val2);
	printf("%s points to %d | %s | %d | %d\n", free_ptr->name, free_ptr->points_to->address, free_ptr->points_to->type, free_ptr->points_to->val1, free_ptr->points_to->val2);
}

void print_list(){
	curr = head;
	int i;
	for (i=0; i<HEAP_SIZE+1; i++){
		printf("%d | %s | %d | %d | %s\n", curr->address, curr->type, curr->val1, curr->val2, curr->color);
		curr = curr->next;
	}
}

void start_gc(int roots[]){
    int i;
    for (i=0; i<NUM_ROOTS; i++){
        move_to_grey(roots[i]);
    }
 //9
    scan_node(roots[0]);
    print_list();
	print_pointers();
}

void find_node(int addr){
	curr = head;
	int i;
	for (i=0; i<HEAP_SIZE; i++){
		if (curr->address == addr){
			return;
		}else{
			curr = curr->next;}}}

void move_to_grey(addr){
	find_node(addr); //set curr to the node we're looking for
	if (white_ptr->points_to->address == curr->address){
		white_ptr->points_to = curr->next;
	} else {
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		grey_ptr->points_to->prev->next = curr;
		curr->prev = grey_ptr->points_to->prev;
		curr->next = grey_ptr->points_to;
		grey_ptr->points_to->prev = curr;
	}	
	curr->color = "grey";
	grey_ptr->points_to = curr;
	print_list();
	print_pointers();
}

void move_to_black(addr){
	find_node(addr); //set curr to the node we're looking for
	if (white_ptr->points_to->address == curr->address){
		white_ptr->points_to = curr->next;
		grey_ptr->points_to = curr->next;
	}
	if (grey_ptr->points_to->address == curr->address){
		if (curr->next->color == "grey"){
			grey_ptr->points_to = curr->next;
		}else if (curr->prev->color == "grey"){
			grey_ptr->points_to = curr->prev;
		}		
	}
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	black_ptr->points_to->prev->next = curr;
	curr->prev = black_ptr->points_to->prev;
	curr->next = black_ptr->points_to;
	black_ptr->points_to->prev = curr;
	curr->color = "black";
	
	black_ptr->points_to = curr;
	
	print_list();
	print_pointers();
}

void scan_node(addr){
    find_node(addr);
    printf("Scanning node %d\n", addr);
    move_to_black(addr);
    parse_structure(addr);
    printf("curr: %d\n", curr->address);
    while (grey_ptr->points_to->address != black_ptr->points_to->address){
        scan_node(grey_ptr->points_to->address);
    }
}

void parse_structure(addr){
    find_node(addr);
    printf("node to parse: %d | %s | %d | %d | %s\n", curr->address, curr->type, curr->val1, curr->val2, curr->color);
    if (curr->type == "IND"){
		find_node(curr->val1);
		if (curr->color == "white"){
			find_node(addr);
        	move_to_grey(curr->val1);
		}else{printf("Already moved %d\n", curr->address);}
    } else if (curr->type == "CONS"){
		printf("Found a CONS object\n");
		printf("Moving %d to grey\n", curr->val1);
		find_node(curr->val1);
		if (curr->color == "white"){
			find_node(addr);
        	move_to_grey(curr->val1);
		}else{printf("Already moved %d\n", curr->address);}
		find_node(addr);
		printf("Moving %d to grey\n", curr->val2);
		find_node(curr->val2);
		if (curr->color == "white"){
			find_node(addr);
        	move_to_grey(curr->val2);
		}else{printf("Already moved %d\n", curr->address);}
    }
}

int main(int argc, char** argv){
	int roots[] = {3,6};
	init_heap(10);	//parameter is total space in memory (# of links in LL)
        start_gc(roots);
	return 0;
}










