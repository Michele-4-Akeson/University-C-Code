/**
 * @file inventory.h
 * @author Michele Akeson
 * @date Auguts 08th, 2021
 * @brief inventory.h is a header file containing prototypes to be used in 
 *        the inventory.c script, doxycomments, as well as the invNode struct
 *        which contains fields describing an Inventory slot, such as the name, 
 *        description, and value of an item, as well as a pointer to the next slot
 *        in the inventory. It also provides the typedef, InvNode for improved readability in code 
 */





/** 
 * \brief invNode is a struct containing fields: name, description, value, and next
 * This structure repersents an inventory slot, and the respective name, and description, as
 * well as the value of an item in that slot. It also contains the pointer to the next slot
 *
 * goblin_loot and orc_loot are global instances of the invNode struct and acts as in game items  
 *
 */
struct invNode {
	char* name; /**< the name of the item*/
	char* description; /**< a short description of the item -- flavor text*/
	int value; /**< the value in gold; the in game currency*/
	struct invNode *next; /**< next is a pointer to the next inventory slot*/
} 
  goblin_loot = {"Necklace Of Teeth", "A necklace made of human teeth.   Perhaps this goblin was a dentist.", 6, NULL},
  orc_loot = {"Orcish Romance Novel", "Ooooo... Steamy!", 13, NULL};

typedef struct invNode InvNode;



/**
 * \brief addItem adds either goblin_loot or orc_loot to Tux's inventory system. It implicitly 
 * returns the begining of the inventory system - being the InvNode at the start of the linked list
 * @param which is an integer indicating the type of loot: 1 indicates that goblin_loot is being added, while 2 indicate orc_loot 
 * @param **inventory is the address of the pointer to the first InvNode - it allows for mutation of what is placed in a inventory slot and for implicit change in the begining of the inventory system
 * @return addItem returns void
 */
void addItem (int which, InvNode **inventory); // Question 3 Part I


/**
 * \brief sellItem remove either goblin_loot or orc_loot from Tux's inventory system. It implicitly 
 * returns the begining of the inventory system - being the InvNode at the start of the linked list
 * and remove the inventory slot which stores the item being sold
 * @param number is an integer indicating the index of the inventory slot being sold 
 * @param **inventory is the address of the pointer to the first InvNode - it allows for mutation of what is placed in a inventory slot and for implicit change in the begining of the inventory system
 * @return addItem returns an integer being the value of the item sold, which is either goblin loot (worth 6 gold) or orc_loot (worth 13 gold)
 */
int sellItem(int number, InvNode **inventory); // Question 3 Part II

/**
 * \brief displayInventory prints InvNode of Tux's inventory system to stdout, indicating the value of each field of that node - the name, descritpion, and value of an item. If the inventory is empty, a special print statement is made indicating this to the player 
 * @param number is an integer indicating the index of the inventory slot to begin printing. Ideally a value of zero is provided to print the entire inventory system
 * @param *inventory is the InvNode 
 * @return displayInventory return void
 */
void displayInventory(InvNode *inventory, int number);
