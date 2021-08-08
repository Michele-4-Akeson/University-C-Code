#include"inventory.h"
#include<stdlib.h>
#include<string.h>




void addItem (int which, InvNode **inventory){
  // *inventory is actually always the pointer to the first
  // item slot - which change the fields of the node and create
  // a new slot which stores the previous values of the field

 
  
  // QUESTION 3 PART I GOES HERE!
  InvNode* new_slot = (InvNode*) malloc(sizeof(InvNode)) ;
  
  switch(which){
  case 1:
    new_slot->name = goblin_loot.name;
    new_slot->description = goblin_loot.description;
    new_slot->value = goblin_loot.value;
    new_slot->next = *inventory;
    break;

  case 2:
    new_slot->name = orc_loot.name;
    new_slot->description = orc_loot.description;
    new_slot->value = orc_loot.value;
    new_slot->next = *inventory;

  }
  
  *inventory = new_slot;

}
 




int sellItem(int number, InvNode **inventory){
  // QUESTION 3 PART II GOES HERE!
  InvNode* sell_slot;
  InvNode* prev_slot;
  InvNode* next_slot;
  int i = 0;
  int value = -1;

  if (*inventory == NULL) {
    return value;

  } else if (number == 0) {
    value = (*inventory)->value;
    (*inventory) = (*inventory)->next;

  } else {
    sell_slot = *inventory;
    next_slot = sell_slot->next;
    while (i != number && sell_slot != NULL) {
      i++;
      prev_slot = sell_slot;
      sell_slot = next_slot;
      
      if (sell_slot->next != NULL) {
	next_slot = next_slot->next;
      }
      
    }

    if (i != number) {
      return value;
    } else {
      value = sell_slot->value;
      prev_slot->next = sell_slot->next;
    }

  }

  return value;


}

  

void displayInventory(InvNode *inventory, int number){
	if (inventory == NULL) {
		printf("*** Inventory Empty ***\n");
		return;
	}
	printf("╔══╤══════════════════════╤════════╗\n");
	printf("║%2.2d|%22.22s│%2d gold ║\n", number, inventory->name, inventory->value);
	printf("╟──┴──────────────────────┴────────╢\n");
	int length = strlen(inventory->description);
	int i = 0;
	while (i < length) {
		printf("║%34.34s║\n", (inventory->description + i));
		i += 34;
	}
	printf("╚══════════════════════════════════╝\n");
	if (inventory->next != NULL) {
		displayInventory(inventory->next, number + 1);
	}	
}
