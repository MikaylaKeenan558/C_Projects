#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

void OregonTrail(void);//first game
int Football(void);//second game
void TicTacToe(void);//third game

int main(void){ //game Picker
int gameChoice;	
char goagain[10];

	do{	
		printf("\nWhat would you like to play?\n\t1. The Oregon Trail\n\t2. Football Kicker Simulation\n\t3. TicTacToe\n\t4. Exit\nChoice: ");
		scanf("%d",&gameChoice);
		
		do{
			switch(gameChoice){
			case 1: 
				OregonTrail();
				break;
			case 2:
				Football();
				break;
			case 3:
				TicTacToe();
				break;
			case 4:
				printf("Thanks for playing!");
				goagain[0] = 'n';
				break;
			}
			}while (gameChoice != 1 && gameChoice != 2 && gameChoice != 3 && gameChoice != 4);
			
			do{
				printf("\n\nWould you like to try a different game? (y/n): ");
				scanf(" %c",&goagain[0]);
			}while (goagain[0] != 'n' && goagain[0] != 'y');
	
		}while (goagain[0] == 'y');
}

//FIRST GAME START
int classfunc(int[], int, int[]);//function 1
int storefunc(double, int, int[]);//function 2
void wagonfunc(int[], int[]);//function 3
void deathsfunc(int[], int[], int[],char[],char[], char[]);//function 4
void statsfunc(int, int, int, char[],char[], char[], int[], int[]);//function 5
int restfunc(int,int[],int[], char[],char[],char[]);//function 6


