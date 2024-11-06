#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
#define SECRET_KEY "MEGABUCK"

void sort(char *message) {
    int tam_message = strlen(message);
    for (int i = 0; i < tam_message - 1; i++) {
        for (int j = i+1; j < tam_message; j++) {
            if (message[i] > message[j]) {
                int aux = message[i];
                message[i] = message[j];
                message[j] = aux;
            }
        }
    }
}

void encrypt_cypher_transposition(char *msg) {
    int tam_msg = strlen(msg);
    int tam_secret_key = strlen(SECRET_KEY);
    int rows = (tam_msg + tam_secret_key - 1) / tam_secret_key;
    char matriz_msg[rows][tam_secret_key];

    char sort_secret_key[] = SECRET_KEY;
    sort(sort_secret_key);

    int *numeric_secret_key = calloc(tam_secret_key - 1, sizeof(int));

    // Pega uma lista de valores de acordo com a ordem mais baixa no alfabeto
    for (int i = 0; i < tam_secret_key; i++) {
        for (int j = 0; j < tam_secret_key; j++) {
            if (sort_secret_key[i] == SECRET_KEY[j]) {
                if (numeric_secret_key[j] == 0) {
                    numeric_secret_key[j] = i + 1;
                    break;
                }
            }
        }
    }

    // cria uma matriz com a mensagem a ser criptografada
    int count_aux = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < tam_secret_key; col++) {
            if (count_aux > tam_msg - 1) {
                matriz_msg[row][col] = 'X';
            } else {
                matriz_msg[row][col] = msg[count_aux];
            }
            count_aux++;
        }
    }

    // pega em ordem as colunas, usando como referência o vetor de ordem alfabetica
    // Onde começa pelo valor 1 por exemplo que pode estar localizado na col
    // Ex: numeric_secret_key=[7, 4, 5, 1, 2, 8, 3, 6]
    //             matriz_msg=[t, r, a, n, s, f, e, r]
    // começa pegando a coluna com valor 1 e assim por diante, então ficaria: nserart
    char encrypt_msg[tam_msg - 1];
    int count_get_col = 1;
    int count_add_caracter = 0;

    while (count_add_caracter < tam_msg) {
        for (int i = 0; i < tam_secret_key; i++) {
            if (numeric_secret_key[i] == count_get_col) {
                for (int row = 0; row < rows; row++) {
                    if(matriz_msg[row][i] != 'X') {
                        encrypt_msg[count_add_caracter] = matriz_msg[row][i];
                        count_add_caracter++;
                    }
                }
                count_get_col++;
            }
        }
    }

    printf("\nEncrypt Message = ");
    for (int i = 0; i < tam_msg; i++) {
        printf("%c", encrypt_msg[i]);
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
