#ifndef dynamic_token_list_h
#define dynamic_token_list_h
#include "tokens.h"

typedef struct {
   Token* tokens;
   int size;
   int capacity;
} DynamicTokenList;

DynamicTokenList* start_list();
int destroy_list(DynamicTokenList* list);
int insert_token(DynamicTokenList* list, Token* token);
int remove_token(DynamicTokenList* list, Token* token);

#endif
