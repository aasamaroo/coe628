#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Alex Samaroo
 */
void PQ_insert(int priority, char * data) {

    
//Create new node to insert
 Node_ptr_t new = malloc(sizeof(Node_t));
new->priority = priority;
new->data = data;
new->next = NULL;

//Create temporary nodes to use
Node_ptr_t temp = malloc(sizeof(Node_t));
Node_ptr_t insertionNode = malloc(sizeof(Node_t));
Node_ptr_t currNode = malloc(sizeof(Node_t));

//Check if head is NULL, if yes then insert new node as head
if(head == NULL){
    head = malloc(sizeof(Node_t));
    head = new;
//If the priority of new node is greater than the current head's priority 
//Then push new node to head, and previous head moves back in PQ
//First store old head onto temp node
} else {
    if(priority >= head->priority){
        temp->data = head->data;
        temp->priority = head->priority;
        temp->next = head->next;
//Make new node the head, and make the next node the previous head
//Which was stored in temp node
        head = new;
        head->next = temp;
//Traverse list until you reach the end, or find a node with
//a lower priority than the new node
    }
    else{
        insertionNode = new;
        currNode = head;
        while(currNode->next != NULL && insertionNode->priority < currNode->next->priority){
            currNode = currNode->next;
        }
//Insert at the end of the PQ 
        if(currNode->next == NULL){
            currNode->next = insertionNode;
            insertionNode->next = NULL;
        } 
//Insert in the middle of PQ (if new node's PQ higher than an existing node's PQ)
        else{
            temp = malloc(sizeof(Node_t));
            temp = currNode->next;
            currNode->next = insertionNode;
            insertionNode->next = temp;
        }
    }
}
}


/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */

Node_ptr_t PQ_delete() {
    
  //Create Temp node
  Node_ptr_t temp = malloc(sizeof(Node_t));

  temp = head; 
  head = head->next;
  free(temp);
    return NULL;
}


/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}






