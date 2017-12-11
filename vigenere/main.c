#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void);
void vigenere_encrypt(char*,char*);
void vigenere_decrypt(char*,char*);

int main(int argc, char *argv[])
{
    // Check to see if the correct number of args were provided.
    if (argc != 4) {
        print_usage();
        return EXIT_FAILURE;
    }
    // Check to see if the correct options are chosen.
    if (strcmp(argv[1], "encrypt") != 0 && strcmp(argv[1], "decrypt") != 0) {
        print_usage();
        return EXIT_FAILURE;
    }

    // Encrypt/Decrypt text using key provided.
    if (strcmp(argv[1], "encrypt") == 0) {
        vigenere_encrypt(argv[2], argv[3]);
    } else {
        vigenere_decrypt(argv[2], argv[3]);
    }
    return EXIT_SUCCESS;
}

void print_usage(void)
{
    // Pretty self-explanatory.
    printf("Usage:\n");
    printf("./vigenere [encrypt/decrypt] [text] [key]\n");
}

void vigenere_encrypt(char *plain_text, char *key)
{
    // E(M) = (M + K) mod 26. Keeping ASCII in mind, we have to sub 96 then add it.
    // Where E -> Encryption, M -> Plain Text Message, K -> Key.
    printf("%s %s\n", plain_text, key);
}

void vigenere_decrypt(char *cipher_text, char *key)
{
    // D(C) = (C - K) mod 26. Keeping ASCII in mind, we have to sub 96 then add it.
    // Where D -> Decryption, C -> Cipher Text, K -> Key.
    printf("%s %s\n", cipher_text, key);
}
