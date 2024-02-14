#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "list.h"
#include "convert.h"

const int Operations[] = {'+', '-', '*', '(', ')'};

// return -1 if the word is not an operator
// return 0 if the word contains '+'
//        1                      '-'
//        2                      '*'
//        3                      '('
//        4                      ')'
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

#ifdef TEST_CONVERT


int precCheck(int);

int precCheck(int operator)
{
  //printf("IS THIS THING WORKING - precCheck");
    if(operator == 0 || operator == 1)
    {
      //printf("OP IS + or -");
      return 1;
    }
    else if(operator == 2)
    {
      //printf("op is *");
      return 2;
    }
    else
    {
      return -1;
    }
}
bool convert(List * arithlist)
{
  if (arithlist == NULL)
    {
      return true;
    }
  if ((arithlist->head) == NULL)
    {
      return true;
    }

  ListNode * current = NULL;
  current = arithlist->head;

  List * conStack = malloc(sizeof(List)); 
  conStack->head = NULL;
  conStack->tail = NULL;

  int operator;
  char * opStack[WORDLENGTH]; 
  int stackNum = -1;

  if(isOperator(current->word) != -1)
  {
    stackNum = stackNum + 1;
    opStack[stackNum] = current->word;
    current = current->next;
    addNode(conStack, current->word);
    //printf("MOST RECENT CONSTACK ADDITION: %s", conStack->tail->word);
    conStack->head = conStack->tail;
    current = current->next;
  }
  else
  {
    addNode(conStack, current->word);
    //printf("MOST RECENT CONSTACK ADDITION: %s", conStack->tail->word);
    conStack->head = conStack->tail;
    current = current->next;
  }
  
  while(current != NULL)
  {
    operator = isOperator(current->word);
    //printf("operator val: %d\n", operator);
    if(operator == -1)
    {
      addNode(conStack, current->word);
      //printf("MOST RECENT CONSTACK ADDITION: %s", conStack->tail->word);
    }
    else if(operator == 3)
    {
      stackNum = stackNum + 1;
      opStack[stackNum] = current->word;
    }
    else if(operator == 4)
    {
      while((isOperator(opStack[stackNum]) != 3))
      {
        addNode(conStack, opStack[stackNum]);
        //printf("MOST RECENT CONSTACK ADDITION: %s", conStack->tail->word);
        stackNum = stackNum - 1;
      }

      stackNum = stackNum - 1;
      //return true;
    }
    if(operator >= 0 && operator <= 2)
    {
      while(precCheck(operator) <= precCheck(isOperator(opStack[stackNum])))
      {
        //return true;
        addNode(conStack, opStack[stackNum]);
        //printf("MOST RECENT CONSTACK ADDITION: %s", conStack->tail->word);
        stackNum = stackNum - 1;
      }
      stackNum = stackNum + 1;
      opStack[stackNum] = current->word;
    }

    current = current->next;
  }

  while(stackNum > -1)
  {
    addNode(conStack, opStack[stackNum]);
    //printf("MOST RECENT CONSTACK ADDITION: %s", conStack->tail->word);
    stackNum = stackNum - 1;
  }

  //commented block below is just for printing
  
  /*/PRINTING CODE START
  printf("printListNode: ");
  ListNode * p = conStack->head;
  while (p != NULL)
    {
      printf("%s ", p -> word);
      p = p -> next;
    }
  printf("\n");

  //PRINTING CODE END*/

  ListNode * temp = conStack->head;
  current = arithlist->head;

  while(current->next != NULL) //note to self: delete list also deletes arithilst pointer so arithlist will be deleted manually to preserve List * pointer
  {
    temp = current;
    current = current->next;
    free(temp);
  }

  arithlist->head = conStack->head;
  arithlist->tail = conStack->tail;
  free(current);
  free(conStack);

  return true;
}
#endif
