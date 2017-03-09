//Authors Michelle Smith / Youssef Beshay
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

//Struct to store the information of the player
typedef struct
{
    char name[20];
    char type[20];
    int lifePoints;
    int smartness,strength, magicSkills, luck,dexterity;
    
}player;

//struct to store the information of the slot
typedef struct
{
    char slotType[20];
    int slotTypeNo;
    int playerNo;
}slot;

//array to store the player types
char playerTypes[4][20]={"Elf","Human","Ogre","Wizard"};

//array to store the slot types
char slotType[3][20]={"Level Ground","Hill","City"};


//array to store the player types
char playerTypes[4][20]={"Elf","Human","Ogre","Wizard"};

//array to store the slot types
char slotType[3][20]={"Level Ground","Hill","City"};

//method to set the capabilities of a player
void setCapabilities(player playerArray[],int playerNumber,int playerTypeChoice);

//method to update the capabilities of the player on moving to next slot
void updateCapabiltitesOnMovingSlot(player playerArray[],int playerNumber,int slotTypeMovedTo);

//method to print the details after a successful turn
void printDetails(player playerArray[],int noOfPlayers);

//method to find the closest player to attack
int findClosestPlayer(int attackerPlayerNo,slot slotArray[], int noOfSlots);

//method to implement the attack
void implementingAttack(player playerArray[],int attackerPlayerNo,int attackedPlayerNo);

//method to perform the actions
void performActions(player playerArray[],slot slotArray[],int noOfPlayers,int noOfSlots);


//method to perform the actions
void performActions(player playerArray[],slot slotArray[],int noOfPlayers,int noOfSlots)

//method to print the details of the player
void printDetails(player playerArray[],int noOfPlayers)

//method to set the capabilities of the players
void setCapabilities(player playerArray[],int playerNumber,int playerTypeChoice)

//method to update the capabalities when a player moves a slot
void updateCapabiltitesOnMovingSlot(player playerArray[],int playerNumber,int slotTypeMovedTo)

//method to implement the attack
void implementingAttack(player playerArray[],int attackerPlayerNo,int attackedPlayerNo)
	
	

