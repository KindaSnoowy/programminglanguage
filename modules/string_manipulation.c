#include "string_manipulation.h"

int own_str_len(char *string) {
   int count = 0;
   while (*string) {
      count++; string++;
   }
   return count;
}
