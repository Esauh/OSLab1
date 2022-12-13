// list/list.c
//
// Implementation for linked list.
//
// Esau Hutcherson

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list_t *list_alloc(){
  node_t *head = node_alloc();
  list_t *list = (list_t *) malloc(sizeof(list_t));
  list->head = head;
  return list;
}

node_t *node_alloc(elem value){
  nnode_t *node = NULL;
  node = (node_t *) malloc(sizeof(node_t));
  return node;
}

void list_free(list_t *l){
  node_t *curr = l->head;
  free(l);
  while(curr->next != NULL) {
    node_free(curr);
    curr = curr->next;
}

void node_free(node_t *n){
  free(n);
}

void list_print(list_t *l){
  node_t * curr = l->head;
  while (curr != NULL) {
    printf("%d -> ", curr->value);
    curr = curr->next;
  }
}

int list_length(list_t *l){
  node_t *curr = l->head;
  int count = 0;
  while (curr->next != NULL) {
    count++;
    curr = curr->next;
  }
  return count; 
}

void list_add_to_back(list_t *l, elem value){
  node_t *curr = l->head;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  node_t *new_node = node_alloc();
  new_node->value = value;
  curr->next = new_node;
}

void list_add_to_front(list_t *l, elem value){
  node_t *pushed_head = l->head;
  node_t *new_node = node_alloc();
  new_node->value = value;
  new_node->next = pushed_head;
  l->head = new_node; 
}

void list_add_at_index(list_t *l, elem value, int index){
  if (index == 0) {
    list_add_to_front(l, value);
    return;
  }
  node_t *curr = l->head;
  node_t *prev = NULL;
  int count = 0;
  while (count < index && curr != NULL) {
    count++;
    prev = curr;
    curr = curr->next;
  }
  if (curr != NULL && count == index) {
    list_add_to_back(l, value);
    return;
  }
  else {
    node_t *new_node = node_alloc();
    new_node->value = value;
    new_node->next = prev->next;
  }
}

elem list_remove_from_back(list_t *l){
  elem removed_val =  -1;
  node_t *curr = l->head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }
  removed_val = curr->next->value;
  node_free(curr->next);
  curr->next = NULL;
  return removed_val;
}

elem list_remove_from_front(list_t *l){
  node_t *head = l->head;
  elem removed_val = head->value;
  node_t *new_head = l->head->next;
  l->head = new_head;
  return removed_val;
}

elem list_remove_at_index(list_t *l, int index){
  if (index == 0) {
    return list_remove_from_front(l);
  }
  node_t *curr = l->head;
  node_t *prev = NULL;
  int count = 0;
  while (count < index && curr->next != NULL) {
    curr = curr->next;
    count++;
  }
  if (curr != NULL && count == index) {
    return list_remove_from_back(l);
  }
  else {
    node_t *hold_node = curr->next;
    int removed_val = hold_node->value;
    curr->next = hold_node->next;
    node_free(hold_node);
    return removed_val;
  }
}

bool list_is_in(list_t *l, elem value){
  node_t *curr = l->head;
  while(curr->next != NULL) {
    if (curr->value == value) {
      return true;
    }
    curr = curr->next;
  }
  return false; 
}

elem list_get_elem_at(list_t *l, int index){
  node_t *curr = l->head;
  int count = 0;
  while (curr->next != NULL) {
    if (count == index) {
      return curr->value;
    }
    curr = curr->next;
    count++;
  }
  return -1; 
}

int list_get_index_of(list_t *l, elem value){
  node_t *curr = l->head;
  int count = 0;
  while (curr->next != NULL) {
    if (curr->value == value) {
      return count;
    }
    curr = curr->next;
    count++;
  }
  return -1; 
}



