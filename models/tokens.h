#ifndef tokens_enum_h
#define tokens_enum_h

typedef enum {
   // single character tokens
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // one or two characters tokens
  EXCLAMATION, EXCLAMATION_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // literals
  IDENTIFIER, STRING, NUMBER,

  // keywords
  AND, CLASS, ELSE, FALSE, FUNC, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  TOKEN_EOF, ERROR
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
