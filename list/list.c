// list/list.c
//
// Implementation for linked list.
//
// Esau Hutcherson

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"


list_t *list_alloc() 
{
  list_t* list = (list_t*)malloc(sizeof(list_t));
  list->head = NULL;
  return list;
}
node_t *node_alloc(elem val)
{

  node_t *node = (node_t *) malloc(sizeof(node_t));
  node->value = val;
  node->next = NULL;
  return node;

}

void list_free(list_t *l) 
{
  node_t *tempptr , *currentptr;
  if (l->head != NULL)
    {  
       if (l->head->next != NULL)
         {
            currentptr = l->head;
            while(currentptr !=NULL)
            {
              tempptr = currentptr->next;
              free(currentptr);
              currentptr = tempptr;
            }
         }
       else
         {
           free(l->head);
         }
       l->head = NULL;
    } 
}
void node_free(node_t *n) 
{
  free(n);
}
/* Prints the list in some format. */
void list_print(list_t *l) 
{
  node_t *cur = l->head;
  while (cur != NULL)
  {  
    printf("%d\n",cur->value);
    cur = cur->next;
  }
}
/* Returns the length of the list. */
int list_length(list_t *l) 
{
  node_t *current = l->head;
  int i = 0;
  while (current != NULL)
  {
    i++;
    current = current->next; 
  }
  return i;
}
/* Methods for adding to the list. */
void list_add_to_back(list_t *l, elem value) 
{
  node_t *current = l->head;
  if(l->head == NULL){
    current->value = value; 
    current->next = NULL; 
  }
  else
  {
     while (current->next != NULL)
      {
        current = current->next;
      }
      current->next = (node_t *)malloc(sizeof(node_t));
      current->next->value = value;
      current->next->next= NULL;
  }

}
void list_add_to_front(list_t *l, elem value) 
{
   node_t *new_node;
   new_node = (node_t *)malloc(sizeof(node_t));
   new_node -> value = value;
   new_node->next =  l->head; 
   l->head = new_node; 
}

void list_add_at_index(list_t *l, elem value, int index)
{
if(l->head == NULL ){
  l->head->value = value;
  l->head->next = NULL; 
}
else{
  node_t * new_node;
  new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  int curr_index = 0;
  node_t *current = l->head;
  while(curr_index < index-1){
    if(current->next == NULL){
      current->next = new_node;
      new_node->next = NULL; 
      return ;
    }
    current = current->next;
    curr_index++;
  }
  new_node->next = current->next;
  current->next = new_node; 
}

}
/* Methods for removing from the list. Returns the removed element. */
elem list_remove_from_back(list_t *l)
{ 
  elem value = (elem)-1;
  node_t *current = l->head;
  if(l->head != NULL) 
  {
    if(current->next == NULL)
    {
      l->head = NULL;
      value = current->value;
      node_free(current);
    }
    else
    {
      while(current->next->next != NULL)
      {
        current = current->next;
      }
      value = current->next->value;
      node_free(current->next->next);
      current->next = NULL;
    }
  }
  return value;
}
elem list_remove_from_front(list_t *l) 
{ 
  elem value = (elem)-1;
  if (l->head == NULL)
  {
    return value;
  }
  else
  {
    node_t *current = l->head;
    value = current->value;
    l->head = l->head->next;
    node_free(current);
  }
  return value;
}
elem list_remove_at_index(list_t *l, int index) 
{
  int i;
  elem value = (elem)-1;
  bool found = false;
  
  if (l->head == NULL)
    {
      return value;
    }
  else 
  if (index == 0)
    {
      return list_remove_from_front(l);
    }
  else 
  if (index > 0)
  {
    node_t *current = l->head;
    node_t *prev = current;
    i = 0;
    while(current != NULL && !found)
    {
      if(i== index)
        {
          found = true;
        }
      else
      {
        prev = current; 
        current = current->next;
        i++;
      }
    }
    if(found)
    {
     value = current->value;
     prev->next = current->next; 
     node_free(current);
    }  
    return value;
  } 
}
/* Checks to see if the given element exists in the list. */
bool list_is_in(list_t *l, elem value) 
{
  node_t *tempnode = l->head; 
  while(tempnode != NULL)
  {
    if(value == tempnode->value)
    {
      return true;
    }
    tempnode = tempnode->next;   
  }
  return false;
  
}
/* Returns the element at the given index. */
elem list_get_elem_at(list_t *l, int index) 
{
  int i;
  elem value = (elem)-1;
  if(l->head == NULL)
    {
      return value;
    }
  else 
  if (index == 0)
    {
      node_t *current = l->head;
      value = current->value;
    }
  else
  if(index > 0)
    {
      node_t *current = l->head;
      i = 0;
      while(current != NULL)
      {
        if(i == index)
          {
            return(current->value);
          }
        else
          {
            current = current->next;
            i++;
          }
      }
    }
  return value;
}
/* Returns the index at which the given element appears. */
int list_get_index_of(list_t *l, elem value) 
{
  int i = 0;
  node_t *current = l->head;
  if(l->head == NULL)
    {
      return value;
    }
  while (current != NULL)
    {
      if (value == current->value)
        {
          return i;
        }
      current = current->next;
      i++;
    }
  return -1; 
}

