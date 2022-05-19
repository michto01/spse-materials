/**
 * @file pexeso.c
 * @author Tomas Michalek (tomas.michalek@spsehavirov.cz)
 * @brief PEXESO game for single player
 *
 * PEXESO variation to be enjoyed by yourself! Just run it and try guessing the
 * location grid know from game `battleships`:
 *
 * Rows: A, B, C
 * Cols: 1, 2, 3, 4
 *
 * example coordinates: a 1 (will be translated translated to [0,0])
 *
 * @version 1.0
 * @date 2022-05-19
 *
 * @copyright Copyright (c) 2022 SPŠE Havířov
 *
 * SPDX-License-Identifier: EUPL-1.2
 */
#include <stdio.h>              // Standard IO: (f)printf, (f)scanf ...
#include <stdlib.h>             // EXIT_SUCCESS
#include <stddef.h>             // size_t
#include <ctype.h>              // isdigit, isalpha
#include <assert.h>             // Check that the conditions are met: assert

#define BLOCKED (2)             // Field is already revealed, do not hide it!
#define CHECK   (1)             // Check is pending, can be hidden
#define EMPTY   (0)             // Field is empty

#define NDEBUG                  // Disable debugging output (remove N to enable)

#define M (4)                   // Size of the Board in X direction
#define N (3)                   // Size of the Board in Y direction
#define SIZE (M*N)              // Total size of the Board
#define WIN_PAIRS (SIZE/2)      // How may pairs do we have to find
#define MSG_SIZE (128)          // Storage for the string message

/**
 * @brief Array that holds the puzzle
 * @note Assumed to be correct, meaning that there is only one pair of each symbol.
 */
const char pexeso[SIZE] = {
    '$', '$', '@', '+',
    '@', 'O', '#', '&',
    '&', '+', '#', 'O',
};

/**
 * @brief Actual game board
 *
 * The array holds the progress of the game.
 */
char game[SIZE] = {
    '?', '?', '?', '?',
    '?', '?', '?', '?',
    '?', '?', '?', '?',
};

/**
 * @brief Array of played moves
 *
 * Helper array to block subsequent attempts to play the same card twice.
 */
int blocked[SIZE] = {
    EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY, EMPTY
};

/**
 * @brief Convert the coordinates to array index
 *
 * As we work with the 1D array, we need to offset the coordinates
 * to match the desired location in it. This works by translating
 * the 2D coordinates (x,y) onto the single index number (i);
 *
 * @param x X coordinate
 * @param y Y coordinate
 * @return size_t Index to access in the array
 */
static inline size_t coords(int x, int y) {
    return x + y * M;
}

/**
 * @brief Draw the game board
 *
 * Simple drawing function to print the actual state of the board.
 *
 * @param board array holding the board to show
 * @param m size in the X direction
 * @param n size in the Y direction
 */
void pexeso_draw_board(const char board[], size_t m, size_t n) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
#ifdef DEBUG
            printf("(%d,%d) ", x, y);
#endif
            printf("[%c] ", board[coords(x, y)]);
        }
        printf("\n");
    }
}

/**
 * @brief Draw the game board
 *
 * Alternative function to `pexeso_draw_board()` demonstrating the use of single
 * loop to complete the same task.
 *
 * @param board array holding the board to show
 * @param m size in the X direction
 * @param n size in the Y direction
 */
void pexeso_draw_board2(const char board[], size_t m, size_t n) {
    for (int i = 0; i < m*n; i++) {
#ifdef DEBUG
        printf("(%d) ", i);
#endif
        printf("[%c] ", board[i]);
        if ((i+1) % m == 0) printf("\n");
    }
}

/**
 * @brief Check that the pexesos match
 *
 * @param a First pexeso to check
 * @param b Second pexeso to check
 * @return int 1 if they are the same, 0 otherwise
 */
static inline int pexeso_validate(char a, char b) {
    return a == b;
}

/**
 * @brief Make field unavailable for the modifications
 *
 * Blocks the field from being erased in case that the field contains known pair.
 *
 * @param block Array to store the blocation
 * @param x X coordinate of the field
 * @param y Y coordinate of the field
 */
void pexeso_block(int block[], int x, int y) {
    block[coords(x, y)] = BLOCKED;
}

/**
 * @brief Is coordinate blocked
 *
 * Check the `block` array to see it the coordinate is already blocked
 *
 * @param block Array to read the blocations from
 * @param x X coordinate of the field
 * @param y Y coordinate of the field
 * @return Returns 0 is the field is accessible, 1 otherwise
 */
