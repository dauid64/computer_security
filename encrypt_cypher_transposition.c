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

    int numeric_secret_key[tam_secret_key];

    for (int i = 0; i < tam_secret_key; i++) {
        numeric_secret_key[i] = i + 1;
    }

    int count_aux = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < tam_secret_key; col++) {
            if (msg[count_aux] == '\0') {
                encrypt_msg[row][col] = 'X';
            } else {
                encrypt_msg[row][col] = msg[count_aux];
            }
            count_aux++;
            printf("%c", encrypt_msg[row][col]);
        }
        printf("\n");
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
