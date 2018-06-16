// Programmer: Sarah Faust

// TA name: Shenghui

// Programming Assignment #1

// Date: Oct. 5 2013

// This is a Hangman game. A file provided by the user will contain
//the list of words for the user to guess. The words are stored into an
//array and one of the words chosen at random. A series of dashes represent
//the length of the word. If the user makes 9 mistakes in guessing the 
//letters in the word, then they lose.
//FILE MUST HAVE ONE WORD PER LINE

#import <stdio.h>
#import <stdlib.h>

int get_random(int limit);
void print_guessed_letters(char *guesses, int length);

int main()
{
        //The game is introduced to the user
        printf("Howdy! Wanna play Hangman? (y/n)  ");
        char playAn = 'n';
        scanf("%c",&playAn);


        //count counts the number of lines
        int count = 0;
	//words is the array list words will be chosen from
        char aim[20][20];



        if(playAn=='y')
        {
        	//gets the file name from the user and opens it as copier
        	printf("What is the name of the word list file? ");
        	char fileName[10];
        	scanf("%s",fileName);
        	FILE *copier;
        	copier = fopen(fileName, "r");
        	if(copier == NULL)
        	{
        		printf("The file doesn't exist.\n");
        		exit(0);
        	}

        	//c is the character being read from the file
        	char c;
   	     	c = fgetc(copier);
   	     	while(c != EOF)
   	     	{
   	     		//the file is read one character at a time 
   	     		//and printed to the screen
   	     		c = fgetc(copier);
   	     		if (c=='\n')
   	     		{
   	     			//count keeps track of new line characters
   	     			count++;
   	     		}
   	     	}

   	     	//goes all the way back to the 
   	     	//begining of the file to reread it.
   	     	rewind(copier);
        	
        	//copies each word into the array list
        	int i;
        	for(i=0; i<count; i++)
        	{
        		fgets(aim[i], 20, copier);
        	}
        	fclose(copier);
        }

        //the game is replayed however many times the user wants
        while(playAn=='y')
        {	
        	//a random number that represent an index is chosen
                int pick = get_random(count);
        	// the chosen word is at aim[pick]
        	
        	//a series of dashes are presented to the user
        	//representing the length of the word
        	char dash[20];
        	int p;
		int length = strlen(aim[pick]);
        	for(p=0; p<(length-1); p++)
        	{
        		aim[pick][p] = toupper(aim[pick][p]);
        		dash[p]='-';
        	}
        	dash[length-1]='\0';
        	
        	//guess is the letter the user chooses
        	char guess;
        	int strikes=0;
        	char pguesses[20];
        	int pgcount=0;
        	
        	//the game itself plays in a loop
        	char finished='n';
        	while((finished=='n')&&(strikes!=9))
        	{
        		//the dashes that represent the mystery letters are displayed
        		printf("\n%s\n\n",dash);

			//the user makes a guess
        		printf("Guess a letter: ");
			guess=getchar();
        		scanf("%c",&guess);
        		
        		guess = toupper(guess);
  		
        		//the guess is stored into the past guesses array
        		pguesses[pgcount]=guess;
        		pgcount++;

        		//the character is searched for in the picked word
        		char *location;
			int find=1;
       			location = strchr(aim[pick], guess);
        		if(location==NULL)
				find = 0;       		

        		if((int)find==0)
        		{
        		    printf("The word doesn't contain that letter.\n");
			    //a strick is counted against the user
        		    strikes++;
			   //the game ends once the user has 9 strikes
        		    if(strikes==9)
        		    	    printf("You Lose.\n");
        		}
        		
        		if((int)find==1)
        		{
        			printf("The chosen word contains that letter!");
   				//a pointer grabs the location of that letter
        			char *location;
        			location = strchr(aim[pick], guess);
        			while(location!=NULL)
        			{
        				//as long as the letter continues to be 
        				//found in the guessed word, dash will
        				//be updated
        				int in = location-(aim[pick]);
        				dash[in]=guess;
        				location=strchr(location+1, guess);
        			}
        		}
        		
        		//checks to see if there are anymore '-' in dash
        		finished='y';
        		int k;
			int len=strlen(dash);
        		for(k=0; k<len; k++)
        		{
        			if((strchr(dash,'-'))!=NULL)
        				finished='n';
        		}
        		if(finished=='y')
        			printf("You Won!\n");
        		
        		
        		print_guessed_letters(pguesses, pgcount);
        		
        		
        	}

                //they are told the picked number and asked if they want to play again
                printf("The correct answer is %s", aim[pick]);
                playAn='n';
                printf("Would you like to play again? (y/n) ");
                playAn=getchar();
                scanf("%c",&playAn);
		if(playAn=='y')
		{
			int j;
		        for(j=0; j<20;j++){
            		    pguesses[j]='\0';
        		}

		}
			
        }
        //signifies the end of the program
        printf("\nThanks for playing!\n\n");
        return 0;
}

//Pre: the lines in the file must have been counted and stored in limit
//Post: a random number is picked based off of limit
int get_random(int limit)
{
	//random numbers will be made based on time
        srand((int)(time(NULL)));
        int pick = (int)(rand()%(limit));
        return pick;
}

//Pre: user guesses must have stored into array guesses and its length noted
//Post: the guesses are printed for the user
void print_guessed_letters(char *guesses, int length)
{
	//their guesses are printed out for them
        printf("\nYour guesses were: ");
        int j;
        for(j=0; j<=length;j++){
        	printf("%c ",guesses[j]);
        }
        printf("\n");
        		
}

