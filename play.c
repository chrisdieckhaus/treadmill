//This will be used for playing around with C and linked lists.#include "fs.h"
#include <stdlib.h>
#include <stdio.h>

//type: 0 = null, 1 = IND, 2 = INT

struct node {
	int address;
	int val2;
	int val1;
	int type;
	const char *typ;
	struct node *next;
	struct node *prev;
};
	

struct node *head = NULL;
	

int main(int argc, char** argv){
	
	initHeap(10);	//parameter is total space in memory (# of links in LL)
	
	return 0;
}

void initHeap(int length){
	//add heap objects
	int allocate = 4;
	int types[4] = {1,1,2,1};
	int val1s[4] = {2,5,10,3};
	int val2s[4] = {0,0,0,0};
	char *typs[] = {"IND","IND","INT","IND"};

	if (head==NULL){
		head = malloc(sizeof(struct node));
		head->address = 0;
		head->next = NULL;
		head->prev = NULL;
	}
	struct node * curr = malloc(sizeof(struct node));
	curr = head;
	
	int i;
	for (i=0; i<length; i++){
		struct node * ptr = malloc(sizeof(struct node));
		ptr->address = 0;
		ptr->type = 0;
		ptr->val1 = 0;
		ptr->val2 = 0;
		ptr->typ = NULL;

		ptr->next = NULL;
		ptr->prev = curr;
		curr->next = ptr;
		curr = ptr;
	}
	curr->next = head;
	head->prev = curr;
	curr = head;
	
	int j;
	for (j=0; j<4; j++){

		curr->address = j*3;
		curr->type = types[j];
		curr->val1 = val1s[j];
		curr->val2 = 0;
		const char *ty = typs[j];
		curr->typ = ty;

		curr = curr->next;
	}
	curr = head;

	for (i=0; i<length; i++){
		printf("%d | %s | %d | %d\n", curr->address, curr->typ, curr->val1, curr->val2);
		curr = curr->next;
	}
}








