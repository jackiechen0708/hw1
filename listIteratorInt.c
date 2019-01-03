/*
  listIteratorInt.c : list Iterator ADT implementation
  Written by .... 
  Date: ....
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorInt.h"

// double linked list node
typedef struct Node {
    int value;
    struct Node *prev;
    struct Node *next;
} Node;

// double linked list iterator with last call node
typedef struct IteratorIntRep {
    int size;
    Node *head;

    Node *nextNode;
    Node *prevNode;

    Node *lastCall;
} IteratorIntRep;

// create new iterator
IteratorInt IteratorIntNew() {
    struct IteratorIntRep *iter = malloc(sizeof(struct IteratorIntRep));
    assert(iter != NULL);
    iter->size = 0;
    iter->head = NULL;
    iter->lastCall = NULL;
    iter->nextNode = NULL;
    iter->prevNode = NULL;
    return iter;
}

// reset iterator
void reset(IteratorInt iter) {
    iter->prevNode = NULL;
    iter->nextNode = iter->head;
	iter->lastCall = NULL;
}

// add node
int add(IteratorInt iter, int v) {

    if (iter == NULL) {
        return 0;
    }

    Node *tmp = malloc(sizeof(Node));
    if (tmp == NULL) {
        return 0;
    }
    tmp->value = v;
    tmp->prev = tmp->next = NULL;


    if (iter->head == NULL) {
        iter->head = tmp;
        iter->prevNode = tmp;
        iter->size++;
        return 1;
    } 
	// insert at head
	else if (hasPrevious(iter) == 0 && hasNext(iter) == 1) {
        iter->head = tmp;
        iter->nextNode->prev = tmp;
        tmp->next = iter->nextNode;
        iter->prevNode = tmp;
        iter->size++;
        return 1;

    }
	// insert at tail
    else if (hasNext(iter) == 0 && hasPrevious(iter) == 1) {

        iter->prevNode->next = tmp;
        tmp->prev = iter->prevNode;
        iter->prevNode = tmp;
        iter->size++;
        return 1;
    }
	// insert at middle
    else {
        iter->prevNode->next = tmp;
        tmp->prev = iter->prevNode;
        iter->nextNode->prev = tmp;
        tmp->next = iter->nextNode;
        iter->prevNode = tmp;
        iter->size++;               
        return 1;
    }
    return 0;
}

// check if iter has next
int hasNext(IteratorInt iter) {
	if (iter == NULL) {
		return 0;
	}
    if (iter->nextNode != NULL) {
        return 1;
    } else {
        return 0;
    }
}

// check if iter has prev
int hasPrevious(IteratorInt iter) {
	if (iter == NULL) {
		return 0;
	}
    if (iter->prevNode != NULL) {
        return 1;
    } else {
        return 0;
    }
}

// get the next
int *next(IteratorInt iter) {
	if (iter == NULL) {
		return NULL;
	}
	// has next node
    if (hasNext(iter)) {
        iter->prevNode = iter->nextNode;
        iter->nextNode = iter->nextNode->next;
        iter->lastCall = iter->prevNode;
        return &(iter->lastCall->value);
    } else {
        iter->lastCall = NULL;
        return NULL;
    }
}

// get the previous
int *previous(IteratorInt iter) {
	if (iter == NULL) {
		return NULL;
	}
    if (hasPrevious(iter)) {
        iter->nextNode = iter->prevNode;
        iter->prevNode = iter->prevNode->prev;
        iter->lastCall = iter->nextNode;
        return &(iter->lastCall->value);
    } else {
        iter->lastCall = NULL;
        return NULL;
    }
}

// delete the last call node
int deleteElm(IteratorInt iter) {
    // precondition fail
    if (iter->lastCall == NULL) {
        return 0;
    }
    // not head
    if (iter->lastCall != iter->head) {
        // not end
        if (iter->lastCall->next != NULL) {
			iter->lastCall->prev->next = iter->lastCall->next;
			iter->lastCall->next->prev = iter->lastCall->prev;
        } else {
			iter->lastCall->prev->next = NULL;
        }
    }
	// head
    else {
        // only one head
        if (iter->head->next == NULL) {
            iter->head = NULL;
            iter->lastCall = NULL;
            iter->prevNode = NULL;
            iter->nextNode = NULL;
            free(iter->lastCall);
            iter->size--;
            return 1;
        }
        // change the head
        iter->head = iter->head->next;
        iter->head->prev = NULL;
    }
    
    if (iter->lastCall == iter->prevNode) {
        iter->prevNode = iter->prevNode->prev;
    } else if (iter->lastCall == iter->nextNode) {
        iter->nextNode = iter->nextNode->next;
    }
    iter->lastCall = NULL;
    free(iter->lastCall);
    iter->size--;                   
    return 1;
}

int set(IteratorInt iter, int v) {
    // precondition fail
    if (iter->lastCall == NULL) {
        return 0;
    }
    // set value
	iter->lastCall->value = v;
    // clear last call
    iter->lastCall = NULL;
    return 1;

}

// find the next node whose value is v
int *findNext(IteratorInt iter, int v) {

    Node *cur = iter->nextNode;
    while (cur != NULL && cur->value != v) {
        cur = cur->next;
    }
    // not found
    if (cur == NULL) {
        iter->lastCall = NULL;
        return NULL;
    }

    // found the node
    iter->prevNode = cur;
    iter->nextNode = cur->next;
    iter->lastCall = cur;

    return &(cur->value);
}

// find the previous node whose value is v
int *findPrevious(IteratorInt iter, int v) {
    Node *cur = iter->prevNode;
    while (cur != NULL && cur->value != v) {
        cur = cur->prev;
    }
	// not found
    if (cur == NULL) {
        iter->lastCall = NULL;
        return NULL;
    }
	// found the node
    iter->nextNode = cur;
    iter->prevNode = cur->prev;
    iter->lastCall = cur;

    return &(cur->value);
}

// free memory
void freeIt(IteratorInt iter) {
    if(iter == NULL){
        return;
    }
    Node *cur;
    cur = iter->head;
	while (cur != NULL) {
		iter->head = cur->next;
		free(cur);
		cur = iter->head;
	}
    free(iter);

}
