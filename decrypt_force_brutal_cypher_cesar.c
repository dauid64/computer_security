#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

void to_upper(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
};

void decrypt_cypher_cesar(const char* encrypt_msg) {
    // Percorre as 26 opções possíveis de chave
    for (int i = 0; i <= 26; i++) {
        char decrypt_text[MAX_SIZE];
        int size_decrypt_text = 0;

        for (int j = 0; encrypt_msg[j] != '\0' && encrypt_msg[j] != '\n'; j++) {
            char decrypt_letter;
            if (encrypt_msg[j] == ' ') {
                decrypt_letter = ' ';
            } else {
                decrypt_letter = ((encrypt_msg[j] - 'A' - i) % 26) + 'A';
            }
            decrypt_text[size_decrypt_text] = decrypt_letter;
            size_decrypt_text++;
        }
        printf("Chave %i: %s\n", i, decrypt_text);
    }
};

int main() {
    char encrypt_msg[100];

    printf("Digite a mensagem a ser criptografada pela Cifra Cesar (max 99 caracteres): ");
    fgets(encrypt_msg, sizeof(encrypt_msg), stdin);

    to_upper(encrypt_msg);
    decrypt_cypher_cesar(encrypt_msg);

    return 0;
};
