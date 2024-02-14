#ifndef LIST_H
#define LIST_H

#define WORDLENGTH 10
//arbitrarily defined, could be longer
// the tenth/last character stores '\0'

#include <stdbool.h>

//doubly linked list nodes
typedef struct Node
{
  char word[WORDLENGTH];
  // word is a string and one element must be '\0'
  struct Node * next;
  struct Node * prev;
} ListNode;

typedef struct
{
  ListNode * head;
  ListNode * tail;
} List;

bool readList(char * filename, List * arithlist);
void deleteList(List * arithlist);
void addNode(List * arithlist, char * word);
bool deleteNode(List * arithlist, ListNode * ln);

#endif