void OregonTrail(void){ //Game 1
	char fam1[50], fam2[50], fam3[50];
	int health[]={100, 100, 100, 100};
	int supplies[]={0, 0, 0};
	int randFoodAte,randHealthLost1, randHealthLost2, randHealthLost3, randHealthLost4;
	int day=1, mile=0;
	int money=0, class[]={0};
	int gameloop1;
	int endGame=0;
	int randNum,randCrossCost,randDayLost;
	int rivercross,score=0;
	int deathcheck[]={1,1,1};

	srand(time(NULL));
	
	printf("Welcome to The Oregon Trail\n");
	printf("This program simulates a trip over The Oregon Trail from Independence, Missouri\n");
	printf("to Oregon City, Oregon. Starting in April 1847 you and your family will cover\n");
	printf("the 2040 mile Oregon Trail in 5-6 months --- if you make it alive.\n\n");
	
	printf("What are the names of your family of three?\n\t1. ");
	scanf("%s",fam1);
	printf("\t2. ");
	scanf("%s",fam2);
	printf("\t3. ");
	scanf("%s",fam3);
	
	money = classfunc(class,money,supplies);
	
	printf("\n---------------------------------\
			\nWelcome to Independce, Missouri!\
			\n---------------------------------\n");
	double location=1; //location price increase multiplier at first location multiplier is 1 second 1.2 third 1.4
	money = storefunc(location, money, supplies);
	
	//start game loop 1
for (mile=0;mile<2040;){
	if(endGame!=1){
		do{
		statsfunc(money,day,mile,fam1,fam2,fam3,health,supplies);
		
		printf("\n\nWhat do you want to do?\
		\n\t1. Keep going.\
		\n\t2. Stop to Rest and use Medicine.\
		\n\t3. Repair Wagon.\nInput: ");
		scanf("%d",&gameloop1);
	
		switch (gameloop1){
			case 1:
			printf("You continue towards Oregon ");
			day=day+5;
			mile=mile+120;
			
			
			randFoodAte= (rand() %30)+5;
			supplies[0]=supplies[0]-randFoodAte;
			if (supplies[0] < 0){//reset to 0 if negative
				supplies[0]=0;}
			
			randHealthLost1= (rand() %25)+1;
			health[0]= health[0]-randHealthLost1;
			
			randHealthLost2= (rand() %25)+1;
			health[1]= health[1]-randHealthLost2;
			
			randHealthLost3= (rand() %25)+1;
			health[2]= health[2]-randHealthLost3;
			
			randHealthLost4= (rand() %15)+1;
			health[3]= health[3]-randHealthLost4;
			break;
			
			case 2:	//use meds and rest
				
				day = restfunc(day,health,supplies,fam1,fam2,fam3);

				break;
				
			case 3: //repair wagon
				wagonfunc(supplies,health);
				break;
			}
			
			if (health[0]<=0 && health[1]<=0 && health[2]<=0){// everyone is dead endig
			printf("but your family has all succumbed to the Oregon trail and everyone has passed away.");
			endGame=1;
			break; //locks user out of rest of game
			}
					
			if (health[3]<=0){ // wagon health is at zero = wagon death ending
				printf("\nYour Wagon has broken down.");
				
				wagonfunc(supplies,health);
				
				if (health[3]<=0){//if wagon health is 0 everyone dies
					printf("Your family breaks down in the wagon and try as you may to fix the wagon you cannot seem to get it working again.\n\
					Your family sets out to walk to the nearest fort. You are faced with the fate of the seasons and with only the food you were able to carry.\n\
					Unfortunately, eventually your entire family runs out of food and dies of starvation.");
					endGame=1; //locks user out of rest of game
				}
			break;
			}
				
			if (supplies[0]<=0){ //if the food runs out each fam member loses health
				
				printf("\n\nOh No! Your family is out of food! Everyone is getting sick and hungry.\n");
				
				randHealthLost1= (rand() %40)+10;
				health[0]= health[0]-randHealthLost1;
				
				randHealthLost2= (rand() %40)+10;
				health[1]= health[1]-randHealthLost2;
			
				randHealthLost3= (rand() %40)+10;
				health[2]= health[2]-randHealthLost3;
			}
			
			deathsfunc(deathcheck,supplies,health,fam1,fam2,fam3);

		}while (gameloop1 !=1);
		
		if (health[0]>0 || health[1]>0 || health[2]>0){
			if (mile == 480){ //first landmark store 1
				printf("\n---------------------------------\
				\nWelcome to Chimney Rock!\
				\n---------------------------------");
				printf("\nYou are 480 miles into your journey. ");
				location =1.2;
				
				money=storefunc(location,money,supplies);
				}
			
			if (mile == 840){ //second landmark river crossing 1
				printf("\n---------------------------------\
				\nWelcome to The Snake River Crossing!\
				\n---------------------------------");
				printf("\nYou have reached the Snake River Crossing at 840 miles into the journey. ");
				printf("\nThe river is 300ft across and 4ft deep.\nHow do you want to get across the river? \n\t1. Ford -- Try to find a shallow part of the river and push the wagon across. \n\t2. Ferry -- Pay someone to ferry you across the river. \nInput: ");
				scanf("%d",&rivercross);
				
				switch (rivercross){
				case 1:
					randNum= (rand() %2)+1;
					switch (randNum){
					case 1:
						printf("You had no issues crossing.");
						break;
					case 2:
						randDayLost= (rand() %6)+1;
						printf("You got stuck in the mud and lost %d of your food and lost %d days.",supplies[0]-randDayLost,randDayLost);
						day=day+randDayLost;
						supplies[0]=supplies[0]-(3*randDayLost);
						break;
					}
					break;
					
				case 2:
					randCrossCost= (rand() %200)+100;
					printf("It costs %d to cross. You have $%d.",randCrossCost,money);
					if(money >= randCrossCost){
						money=money-randCrossCost;
						printf("\nYou now have $%d",money);
					}
					else {
						printf("You don't have enough money you must ford across.");
						randNum= (rand() %2)+1;
						switch (randNum){
							case 1:
								printf("You had no issues crossing.");
								break;
							case 2:
								randDayLost= (rand() %6)+1;
								printf("You got stuck in the mud and lost %d of your food and lost %d days.",supplies[0]-randDayLost,randDayLost);
								day=day+randDayLost;
								supplies[0]=supplies[0]-(3*randDayLost);
								break;
						}
					}
					break;
				}
			}
			
			if (mile == 1320){ //third landmark store 2
				printf("\n---------------------------------\
				\nWelcome to Fort Boise!\
				\n---------------------------------");
				printf("\nYou are 1320 miles into your journey. ");
				location =1.4;
				
				money=storefunc(location,money,supplies);
				}
			
			if (mile == 1800){ //fourth landmark river crossing 2
				printf("\n---------------------------------\
				\nWelcome to The Columbia River!\
				\n---------------------------------");
				printf("You have reached the Columbia river at 1800 miles into the journey. ");
				printf("\nThe river is 700ft across and 20ft deep.\nHow do you want to get across the river? \n\t1. Ford -- Try to find a shallow part of the river and push the wagon across. \n\t2. Ferry -- Pay someone to ferry you across the river. \nInput: ");
				scanf("%d",&rivercross);
				
				switch (rivercross){
				case 1:
					randNum= (rand() %4)+1;
					switch (randNum){
					case 1:
						printf("You had no issues crossing.");
						break;
					
					case 2:
						randDayLost= (rand() %5)+1;
						printf("You got stuck in the mud and %d of your food floated away and you lost %d days.",(supplies[0]-(randDayLost*3)),randDayLost);
						day=day+randDayLost;
						supplies[0]=supplies[0]-(3*randDayLost);
						if (supplies[0]<0){
							supplies[0]=0;}
						break;
					
					case 3:
						randDayLost= (rand() %8)+3;
						printf("Uh oh! The mud caught your family and %d of your food floated away and you lost %d days.",(supplies[0]-(randDayLost*3)),randDayLost);
						day=day+randDayLost;
						supplies[0]=supplies[0]-(3*randDayLost);
						if (supplies[0]<0){
							supplies[0]=0;}
						break;
					
					case 4:
						randDayLost= (rand() %10)+5;
						printf("Oh no! You got stuck in the mud. %d of your food floated down the river and you lost %d days.",(supplies[0]-(randDayLost*3)),randDayLost);
						day=day+randDayLost;
						supplies[0]=supplies[0]-(3*randDayLost);
						if (supplies[0]<0){
							supplies[0]=0;}
						break;
					}
					
					break;
					
				case 2:
					randCrossCost= (rand() %400)+200;
					printf("You have $%d and it costs $%d to cross. ",money,randCrossCost);
					if(money >= randCrossCost){
						money=money-randCrossCost;
						printf("\nYou now have $%d",money);
					}
					else {
						printf("You don't have enough money you must ford across.");
						randNum= (rand() %2)+1;
						switch (randNum){
							case 1:
								printf("\nYou had no issues crossing.");
								break;
							case 2:
								randDayLost= (rand() %6)+1;
								printf("\nYou got washed away in the river and %d of your food washed down stream and you lost %d days.",(supplies[0]-(randDayLost*3)),randDayLost);
								day=day+randDayLost;
								supplies[0]=supplies[0]-(3*randDayLost);
								break;
						}
					}
					break;
				}
			
			}
		}
	}
}//end of game when you hit oregon
		
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\nWelcome to Oregon City, Oregon!");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

	printf("\nYou finally arrived at Oregon City after 2040 long miles - Hooray!!\nA Real Pioneer!");
	
	if (class[0]==1){//score for banker *1
		score=score+1000*1; //1000 for making it to Oregon
		printf("\n\n\t 1000");
		
		if (health[0]>0){ //500 for fam1 alive
			score=score+500;
			printf("\n\t+ 500");
			}
			
		if (health[1]>0){  //500 for fam2 alive
			score=score+500;
			printf("\n\t+ 500");
			}
		if (health[2]>0){  //500 for fam3 alive
			score=score+500;
			printf("\n\t+ 500");
			}
			
		score=score+supplies[0]; //food points
		printf("\n\t+ %d",supplies[0]);
		score=score+supplies[1]*200; //med points
		printf("\n\t+ %d",supplies[1]*200);
		score=score+supplies[2]*150; //parts points
		printf("\n\t+ %d",supplies[2]*150);
		
		printf("\n\t-------\nScore is %d",score);
	}
	else {//score for farmer *3
		score=score+1000*3; //1000 for making it to Oregon
		printf("\n\n\t 3000");
		
		if (health[0]>0){ //500 for fam1 alive
			score=score+500;
			printf("\n\t+ 500");
			}
			
		if (health[1]>0){  //500 for fam2 alive
			score=score+500;
			printf("\n\t+ 500");
			}
		if (health[2]>0){  //500 for fam3 alive
			score=score+500;
			printf("\n\t+ 500");
			}
			
		score=score+supplies[0]; //food points
		printf("\n\t+ %d",supplies[0]);
		score=score+supplies[1]*200; //med points
		printf("\n\t+ %d",supplies[1]*200);
		score=score+supplies[2]*150; //parts points
		printf("\n\t+ %d",supplies[2]*150);
		
		printf("\n\t-------\nScore is %d",score);
	}
		
}

