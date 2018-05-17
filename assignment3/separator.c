#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#define STRING_LEN 256 /*Assumed char array len */

struct		Word
{
     char*		    textPtr_;
     struct Word*	nextPtr_;
};


struct Word* obtainCommaSeparatedList (const char* string)
{
    struct Word*	toReturn	= NULL; // points to the "first" node 
    struct Word*	currentPtr	= NULL; // points to the "last" node

    while (1) // go through the list to find strings and comma
    {
         const char*	commaPtr	= strchr(string,',');
         struct Word*	temp	= (struct Word*)malloc(sizeof(struct Word));
          
         /*  checking node condition */
         if (toReturn == NULL) // if the list is empty, ctreate the first node
             {
                toReturn = temp;
                currentPtr = temp;
                temp -> nextPtr_ = NULL;
             }
             else
             {
                currentPtr -> nextPtr_ = temp;
                currentPtr = temp;
                temp -> nextPtr_ = NULL;
             }

         /* checking string condition */
         if  (commaPtr == NULL) //  Points to to end of string
         {
             /* allocate space for stringd copied */
             temp -> textPtr_ = (char*) malloc(strlen(string) + 1); 
             strncpy(temp -> textPtr_, string, strlen(string)); // copy the string up to the comma into this malloc-ed memory
            
             break;
         }
         else
         { 
             /* allocate space for stringd copied */
             temp -> textPtr_ = (char*) malloc(((commaPtr - string) + 1));
             strncpy(temp -> textPtr_, string,((commaPtr - string))); // copy the string up to the comma into this malloc-ed memory
	     
	     /* replace comma with "\0" */
	     char* replacePtr = strchr(temp -> textPtr_,',');
	     if (replacePtr != NULL)
	     {
	        replacePtr = '\0';
	     }
             string = commaPtr + 1;
        }

    }

    return(toReturn);
}

void printCommaSeparatedList (const struct Word* list)
{
    if (list != NULL)
        {
	    printf("\"%s\"\n", list -> textPtr_);
            printCommaSeparatedList (list -> nextPtr_);
        } else return;
}

void freeCommaSeparatedList (struct Word* list)
{
    if (list != NULL)
        {
	    freeCommaSeparatedList(list -> nextPtr_);
            list -> textPtr_ = NULL;
	    free(list);
        } else return;
}

int main() 
{
     
     char string[STRING_LEN];

     printf("Please enter a line of text with comma(,): ");
     fgets(string, STRING_LEN, stdin);

     // To get rid of the \n char that fgets() adds to the end of entered strings
     char*		cPtr	= strchr(string,'\n');
     if  (cPtr != NULL)
     {
         *cPtr = '\0';
     } 
        
     struct Word* list = obtainCommaSeparatedList(string);
     printCommaSeparatedList(list);
     freeCommaSeparatedList(list);
     return(EXIT_SUCCESS);
}
