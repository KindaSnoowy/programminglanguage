#include <tokens.h>
#ifndef scanner_h
#define scanner_h

typedef struct {
    const char* start;
    const char* current;
    int line;
} Scanner;

void scanner_init(Scanner* scanner, const char* source) ;
Token scanner_scan_token(Scanner* scanner);

#endif