int classfunc(int class[], int money, int supplies[]){
	srand(time(NULL));
	
	printf("\nWhat type of traveler are you?\n\t1. Banker -- Start with $3000 (1 times score multiplier)\n\t2. Farmer -- Start with $1500 and 150 food (3 times score multiplier)\nInput: ");

	do{
		scanf("%d",&class[0]);
		switch (class[0]){
			case 1:
				money = 3000;
				break;
			case 2: 
				money = 1500;
				supplies[0]=150;
				break;
			default: 
				printf("That is not a valid option please choose again\n1.\tBanker\n2.\tFarmer\nInput: ");
		}
	}while (class[0] != 1 && class[0] !=2);
	
	return (money);
}

int storefunc(double location, int money, int supplies[]){
	int foodcost=5*location,medscost=200*location,partscost=150*location;
	int foodquant=0,medsquant=0,partsquant=0;
	int storeChoice,cost;
	int goagain=1;
	
	srand(time(NULL));
	
	do{
		printf("\nYou have $%d to spend. What would you like to buy?\
		\n\t1. Food -- $%d\
		\n\t2. Medicine -- $%d\
		\n\t3. Wagon Repair Parts -- $%d\
		\n\t4. Exit\
		\nInput: ",money,foodcost,medscost,partscost);
		do{
			scanf("%d",&storeChoice);
			switch(storeChoice){
				case 1://food
					printf("How much food? ");
					scanf("%d",&foodquant);
					cost=foodcost*foodquant;
					
					if (money >= cost) {
						supplies[0]=supplies[0]+foodquant;
						money=money-cost;				
						printf("You have $%d left and %d food\n\n",money,supplies[0]);
					}
					else {
					printf("You do not have enough money. You have $%d.\n\n",money);
					}
					break;
				case 2://medicine
					printf("How many Medicine packs? ");
					scanf("%d",&medsquant);
					cost=medscost*medsquant;
					
					if (money >= cost) {
						supplies[1]=supplies[1]+medsquant;
						money=money-cost;				
						printf("You have $%d left and %d Med Pack\n\n",money,supplies[1]);
					}
					else {
					printf("You do not have enough money. You have $%d.\n\n",money);
					}
					break;
				case 3: //repair parts
					printf("How many Parts? ");
					scanf("%d",&partsquant);
					cost=partscost*partsquant;
					
					if (money >= cost) {
						supplies[2]=supplies[2]+partsquant;
						money=money-cost;				
						printf("You have $%d left and %d Repair Parts\n\n",money,supplies[2]);
					}
					else {
					printf("You do not have enough money. You have $%d.\n\n",money);
					}
					break;
				case 4:
					break;
				default: 
					printf("That is not a valid option please choose again. ");
				}
		}while (storeChoice != 1 && storeChoice != 2 && storeChoice != 3 && storeChoice != 4);
	
		printf("Do you want to buy another item or start your journey to Oregon?\n\t1. Buy another Item\n\t2. Start the journey\nInput: ");
		scanf("%d",&goagain);
	}while (goagain == 1);
	
	return (money);
}

int restfunc(int day,int health[],int supplies[], char fam1[],char fam2[],char fam3[]){
	int restdays,famMemb,giveMeds;
	
	while(1){ //increasing health and decreasing food based on how long you rest
		printf("How many days do you want to rest?(1-10): ");
		scanf("%d",&restdays);
			if(restdays>0 && restdays<11){
				if(health[0]>0){
					health[0]=health[0]+(5*restdays);}
				if(health[1]>0){
					health[1]=health[1]+(5*restdays);}
				if(health[2]>0){
					health[2]=health[2]+(5*restdays);}
				
				supplies[0]=supplies[0]-(2*restdays);
				
				//if the food is less than zero resets it to zero
				if (supplies[0] < 0){
					supplies[0]=0;}
				day=day+restdays;
				break;
			}
			else{
				printf("Please pick a day between 1 and 10.\n");
			}
		}
		
		printf("\nThe rest was good for your family. ");
		if (health[0]<=0){ //check if fam1 is dead
			printf("\n\t%s is deceased.",fam1);}
		if (health[0]> 0){
			printf("\n\t%s has %d%% health.",fam1,health[0]);}
		
		if (health[1]<=0){ //check if fam2 is dead
			printf("\n\t%s is deceased.",fam2);}
		if (health[1]> 0){
			printf("\n\t%s has %d%% health.",fam2,health[1]);}
			
		if (health[2]<=0){ //check if fam3 is dead
			printf("\n\t%s is deceased.",fam3);}
		if (health[2]> 0){
			printf("\n\t%s has %d%% health.",fam3,health[2]);}
		
	do{ //giving medicine to one of 3 fam members
				printf("\n\nDo you want to give any of your family medicine (currently have: %d)? \n1. Yes\n2. No\nInput: ",supplies[1]);
				scanf("%d",&giveMeds);
				if (giveMeds == 1){
					printf("\nWho do you want to give the Medicine to? \n\t1. %s\n\t2. %s\n\t3. %s \nInput: ",fam1,fam2,fam3);
					scanf("%d",&famMemb);
					if (famMemb == 1 && health[0]>0 && supplies[1]>0){
						health[0]=health[0]+50;
						printf("\n%s now has %d%% health.\n", fam1, health[0]);
						supplies[1]=supplies[1]-1;
						famMemb=0;
					}
					else if (famMemb == 1 && health[0]<=0){
						printf("\nSadly %s is already deceased.\n",fam1);
					}					 
					else if (famMemb == 2 && health[1]>0 && supplies[1]>0) {
						health[1]=health[1]+50;
						printf("\n%s now has %d%% health.\n", fam2, health[1]);
						supplies[1]=supplies[1]-1;
						famMemb=0;
					}
					else if (famMemb == 2 && health[1]<=0){
						printf("\nSadly %s is already deceased.\n",fam2);
					}	
					else if (famMemb == 3 && health[2]>0 && supplies[1]>0){
						health[2]=health[2]+50;
						printf("\n%s now has %d%% health.\n.\n", fam3, health[2]);
						supplies[1]=supplies[1]-1;
						famMemb=0;
					} 
					else if (famMemb == 3 && health[2]<=0){
						printf("\nSadly %s is already deceased\n",fam3);
					}	
					else {
						printf("\nPlease try again. ");
					}
				}
			}while (giveMeds == 1);
				
return (day);
}

