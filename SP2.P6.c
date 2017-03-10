//Author Michelle Smith
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


//method to find the closest player
int findClosestPlayer(int attackerPlayerNo,slot slotArray[], int noOfSlots)
{
    //variables to store the attacker nd attacked player slot position
    int attackerPlayerSlotPosition=0;
    int attackedPlayerSlotPosition=0;
    
    //loop to find the position of the attacker
    for(int i=0;i<noOfSlots;i++)
    {
        if(slotArray[i].playerNo==attackerPlayerNo)
        {
            attackerPlayerSlotPosition=i;
        }
    }
    
    //boolean to store if the closest player has been found
    bool foundClosestPlayer=false;
    
    //counter to keep a track of the varaiable
    int counter=1;
    
    //runs loop until finds the closest enemy
    while(foundClosestPlayer!=true)
    {
        //checks if the attacker slot position has a previous or next slot
        if(attackerPlayerSlotPosition-counter>=0 || attackerPlayerSlotPosition+counter<noOfSlots)
        {
            //checks if the attacker slot position has a previous and a next slot
            if(attackerPlayerSlotPosition-counter>=0 && attackerPlayerSlotPosition+counter<noOfSlots)
            {
                //checks if both the slots has a player in it to attack
                if((slotArray[attackerPlayerSlotPosition+counter].playerNo!=-1)&&(slotArray[attackerPlayerSlotPosition-counter].playerNo!=-1))
                {
                    //updates the foundClosestPlayer to true
                    foundClosestPlayer=true;
                    
                    //gives an option to the player to attack either the previous player or the next player
                    printf("There are 2 closest slots to attack\nPress 1 to attack precious slot\nPress 2 to attack next slot\n");
                    int slotChoice;
                    scanf("%d",&slotChoice);
                    
                    //if wrong input then re enter the choice
                    while(!(slotChoice==1 || slotChoice==2))
                    {
                        printf("Wrong Choice Entered\nRe-enter your choice: ");
                        scanf("%d",&slotChoice);
                    }
                    
                    //checks if the user wanted option 1 to attack previous player
                    if(slotChoice==1)
                    {
                        attackedPlayerSlotPosition=attackerPlayerSlotPosition-counter;
                    }
                    else{
                        //if the user wanted to attack the next player
                        attackedPlayerSlotPosition=attackerPlayerSlotPosition+counter;
                    }
                    
                }
                //checks if the previous slot has a player in it
                else if(slotArray[attackerPlayerSlotPosition-counter].playerNo!=-1)
                {
                    //updates the foundClosestPlayer to true
                    foundClosestPlayer=true;
                    
                    //updates the attackedPlayerSlotPosition
                    attackedPlayerSlotPosition=attackerPlayerSlotPosition-counter;
                }
                else if(slotArray[attackerPlayerSlotPosition+counter].playerNo!=-1)
                {
                    //updates the foundClosestPlayer to true
                    foundClosestPlayer=true;
                    
                    //updates the attackedPlayerSlotPosition
                    attackedPlayerSlotPosition=attackerPlayerSlotPosition+counter;
                }
            }
            //checks if the attacker slot position has a previous slot possible
            else if(attackerPlayerSlotPosition-counter>=0)
            {
                //checks if the previous slot has a player to attack
                if(slotArray[attackerPlayerSlotPosition-counter].playerNo!=-1)
                {
                    //updates the foundClosestPlayer to true
                    foundClosestPlayer=true;
                    
                    //updates the attackedPlayerSlotPosition
                    attackedPlayerSlotPosition=attackerPlayerSlotPosition-counter;
                }
            }
            //checks if the attacker slot position has a next slot possible
            else if(attackerPlayerSlotPosition+counter<noOfSlots)
            {
                //checks if the next slot has a player in it to attack
                if(slotArray[attackerPlayerSlotPosition+counter].playerNo!=-1)
                {
                    //updates the foundClosestPlayer to true
                    foundClosestPlayer=true;
                    
                    //updates the attackedPlayerSlotPosition
                    attackedPlayerSlotPosition=attackerPlayerSlotPosition+counter;
                }
            }
        }
        //increments the counter
        counter++;
    }
    return slotArray[attackedPlayerSlotPosition].playerNo;
}


