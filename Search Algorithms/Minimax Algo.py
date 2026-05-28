#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 9

void initBoard(char board[BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = ' ';
    }
}

void printBoard(const char board[BOARD_SIZE]) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
    printf("\n");
}

int checkWin(const char board[BOARD_SIZE], char player) {
    int winStates[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (int i = 0; i < 8; i++) {
        if (board[winStates[i][0]] == player &&
            board[winStates[i][1]] == player &&
            board[winStates[i][2]] == player) {
            return 1;
        }
    }
    return 0;
}

int isBoardFull(const char board[BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == ' ') {
            return 0;
        }
    }
    return 1;
}

int minimax(char board[BOARD_SIZE], int depth, int isMax, char aiPlayer, char opponent) {
    if (checkWin(board, aiPlayer)) {
        return 10 - depth;
    }
    if (checkWin(board, opponent)) {
        return depth - 10;
    }
    if (isBoardFull(board)) {
        return 0;
    }

    if (isMax) {
        int bestScore = -1000;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == ' ') {
                board[i] = aiPlayer;
                int score = minimax(board, depth + 1, 0, aiPlayer, opponent);
                board[i] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == ' ') {
                board[i] = opponent;
                int score = minimax(board, depth + 1, 1, aiPlayer, opponent);
                board[i] = ' ';
                if (score < bestScore) {
                    bestScore = score;
                }
            }
        }
        return bestScore;
    }
}

int getBestMove(char board[BOARD_SIZE], char aiPlayer, char opponent) {
    int bestMove = -1;
    int bestScore = -1000;

    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == ' ') {
            board[i] = aiPlayer;
            int score = minimax(board, 0, 0, aiPlayer, opponent);
            board[i] = ' ';

            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

void runTests() {
    printf("\n=== Running Minimax Tests ===\n");
    int passed = 0;
    int total = 4;

    {
        char testBoard[9] = {
            'X', 'X', ' ',
            'O', ' ', ' ',
            'O', ' ', ' '
        };
        int move = getBestMove(testBoard, 'X', 'O');
        if (move == 2) {
            printf("[PASS] Test 1: AI completed immediate win at index 2.\n");
            passed++;
        } else {
            printf("[FAIL] Test 1: AI failed to win immediately. Got move %d, expected 2.\n", move);
        }
    }

    {
        char testBoard[9] = {
            'X', 'X', ' ',
            ' ', 'O', ' ',
            ' ', ' ', ' '
        };
        int move = getBestMove(testBoard, 'O', 'X');
        if (move == 2) {
            printf("[PASS] Test 2: AI blocked opponent's win at index 2.\n");
            passed++;
        } else {
            printf("[FAIL] Test 2: AI failed to block opponent. Got move %d, expected 2.\n", move);
        }
    }

    {
        char testBoard[9] = {
            'X', ' ', ' ',
            ' ', 'O', ' ',
            ' ', ' ', 'X'
        };
        int move = getBestMove(testBoard, 'O', 'X');
        if (move == 1 || move == 3 || move == 5 || move == 7) {
            printf("[PASS] Test 3: AI played side (index %d) to defend against corner fork.\n", move);
            passed++;
        } else {
            printf("[FAIL] Test 3: AI failed fork defense. Played corner/invalid index %d.\n", move);
        }
    }

    {
        char testBoard[9] = {
            'X', 'O', 'X',
            ' ', 'O', 'O',
            'O', 'X', ' '
        };
        int move = getBestMove(testBoard, 'X', 'O');
        if (move == 3) {
            printf("[PASS] Test 4: AI blocked win/forced draw at index 3.\n");
            passed++;
        } else {
            printf("[FAIL] Test 4: AI failed endgame draw force. Got move %d, expected 3.\n", move);
        }
    }

    printf("\nTest Results: %d/%d tests passed.\n", passed, total);
    if (passed == total) {
        printf(">>> MINIMAX VERIFICATION SUCCESSFUL! <<<\n\n");
    } else {
        printf(">>> MINIMAX VERIFICATION FAILED! <<<\n\n");
    }
}

void playInteractiveGame() {
    char board[BOARD_SIZE];
    initBoard(board);
    char human, ai;
    char choice;

    printf("\nChoose your symbol (X goes first, O goes second) [X/O]: ");
    if (scanf(" %c", &choice) != 1) return;
    if (choice == 'x' || choice == 'X') {
        human = 'X';
        ai = 'O';
    } else {
        human = 'O';
        ai = 'X';
    }

    char currentTurn = 'X';
    printf("\n--- Starting Game: You are %c, AI is %c ---\n", human, ai);
    printBoard(board);

    while (!isBoardFull(board) && !checkWin(board, 'X') && !checkWin(board, 'O')) {
        if (currentTurn == human) {
            int move = -1;
            while (1) {
                printf("Enter your move (1-9): ");
                if (scanf("%d", &move) != 1) {
                    while (getchar() != '\n');
                    printf("Invalid input. Enter a number from 1 to 9.\n");
                    continue;
                }
                move--;
                if (move >= 0 && move < 9 && board[move] == ' ') {
                    board[move] = human;
                    break;
                }
                printf("Invalid move. Spot is taken or out of range.\n");
            }
            currentTurn = ai;
        } else {
            printf("AI is thinking...\n");
            int move = getBestMove(board, ai, human);
            board[move] = ai;
            printf("AI plays at position %d\n", move + 1);
            currentTurn = human;
        }
        printBoard(board);
    }

    if (checkWin(board, human)) {
        printf("Congratulations! You won!\n");
    } else if (checkWin(board, ai)) {
        printf("AI wins! Better luck next time.\n");
    } else {
        printf("It's a draw!\n");
    }
}

int main() {
    int choice = 0;
    while (1) {
        printf("===============================\n");
        printf("   TIC-TAC-TOE MINIMAX SEARCH  \n");
        printf("===============================\n");
        printf("1. Play Interactive Game (vs AI)\n");
        printf("2. Run Automated Test Cases\n");
        printf("3. Exit\n");
        printf("Enter selection (1-3): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid selection.\n");
            continue;
        }

        if (choice == 1) {
            playInteractiveGame();
        } else if (choice == 2) {
            runTests();
        } else if (choice == 3) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice. Please select 1, 2, or 3.\n");
        }
    }
    return 0;
}