void wagonfunc(int supplies[], int health[]){
	srand(time(NULL));
	
	int usePart;
		printf("\nDo you want to repair your wagon (currently have: %d Part)? \n1. Yes\n2. No\nInput: ",supplies[2]);
		scanf("%d",&usePart);
		do{	
		if (usePart == 1 && supplies[2]>0){
			health[3]=health[3]+50;
			printf("Your wagon now has %d%% health.", health[3]);
			supplies[2]=supplies[2]-1;
		}
		else if (usePart == 1 && supplies[2]<=0){
			printf("You dont have any repair parts.");
			usePart = 2;
		}
		
		printf("\nDo you want to repair your wagon again? (currently have: %d Part)? \n1. Yes\n2. No\nInput: ",supplies[2]);
		scanf("%d",&usePart);
	}while (usePart == 1);
				
}

void deathsfunc(int deathcheck[],int supplies[], int health[],char fam1[],char fam2[], char fam3[]){
	srand(time(NULL));
	
	if (health[0]<=0 && supplies[0]<=0 && deathcheck[0]==1){ //if out of food and out of health starvation death
		printf("\n\n~~~~~~~~~~(X~X)~~~~~~~~~~");
		printf("\n%s has died of starvation",fam1);	
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~");
		deathcheck[0]=0;
	}
	if (health[1]<=0 && supplies[0]<=0 && deathcheck[1]==1){
		printf("\n\n~~~~~~~~~~(X~X)~~~~~~~~~~");
		printf("\n%s has died of starvation",fam2);
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~");
		deathcheck[1]=0;
	}
	if (health[2]<=0 && supplies[0]<=0 && deathcheck[2]==1){
		printf("\n\n~~~~~~~~~~(X~X)~~~~~~~~~~");
		printf("\n%s has died of starvation",fam3);
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~");
		deathcheck[2]=0;
	}
	
	if (health[0]<=0 && supplies[0]>=0 && deathcheck[0]==1){ //if have food and out of health dysentery death
		printf("\n\n~~~~~~~~~~(X~X)~~~~~~~~~~");
		printf("\n%s has died of dysentery",fam1);	
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~");
		deathcheck[0]=0;
	}
	if (health[1]<=0 && supplies[0]>=0 && deathcheck[1]==1){
		printf("\n\n~~~~~~~~~~(X~X)~~~~~~~~~~");
		printf("\n%s has died of dysentery",fam2);
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~");
		deathcheck[1]=0;	
	}
	if (health[2]<=0 && supplies[0]>=0 && deathcheck[2]==1){
		printf("\n\n~~~~~~~~~~(X~X)~~~~~~~~~~");
		printf("\n%s has died of dysentery",fam3);
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~");
		deathcheck[2]=0;			
	}
}

void statsfunc(int money, int day, int mile, char fam1[],char fam2[], char fam3[], int health[], int supplies[]) {
	printf("\n----------------------------------------------------");
	printf("\n\nDay = %d\t\tMiles Traveled = %d/2040\tMoney = $%d",day,mile,money);
	printf("\nFood = %d\tMedicine = %d\tRepair Parts = %d\n",supplies[0],supplies[1],supplies[2]);

	printf("\n\tWagon health = %d%%\n",health[3]);
	
	if (health[0]<=0){
		printf("\n\n\t%s is deceased.",fam1);}
	if (health[0]> 0){
		printf("\n\t%s has %d%% health.",fam1,health[0]);}
	
	if (health[1]<=0){
		printf("\n\t%s is deceased.",fam2);}
	if (health[1]> 0){
		printf("\n\t%s has %d%% health.",fam2,health[1]);}
	
	if (health[2]<=0){
		printf("\n\t%s is deceased.\n",fam3);}
	if (health[2]> 0){
		printf("\n\t%s has %d%% health.\n",fam3,health[2]);}
}

//END OF FIRST GAME



//SECOND GAME START
int KickAngle(int);//Function 7