//method to perform the actions
void performActions(player playerArray[],slot slotArray[],int noOfPlayers,int noOfSlots);

{
    //loop which runs throught the number of players
    //each player gets one chance
    for(int i=0;i<noOfPlayers;i++)
    {
        //boolean to store if the players turn was successful
        //if not successful then player does his turn again
        bool turnSuccessful=false;
        
        //Player gets his turn
        printf("%s : Please do your turn\n",playerArray[i].name);
        
        //player inputs his move
        printf("Enter 1 to attack the closest player\nEnter 2 to move to the previous slot\nEnter 3 to move to the next slot\n");
        int moveChoice;
        scanf("%d",&moveChoice);
        
        //checks if the choice entered was correct
        //if not takes an new input again
        while(!(moveChoice>=1 && moveChoice<=3))
        {
            printf("Wrong Choice Entered\nRe-enter your choice: ");
            scanf("%d",&moveChoice);
        }
        
        int playerSlotPosition=0;
        
        //finds the player position in the slotArray
        for(int j=0;j<noOfSlots;j++)
        {
            if(slotArray[j].playerNo==i)
            {
                playerSlotPosition=j;
            }
        }
        
        //checks the move taken by the user
        if(moveChoice==1)
        {
            //calls the method to return the closest player to be attacked
            int attackedPlayerNo=findClosestPlayer(i,slotArray,noOfSlots);
            
            //calls the method to implement the attack
            implementingAttack(playerArray, i, attackedPlayerNo);
            
            //updates the turnSuccessful
            turnSuccessful=true;
        }
        //checks if the move is to move previous
        else if(moveChoice==2)
        {
            //checks if the previous position is possible
            if(playerSlotPosition-1>=0)
            {
                //checks if the slot has a player
                if(slotArray[playerSlotPosition-1].playerNo==-1)
                {
                    //method to update the capabilities on moving the slot
                    updateCapabiltitesOnMovingSlot(playerArray, i, slotArray[playerSlotPosition-1].slotTypeNo);
                    
                    //updating the turnSuccessful
                    turnSuccessful=true;
                }
                else
                {
                    //prints a message if the previous slot was not possible
                    printf("Unable to move to the previous slot\n");
                }
            }
            else
            {
                //print a message if the previous slot was not possible
                printf("Unable to move to the previous slot\n");
            }
        }
        else
        {
            //checks if the next slot is possible i.e within bounds
            if(playerSlotPosition+1<noOfSlots)
            {
                //checks if the next slot is empty
                if(slotArray[playerSlotPosition+1].playerNo==-1)
                {
                    //calling the method to update the capabilities of the player
                    updateCapabiltitesOnMovingSlot(playerArray, i, slotArray[playerSlotPosition+1].slotTypeNo);
                    
                    //update the turn successful
                    turnSuccessful=true;
                }
                else
                {
                    //print a message if the next slot is not possible
                    printf("Unable to move to the next slot\n");
                }
            }
            else
            {
                //print a message if the next slot is not possible
                printf("Unable to move to the next slot\n");
            }
            
        }
        
        //if the turn was successful
        if(turnSuccessful)
        {
            //calling the method to print the details
            printDetails(playerArray, noOfPlayers);
        }
        else
        {
            //if unsuccessful then decrements the value of i
            //player i gets another chance to make a move
            i--;
        }
        
    }
}



//method to perform the actions
void performActions(player playerArray[],slot slotArray[],int noOfPlayers,int noOfSlots)
	
