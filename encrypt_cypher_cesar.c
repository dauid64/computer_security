#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* encrypt_cypher_cesar(const char* msg) {
    char* encrypt_msg = malloc(strlen(msg) + 1);

    for (int i = 0; msg[i] != '\0'; i++) {
        if (msg[i] == ' ') {
            encrypt_msg[i] = ' ';
        } else {
            const char base = isupper(msg[i]) ? 'A' : 'a'; // Seleciona a base que iremos usar da tabela ASCII
            int letra_aux = msg[i] - base; // Decrementa o caractere pela base, isso nós dará o valor 0 até 25
            letra_aux = (letra_aux + 3) % 26; // 13%25=13 e 26%25=1, então sempre voltamos para a letra inicial caso exceda
            encrypt_msg[i] = letra_aux + base; // incrementamos a nova letra mais a base, que nos retornará a letra real após a criptografia
        }
    }

    encrypt_msg[strlen(msg)] = '\0';
    return encrypt_msg;
}

void to_upper(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
};

int main() {
    char msg[100];

    printf("Digite a mensagem a ser criptografada pela Cifra Cesar (max 99 caracteres): ");
    fgets(msg, sizeof(msg), stdin);

    msg[strcspn(msg, "\n")] = '\0';
    to_upper(msg);

    char* encrypted_msg = encrypt_cypher_cesar(msg);

    printf("Mensagem criptografada: %s\n", encrypted_msg);

    return 0;
}