int Football(void)//Game 2
{
	int fan;
	double points = -0.2;//starts with a losing score (will not make kick)
	
	do
	{
	printf("\n\n\nALERT! Important Question\n\nAre you a Pittsburgh Steelers Fan?\n(1) Yes\n(2) No\n");//get points if you are a steelers fan
	scanf("%d",&fan);
	}while (fan !=1 && fan !=2);//indefinitely checking for correct input
	if (fan == 1)
	{
		printf("\nGood choice... now onto the game at hand!\n\n\n\n");
		points = points + 0.1;
	}
	int season,power,angle;
	char again[0];
	//description of the game!!
	printf("You chose Football Kicker Simulator!!!\n\nThe objective is to choose the correct options in order to make the game winning field goal!!!");
	printf("\n\nYou are kicking a field goal from the 30-yard line, and you are in the center of the field.");
do//play game again??
{
	do
	{
	printf("\n\nWhich season is this game in?\n(1) Spring\n(2) Summer\n(3) Fall\n(4) Winter\n");//deciding which season game is in to predict the angle needed to make the kick due to the wind direction :)
	scanf("%d",&season);
	}while (1>season || season>4);//indefinitely checking for correct input
	switch(season)//switch case woot
	{
		case 1:
		printf("\n\nThe wind is currently at a high rate of speed in the West direction (You are kicking North)");
		angle = KickAngle(angle);//angle function to determine direction of kick
		if (angle == 3)
		{
			points = points + 0.2;//adding points is kicking in the right direction
		}
		else if (angle == 1)
		{
			points = points -0.2;
		}
		break;
		case 2:
		printf("\n\nThere is no wind!! Perfect day to be a kicker!");//no wind!!
		angle = KickAngle(angle);//call function
		if (angle == 3)
		{
			points = points - 0.2;
		}
		else if (angle == 1)
		{
			points = points -0.2;
		}
		break;
		case 3:
		printf("\n\nThe wind is currently at a high rate of speed in the East direction (You are kicking North)");//east wind
		angle = KickAngle(angle);//call function
		if (angle == 1)
		{
			points = points + 0.2;
		}
		else if (angle == 3)
		{
			points = points -0.2;
		}
		break;//break in every case!!
		case 4:
		printf("\n\nThe wind is currently at a high rate of speed in the West direction (You are kicking North)");
		angle = KickAngle(angle);//call function
		if (angle == 3)
		{
			points = points + 0.2;
		}
		else if (angle == 1)
		{
			points = points -0.2;
		}
		break;
		
	}
	
	
	do
	{
	printf("How much power do you want to kick with? (1-100): ");
	scanf("%d",&power);
	}while (power<1 || power>100);//indefinitely checking for correct input
	if (power >= 50)//plus points for more power
	{
		points = points + 0.1;
	}

	if (points <=0)
	{
	printf("\n\n\nYou have lost!! Oh no!\n\nMaybe next time you should wait before you talk bad about a kicker!");//that is too bad
	}
	else
	{
	printf("\n\n\nAnnnnnnndddddd it\'s goooooooood!!!!! YOU MADE IT!\n\n");//winner winner chicken dinner
	}

	do
	{
	printf("\n\nWould you like to try again? (y/n): ");
	scanf(" %c",&again[0]);
	}while (again[0] != 'n' && again[0] != 'y');//indefinitely checking for correct input
	
}while (again[0] == 'y');//play again

return 0;
}
int KickAngle(int angle)//function to determine the angle of the kick
{
	do
		{
		printf("\n\nAt what angle do you want to kick?\n(1) -30 degrees\n(2) 0 degrees\n(3) 30 degrees\n");
		scanf("%d",&angle);
		}while (angle <1 || angle>3);//check to make sure correct values entered
		return(angle);//return number
}
//END OF SECOND GAME

