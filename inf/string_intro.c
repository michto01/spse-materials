/**
 * @file string_intro.c
 * @author Tomas Michalek (tomas.michalek@spsehavirov.cz)
 * @brief Příklad v úvodu do řeťezců
 *
 * Jednoduchý program demonstrující některé z věcí o kterých jsme si povídali
 * na hodině.
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

#define UPCOUNT

int main(void) {
    char jmeno[69];
    printf("Zadej jmeno: ");
    scanf("%s", jmeno);

#ifndef UPCOUNT
    /* Smyčka když počítáme dolů */
    for (int i = strlen(jmeno) + 1; i >= 0; i--) {
#else
    /* Smyčka když počítáme nahoru */
    for (int i = 0; i < strlen(jmeno); i++) {
#endif
        /* Pokud znak není písmeno, tak ho přeskočíme */
        if (!isalpha(jmeno[i])) continue;

        /* Malé písmena změníme na VELKÉ a opačně */
        if (islower(jmeno[i])) {
            jmeno[i] = toupper(jmeno[i]);
        }
        else if (isupper(jmeno[i])) {
            jmeno[i] = tolower(jmeno[i]);
        }
    }

    printf("Mamlas: %s", jmeno);

#if 0
    printf("Ahoj, %s... Dnes je venku krasne a parno\n", jmeno);
#endif

    return 0;
}