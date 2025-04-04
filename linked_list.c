#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) 
{ 
  struct list_node * new_node = malloc(sizeof(struct list_node));
  new_node -> value = value;
  new_node-> next = NULL;
  return new_node;
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node * ptr = new_node(value);
  ptr -> next = list -> head;
  list -> head = ptr;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  if((list -> head) == NULL)
  {
    list -> head = new_node(value);
  }
  else
  {
    struct list_node * ptr = list -> head;
    while((ptr -> next) != NULL)
    {
      ptr = ptr -> next;
    }
    ptr -> next = new_node(value);
  }
}

size_t remove_from_head(struct linked_list *list) 
{ 
  if(list -> head == NULL)
  {
    return 0;
  }

  printf("remove from head\n");

  struct list_node * ptr = list -> head;
  printf("am i stuck\n");
  size_t ret_value = ptr -> value;
  printf("am i stuck pt2\n");
  list -> head = list -> head -> next;
  printf("am i stuck pt3\n");
  free(ptr);
  printf("past the free\n");
  return ret_value;
}

size_t remove_from_tail(struct linked_list *list) 
{ 
  if(list -> head == NULL)
  {
    return 0; 
  }

  if(list -> head -> next == NULL)
  {
    size_t ret_value = list -> head -> value;
    free(list -> head);
    list -> head = NULL;
    return ret_value;
  }
  
  struct list_node * remove_tail = list -> head;
  while(remove_tail->next != NULL && remove_tail->next->next != NULL)
  {
    remove_tail = remove_tail -> next;
  }

  size_t ret_value = remove_tail -> next -> value;
  free(remove_tail->next);
  remove_tail -> next = NULL;
  return ret_value;
}

void free_list(struct linked_list list) 
{
  while(list.head != NULL)
  {
    struct list_node * temp = list.head;
    list.head = temp -> next;
    free(temp);
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