//THIRD GAME START
int winFunction(char , char , char[]);//Function 7
void TicTacToe(void)     
{ 
char  name1[50];  
char  name2[50];
char  xOrO1, xOrO2; 
int  numPlayer1, numPlayer2, numPlayer3, numPlayer4, numPlayer5, numPlayer6, numPlayer7, numPlayer8, numPlayer9;
char spot[50];
int a;

	printf("  \nWelcome to Tic-Tac-Toe!\n\n");
		  printf("        |     \t|\n"); 
		  printf("    1   |   2   |   3\n"); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    4   |   5   |   6\n"); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    7   |   8   |   9\n"); 
		  printf("      \t|     \t|\n\n");
		  
		  printf("What is the player one's name?\n");     //asks for player one’s name
		  scanf("%s", name1); 
		  printf("What is your player two's name?\n");    //asks for player two’s name
		  scanf("%s", name2);
		   
		  printf("Player one is: %s\n",name1);       //prints inputted values for both players
		  printf("Player two is: %s\n",name2);
		  
		  printf("%s, Choose your symbol: ",name1);    //choose your symbol for player 1
		  scanf(" %c", &xOrO1); 
		  printf("%s, Choose your symbol: ",name2);   //choose your symbol for player 2
		  scanf(" %c", &xOrO2);
		  while(xOrO1 == xOrO2)            //error check to see if symbols are different
		  {
		  printf("Sorry, you can't choose the same symbol. Try again.\n");
		  printf("%s, Choose your symbol: ", name1);
		  scanf(" %c", &xOrO1);
		  printf("%s, Choose your symbol: ", name2);
		  scanf(" %c", &xOrO2);
	  }
		  printf("The game has started.\n");            //start of the game
		  printf("Keep playing until all the boxes are taken.");
		  printf("%s, Choose your first move by typing in 1-9 corresponding to the boxes. ", name1);                                         //choose move by looking at the key
		  scanf("%d", &numPlayer1);
	      spot[1] = ' ';                                 //clears all spots on the board
	      spot[2] = ' ';
	      spot[3] = ' ';
	      spot[4] = ' ';
	      spot[5] = ' ';
	      spot[6] = ' ';
	      spot[7] = ' ';
	      spot[8] = ' ';
	      spot[9] = ' ';
		  switch(numPlayer1)                       //first move by player 1
		  {
		  case 1:
		  spot[1] = xOrO1;
		  spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 2:
	      spot[1] = spot[1];
		  spot[2] = xOrO1;
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 3:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = xOrO1;
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 4:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = xOrO1;
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 5:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = xOrO1;
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 6:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = xOrO1;
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 7:
		  spot[1] = spot[1];
		  spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = xOrO1;
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 8:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = xOrO1;
	      spot[9] = spot[9]; 
	   break;
		  case 9:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = xOrO1;
	  break;
  }
	 printf("        |     \t|\n");       //puts in pieces onto the board
		  printf("    %c   |   %c   |   %c\n", spot[1], spot[2], spot[3]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[4], spot[5], spot[6]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[7], spot[8], spot[9]); 
		  printf("      \t|     \t|\n\n");
	
	printf("%s, Choose your first move by typing in 1-9 corresponding to the boxes. \n", name2);  //player 2 chooses first move
		  scanf("%d", &numPlayer2);
		  a = winFunction(xOrO1, xOrO2, spot);         //function that checks for wins 
		  while(a == 1)   //if win from player 1, game over
		  {
			  printf("Player 1, %s, has won.\n", name1);
			  printf("Game Over\n");
			  exit(0);
		  }
		  
		  while(a == 2)   //if win from player 2, game over
		  {
			  printf("Player 2, %s, has won.\n", name2);
			  printf("Game Over\n");
			  exit(0);
          }

		  
		while(numPlayer1 == numPlayer2)     //if the player chooses a spot that’s already taken, then the player gets an error message
		{
		printf("Hey! You can't choose there. Your competitor has already chosen that spot.\n");
		printf("Please choose another spot.\n");
		scanf("%d", &numPlayer2);
	}
	
		switch(numPlayer2)              //first move by player 2
		  {
		  case 1:
		  spot[1] = xOrO2;
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 2:
		  spot[1] = spot[1];
	      spot[2] = xOrO2;
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 3:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = xOrO2;
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 4:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = xOrO2;
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 5:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = xOrO2;
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 6:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = xOrO2;
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 7:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = xOrO2;
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 8:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = xOrO2;;
	      spot[9] = spot[9];
	   break;
		  case 9:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = xOrO2;
	  break;
  }
		  printf("        |     \t|\n");             //puts in pieces onto a board
		  printf("    %c   |   %c   |   %c\n", spot[1], spot[2], spot[3]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[4], spot[5], spot[6]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[7], spot[8], spot[9]); 
		  printf("      \t|     \t|\n\n");
		  a = winFunction(xOrO1, xOrO2, spot); //function that checks for wins 
		  
		  
		  while(a == 1) //if win from player 1, game over
		  {
			  printf("Player 1, %s, has won.\n", name1);
			  printf("Game Over\n");
			  exit(0);
		  }
		  while(a == 2) //if win from player 2, game over
		  {
			  printf("Player 2, %s, has won.\n", name2);
			  printf("Game Over\n");
			  exit(0);
		  }
		  printf("%s, Choose your second move by typing in 1-9 corresponding to the boxes. \n", name1); 
		  scanf("%d", &numPlayer3);
		
		while(numPlayer3 == numPlayer2 ||numPlayer3 == numPlayer1) //if the player chooses a spot that’s already taken, then the player gets an error message
		{
		printf("Hey! You can't choose there. The space is already taken.\n");
		printf("Please choose another spot.\n");
		scanf("%d", &numPlayer3);
	}
		switch(numPlayer3)   //second move by player 1
		  {
		  case 1:
		  spot[1] = xOrO1;
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 2:
		  spot[1] = spot[1];
	      spot[2] = xOrO1;
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 3:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = xOrO1;
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 4:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = xOrO1;
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 5:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = xOrO1;
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 6:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = xOrO1;
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 7:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = xOrO1;
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 8:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = xOrO1;
	      spot[9] = spot[9];
	   break;
		  case 9:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = xOrO1;
	  break;
  }
	  printf("        |     \t|\n");                         //puts in pieces onto the board
		  printf("    %c   |   %c   |   %c\n", spot[1], spot[2], spot[3]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[4], spot[5], spot[6]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[7], spot[8], spot[9]); 
		  printf("      \t|     \t|\n\n");
		  a = winFunction(xOrO1, xOrO2, spot); //function that checks for wins 
		  while(a == 1) //if win from player 1, game over
		  {
			  printf("Player 1, %s, has won.\n", name1);
			  printf("Game Over\n");
			  exit(0);
		  }
		  while(a == 2)  //if win from player 2, game over
		  {
			  printf("Player 2, %s, has won.\n", name2);
			  printf("Game Over\n");
			  exit(0);
		  }
		  printf("%s, Choose your second move by typing in 1-9 corresponding to the boxes. \n", name2);
		  scanf("%d", &numPlayer4);
	  while(numPlayer4 == numPlayer1 || numPlayer4 == numPlayer2 || numPlayer4 == numPlayer3) //if the player chooses a spot that’s already taken, then the player gets an error message
		{
		printf("Hey! You can't choose there. That space is taken.\n");
		printf("Please choose another spot.\n");
		scanf("%d", &numPlayer4); 
	}
		switch(numPlayer4) //second move by player 2
		  {
		  case 1:  
		  spot[1] = xOrO2;
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 2:
		  spot[1] = spot[1];
	      spot[2] = xOrO2;
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 3:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = xOrO2;
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 4:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = xOrO2;
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 5:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = xOrO2;
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 6:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = xOrO2;
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 7:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = xOrO2;
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 8:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = xOrO2;;
	      spot[9] = spot[9];
	   break;
		  case 9:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = xOrO2;
	  break;
  }   
	   printf("        |     \t|\n");                //puts in pieces onto a new board
		  printf("    %c   |   %c   |   %c\n", spot[1], spot[2], spot[3]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[4], spot[5], spot[6]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[7], spot[8], spot[9]); 
		  printf("      \t|     \t|\n\n");
		  a = winFunction(xOrO1, xOrO2, spot);   //function that checks for wins 
		  while(a == 1)    //if win from player 1, game over
		  {
			  printf("Player 1, %s, has won.\n", name1);
			  printf("Game Over\n");
			  exit(0);
		  }
		  while(a == 2)   //if win from player 2, game over
		  {
			  printf("Player 2, %s, has won.\n", name2);
			  printf("Game Over\n");
			  exit(0);
		  }
	  printf("%s, Choose your third move by typing in 1-9 corresponding to the boxes. \n", name1);
		  scanf("%d", &numPlayer5);
	  while( numPlayer5 == numPlayer4 || numPlayer5 == numPlayer3 || numPlayer5 == numPlayer2 || numPlayer5 == numPlayer1) //if the player chooses a spot that’s already taken, then the player gets an error message
		{
		printf("Hey! You can't choose there. That space is taken.\n");
		printf("Please choose another spot.\n");
		scanf("%d", &numPlayer5);
  }
  switch(numPlayer5) //third move by player 1
		  {
		  case 1:
		  spot[1] = xOrO1;
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 2:
		  spot[1] = spot[1];
	      spot[2] = xOrO1;
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 3:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = xOrO1;
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 4:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = xOrO1;
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 5:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = xOrO1;
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 6:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = xOrO1;
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 7:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = xOrO1;
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 8:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = xOrO1;
	      spot[9] = spot[9];
	   break;
		  case 9:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = xOrO1;
	  break;
  }
	   printf("        |     \t|\n");    //puts in pieces onto a new board
		  printf("    %c   |   %c   |   %c\n", spot[1], spot[2], spot[3]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[4], spot[5], spot[6]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[7], spot[8], spot[9]); 
		  printf("      \t|     \t|\n\n");
		  a = winFunction(xOrO1, xOrO2, spot);    //function that checks for wins 
		  while(a == 1)   //if win from player 1, game over
		  {
			  printf("Player 1, %s, has won.\n", name1);
			  printf("Game Over\n");
			  exit(0);
		  }
		  while(a == 2)   //if win from player 2, game over
		  {
			  printf("Player 2, %s, has won.\n", name2);
			  printf("Game Over\n");
			  exit(0);
		  }
		  printf("%s, Choose your third move by typing in 1-9 corresponding to the boxes. \n", name2);
		  scanf("%d", &numPlayer6);
		  while(numPlayer6 == numPlayer5 || numPlayer6 == numPlayer4 || numPlayer6 == numPlayer3 || numPlayer6 == numPlayer2 || numPlayer6 == numPlayer1)  //if the player chooses a spot that’s already taken, then the player gets an error message

		{
		printf("Hey! You can't choose there. That space is taken.\n");
		printf("Please choose another spot.\n");
		scanf("%d", &numPlayer6);
  }
  switch(numPlayer6) //third move from player 2
		  {
		  case 1:
		  spot[1] = xOrO2;
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 2:
		  spot[1] = spot[1];
	      spot[2] = xOrO2;
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 3:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = xOrO2;
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 4:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = xOrO2;
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 5:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = xOrO2;
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 6:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = xOrO2;
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 7:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = xOrO2;
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 8:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = xOrO2;
	      spot[9] = spot[9];
	   break;
		  case 9:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = xOrO2;
	  break;
  }
	   printf("        |     \t|\n");     //puts in pieces onto a new board
		  printf("    %c   |   %c   |   %c\n", spot[1], spot[2], spot[3]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[4], spot[5], spot[6]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[7], spot[8], spot[9]); 
		  printf("      \t|     \t|\n\n");
		  a = winFunction(xOrO1, xOrO2, spot);  //function that checks for wins 
		  while(a == 1)     //if win from player 1, game over
		  {
			  printf("Player 1, %s, has won.\n", name1);
			  printf("Game Over\n");
			  exit(0);
			  
		  } 
		  while(a == 2)    //if win from player 2, game over
		  {
			  printf("Player 2, %s, has won.\n", name2);
			  printf("Game Over\n");
			  exit(0);
			  
		  }
		  printf("%s, Choose your fourth move by typing in 1-9 corresponding to the boxes. \n", name1);
		  scanf("%d", &numPlayer7);
		
		while(numPlayer7 == numPlayer6 || numPlayer7 == numPlayer5 || numPlayer7 == numPlayer4 || numPlayer7 == numPlayer3 || numPlayer7 == numPlayer2 || numPlayer7 == numPlayer1) //if the player chooses a spot that’s already taken, then the player gets an error message
		{
		printf("Hey! You can't choose there. That space is taken.\n");
		printf("Please choose another spot.\n");
		scanf("%d", &numPlayer7);
}
switch(numPlayer7)  //fourth move by player 1

		  {
		  case 1:
		  spot[1] = xOrO2;
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 2:
		  spot[1] = spot[1];
	      spot[2] = xOrO2;
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 3:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = xOrO2;
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 4:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = xOrO2;
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 5:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = xOrO2;
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 6:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = xOrO2;
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 7:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = xOrO2;
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 8:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = xOrO2;
	      spot[9] = spot[9];
	   break;
		  case 9:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = xOrO2;
	  break;
  }
	   printf("        |     \t|\n");      //puts in pieces onto a new board
		  printf("    %c   |   %c   |   %c\n", spot[1], spot[2], spot[3]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[4], spot[5], spot[6]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[7], spot[8], spot[9]); 
		  printf("      \t|     \t|\n\n");  
		  a = winFunction(xOrO1, xOrO2, spot);     //function that checks for wins 
		  while(a == 1)    //if win from player 1, game over
		  {
			  printf("Player 1, %s, has won.\n", name1);
			  printf("Game Over\n");
			  exit(0);
			  
		  }
		  while(a == 2)   //if win from player 2, game over
		  {
			  printf("Player 2, %s, has won.\n", name2);
			  printf("Game Over\n");
			  exit(0);
			  
		  }
		  printf("%s, Choose your fifth move by typing in 1-9 corresponding to the boxes. \n", name1);
		  scanf("%d", &numPlayer8);
		
		while(numPlayer8 == numPlayer7 || numPlayer8 == numPlayer6 || numPlayer8 == numPlayer5 || numPlayer8 == numPlayer4 || numPlayer8 == numPlayer3 || numPlayer8 == numPlayer2 || numPlayer8 == numPlayer1)   //if the player chooses a spot that’s already taken, then the player gets an error message
		{
		printf("Hey! You can't choose there. That space is taken.\n");
		printf("Please choose another spot.\n");
		scanf("%d", &numPlayer8);

  }
  switch(numPlayer8)  //fourth move by player 2
		  {
		  case 1:
		  spot[1] = xOrO1;
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 2:
		  spot[1] = spot[1];
	      spot[2] = xOrO1;
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 3:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = xOrO1;
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 4:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = xOrO1;
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 5:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = xOrO1;
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 6:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = xOrO1;
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 7:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = xOrO1;
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 8:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = xOrO1;
	      spot[9] = spot[9];
	   break;
		  case 9:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = xOrO1;
	  break;
  }
  printf("        |     \t|\n");      //puts in pieces onto a new board
		  printf("    %c   |   %c   |   %c\n", spot[1], spot[2], spot[3]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[4], spot[5], spot[6]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[7], spot[8], spot[9]); 
		  printf("      \t|     \t|\n\n");
		  a = winFunction(xOrO1, xOrO2, spot);   //function that checks for wins 
		  while(a == 1)     //if win from player 1, game over
		  {
			  printf("Player 1, %s, has won.\n", name1);
			  printf("Game Over\n");
			  exit(0);
		  }
		  while(a == 2)    //if win from player 2, game over
		  {
			  printf("Player 2, %s, has won.\n", name2);
			  printf("Game Over\n");
			  exit(0);
		  }
		  printf("%s, Choose your fifth move by typing in 1-9 corresponding to the boxes. \n", name2);
		  scanf("%d", &numPlayer9);
		while(numPlayer9 == numPlayer8 || numPlayer9 == numPlayer7 || numPlayer9 == numPlayer6 || numPlayer9 == numPlayer5 || numPlayer9 == numPlayer4 || numPlayer9 == numPlayer3 || numPlayer9 == numPlayer2 || numPlayer9 == numPlayer1)   //if the player chooses a spot that’s already taken, then the player gets an error message
		{
		printf("Hey! You can't choose there. That space is taken.\n");
		printf("Please choose another spot.\n");
		scanf("%d", &numPlayer9);
  }
  
  switch(numPlayer9)      //fifth move by player 1
		  {
		  case 1:
		  spot[1] = xOrO1;
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 2:
		  spot[1] = spot[1];
	      spot[2] = xOrO1;
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 3:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = xOrO1;
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 4:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = xOrO1;
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 5:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = xOrO1;
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 6:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = xOrO1;
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 7:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = xOrO1;
	      spot[8] = spot[8];
	      spot[9] = spot[9];
	      break;
		  case 8:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = xOrO1;
	      spot[9] = spot[9];
	   break;
		  case 9:
		  spot[1] = spot[1];
	      spot[2] = spot[2];
	      spot[3] = spot[3];
	      spot[4] = spot[4];
	      spot[5] = spot[5];
	      spot[6] = spot[6];
	      spot[7] = spot[7];
	      spot[8] = spot[8];
	      spot[9] = xOrO1;
	  break;
  }
    printf("        |     \t|\n");   //puts in pieces onto a new board
		  printf("    %c   |   %c   |   %c\n", spot[1], spot[2], spot[3]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[4], spot[5], spot[6]); 
		  printf("      \t|     \t|\n");
	printf("--------+-------+--------\n"); 
	      printf("        |     \t|\n"); 
		  printf("    %c   |   %c   |   %c\n", spot[7], spot[8], spot[9]); 
		  printf("      \t|     \t|\n\n");
		  a = winFunction(xOrO1, xOrO2, spot);   //function that checks for wins 
		  while(a == 1)     //if win from player 1, game over
		  {
			  printf("Player 1, %s, has won.\n", name1);
			  printf("Game Over\n");
			  exit(0);
		  }
		  while(a == 2)    //if win from player 2, game over
		  {
			  printf("Player 2, %s, has won.\n", name2);
			  printf("Game Over\n");
			  exit(0);
		}
		  
		  printf("You all have tied.\n"); //the game has tied when all the pieces are on the board
		  printf("Game over\n");    //game ends
		  }
