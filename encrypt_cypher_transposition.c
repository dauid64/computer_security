#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
#define SECRET_KEY "MEGABUCK"

void sort_alphabetically(char *msg) {
    int tam_msg = strlen(msg) - 1;

    for (int i = 0; i < tam_msg; i++) {
        for (int j = i; j < tam_msg; j++) {
            if (msg[i] > msg[j + 1]) {
                char aux = msg[i];
                msg[i] = msg[j + 1];
                msg[j + 1] = aux;
            }
        }
    }
}

void encrypt_cypher_transposition(char *msg) {
    int tam_msg = strlen(msg);
    int tam_secret_key = strlen(SECRET_KEY);
    int rows = (tam_msg + tam_secret_key - 1) / tam_secret_key;

    char encrypt_msg[rows - 1][tam_secret_key - 1];

    char sort_secret_key[] = SECRET_KEY;
    sort_alphabetically(sort_secret_key);

    for (int i = 0; i < tam_secret_key; i++) {
        encrypt_msg[0][i] = sort_secret_key[i];
        printf("%c", encrypt_msg[0][i]);
    }
}

void to_upper(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
};

int main() {
    char msg[MAX_SIZE];

    printf("Digite a mensagem a ser criptografada pela Cifra de transposição (max 99 caracteres e sem espaço): ");
    fgets(msg, MAX_SIZE, stdin);

    msg[strcspn(msg, "\n")] = '\0';
    to_upper(msg);

    encrypt_cypher_transposition(msg);

    return 0;
}
