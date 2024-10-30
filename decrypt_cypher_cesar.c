#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct freq_letter{
    char letter;
    float frequency;
};

int populate_frequency_letter(struct freq_letter *freq_letters, int *total_letter, char search_letter) {
    for (int i = 0; i < *total_letter; i++) {
        if (freq_letters[i].letter == search_letter) {
            freq_letters[i].frequency++;
            return 0;
        }
    }

    freq_letters[*total_letter].letter = search_letter;
    freq_letters[*total_letter].frequency = 1;
    (*total_letter)++;
    return 1;
};

char find_letter_most_frequency(struct freq_letter *freq_letters, int *total_letter) {
    struct freq_letter letter_most_frequency;
    letter_most_frequency.letter = 'A';
    letter_most_frequency.frequency = 0.0;

    for (int i = 0; i < total_letter; i++) {
        if (freq_letters[i].frequency > letter_most_frequency.frequency) {
            letter_most_frequency.letter = freq_letters[i].letter;
            letter_most_frequency.frequency = freq_letters[i].frequency;
        }
    }

    return letter_most_frequency.letter;
};

void decrypt_cypher_cesar(const char* encrypt_msg) {
    struct freq_letter freq_letter_encrypt_msg[MAX_SIZE];
    int total_letter = 0;

    char* decrypt_cypher = malloc(MAX_SIZE);

    // Region - Pegar a letra mais frequente da palavra criptografada
    for (int i = 0; encrypt_msg[i] != '\0' && encrypt_msg[i] != '\n'; i++) {
        if (encrypt_msg[i] != ' ') {
            populate_frequency_letter(freq_letter_encrypt_msg, &total_letter, encrypt_msg[i]);
        }
    }

    char letter_most_frequency = find_letter_most_frequency(freq_letter_encrypt_msg, total_letter);
    // Endregion

    // Baseado na distribuição de frequência peguei as duas letras mais frequentes da lingua portguesa
    int possible_keys[1];
    char letter_common[2] = {'A', 'E'};

    // Encontra as possíveis chaves se baseando nas letras mais frequentes na lingua portuguesa e na palavra criptografada
    for (int i = 0; i < 2; i++) {
        int key = (letter_most_frequency - letter_common[i]) % 26;
        possible_keys[i] = key;
    }

    // fazemos a descriptografia testando as duas possíveis chaves encontradas
    for (int i = 0; i < 2; i++) {
        char decrypt_text[MAX_SIZE];
        int size_decrypt_text = 0;
        for (int j = 0; encrypt_msg[j] != '\0' && encrypt_msg[j] != '\n'; j++) {
            char decrypt_letter;
            if (encrypt_msg[j] == ' ') {
                decrypt_letter = ' ';
            } else {
                decrypt_letter = ((encrypt_msg[j] - 'A' - possible_keys[i]) % 26) + 'A';
            }
            decrypt_text[size_decrypt_text] = decrypt_letter;
            size_decrypt_text++;
        }
        printf("Chave %i: %s\n", possible_keys[i], decrypt_text);
    }
};

void to_upper(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
};

int main() {
    char *encrypt_msg;
    encrypt_msg = malloc(MAX_SIZE);

    printf("Digite a mensagem a ser descriptografada pela Cifra Cesar (max 99 caracteres): ");
    fgets(encrypt_msg, MAX_SIZE, stdin);

    to_upper(encrypt_msg);
    decrypt_cypher_cesar(encrypt_msg);

    free(encrypt_msg);
    return 0;
}