//took this out

int winFunction(char xOrO1, char xOrO2, char spot[]) //function that scans for wins
{
	
	int a;
	if(spot[1] == xOrO1 && spot[5] == xOrO1 && spot[9] == xOrO1)
	{
		a=1;
	} 
	else if(spot[1] == xOrO1 && spot[4] == xOrO1 && spot[7] == xOrO1)
	{
		a=1;
	}
	else if(spot[3] == xOrO1 && spot[5] == xOrO1 && spot[7] == xOrO1)
	{
		a=1;
	}
	else if(spot[3] == xOrO1 && spot[6] == xOrO1 && spot[9] == xOrO1)
	{
		a=1;
	}
	else if(spot[7] == xOrO1 && spot[8] == xOrO1 && spot[9] == xOrO1)
	{
		a=1;
	}
	else if(spot[4] == xOrO1 && spot[5] == xOrO1 && spot[6] == xOrO1)
	{
		a=1;
	}
	else if(spot[1] == xOrO1 && spot[2] == xOrO1 && spot[3] == xOrO1)
	{
		a=1;
	}
else if(spot[1] == xOrO1 && spot[2] == xOrO1 && spot[3] == xOrO1)
	{
		a=1;
	}
if(spot[1] == xOrO2 && spot[5] == xOrO2 && spot[9] == xOrO2)
	{
		a=2;
	} 
	else if(spot[2] == xOrO1 && spot[4] == xOrO2 && spot[7] == xOrO2)
	{
		a=2;
	}
	else if(spot[3] == xOrO2 && spot[5] == xOrO2 && spot[7] == xOrO2)
	{
		a=2;
	}
	else if(spot[3] == xOrO2 && spot[6] == xOrO2 && spot[9] == xOrO2)
	{
		a=2;
	}
	else if(spot[7] == xOrO2 && spot[8] == xOrO2 && spot[9] == xOrO2)
	{
		a=2;
	}
	else if(spot[4] == xOrO2 && spot[5] == xOrO2 && spot[6] == xOrO2)
	{
		a=2;
	}
	else if(spot[1] == xOrO2 && spot[2] == xOrO2 && spot[3] == xOrO2)
	{
		a=2;
	}
else if(spot[1] == xOrO2 && spot[2] == xOrO2 && spot[3] == xOrO2)
	{
		a=2;
	}
		return (a);
}




//END OF THIRD GAME





