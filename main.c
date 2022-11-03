/***********************
* Name: Omer Bar
* ID: 315318766
* Assignment: ex_4
***********************/

#include <stdio.h>
#include <string.h>

#ifndef STRING_SIZE
#define STRING_SIZE 21 /// max word 20 letter with 1 extra '\0'
#endif
#ifndef OPTIONS
#define OPTIONS 16 /// clue + 15 options
#endif

#define MAX_TRYS STRING_SIZE + 6 ///MAX_TRYS is the size of the STRING_SIZE + 6 tries of failures
///magic char defines
#define UNDER_LINE '_'
#define SPACE ' '
#define DELIM ":,"
#define CLUE '*'
///max stages in the game
#define MAX_STAGES 6

///function declaration
void hangedman(int stage);
void SortStringArr(char options[][STRING_SIZE], int sizeArr);
void swapStrings(char string1[], char string2[]);
int strtok_ex(char str[], char delim[], char arr[][STRING_SIZE],char clue[], int sizeArr);
int isTheSame(char string1[], char string2[], int length);
int onlySpaces(char string1[]);

int main() {
    ///variable deceleration
    char input[OPTIONS*STRING_SIZE], options[OPTIONS][STRING_SIZE], clue[STRING_SIZE], gameWord[STRING_SIZE];
    char game[STRING_SIZE], usedLetters[MAX_TRYS], ch;
    int userChoice ,length, stage=1, flagOfCLUE=0, cp=0, usedINDEX=0, LetterCounter=0, flagCheckLetter=0, i,k;
    printf("Enter your words:\n");
    scanf("%[^\n]", input); //gets the string with the spaces
    ///initialized the options array with the string from the input
    k = strtok_ex(input, DELIM, options,clue ,OPTIONS); //and returning the size of the array
    SortStringArr(options, k);//sorting the string in the array
    printf("choose an option:\n");
    for(int i = 0; i < k; i++)
        printf("%d: %s\n",i + 1 ,options[i]);
    scanf("%d", &userChoice);
    ///if the userChoice is not define in the options
    if(userChoice > k || userChoice < 1)
        printf("Error!\n");
    else
    {
        strcpy(gameWord , options[userChoice - 1]);
        length = strlen(gameWord);
        ///initialize the array with _____ format
        for(i = 0; i < length; i++)
        {
            if(gameWord[i] == SPACE)
            {
                game[i] = SPACE;
            }
            else
            {
                game[i] = UNDER_LINE;
            }
        }
        game[i] = '\0'; //puts '\0' in the end of the string for easy print in %s printf function
        ///While loop that ends when IT IS GAME OVER!
        while(stage <= MAX_STAGES)
        {
            hangedman(stage); //prints the hangedman by stages
            if(stage == MAX_STAGES)
                break; //END GAME!
            printf("%s\n", game);
            ///if the player didnt asked for clue PRINT THE OPTION FOR CLUE
            if(flagOfCLUE == 0)
            {
                printf("do you want a clue? press -> *\n");
            }
            printf("The letters that you already tried:");
            for(int i = 0; i < LetterCounter;i++)
            {
                if(i == 0)
                {
                    printf(" %c", usedLetters[i]);//first letter print format
                }
                else
                    printf(", %c", usedLetters[i]);//every other letter print format
            }
            printf("\nplease choose a letter:\n");
            scanf(" %c", &ch); //player inputs
            ///if the player need's a clue PRINT CLUE
            if(ch == CLUE && flagOfCLUE == 0)
            {
                printf("the clue is: %s.\n", clue);
                flagOfCLUE = 1;
            }
            ///Search if the letter was tried
            for(int i = 0; i < LetterCounter;i++)
            {
                if(usedLetters[i] == ch)
                {
                    flagCheckLetter = 1;
                    printf("You've already tried that letter.\n");
                }
            }
            if(ch != CLUE && flagCheckLetter != 1)
            {
                ///check if the letter is in the gameWord
                for(int i = 0; i < length;i++)
                {
                    if(gameWord[i] == ch)
                    {
                        game[i] = ch; // update the game array
                    }
                    else
                    {
                        cp++; // counter that indicate if the game was not updated
                    }
                }
                ///game array did not update therefore the hangedman need to be rewriting in the new stage.
                if(cp == length) //the cp == length means the letter is not in the word.
                {
                    usedLetters[usedINDEX] = ch; //input the used letter to the usedLetter Array
                    usedINDEX++;
                    LetterCounter++;
                    stage++; // player failed to guess therefore the stage need to update
                    cp = 0; //reset the cp for next loop
                }
                    ///game array was update means the letter was correct
                else
                {
                    usedLetters[usedINDEX] = ch; //input the used letter to the usedLetter Array
                    LetterCounter++;
                    usedINDEX++;
                    cp = 0; //reset the cp for next loop
                }
            }
            ///compare if the chosen word is as the array word
            if(isTheSame(gameWord, game, length))
            {
                hangedman(stage);
                printf("The word is %s, good job!\n", gameWord);
                return 0; // exit game
            }
            flagCheckLetter = 0; //resets the flag for next input
        }
        ///GAME OVER!
        if(stage == MAX_STAGES)
        {
            printf("The word is %s, GAME OVER!\n", gameWord);
        }

    }
    return 0; //exit game
}

