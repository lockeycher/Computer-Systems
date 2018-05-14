#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRING_LEN 20 /*Assumed char array len */
#define NUMBER_LEN 3


void enterName(char* nPtr)
{
  printf("Your name: ");
  fgets(nPtr,STRING_LEN,stdin);
}


void enterAge(int* agePtr)
{
  char numberText[NUMBER_LEN];

  printf("Your age: ");
  fgets(numberText,NUMBER_LEN,stdin);
  *agePtr=strtol(numberText,0,0);
}


void enterFavoriteColor (const char* itemNamePtr, char* entryPtr)
{
  printf("Favorite color for %s.",itemNamePtr);
  fgets(entryPtr,STRING_LEN,stdin);
}


void printInfo (char* nameP, int y, char* carCP,char* houseCP)
{
  char text[STRING_LEN];

  snprintf(text,STRING_LEN,"%s who’s %d yrs old",nameP,y);
  printf ("%s likes car color %s",text,carCP);

  if(strncmp(carCP,houseCP,STRING_LEN) == 0)
    puts("They like same color for houses");
  else
    printf("They like house color %s",houseCP);
}


int main ()
{
  char name[STRING_LEN];
  int age;
  char carColor[STRING_LEN];
  char houseColor[STRING_LEN];

  enterName(name);
  enterAge(&age);
  enterFavoriteColor("car",carColor);
  enterFavoriteColor("house",houseColor);
  printInfo(name,age,carColor,houseColor);
  return(EXIT_SUCCESS);
}