{
    //variables to store the attacker nd attacked player slot position
    int attackerPlayerSlotPosition=0;
    int attackedPlayerSlotPosition=0;
    
    //loop to find the position of the attacker
    for(int i=0;i<noOfSlots;i++)
    {
        if(slotArray[i].playerNo==attackerPlayerNo)
        {
            attackerPlayerSlotPosition=i;
        }
    }
    
    //boolean to store if the closest player has been found
    bool foundClosestPlayer=false;
    
    //counter to keep a track of the varaiable
    int counter=1;
    
    //runs loop until finds the closest enemy
    while(foundClosestPlayer!=true)
    {
        //checks if the attacker slot position has a previous or next slot
        if(attackerPlayerSlotPosition-counter>=0 || attackerPlayerSlotPosition+counter<noOfSlots)
        {
            //checks if the attacker slot position has a previous and a next slot
            if(attackerPlayerSlotPosition-counter>=0 && attackerPlayerSlotPosition+counter<noOfSlots)
            {
                //checks if both the slots has a player in it to attack
                if((slotArray[attackerPlayerSlotPosition+counter].playerNo!=-1)&&(slotArray[attackerPlayerSlotPosition-counter].playerNo!=-1))
                {
                    //updates the foundClosestPlayer to true
                    foundClosestPlayer=true;
                    
                    //gives an option to the player to attack either the previous player or the next player
                    printf("There are 2 closest slots to attack\nPress 1 to attack precious slot\nPress 2 to attack next slot\n");
                    int slotChoice;
                    scanf("%d",&slotChoice);
                    
                    //if wrong input then re enter the choice
                    while(!(slotChoice==1 || slotChoice==2))
                    {
                        printf("Wrong Choice Entered\nRe-enter your choice: ");
                        scanf("%d",&slotChoice);
                    }
                    
                    //checks if the user wanted option 1 to attack previous player
                    if(slotChoice==1)
                    {
                        attackedPlayerSlotPosition=attackerPlayerSlotPosition-counter;
                    }
                    else{
                        //if the user wanted to attack the next player
                        attackedPlayerSlotPosition=attackerPlayerSlotPosition+counter;
                    }
                    
                }
                //checks if the previous slot has a player in it
                else if(slotArray[attackerPlayerSlotPosition-counter].playerNo!=-1)
                {
                    //updates the foundClosestPlayer to true
                    foundClosestPlayer=true;
                    
                    //updates the attackedPlayerSlotPosition
                    attackedPlayerSlotPosition=attackerPlayerSlotPosition-counter;
                }
                else if(slotArray[attackerPlayerSlotPosition+counter].playerNo!=-1)
                {
                    //updates the foundClosestPlayer to true
                    foundClosestPlayer=true;
                    
                    //updates the attackedPlayerSlotPosition
                    attackedPlayerSlotPosition=attackerPlayerSlotPosition+counter;
                }
            }
            //checks if the attacker slot position has a previous slot possible
            else if(attackerPlayerSlotPosition-counter>=0)
            {
                //checks if the previous slot has a player to attack
                if(slotArray[attackerPlayerSlotPosition-counter].playerNo!=-1)
                {
                    //updates the foundClosestPlayer to true
                    foundClosestPlayer=true;
                    
                    //updates the attackedPlayerSlotPosition
                    attackedPlayerSlotPosition=attackerPlayerSlotPosition-counter;
                }
            }
            //checks if the attacker slot position has a next slot possible
            else if(attackerPlayerSlotPosition+counter<noOfSlots)
            {
                //checks if the next slot has a player in it to attack
                if(slotArray[attackerPlayerSlotPosition+counter].playerNo!=-1)
                {
                    //updates the foundClosestPlayer to true
                    foundClosestPlayer=true;
                    
                    //updates the attackedPlayerSlotPosition
                    attackedPlayerSlotPosition=attackerPlayerSlotPosition+counter;
                }
            }
        }
        //increments the counter
        counter++;
    }
    return slotArray[attackedPlayerSlotPosition].playerNo;
}
	

//method to print the details of the player
void printDetails(player playerArray[],int noOfPlayers)
	
{
    //loop to print all the player details
    for(int i=0;i<noOfPlayers;i++)
    {
        //prints the player  name, type and life points
        printf("%s\t(%s, %d)\n",playerArray[i].name,playerArray[i].type,playerArray[i].lifePoints);
    }
}
	

	
//method to set the capabilities of the players
void setCapabilities(player playerArray[],int playerNumber,int playerTypeChoice)
	

//method to update the capabalities when a player moves a slot
void updateCapabiltitesOnMovingSlot(player playerArray[],int playerNumber,int slotTypeMovedTo)
	

//method to implement the attack
void implementingAttack(player playerArray[],int attackerPlayerNo,int attackedPlayerNo)
	

	
	
	

