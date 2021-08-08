#include<stdbool.h>
#include"utils.h"
#include"stats.h"
#include"locations.h"

enum TownOption readTownOption (char resp[50]) {
	if (strncmp(resp, "rest", 5) == 0) {
		return rest;
	} else if (strncmp(resp, "sell", 5) == 0) {
		return sell;
	} else if (strncmp(resp, "atk", 4) == 0) {
		return atk;
	} else if (strncmp(resp, "def", 4) == 0) {
		return def;
	} else if (strncmp(resp, "leave", 4) == 0) {
		return leave;
	} else {
		return -1;
	}
}

void townLoop (Player *tux) {
	bool inTown = true;
	char response[50];
	enum TownOption resp;
	printf("You arrive in Torvaldia, a small settlement\n");
	printf("in the forest of unmerged branches.\n");
	displayImage("images/town.ascii");
	while (inTown) {
		// get Scenario
		printf("Available actions are: \n");
		printf("- Stay at the Nested Loop Inn (rest) [-10 gold]\n");
		printf("- Flog some loot (sell)\n");
		printf("- Have your beak sharpened (atk) [+1 ATK, -50 gold]\n");
		printf("- Have your feathers fluffed (def) [+1 DEF, -50 gold]\n");
		printf("- Continue your adventure (leave)\n");
		printf(">> ");
		scanf("%50s", response);
		printf("\n");
		resp = readTownOption(response);
		switch (resp) {
			case rest :
				if (tux->gold >= 10) {
					printf("You awake refreshed and ready for battle!\n");
					tux->stats.HP = tux->stats.MAX_HP;
					tux->gold -= 10;
				} else {
					printf("You can't afford the inn, so you sleep in a smelly\n"); 
					printf("garbage can, restoring half your health\n");
					tux->stats.HP += tux->stats.MAX_HP / 2;
					if (tux->stats.HP > tux->stats.MAX_HP) {
						tux->stats.HP = tux->stats.MAX_HP;
					}
				}
				break;
			case sell :
				printf("Select an item to sell by number : \n");
				displayInventory(tux->inventory, 0);
				printf(">> ");
				int item;
				scanf("%2d", &item);
				int result = sellItem(item, &(tux->inventory));
				if (result == -1) {
					printf("Command Not Recognized!\n");
				} else {
					printf("Loot Successfully Flogged.\n");
					printf("Tux gains %d gold!\n", result);
					tux->gold += result;
				}
				break;
			case atk :
				if (tux->gold >= 50) {
					printf("The beaksmith sharpens your beak for a modest fee.\n");
					printf("Attack power increased by 1!\n");
					tux->stats.ATK += 1;
					tux->gold -= 50;
				} else {
					printf("The beaksmith says \"We only serve the economically");
					printf("advantaged 'round these parts!\"");
				}
				break;
			case def :
				if (tux->gold >= 50) {
					printf("A featherworker fluffs your feathers for a modest fee.\n");
					printf("Defense power increased by 1!\n");
					tux->stats.DEF += 1;
					tux->gold -= 50;
				} else {
					printf("The featherworker says \"We only serve the economically");
					printf("advantaged 'round these parts!\"");
				}
				break;
			case leave:
				printf("You continue your quest!\n");
				inTown = false;
				break;
			default : 
				printf("Command Not Recognized!\n"); 
				break; 
		}	
	}
}

