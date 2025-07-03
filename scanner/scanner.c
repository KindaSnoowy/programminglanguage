
#include <string.h>
#include <stdlib.h>

#include "scanner.h"
#include "tokens.h"

void scanner_init(Scanner* scanner, const char* source) {
   scanner->start = source;
   scanner->current = source;
   scanner->line = 1;
}

static int is_at_end(const Scanner* scanner) {
   return *scanner->current == '\0';
}

static Token make_token(const Scanner* scanner, const TokenType type) {
   Token token;
   token.start = scanner->start;
   token.length = (int)(scanner->current - scanner->start);
   token.line = scanner->line;
   token.type = type;

   return token;
}

static int is_digit(const char c) {
   return (c >= '0' && c <= '9');
}

static int is_alpha(const char c) {
   return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static int is_alphanumeric(const char c) {
   return (is_digit(c) || is_alpha(c));
}

static char advance(Scanner* scanner) {
   scanner->current++;
   return scanner->current[-1];
}

// peek is already at the next character, for it to check the next, distance should be 0
static char peek(Scanner* scanner, int distance) {
   if (is_at_end(scanner)) return '\0';
   return scanner->current[distance];
}

static Token make_error_token(const Scanner* scanner, const char* message) {
    Token token;
    token.type = ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner->line;
    return token;
}

static TokenType identifier_type(Scanner* scanner) {
   int length = (int)(scanner->current - scanner->start);

   switch (scanner->start[0]) {
      case 'a':
         if (length == 3 && memcmp(scanner->start, "and", 3) == 0) {
            return AND;
         }
         break;

      case 'c':
         if (length == 5 && memcmp(scanner->start, "class", 5) == 0) {
            return CLASS;
         }
         break;

      case 'e':
         if (length == 4 && memcmp(scanner->start, "else", 4) == 0) {
            return ELSE;
         }
         break;

      case 'f':
         if (length == 5 && memcmp(scanner->start, "false", 5) == 0) {
            return FALSE;
         } else if (length == 4 && memcmp(scanner->start, "func", 4) == 0) {
            return FUNC;
         } else if (length == 3 && memcmp(scanner->start, "for", 3) == 0) {
            return FOR;
         }
         break;

      case 'i':
         if (length == 2 && memcmp(scanner->start, "if", 2) == 0) {
            return IF;
         }
         break;

      case 'n':
         if (length == 3 && memcmp(scanner->start, "nil", 3) == 0) {
            return NIL;
         }
         break;

      case 'o':
         if (length == 2 && memcmp(scanner->start, "or", 2) == 0) {
            return OR;
         }
         break;

      case 'p':
         if (length == 5 && memcmp(scanner->start, "print", 5) == 0) {
            return PRINT;
         }
         break;

      case 'r':
         if (length == 6 && memcmp(scanner->start, "return", 6) == 0) {
            return RETURN;
         }
         break;

      case 's':
         if (length == 5 && memcmp(scanner->start, "super", 5) == 0) {
            return SUPER;
         }
         break;

      case 't':
         if (length == 4 && memcmp(scanner->start, "this", 4) == 0) {
            return THIS;
         } else if (length == 4 && memcmp(scanner->start, "true", 4) == 0) {
            return TRUE;
         }
         break;

      case 'v':
         if (length == 3 && memcmp(scanner->start, "var", 3) == 0) {
            return VAR;
         }
         break;

      case 'w':
         if (length == 5 && memcmp(scanner->start, "while", 5) == 0) {
            return WHILE;
         }
         break;
   }

   return IDENTIFIER;
}



static int match(Scanner* scanner, const char expected) {
   if (is_at_end(scanner) == 1) return 0;
   if (*scanner->current != expected) return 0;
   scanner->current++;
   return 1;
}

static Token make_token_string(Scanner* scanner) {
   while (peek(scanner, 0) != '"' && !is_at_end(scanner)) {
      if (peek(scanner, 0) == '\n') scanner->line++;
      advance(scanner);
   }

   if (is_at_end(scanner)) {
       return make_error_token(scanner, "Invalid string");
   }

   advance(scanner);

   Token token = make_token(scanner, STRING);
   const char* string_start = scanner->start + 1;

   char* value_string = (char *)malloc(token.length + 1); // token.length + 1 is because of the terminator '\0'
   strncpy(value_string, string_start, token.length - 2); // token.length - 2 is the string value length without the quotes ""
   value_string[token.length - 2] = '\0'; // end of the string
   token.value.string = value_string;

   return token;
}



static Token make_token_number(Scanner* scanner) {
   while (is_digit(peek(scanner, 0))) { advance(scanner); }

   if (peek(scanner, 0) == '.' && is_digit(peek(scanner, 1))) {
      advance(scanner);

      while (is_digit(peek(scanner, 0))) { advance(scanner); }
   }

   Token token = make_token(scanner, NUMBER);
   token.value.number = strtod(scanner->start, NULL);

   return token;
}

static Token identifier(Scanner* scanner) {
   while (is_alphanumeric(peek(scanner, 0))) {
      advance(scanner);
   }

   TokenType type = identifier_type(scanner);
   return make_token(scanner, type);
}

static void skip_whitespace(Scanner* scanner) {
    for (;;) {
        char c = peek(scanner, 0);
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance(scanner);
                break;
            case '\n':
                scanner->line++;
                advance(scanner);
                break;
            case '/':
                // comments (with "//"), are ignored
                if (match(scanner, '/')) {
                    while (peek(scanner, 0) != '\n' && !is_at_end(scanner)) { advance(scanner); }
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

Token scanner_scan_token(Scanner* scanner) {
    skip_whitespace(scanner);

   scanner->start = scanner->current;

   if (is_at_end(scanner)) return make_token(scanner, TOKEN_EOF);
   char c = advance(scanner);
   switch (c) {
      // single characters
      case '(':
         return make_token(scanner, LEFT_PAREN);
      case ')':
         return make_token(scanner, RIGHT_PAREN);
      case '{':
         return make_token(scanner, LEFT_BRACE);
      case '}':
         return make_token(scanner, RIGHT_BRACE);
      case ',':
         return make_token(scanner, COMMA);
      case '.':
         return make_token(scanner, DOT);
      case '-':
         return make_token(scanner, MINUS);
      case '+':
         return make_token(scanner, PLUS);
      case ';':
         return make_token(scanner, SEMICOLON);
      case '*':
         return make_token(scanner, STAR);

      // one or two characters
      case '!': // and !=
         return make_token(scanner, match(scanner, '=') ? EXCLAMATION : EXCLAMATION_EQUAL);
      case '=': // and ==
         return make_token(scanner, match(scanner, '=') ? EQUAL_EQUAL : EQUAL);
      case '<': // and <=
         return make_token(scanner, match(scanner, '=') ? LESS_EQUAL : LESS);
      case '>': // and >=
         return make_token(scanner, match(scanner, '=') ? GREATER_EQUAL : GREATER);

      // strings

      case '"':
         return make_token_string(scanner);



      default:
        if (is_digit(c)) {
            return make_token_number(scanner);
        } else if (is_alpha(c)) {
            return identifier(scanner);
        }

        make_error_token(scanner, "Invalid token");
   }
}
