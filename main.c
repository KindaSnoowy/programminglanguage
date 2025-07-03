#include <stdio.h>
#include <stdlib.h>
#include "scanner/scanner.h"
#include "tokens.h"

// debbuging token name
const char* token_type_to_string(TokenType type) {
    switch (type) {
        // Tokens de um caractere
        case LEFT_PAREN: return "LEFT_PAREN";
        case RIGHT_PAREN: return "RIGHT_PAREN";
        case LEFT_BRACE: return "LEFT_BRACE";
        case RIGHT_BRACE: return "RIGHT_BRACE";
        case COMMA: return "COMMA";
        case DOT: return "DOT";
        case MINUS: return "MINUS";
        case PLUS: return "PLUS";
        case SEMICOLON: return "SEMICOLON";
        case SLASH: return "SLASH";
        case STAR: return "STAR";

        // Tokens de um ou dois caracteres
        case EXCLAMATION: return "EXCLAMATION";
        case EXCLAMATION_EQUAL: return "EXCLAMATION_EQUAL";
        case EQUAL: return "EQUAL";
        case EQUAL_EQUAL: return "EQUAL_EQUAL";
        case GREATER: return "GREATER";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case LESS: return "LESS";
        case LESS_EQUAL: return "LESS_EQUAL";

        // Literais
        case IDENTIFIER: return "IDENTIFIER";
        case STRING: return "STRING";
        case NUMBER: return "NUMBER";

        // Palavras-chave
        case AND: return "AND";
        case CLASS: return "CLASS";
        case ELSE: return "ELSE";
        case FALSE: return "FALSE";
        case FUNC: return "FUNC";
        case FOR: return "FOR";
        case IF: return "IF";
        case NIL: return "NIL";
        case OR: return "OR";
        case PRINT: return "PRINT";
        case RETURN: return "RETURN";
        case SUPER: return "SUPER";
        case THIS: return "THIS";
        case TRUE: return "TRUE";
        case VAR: return "VAR";
        case WHILE: return "WHILE";

        // Controle
        case TOKEN_EOF: return "EOF";
        case ERROR: return "ERROR";

        default: return "UNKNOWN_TOKEN";
    }
}

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

        Scanner scanner;
        scanner_init(&scanner, buffer);

    for (;;) {
        Token token = scanner_scan_token(&scanner);
        printf("Tipo: %-20s | Linha: %4d | Lexema: '%.*s'\n",
                token_type_to_string(token.type),
                token.line,
                token.length,
                token.start);

        if (token.type == NUMBER) {
            printf("  └─> Valor Numérico: %g\n", token.value.number);
        } else if (token.type == STRING) {
            printf("  └─> Valor String: \"%s\"\n", token.value.string);
        }

        if (token.type == TOKEN_EOF) {
            break;
        }
    }

      fclose(fptr);
   }

  return 0;
}
