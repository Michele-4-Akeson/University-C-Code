#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct node *element(struct node *dll, int i) ;
struct node *add(struct node *dll, int i, int value) ;
struct node *delete(struct node *dll, int i);


typedef struct node {
  int value;
  struct node* next;
  struct node* prev;
} Node;




struct node *element(struct node *dll, int i)  {
  int index = 0;
  struct node* current_node = dll;
  struct node* next_node = dll->next;

  if (i < 0) {
    current_node = NULL;
    return current_node;
  }

  while (index < i && current_node != NULL) {
    //printf("\nINDEX: %d  ADDRESS: %p\n", index, current_node);
    index++;
    current_node = next_node;
    
    if (current_node != NULL) {
      next_node = next_node->next;
    }
    
    
    
  }

  return current_node;
}



struct node *delete(struct node *dll, int i){
  Node* delete_address = element(dll, i);
  Node* left_node;
  Node* right_node;

  if (delete_address != NULL) {
    if (i == 0) {
      dll = dll->next;
      
    } else if (delete_address->next == NULL) {
      right_node = element(dll, i - 1);
      right_node->next = NULL;
    
    
    } else {
	left_node = element(dll, i - 1);
	right_node = element(dll, i + 1);

	left_node->next = right_node;
	right_node->prev = left_node;
      }    
  }
  
  return dll;
}



struct node *add(struct node *dll, int i, int value){
  Node* node_address = element(dll, i);
  Node* list_end = dll;
  Node* insert_node = malloc(sizeof(struct node));

  //printf("INDEX: %d  NODE ADDRESS OF INDEX %p\n", i, node_address);
  // APPEND TO END
  if (node_address == NULL) {
    int index = 0;
    while (list_end->next != NULL) {
      index++;
      list_end = element(dll, index);
    }

    insert_node->value = value;
    insert_node->next = NULL;
    insert_node->prev = list_end;

    list_end->next = insert_node;

  } else {
    Node* left_node = NULL;
    Node* right_node = NULL;

    //INSERT AT START
    if (i == 0){
      right_node = dll;
      insert_node->value = value;
      insert_node->next = dll;
      insert_node->prev = NULL;
      dll->prev = insert_node;
      return insert_node;
      
      // INSERT AT INDEX  
    } else {
      left_node = element(dll, i - 1);
      right_node = element(dll, i);

      insert_node->value = value;
      insert_node->next = right_node;
      insert_node->prev = left_node;

      left_node->next = insert_node;
      right_node->prev = insert_node;

    }

  }

  return dll;
  
}



void printNode (struct node *dll) {
    if (dll != NULL) {
        printf("< This: %p - %d - P : %p - N : %p >\n", dll, dll->value, dll->prev, dll->next);
    } else {
        printf("Null Pointer");
    }
}


void printLL (struct node *dll) {
    struct node* ptr = dll;
    printf("---\n");
    while (ptr != NULL) {
        printNode(ptr);
        ptr = ptr->next;
    }
    printf("---\n\n");
}

int main () {
    struct node *dll = malloc(sizeof(struct node));
    dll->value = 1;
    printLL(dll);
    
    dll = add(dll, -1, 3);
    printLL(dll);
    dll = add(dll, -1, 4);
    printLL(dll);
    dll = add(dll, 1, 2);
    printLL(dll);
    dll = add(dll, 2, 7);
    printLL(dll);
    dll = add(dll, 9, -1);
    printLL(dll);
   
    printf("\nDELETE\n");

    
    dll = delete(dll, 2);
    printLL(dll);
    dll = delete(dll, 0);
    printLL(dll);
    dll = delete(dll, 4);
    printLL(dll);
    dll = delete(dll, 0);
    dll = delete(dll, 0);
    dll = delete(dll, 0);
    dll = delete(dll, 0);
    
    

    return 0;
}

/* Expected Output: 

Obviously the pointers will be different each time, the point is that the previous and next pointers are pointing to the correct node. 

---
< This: 0x1cf8590 - 1 - P : (nil) - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf8590 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf8590 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85f0 >
< This: 0x1cf85f0 - 2 - P : 0x1cf8590 - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf85f0 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85f0 >
< This: 0x1cf85f0 - 2 - P : 0x1cf8590 - N : 0x1cf8610 >
< This: 0x1cf8610 - 7 - P : 0x1cf85f0 - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf8610 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85f0 >
< This: 0x1cf85f0 - 2 - P : 0x1cf8590 - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf85f0 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

---
---

*/ 
