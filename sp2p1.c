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
int main()
{
    //input the number of players
    printf("Enter the number of players: ");
    int noOfPlayers;
    scanf("%d",&noOfPlayers);
    while(!(noOfPlayers>0 && noOfPlayers<6))
    {
        printf("Maximum number of players is 6\nPlease re-enter your choice: ");
        scanf("%d",&noOfPlayers);
    }
    
    //make a player array to store the player information
    player playerArray[noOfPlayers];
    
    //loop to store the player information
    for(int i=0;i<noOfPlayers;i++)
    {
        //input the player name
        printf("Please enter the name of Player %d :",(i+1));
        scanf("%s",playerArray[i].name);
        
        //input the player type
        printf("Please enter the type of Player %d\n",(i+1));
        printf("Enter 1 for Elf\nEnter 2 for Human\nEnter 3 for Orge\nEnter 4 for Wizard\n");
        int playerTypeChoice=0;
        scanf("%d",&playerTypeChoice);
        
        //loop to check if input is correct
        //if not again asks for input
        while(!(playerTypeChoice>=1 && playerTypeChoice<=4))
        {
            printf("Wrong Choice Entered\nRe-enter your choice: ");
            scanf("%d",&playerTypeChoice);
            
        }
        
        strcpy(playerArray[i].type,playerTypes[playerTypeChoice-1]);
        
        //calling the method to set the capability of the player
        setCapabilities(playerArray, i,playerTypeChoice);
    }
    
    
    //input the number of slots
    printf("Please Enter the number of slots (Maximum is 20):");
    int noOfSlots;
    scanf("%d",&noOfSlots);
    
    //checks if number of slots is within range
    //if not takes another input
    while(!(noOfSlots>noOfPlayers && noOfSlots<=20))
    {
        printf("Number of slots selected is out of bound\nRe-enter the number of slots: ");
        scanf("%d",&noOfSlots);
    }
    
    //creates slot array to store information about the slots
    slot slotsArray[noOfSlots];
    
    //initialising the slot
    //initialising the slotTypeNo and PlayerNo to -1
    for(int i=0;i<noOfSlots;i++)
    {
        slotsArray[i].slotTypeNo=-1;
        slotsArray[i].playerNo=-1;
    }
    srand((unsigned int)time(NULL));
    
    
    //stores the slotType
    for(int i=0;i<noOfSlots;i++)
    {
        slotsArray[i].slotTypeNo=rand()%3;
        strcpy(slotsArray[i].slotType,slotType[slotsArray[i].slotTypeNo]);
    }
    
    
    //stores the playerNumber
    for(int i=0;i<noOfPlayers;i++)
    {
        //generates a random number
        int randomNumber=rand()%noOfSlots;
        
        //if the slot is not occupied by any player
        //then the player is allocated to the slot
        if(slotsArray[randomNumber].playerNo==-1)
        {
            slotsArray[randomNumber].playerNo=i;
        }
        else
        {
            //generating a random number
            randomNumber=rand()%noOfSlots;
            
            //loop runs until it finds a slot position which was empty and had no player in it
            while(!(slotsArray[randomNumber].playerNo==-1))
            {
                //generating random number
                randomNumber=rand()%noOfSlots;
                
            }
            
            //stores the player in the slot
            slotsArray[randomNumber].playerNo=i;
        }
        
    }
    //call the method to start the game
    performActions(playerArray, slotsArray, noOfPlayers, noOfSlots);
    
}

//method to perform the actions
void performActions(player playerArray[],slot slotArray[],int noOfPlayers,int noOfSlots)
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
