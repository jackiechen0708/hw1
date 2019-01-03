/*
  listIteratorInt.c : list Iterator ADT implementation
  Written by .... 
  Date: ....
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorInt.h"


typedef struct Node {
    int value;
    struct Node *prev;
    struct Node *next;
} Node;


typedef struct IteratorIntRep {
    int size;
    Node *head;

    Node *nextNode;
    Node *prevNode;

    Node *tail;
} IteratorIntRep;


IteratorInt IteratorIntNew() {
    struct IteratorIntRep *iter = malloc(sizeof(struct IteratorIntRep));
    assert(iter != NULL);
    iter->size = 0;
    iter->head = NULL;
    iter->tail = NULL;
    iter->nextNode = NULL;
    iter->prevNode = NULL;
    return iter;
}


void reset(IteratorInt iter) {
    iter->prevNode = NULL;
    iter->nextNode = iter->head;
}

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
    assert(tmp != NULL);


    if (iter->head == NULL) {
        iter->head = tmp;
        iter->tail = tmp;
        iter->prevNode = tmp;
        iter->size++;
        return 1;
    } else if (hasPrevious(iter) == 0 && hasNext(iter) == 1) {
        iter->head = tmp;
        iter->nextNode->prev = tmp;
        tmp->next = iter->nextNode;
        iter->prevNode = tmp;
        iter->size++;
        return 1;

    }

    else if (hasNext(iter) == 0 && hasPrevious(iter) == 1) {

        iter->prevNode->next = tmp;
        tmp->prev = iter->prevNode;
        iter->prevNode = tmp;
        iter->tail=tmp;
        iter->size++;
        return 1;
    }

    else {
        // link the tmp node to where cursor currently is (which is prevNode->next)
        iter->prevNode->next = tmp;
        tmp->prev = iter->prevNode;
        // link the existing nodes after cursor to the tmp node and redefine cursor position
        iter->nextNode->prev = tmp;
        tmp->next = iter->nextNode;
        iter->prevNode = tmp;
        iter->size++;                //showLL(iter->head);
        return 1;
    }
    return 0;
}

// Check if there are any elements in the forward direction
int hasNext(IteratorInt iter) {
    assert(iter != NULL);
    if (iter->nextNode != NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Check if there are any elements in the previous direction.
int hasPrevious(IteratorInt iter) {
    assert(iter != NULL);
    if (iter->prevNode != NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Move the cursor to the next position and return the pointer to the element iter went passed by
int *next(IteratorInt iter) {
    assert(iter != NULL);
    // If there is next value
    if (hasNext(iter) == 1) {
        // Move to next value by moving the cursor position
        iter->prevNode = iter->nextNode;
        iter->nextNode = iter->nextNode->next;

        // Update tail called value
        iter->tail = iter->prevNode;

        int *p = &(iter->tail->value);
        return p;
    } else {
        iter->tail = NULL;
        return NULL;
    }
}

// Move the cursor in backward direction and return the pointer to the element iter went passed by.
int *previous(IteratorInt iter) {
    assert(iter != NULL);
    if (hasPrevious(iter) == 1) {
        // Move the cursor position forward
        iter->nextNode = iter->prevNode;
        iter->prevNode = iter->prevNode->prev;

        // Update tail called value
        iter->tail = iter->nextNode;

        int *p = &(iter->tail->value);
        return p;
    } else {
        iter->tail = NULL;
        return NULL;
    }
}

// Delete the tail called element that was returned by next or previous or findNext or findPrevious.
int deleteElm(IteratorInt iter) {
    //If there is no tail called, return 0. Hence, precondition not met
    if (iter->tail == NULL) {
        return 0;
    }
    //showLL(iter->head);
    // If the tail called element is not the head, we need to traverse through the list and find the tail called
    if (iter->tail != iter->head) {
        Node *current = iter->head;    // set current to head and start moving
        while (current != NULL && current != iter->tail) {
            current = current->next;
        }
        // If somwhere in the middle of the list
        if (current->next != NULL) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        } else {
            // If at end of the list
            current->prev->next = NULL;
        }
    }
        // Otherwise, iter is at head we we need to assign tmp head, remove link as well
    else {
        // If deleting only element, reset everything
        if (iter->head->next == NULL) {
            iter->head = NULL;
            iter->tail = NULL;
            iter->prevNode = NULL;
            iter->nextNode = NULL;
            free(iter->tail);
            iter->size--;
            return 1;
        }
        // Make the next element the head and remove its link
        iter->head = iter->head->next;
        iter->head->prev = NULL;
    }
    // Adjust the cursor accordingly. If the element we are deleting is currently defining the cursor, we need to change the cursor.
    if (iter->tail == iter->prevNode) {
        iter->prevNode = iter->prevNode->prev;
    } else if (iter->tail == iter->nextNode) {
        iter->nextNode = iter->nextNode->next;
    }
    iter->tail = NULL;
    free(iter->tail);
    iter->size--;                   //showLL(iter->head);
    return 1;
}

// Replace the tail element returned by next or previous or findNext or findPrevious with the specfied element v
int set(IteratorInt iter, int v) {
    // if precondition not met
    if (iter->tail == NULL) {
        return 0;
    }
    // Move through the list until we find tail called element
    Node *current = iter->head;
    while (current != NULL && current != iter->tail) {
        current = current->next;
    }
    // Set the value to v
    current->value = v;
    // Set tail to Null as set/delete must be immediately followed by either next, previous, findNext or findPrevious
    iter->tail = NULL;
    //showLL(iter->head);
    return 1;

}

// Returns pointer to the next value in iter that matches the given value v and advances the cursor position past the value returned
int *findNext(IteratorInt iter, int v) {
    // Traverse through the list from current cursor position until we reach a node with the value v
    Node *current = iter->nextNode;
    while (current != NULL && current->value != v) {
        current = current->next;
    }
    // If we moved through the list without finding an element that matched
    if (current == NULL) {
        iter->tail = NULL;
        return NULL;
    }

    // Initialize pointer variable to point to the next value in the list that matches the given value v to be returned
    int *p = &(current->value);

    // When value is found, we want to move our cursor to behind iter.
    iter->prevNode = current;
    iter->nextNode = current->next;
    // Set tail called value
    iter->tail = current;

    return p;
}

// Works similarly as findNext but in reverse direction
int *findPrevious(IteratorInt iter, int v) {
    Node *current = iter->prevNode;
    while (current != NULL && current->value != v) {
        current = current->prev;
    }
    if (current == NULL) {
        iter->tail = NULL;
        return NULL;
    }

    int *p = &(current->value);
    iter->nextNode = current;
    iter->prevNode = current->prev;
    iter->tail = current;

    return p;
}

// Deletes all nodes in iter and free associated memory
void freeIt(IteratorInt iter) {


    if(iter == NULL){
        return;
    }
    Node *curr, *prev;
    curr = iter->head;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(curr);
    free(iter);

}