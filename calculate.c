#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calculate.h"

const int Operations[] = {'+', '-', '*'};

// return -1 if the word is not an operator
// return 0 if the word contains '+'
// return 1 if the word contains '-'
// ...
int isOperator(char * word)
{
  int ind;
  int numop = sizeof(Operations) / sizeof(int);
  for (ind = 0; ind < numop; ind ++)
    {
    char *loc = strchr(word, Operations[ind]);
    if (loc != NULL && !isdigit(loc[1]))
	{
	  return ind;
	}
    }
  return -1;
}

#ifdef TEST_CALCULATE
bool calculate(List * arithlist)
{
  //printf("IS THIS THING WORKING? - CALCULATE\n");
  if (arithlist == NULL)
    {
      return true;
    }
  if ((arithlist -> head) == NULL)
    {
      return true;
    }

    ListNode * current = arithlist->head;
    ListNode * priorNode = NULL;
    int newNum;

    int constantChecker = 0;
    int opChecker = 0;
    int listLength = 0;
    
    while(current != NULL)
    {
      if(isOperator(current->word) == -1)
      {
        constantChecker++;
      }
      current = current->next;
      listLength++;
    }
    
    current = arithlist->head;

    while(current != NULL)
    {
      if(isOperator(current->word) >= 0)
      {
        opChecker++;
      }
      current = current->next;
    }

    if(opChecker == listLength) //checks if the lists is made up of just operators
    {
      return false;
    }

    if (opChecker != (constantChecker - 1)) //note to self: there will always be n-1 operators! n being the number of constants
    {
      return false;
    }

    current = arithlist->head;


    while(current != NULL)
    {
      if (isOperator(current->word) == -1)
      {
        //printf("value of current->word is: %s\n", current->word);
        current = current->next;
      }
      else if (isOperator(current->word) == 0) ////////adding
      {
        //printf("value of current->word is: %s\n", current->word);
        priorNode = current->prev;
        if (priorNode == NULL || priorNode->prev == NULL || (isOperator(priorNode->word) != -1) || isOperator(priorNode->prev->word) != -1)
        {
          return false;
        }

        newNum = atoi(priorNode->word) + atoi(priorNode->prev->word);
        deleteNode(arithlist, priorNode->prev);
        deleteNode(arithlist, priorNode);
        sprintf(current->word, "%d\n", newNum);
        //printf("current-> word is now: %s\n", current->word);
        //printf("newNum value plus: %d\n", newNum);
        current = arithlist->head;
        //printf("arithlist-> head (current) is now: %s\n", current->word);
      }
      else if (isOperator(current->word) == 1) /////////subtracting
      {
        //printf("value of current->word is: %s\n", current->word);
        //printf("NEGATIVE IN PROGRESS\n");
        priorNode = current->prev;
        if (priorNode == NULL || priorNode->prev == NULL || (isOperator(priorNode->word) != -1) || isOperator(priorNode->prev->word) != -1)
        {
          return false;
        }

        newNum = atoi(priorNode->prev->word) - atoi(priorNode->word);
        deleteNode(arithlist, priorNode->prev);
        deleteNode(arithlist, priorNode);
        sprintf(current->word, "%d\n", newNum);
        //printf("current-> word is now: %s\n", current->word);
        //printf("newNum value minus: %d\n", newNum);
        
        current = arithlist->head;
      }
      else{
        //printf("value of current->word is: %s\n", current->word);

        priorNode = current->prev;
        if (priorNode == NULL || priorNode->prev == NULL || (isOperator(priorNode->word) != -1) || isOperator(priorNode->prev->word) != -1)
        {
          return false;
        }

        newNum = atoi(priorNode->word) * atoi(priorNode->prev->word);
        deleteNode(arithlist, priorNode->prev);
        deleteNode(arithlist, priorNode);
        sprintf(current->word, "%d\n", newNum);
        //printf("current-> word is now: %s\n", current->word);
        //printf("newNum value multiplying: %d\n", newNum);

        current = arithlist->head;
        
      
      }
  return true;
}
#endif
