
#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include <string.h>
#define _HISTORY__



/* Initialize the linked list to keep the history. */
List* init_history(){
 List *history=(List*)malloc(sizeof(List));
 if(history==NULL){
   return NULL;
 }
 history -> root=NULL;
 return history;
}
/* Add a history item to the end of the list.                                                                                                                                                                                                    
   List* list - the linked list
   char* str - the string to store                                                                                                                                                                                                               
*/
void add_history(List *list, char *str) {
    // Check if the list is NULL
    if (list == NULL) return;

    // Allocate memory for the new item
    Item *new_item = (Item *)malloc(sizeof(Item));
    if (new_item == NULL) {
        printf("Memory allocation failed\n");
        return;
    }


    // Copy the string into the new item
    new_item->str = strdup(str);  // strdup allocates memory and copies the string
    if (new_item->str == NULL) {
        printf("Memory allocation for string failed\n");
        free(new_item);  // Free the allocated memory for the item itself
        return;
    }

    // Assign an ID to the new item
    int new_id=1;
  Item *current =list->root;
 while(current !=NULL){
   new_id=current->id+1;
   current =current->next;
 }
 new_item->id=new_id;
 
    // If the list is empty, set the root to the new item
    if (list->root == NULL) {
        list->root = new_item;
    } else {
        // Traverse to the end of the list
        Item *current = list->root;
        while (current->next != NULL) {
            current = current->next;
        }

        // Attach the new item to the end
        current->next = new_item;
    }

}
/* Retrieve the string stored in the node where Item->id == id.                                   
   List* list - the linked list
   int id - the id of the Item to find */

char *get_history(List *list, int id){

  if(list ==NULL||list->root==NULL){
  printf("List is empty\n");
  return NULL;
  }
  Item *current =list -> root;
  while (current != NULL) {
    if(current ->id==id){
      return current->str;
}
    current=current->next;
}
  return NULL;
}
/*Print the entire contents of the list. */
void print_history(List *list){
  if(list ==NULL) return;
  
  Item *current =list -> root;
   while (current != NULL) {
     printf("ID %d: %s\n",current->id, current->str);
     current = current->next;
	 }
}
  
/*Free the history list and the strings it references. */
  void free_history(List *list) {
    if (list == NULL) return;

    Item *current = list->root;
    while (current != NULL) {
        Item *next = current->next;  // Save the next item
        free(current->str);          // Free the string
        free(current);               // Free the node itself
        current = next;              // Move to the next item
    }
    list->root = NULL;               // Set root to NULL after freeing
}
