#ifndef STATS_HEADER
#define STATS_HEADER 1
#include"inventory.c"


/**
 * @file stats.h
 * @author Michele Akeson
 * @date August 08th, 2021
 * @brief stats.h is a header file containing prototypes to be used in 
 *        the stats.c script, doxycomments, as well as the statblock and player structs:
 *
 *        statblock is a struct which provides the basic stats of a character such as their NAME, MAX_HP, HP, XP, ATK, and DEF
 *        player is a struct which provides player data on Tux, such as the level, amount of gold, inventory, and stats (via a statblock struct)
 *        struct which contains fields describing a the stats of a character in the, such as name, code, 
 */


/** brief statblock is a struct containing fields: NAME, MAX_HP, HP, XP, ATK, and DEF
 *  This structure repersents a character, specifically their fighting stats which are used
 *  in game to determine how much damage is dealt, and the amount of XP and gold gained by the player
 *  of students enrolled in the course
 */
struct statblock {
  char *NAME; /**< the name of the character*/
  int MAX_HP; /**< the maximum hitpoints a character can have*/
  int HP; /**< the current hitpoints a character has*/
  int XP; /**< the experiecne points Tux gets if they beat this character */
  int ATK; /**< the attack points of the character determining how much damage it can deal */
  int DEF; /**< the defence points of a character how much damage it can block */
}
goblin_init = {"goblin", 20, 20, 20, 8, 6},
orc_init = {"orc", 50, 50, 50, 15, 8},
dragon_init = {"dragon", 250, 250, 250, 35, 28};

typedef struct statblock Statblock;

struct player {
	int level;
	int gold;
	InvNode *inventory;
	Statblock stats;
} player_init = {1, 50, NULL, {"Tux", 25, 25, 0, 10, 5}};

typedef struct player Player;

void displayStats(Player *tux);

#endif
