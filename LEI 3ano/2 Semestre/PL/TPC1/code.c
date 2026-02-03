#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int match_regex(const char *pattern, const char *text) {
    regex_t regex;
    int result;
    
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0;
    }
    
    result = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);
    
    return result == 0;
}

int main() {
    FILE *file = fopen("tpc1.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o ficheiro\n");
        return 1;
    }
    
    char token[1024];
    int count1 = 0, count2 = 0;
    
    // Pergunta 1: Tokens que começam com letra minúscula e terminam com dígito
    // Regex: ^[a-z].*[0-9]$
    const char *regex1 = "^[a-z].*[0-9]$";
    
    // Pergunta 2: Tokens que começam e acabam com '+' e têm apenas alfanuméricos entre eles
    // Regex: ^\+[a-zA-Z0-9]+\+$
    const char *regex2 = "^\\+[a-zA-Z0-9]+\\+$";
    
    while (fscanf(file, "%s", token) != EOF) {
        if (match_regex(regex1, token)) count1++;
        if (match_regex(regex2, token)) count2++;
    }
    
    fclose(file);
    
    printf("Pergunta 1 - Tokens que começam com letra minúscula e terminam com dígito: %d\n", count1);
    printf("Pergunta 2 - Tokens que começam e acabam com '+' e têm apenas alfanuméricos entre eles: %d\n", count2);
    
    return 0;
}