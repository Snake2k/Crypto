#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

// Using intmax_t so that if someone is using an absurdly large shift, it'll still work.
void print_usage(void);
void caesar_encrypt(char*,intmax_t);
void caesar_decrypt(char*,intmax_t);

int main(int argc, char *argv[])
{
    // Check to see if the correct number of args were provided.
    if (argc <= 2 || argc > 4) {
        print_usage();
        return EXIT_FAILURE;
    }
    // Check to see if the correct options are chosen.
    if (strcmp(argv[1], "encrypt") != 0 && strcmp(argv[1], "decrypt") != 0) {
        print_usage();
        return EXIT_FAILURE;
    }

    // Check to see if a shift was specifed (if not, use default of 3).
    intmax_t shift = abs(argc == 4 ? atoi(argv[3]) : 3);

    // Encrypt/Decrypt text using shift.
    if (strcmp(argv[1], "encrypt") == 0) {
        caesar_encrypt(argv[2], shift);
    } else {
        caesar_decrypt(argv[2], shift);
    }
    return EXIT_SUCCESS;
}

void print_usage(void)
{
    // Seems pretty self-explanatory to me.
    printf("Usage:\n");
    printf("./caesar [encrypt/decrypt] [text] [shift (default: 3)]\n");
}

void caesar_encrypt(char *plain_text, intmax_t shift)
{
    intmax_t len = strlen(plain_text);
    char cipher_text[len];
    for (size_t i = 0; i < strlen(plain_text); i++) {
        // If the user provides anything other than an alphabet.
        if (tolower(plain_text[i]) < 97 || tolower(plain_text[i]) > 122) {
            cipher_text[i] = plain_text[i];
            continue;
        }

        // E(x) = (x + n) mod 26. Keeping ASCII in mind, we have to sub 96 then add it.
        // Where E -> Encryption, x -> plain text, n -> shift.
        char letter = plain_text[i] - 96;
        intmax_t x_plus_n = letter + shift;

        // If (x + n) is not in the range 0 - 25, it must be brought back into it.
        while (x_plus_n > 26) {
            x_plus_n -= 26;
        }
        while (x_plus_n < 0) {
            x_plus_n += 26;
        }

        // Make sure the mod doesn't result in 0, it must be 1 to 26, then add 96 back.
        letter = ((x_plus_n % 26) == 0 ? 26 : (x_plus_n % 26)) + 96;
        cipher_text[i] = letter;
    }
    printf("%s -> %s\n", plain_text, cipher_text);
}

void caesar_decrypt(char *cipher_text, intmax_t shift)
{
    intmax_t len = strlen(cipher_text);
    char plain_text[len];
    for (size_t i = 0; i < strlen(cipher_text); i++) {
        // If the user provides anything other than an alphabet.
        if (tolower(cipher_text[i]) < 97 || tolower(cipher_text[i]) > 122) {
            plain_text[i] = cipher_text[i];
            continue;
        }

        // D(x) = (x + n) mod 26. Keeping ASCII in mind, we have to sub 96 then add it.
        // Where E -> Decryption, x -> cipher text, n -> shift.
        char letter = cipher_text[i] - 96;
        intmax_t x_minus_n = letter - shift;

        // If (x - n) is not in the range 0 - 25, it must be brought back into it.
        while (x_minus_n > 26) {
            x_minus_n -= 26;
        }
        while (x_minus_n < 0) {
            x_minus_n += 26;
        }

        // Make sure the mod doesn't result in 0, it must be 1 to 26, then add 96 back.
        letter = ((x_minus_n % 26) == 0 ? 26 : (x_minus_n % 26)) + 96;
        plain_text[i] = letter;
    }
    printf("%s -> %s\n", cipher_text, plain_text);
}