bool runEncounter (enum Area type, Player *tux) {
	Statblock creature;
	switch (type) {
		case camp :
			displayImage("images/goblincamp.ascii");
			printf("\nAs you approach the goblin camp, a goblin\n");
			printf("says something rude about your beak.\n");
			creature = goblin_init;
			displayImage("images/goblin.ascii");
			break;
		case fort :
			displayImage("images/orcfort.ascii");
			printf("\nAs you approach the orc fort, an orc approaches\n");
			printf("you, warning you the floor is wet as he just mopped.\n");
			creature = orc_init;
			displayImage("images/orc.ascii");
			break;
		case cave :
			displayImage("images/dragoncave.ascii");
			printf("\nAfter a perilous climb through the Mountains of Noob,\n");
			printf("you come upon it at last... the dragon's lair!\n");
			printf("The dragon emerges, its ferocity quickened by hunger.\n");
			creature = dragon_init;
			displayImage("images/dragon.ascii");
			break;
		case town:
			return false;
	}
	printf("...\nTo the death!!!\n");	
	
	// QUESTION 4 PART I GOES HERE!
	int damage_to_creature = tux->stats.ATK - creature.DEF;
	int damage_to_tux = creature.ATK - tux->stats.DEF;
	int tux_HP = tux->stats.HP;
	int creature_HP = creature.HP;
	char* creature_name = creature.NAME;
	while (tux_HP > 0 && creature_HP > 0){
	  if (damage_to_creature <= 0) {
	    printf("Tux attacks! Uh-Oh, no damage!\n");
	  } else {
	    printf("Tux attacks! %d damage!\n", damage_to_creature);
	    creature.HP -= damage_to_creature;
	    creature_HP = creature.HP;
	  }

	  if (creature_HP > 0) {
	    if (damage_to_tux <=0) {
	      printf("The %s attacks! Ha Ha! No damage!\n", creature_name);

	    } else {
	      printf("The %s attacks! %d damage!\n", creature_name, damage_to_tux); 
	      tux->stats.HP -= damage_to_tux;
	      tux_HP = tux->stats.HP;
	    }

	  }

	}
	  
	
	
	// QUESTION 4 PART II GOES HERE!

	if (tux_HP > 0) {
	  int xp = creature.XP;
	  int gold = xp/2;
	  
	  printf("You emerge victorious!\n");
	  printf("Gained %d XP\n", xp);
	  tux->stats.XP += xp;
	  printf("Gained %d Gold\n", gold);
	  tux->gold += gold;

	  if (strcmp(creature_name, "goblin") == 0) {
	    addItem(1, &(tux->inventory));
	  } else if (strcmp(creature_name, "orc") == 0) {
	     addItem(2, &(tux->inventory));
	  }

	  while (tux->stats.XP >= 100) {
	    tux->stats.XP -= 100;
	    tux->level += 1;
	    printf(">><<>><<>><<>><<>><<>><<\n");
	    printf("Tux achieves level %d!\n", tux->level);
	    printf(">><<>><<>><<>><<>><<>><<\n");
	    tux->stats.MAX_HP += 5;
	    tux->stats.HP = tux->stats.MAX_HP;
	    tux->stats.ATK += 1;
	    tux->stats.DEF += 1;
	  }

	  if (type == cave) {
	    return true;
	  }
	  
	} else {
	  displayImage("images/death.ascii");
	  exit(0);

	}

	return false;
}

enum Area readTravelOption (char resp[50]) {
	if (strncmp(resp, "town", 5) == 0) {
		return town;
	} else if (strncmp(resp, "camp", 5) == 0) {
		return camp;
	} else if (strncmp(resp, "fort", 5) == 0) {
		return fort;
	} else if (strncmp(resp, "cave", 5) == 0) {
		return cave;
	} else {
		return -1;
	}
}

bool travelDispatch (Player *tux) {
	char response[50];
	printf("Available Locations are: \n");
	printf("- Torvaldia Town (town)\n");
	printf("- The Goblin Camp (camp)\n");
	printf("- The Orc's Fortress (fort)\n");
	printf("- The Dragon's Cave (cave)\n");
	printf(">> ");
	scanf("%50s", response);
	printf("\n");
	enum Area resp = readTravelOption(response);
	switch (resp) {
	case town :	
	  townLoop(tux);
	  break;
	case camp :
	case fort :
	case cave :
	  return runEncounter(resp, tux);
	default :
	  printf("Command Not Recognized!");
	}
	return 0;
}

