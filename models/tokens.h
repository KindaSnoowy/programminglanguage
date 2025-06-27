#ifndef tokens_enum_h
#define tokens_enum_h

typedef enum {
   // one line tokens
   EQUAL_TOKEN, QUOTE_TOKEN,

   // literal tokens
   TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER
} TokenType;

typedef struct {
   TokenType type;
   const char* start;
   int length;
   int line;

   // values
   union {
      char* string;
      double number;
   } value;
} Token;

#endif