#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

int main(int argc, char const *argv[])
{
   // if argument has at least one argument (file name)
   if (argc == 2) {
      FILE *fptr;
      fptr = fopen(argv[1], "r");
      fseek(fptr, 0L, SEEK_END);
      size_t fileSize = ftell(fptr);
      rewind(fptr);

      char* buffer = (char *)malloc(fileSize + 1);
      if (buffer != NULL) {
         fread(buffer, 1, fileSize, fptr);
         buffer[fileSize] = '\0';
      }

      for (int i = 0; i < fileSize; i++) {
         char c = buffer[i];
         switch (c) {
            
         }
      }


      fclose(fptr);
   }

  return 0;
}   