int pexeso_isblocked(int block[], int x, int y) {
    return BLOCKED == block[coords(x, y)];
}

/**
 * @brief Reveal the hidden pexeso card
 *
 * Show the card that resides in the position specified by (x, y) pair.
 *
 * @param solution Board from which we will to the revealing
 * @param board Board to save the changes to
 * @param m Size of the board in X direction
 * @param n Size of the board in Y direction
 * @param x X coordinate of the field
 * @param y Y coordinate of the field
 * @return Returns character present on the revealed board.
 */
char pexeso_show(const char solution[], char board[], size_t m, size_t n, int x, int y) {
    assert(x < m && x >= 0);
    assert(y < n && y >= 0);

    board[coords(x, y)] = solution[coords(x, y)];
    return board[coords(x, y)];
}

/**
 * @brief Hide the pexeso card
 *
 * @param board Board to manipulate
 * @param m Size of the board in X direction
 * @param n Size of the board in Y direction
 * @param x X coordinate of the field
 * @param y Y coordinate of the field
 */
void pexeso_hide(char board[], size_t m, size_t n, int x, int y) {
    assert(x < m && x >= 0);
    assert(y < n && y >= 0);

    if (pexeso_isblocked(blocked, x, y))  return;

    board[coords(x, y)] = '?';
}

/**
 * @brief Get coordinates
 *
 * Get the coordinates from the stdin and convert them from `battleship` arrangement
 * to the Cartesian's (x,y) coordinate pair
 *
 * @param x X coordinate of the field
 * @param y Y coordinate of the field
 */
void pexeso_get_coords(int *x, int *y) {
    char c_x;
    char c_y;
    fprintf(stdout, "What shall I show you [A-%c 1-%d]: ", 'A' + (N - 1), (M-1));
    fscanf(stdin, " %c %c", &c_y, &c_x);

    assert(isdigit(c_x));
    assert(isalpha(c_y));

    *x = c_x - '1';
    *y = toupper(c_y) - 'A';
    fflush(stdin);
}

/**
 * @brief Clean the screen
 *
 * Semi-portable way of simple screen wipe
 */
void clear(void) {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

/**
 * @brief Utility: Pause the game until the ENTER is not pressed
 *
 * As the game progresses, the player needs time to look
 * at the board, so this simple delay mechanism is implemented
 * to simplify the wait condition.
 */
void pexeso_pause(void) {
    char c;
    fprintf(stdout, "Press ENTER key to continue ...");
    fflush(stdin);
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
    fflush(stdin);
}

/**
 * @brief Utility: Quick draw the board with additional message
 *
 * @param game Board to draw
 * @param m Size of the board in X direction
 * @param n Size of the board in Y direction
 * @param msg Message to write
 */
void pexeso_game_draw(char game[], size_t m, size_t n, const char *__restrict__ msg) {
    clear();
    fprintf(stdout, "%s\n\n", msg);
    pexeso_draw_board(game, m, n);
    printf("\n");
}

int main(int argc, char *argv[]) {
    int pairs = 0; /* pair that the player already found */
    int turns = 0; /* how long does the player play the game for (in terms) */

    /* Text string, Welcome message */
    char message[MSG_SIZE] = "Shall we play a game? Let's play pexeso!";

    do {
        ++turns; /* let's count the turns */
        pexeso_game_draw(game, M, N, message);

        int x_a, y_a;
        pexeso_get_coords(&x_a, &y_a);
        char a = pexeso_show(pexeso, game, M, N, x_a, y_a);

        pexeso_game_draw(game, M, N, message);

        int x_b, y_b;
        pexeso_get_coords(&x_b, &y_b);
        char b = pexeso_show(pexeso, game, M, N, x_b, y_b);

        pexeso_game_draw(game, M, N, message);

        if (pexeso_validate(a, b)) {
            if (!pexeso_isblocked(blocked, x_a, y_a)
             && !pexeso_isblocked(blocked, x_b, y_b)) {
                ++pairs;
            } else  {
                fprintf(stdout, "You've already played see this cards!\n");
            }
            pexeso_block(blocked, x_a, y_a);
            pexeso_block(blocked, x_b, y_b);
        } else {
            pexeso_hide(game, M, N, x_a, y_a);
            pexeso_hide(game, M, N, x_b, y_b);
        }

        sprintf(message, "You found %d pairs! Need %d more pairs to win ...", pairs, WIN_PAIRS - pairs);
        pexeso_pause();
    } while (pairs < WIN_PAIRS);

    sprintf(message, "You've WON! It only took you %d turns!\n", turns);
    pexeso_game_draw(game, M, N, message);

    return EXIT_SUCCESS;
}
