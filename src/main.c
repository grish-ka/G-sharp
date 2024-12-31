#include <stdio.h>
#include "include/lexer.h"

int main(int argc, char* argv[]) {
    
    lexer_T* lexer = init_lexer(
        "name = \"hello\";"
    );

    token_T* tokon = (void*)0;
    int i = 0;

    while ((tokon = lexer_get_next_token(lexer)) != (void*)0) {
        printf("TOKEN(%d, %s)\n", tokon->type, tokon->value);
        printf("i=%d\n", i);
        i ++;

    }
    printf("I Am stuck\n");

    return 0;
}