#include <stdio.h>
#include <stdlib.h>
typedef struct node node;
typedef struct linked_list linked_list;


struct node {
    int value;
    node *next;       
};

struct linked_list {
    unsigned int size;
    node *head;
};


/** Initialize a new linked_list */
void linked_list_init(linked_list *list) {
    list->size = 0U;
    list->head = NULL;
}


/** Create a new node with a value @val and push it to the end of list */
void linked_list_push_back(linked_list *list, int val) {
    node *new = malloc(sizeof(node)); // create a new node
    new->value = val; // assign a value to it
    new->next = NULL; // make the node after it be a NULL

    if (list->size == 0U) {
        list->head = new;
        ++list->size;
        return;  
    }
    
    node *lastNode = list->head;
    while(lastNode->next != NULL) { // iterate to the last node in list
        lastNode = lastNode->next;    
    }

    lastNode->next = new;

    ++list->size;
}


/**
    Insert a new node with a value @val to the position @pos
    - if @pos >= size of the list, then insert a new node to the end of list
*/
void linked_list_insert_node(linked_list *list, int val, unsigned int pos) {
    if (pos >= list->size) {
        linked_list_push_back(list, val);   
        return; 
    }
    
    // init a new node
    node *new = malloc(sizeof(node));
    new->value = val;
    
    // iterate to the node with position (@pos - 1)
    node *currentNode = list->head;    
    for (unsigned int currentPos = 0U; currentPos + 1 < pos; ++currentPos) {
        currentNode = currentNode->next;
    }
        
    node *prev = currentNode; // before the new node
    node *next = currentNode->next; // after the new node

    prev->next = new;
    new->next = next;

    ++list->size;
}


/**
    Delete a node by a position @pos
    - if @pos >= size then do nothing
*/
void linked_list_delete_node(linked_list *list, unsigned int pos) {
    if (pos >= list->size)
        return;
    
    // iterate to the node with position (@pos - 1)
    node *currentNode = list->head;    
    for (unsigned int currentPos = 0U; currentPos + 1 < pos; ++currentPos) {
        currentNode = currentNode->next;
    }
    
    node *prev = currentNode; // before the node to be deleted
    node *delete = currentNode->next; // the node to be deleted
    node *next = currentNode->next->next; // after the node to be deleted

    prev->next = next; // exclude node to be deleted from the list

    free(delete);
    delete = NULL;

    --list->size;
}


void linked_list_print(linked_list *list) {
    printf("The list: "); 
   
    node *currentNode = list->head;
    while(currentNode != NULL) {
        printf("%d ", currentNode->value); 
        currentNode = currentNode->next;
    }
    printf("\n");
}



int main() {
    linked_list list;
    linked_list_init(&list);
    linked_list_print(&list);
    
    linked_list_insert_node(&list, 0, 12U); // pos: 0
    linked_list_print(&list);

    linked_list_push_back(&list, 1);
    linked_list_print(&list);

    linked_list_push_back(&list, 3);
    linked_list_print(&list);

    linked_list_push_back(&list, 4);
    linked_list_print(&list);

    linked_list_insert_node(&list, 2, 2U);
    linked_list_print(&list);

    linked_list_delete_node(&list, 1U);
    linked_list_print(&list);

    linked_list_delete_node(&list, 134U);
    linked_list_print(&list);

    linked_list_delete_node(&list, 3U);
    linked_list_print(&list);

    return 0;
}
