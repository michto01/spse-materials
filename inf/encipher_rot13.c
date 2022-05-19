/**
 * @file encipher_rot13.c
 * @author Tomas Michalek (tomas.michalek@spsehavirov.cz)
 * @brief Jednoduchý program pro (de)šifrování pomocí rotační šifry
 *
 * Rotační šifra (známá také jako cézarova šifra) je velmi přímočarý a jednoduchý
 * způsob obfuskace (zakrytí) informací. Tento jednoduchý program demonstruje
 * některé aspekty práce se řetězcem a ASCII tabulkou (a matematikou s nimi).
 *
 * Dále pak je jednoduchým úvodem do bezpečnosti a ukázce toho, jakým způsobem
 * chráníme data v počítači.
 *
 * @version 1.0
 * @date 2022-05-19
 *
 * @copyright Copyright (c) 2022 SPŠE Havířov
 *
 * SPDX-License-Identifier: EUPL-1.2
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <assert.h>

/**
 * @brief Encrypt/Decrypt single character using rotary cipher
 *
 * The simple rotation of the "second" alphabet "ring" will produce diferent
 * "encrypted" characters. To reverse the process, one must substract the
 * same amout of the rotation as in the encryption process
 *
 * @code
 * char enc = encrypt('a', 1);
 * // enc is: "b"
 * char dec = encrypt(enc, -1);
 * // dec is: "a"
 * @endcode
 *
 * @param plaintext Character we want to encrypt
 * @param rotate    Gap between the substitution letters
 * @return Returns the encrypted character
 */
char encrypt(char plaintext, int rotate) {
    /* Skip the non-alphabet characters */
    if (!isalpha(plaintext)) return plaintext;

    /* Convert all to uppercase, remember the capitalization to remove it later. */
    int capitalize = 0;
    if (islower(plaintext)) {
        capitalize = 1;
        plaintext = toupper(plaintext);
    }

    /* Calculate how many letters are in our alphabet (+1 for the 0. index letter) */
    const int offset = 'Z' - 'A' + 1;
    /* Calculate the rotated letter relative position */
    char ciphertext = ((plaintext - 'A') + rotate) % (offset);
    /* Add back the needed letter for the circle rotation */
    if (ciphertext >= 0) {
        ciphertext += 'A';
    } else {
        ciphertext += 'Z' + 1;
    }

    /* Reverse capitalization and return the newly encrypted character */
    if (capitalize) {
        return tolower(ciphertext);
    } else  {
        return ciphertext;
    }
}



#ifdef TEST_TDD
void test_encrypt(char (*fn)(char, int)) {
    /* Non-alphabet input */
    assert('!' == fn('!', 2));
    assert('4' == fn('4', 3));
    /* Simple forward rotation */
    assert('b' == fn('a', 1));
    assert('c' == fn('a', 2));
    assert('z' == fn('x', 2));
    assert('a' == fn('z', 1));
    /* Bacward rotation */
    assert('a' == fn('b', -1));
    assert('a' == fn('c', -2));
    assert('x' == fn('z', -2));
    assert('z' == fn('a', -1));
    /* Simple edge cases */
    assert('A' == fn('B', -1));
    assert('A' == fn('Z', 1));
}

void __attribute__((constructor)) setup(void) {
    test_encrypt(encrypt);
}
#endif

int main() {
#if 0
    printf("%c\n", encrypt('4', 1));
    printf("%c\n", encrypt('*', 1));
    printf("%c\n", encrypt('a', -3));
    printf("%c\n", encrypt('B', -1));
#endif

    char jmeno[64];

    printf("Zadej jmeno: ");
    scanf("%s", jmeno);

    for (int i = 0; i < strlen(jmeno); i++) {
        jmeno[i] = encrypt(jmeno[i], 1);
    }

    printf("%s\n", jmeno);
    return 0;
}