/******************
* Function Name:hangedman
* Input: int
* Output: NONE
* Function Operation: prints the hanged man by stages from 1-6
******************/
void hangedman(int stage)
{
    switch (stage)
    {
        case 1:
        {
            printf(" _________________\n"
                   "|                |\n"
                   "|                |\n"
                   "|                |\n"
                   "|                |\n"
                   "|                |\n"
                   "|________________|\n");
            return;
        }
        case 2:
        {
            printf(" _________________\n"
                   "|                |\n"
                   "|  **            |\n"
                   "|  **            |\n"
                   "|                |\n"
                   "|                |\n"
                   "|________________|\n");
            return;
        }
        case 3:
        {
            printf(" _________________\n"
                   "|                |\n"
                   "|  **        **  |\n"
                   "|  **        **  |\n"
                   "|                |\n"
                   "|                |\n"
                   "|________________|\n");
            return;
        }
        case 4:
        {
            printf(" _________________\n"
                   "|  --            |\n"
                   "|  **        **  |\n"
                   "|  **        **  |\n"
                   "|                |\n"
                   "|                |\n"
                   "|________________|\n");
            return;
        }
        case 5:
        {
            printf(" _________________\n"
                   "|  --        --  |\n"
                   "|  **        **  |\n"
                   "|  **        **  |\n"
                   "|                |\n"
                   "|                |\n"
                   "|________________|\n");
            return;
        }
        case 6:
        {
            printf(" _________________\n"
                   "|  --        --  |\n"
                   "|  **        **  |\n"
                   "|  **        **  |\n"
                   "|                |\n"
                   "| \\/\\/\\/\\/\\/\\/\\  |\n"
                   "|________________|\n");
            return;
        }
            ///no default is needed because the function cannot get any other input then 1 - 6,
            ///when the program is running
    }
}

/******************
* Function Name:strtok_ex
* Input: char arr[], char delim, char arr[][] , char clue[] ,int sizeArr
* Output: int
* Function Operation: set the string input inside an array of chars and return the size of the array
******************/
int strtok_ex(char str[], char delim[], char arr[][STRING_SIZE],char clue[], int sizeArr)
{
    int i = 0;
    char* token = strtok(str, delim);
    while (token != NULL && i < sizeArr)
    {
        ///saves the clue not in the ARRAY
        if(i == 0)
        {
            strcpy(clue, token);
            i++;
        }
        else if(onlySpaces(token)) // if the input is only spaces don't save in the array
        {
            strcpy(arr[i - 1], token);
            i++;
        }
        token = strtok(NULL, delim);
    }
    return i - 1; // size of the array
}

/******************
* Function Name:swapStrings
* Input: char string1[], char string2[]
* Output: NONE
* Function Operation: swap places of the given strings
******************/
void swapStrings(char string1[], char string2[])
{
    char temp[STRING_SIZE];
    strcpy(temp, string1);
    strcpy(string1, string2);
    strcpy(string2, temp);
}

/******************
* Function Name:SortStringArr
* Input: char options[][], int sizeArr
* Output: NONE
* Function Operation: gets an array of strings and sorts it in alphabetical order.
******************/
void SortStringArr(char options[][STRING_SIZE], int sizeArr)
{
    ///bubble sort algorithm
    for(int i = 0 ;i < sizeArr;i++)
    {
        for(int j = 0; j < sizeArr - 1 - i; j++)
        {
            if(strcmp(options[j], options[j + 1]) > 0)
            {
                swapStrings(options[j], options[j+1]); //swap the places
            }
        }
    }
}

/******************
* Function Name:isTheSame
* Input: char string1[], char string2[], int length
* Output: NONE
* Function Operation: check if a word is the same until given length
******************/
int isTheSame(char string1[], char string2[], int length)
{
    for(int i = 0; i < length;i++)
    {
        if(string1[i] != string2[i])
            return 0;
    }
    return 1;
}

/******************
* Function Name:onlySpaces
* Input: char string1[]
* Output: int
* Function Operation: check if the word is only spaces if it is return 0
******************/
int onlySpaces(char string1[])
{
    //check if the word is only "     "
    for(int i = 0; i < strlen(string1);i++)
    {
        if(string1[i] != SPACE)
        {
            return 1;
        }
    }
    return 0;
}

