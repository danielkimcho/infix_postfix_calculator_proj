#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// This function will: use fgets to go through the input file. It will store each line as a character array or "word".
// Then, it will call the addNode function to add a node to the doubly linked list.
bool readList(char * filename, List * arithlist)
{
  //printf("IS THIS THING WORKING - readlist\n");
  if (arithlist == NULL)
  {
    return false;
  }

  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL)
  {
    return false;
  }

  char * temp; //this will store the character/word that will then be passed to ListNode's "word" array
  temp = malloc(sizeof(char) * (WORDLENGTH+1));

  while (fgets(temp, WORDLENGTH + 1, fptr) != NULL)
  {
    if ((sizeof(temp)) >= (WORDLENGTH + 1)) //this if statement checks if the "word" is 11 or more characters long. The max word length is 10 including the null terminator therefore anything above or equal to 11 will not be tolerated
    {
      deleteList(arithlist);
      free(temp);
      fclose(fptr);
      return false;
    }
    addNode(arithlist, temp);
  }

  //deleteNode(arithlist, arithlist->tail);
  //deleteList(arithlist);

  //these commented statements below are to print out the linked lists, one from the head, one from the tail for verification!

  /*/PRINTING CODE START
  printf("printListNode: ");
  ListNode * p = arithlist->head;
  while (p != NULL)
    {
      printf("%s ", p -> word);
      p = p -> next;
    }
  printf("\n");

  //PRINTING CODE END*/

    /*/PRINTING CODE END 
  printf("tail printListNode: ");
  ListNode * p1 = arithlist->tail;
  while (p1 != NULL)
    {
      printf("%s ", p1 -> word);
      p1 = p1 -> prev;
    }
  printf("\n");

  //PRINTING CODE START*/
  free(temp);
  fclose(fptr);
  return true;
}

void deleteList(List * arithlist)
{
  //printf("IS THIS THING WORKING - deleteList\n");
  ListNode * p = NULL;
  ListNode * current = NULL;
  p = arithlist->head;

  while(p != NULL)
  {
    current = p;
    p = p->next;
    free(current);
  }
  //free(p);
  free(arithlist);
}

void addNode(List * arithlist, char * word)
{
  //printf("IS THIS THING WORKING - addNode\n");
  if (arithlist == NULL)
  {
    return;
  }
  ListNode * p = NULL;
  ListNode * newNode = NULL;
  ListNode * tailNode = NULL;
  newNode = malloc(sizeof(ListNode));
  if (newNode == NULL)
  {
    return;
  }
  memcpy(newNode->word, word, strlen(word) + 1);
  //printf("ADDNODE CONFIRMATION: %s\n",newNode->word);
  newNode->next = NULL;

  if (arithlist->head == NULL)
  {
    arithlist->head = newNode;
    newNode->prev = NULL;
    arithlist->tail = newNode;
    return;
  }
  else
  {
    tailNode = arithlist->head;
    while (tailNode->next != NULL)
    {
      tailNode = tailNode->next;
    }
    tailNode->next = newNode;

    p = arithlist->head;
    while (p->next != newNode)
    {
      p = p->next;
    }
    newNode->prev = p;
  }

  arithlist->tail = tailNode->next;
  return;
}

bool deleteNode(List * arithlist, ListNode * ln)
{
  if (arithlist == NULL)
  {
    return false;
  }

  if ((arithlist->head == NULL) && (arithlist->tail == NULL))
  {
    return false;
  }

  ListNode * current = arithlist->head;

  while(current != NULL)
  {
    if (current == ln)
    {
      if (current == arithlist->head)
      {
        arithlist->head = current->next;
        free(current);
        arithlist->head->prev = NULL;
        return true;
      }
      if (current->next == NULL)
      {
        arithlist->tail = current->prev;
        current->prev->next = NULL;
        free(current);
        return true;
      }
      
      current->prev->next = current->next;
      current->next->prev = current->prev;
      free(current);
      return true;
    }
    current = current->next;
  }
  return false;
}
