//This will be used for playing around with C and linked lists.#include "fs.h"
#include <stdlib.h>
#include <stdio.h>

struct node {
	int data;
	struct node *next;
	struct node *prev;
};

struct node *head = NULL;
	

int main(int argc, char** argv){
	
	createList(10);
	
	return 0;
}

void createList(int length){
	if (head==NULL){
		head = malloc(sizeof(struct node));
		head->data = 0;
		head->next = NULL;
		head->prev = NULL;
	}
	struct node * curr = malloc(sizeof(struct node));
	curr = head;
	
	int i;
	for (i=1; i<length; i++){
		struct node * ptr = malloc(sizeof(struct node));
		ptr->data = i;
		ptr->next = NULL;
		ptr->prev = curr;
		curr->next = ptr;
		curr = ptr;
	}
	curr->next = head;
	head->prev = curr;
	curr = head;
	while (curr != NULL){
		printf("%d ", curr->data);
		curr = curr->next;
	}
}








