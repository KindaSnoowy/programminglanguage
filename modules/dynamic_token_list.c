#include "dynamic_token_list.h"
#include <stdlib.h>
#include <stdio.h>

DynamicTokenList* start_list() {
   DynamicTokenList* list = (DynamicTokenList*)malloc(sizeof(DynamicTokenList));
   if (list == NULL) return NULL;

   list->size = 0;
   list->capacity = 8;
   list->tokens = (Token*)malloc(sizeof(Token) * list->capacity);
   if (list->tokens == NULL) {
      fprintf(stderr, "Error: Fail at allocating tokens list.\n");
      exit(1);
   }

   return list;
}

int destroy_list(DynamicTokenList* list) {
   if (list == NULL) {
      fprintf(stderr, "Error: List not found while destroying.\n");
      exit(1);
   };
   free(list->tokens);
   free(list);
   return 0;
}
 
int insert_token(DynamicTokenList* list, Token* token) {
   if (list == NULL || token == NULL) return -1;
   if (list->size >= list->capacity) {
      int new_capacity = list->capacity * 2;
      Token* new_tokens = (Token*)realloc(list->tokens, sizeof(Token) * new_capacity);
      if (new_tokens == NULL) {
         fprintf(stderr, "Error: Fail at realocating tokens list.\n");
         exit(1);
      }
      list->capacity *= 2;
      list->tokens = new_tokens;
   }

   list->tokens[list->size] = *token;
   list->size++;
   
   return 0; 
}

int remove_token(DynamicTokenList* list, int position) {
   if (list == NULL || position < 0 || position >= list->size) {
      return -1; 
   }
   for (int i = position; i < list->size - 1; i++) {
      list->tokens[i] = list->tokens[i + 1];
   }
   list->size--;

   return 0;
}