#ifndef dynamic_token_list_h
#define dynamic_token_list_h
#include "tokens.h"

typedef struct {
   Token* tokens;
   int size;
   int capacity;
} DynamicTokenList;

DynamicTokenList* start_list();
void destroy_list(DynamicTokenList* list);
void insert_token(DynamicTokenList* list, Token* token);
void remove_token(DynamicTokenList* list, Token* token);

#endif