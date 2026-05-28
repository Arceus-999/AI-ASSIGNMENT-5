#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 9
#define HEURISTIC_MAX_DEPTH 3

int nodesEvaluated = 0;

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

int evaluateLine(char c1, char c2, char c3, char aiPlayer, char opponent) {
    int aiCount = 0;
    int oppCount = 0;

    if (c1 == aiPlayer) aiCount++;
    else if (c1 == opponent) oppCount++;

    if (c2 == aiPlayer) aiCount++;
    else if (c2 == opponent) oppCount++;

    if (c3 == aiPlayer) aiCount++;
    else if (c3 == opponent) oppCount++;

    if (aiCount > 0 && oppCount > 0) {
        return 0;
    }
    if (aiCount == 3) return 100;
    if (aiCount == 2) return 10;
    if (aiCount == 1) return 1;
    if (oppCount == 3) return -100;
    if (oppCount == 2) return -10;
    if (oppCount == 1) return -1;
    return 0;
}

int evaluateHeuristic(const char board[BOARD_SIZE], char aiPlayer, char opponent) {
    int score = 0;

    score += evaluateLine(board[0], board[1], board[2], aiPlayer, opponent);
    score += evaluateLine(board[3], board[4], board[5], aiPlayer, opponent);
    score += evaluateLine(board[6], board[7], board[8], aiPlayer, opponent);

    score += evaluateLine(board[0], board[3], board[6], aiPlayer, opponent);
    score += evaluateLine(board[1], board[4], board[7], aiPlayer, opponent);
    score += evaluateLine(board[2], board[5], board[8], aiPlayer, opponent);

    score += evaluateLine(board[0], board[4], board[8], aiPlayer, opponent);
    score += evaluateLine(board[2], board[4], board[6], aiPlayer, opponent);

    return score;
}

int heuristicAlphaBeta(char board[BOARD_SIZE], int depth, int maxDepth, int alpha, int beta, int isMax, char aiPlayer, char opponent) {
    nodesEvaluated++;

    if (checkWin(board, aiPlayer)) {
        return 1000 - depth;
    }
    if (checkWin(board, opponent)) {
        return depth - 1000;
    }
    if (isBoardFull(board)) {
        return 0;
    }

    if (depth >= maxDepth) {
        return evaluateHeuristic(board, aiPlayer, opponent);
    }

    if (isMax) {
        int bestScore = -10000;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == ' ') {
                board[i] = aiPlayer;
                int score = heuristicAlphaBeta(board, depth + 1, maxDepth, alpha, beta, 0, aiPlayer, opponent);
                board[i] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                }
                if (bestScore > alpha) {
                    alpha = bestScore;
                }
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 10000;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == ' ') {
                board[i] = opponent;
                int score = heuristicAlphaBeta(board, depth + 1, maxDepth, alpha, beta, 1, aiPlayer, opponent);
                board[i] = ' ';

                if (score < bestScore) {
                    bestScore = score;
                }
                if (bestScore < beta) {
                    beta = bestScore;
                }
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return bestScore;
    }
}

int getBestMove(char board[BOARD_SIZE], char aiPlayer, char opponent) {
    int bestMove = -1;
    int bestScore = -10000;
    nodesEvaluated = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == ' ') {
            board[i] = aiPlayer;
            int score = heuristicAlphaBeta(board, 0, HEURISTIC_MAX_DEPTH, -10000, 10000, 0, aiPlayer, opponent);
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
    printf("\n=== Running Heuristic Alpha-Beta Tests ===\n");
    int passed = 0;
    int total = 4;

    {
        char testBoard[9] = {
            'X', 'X', ' ',
            'O', ' ', ' ',
            'O', ' ', ' '
        };
        int move = getBestMove(testBoard, 'X', 'O');
        printf("Nodes evaluated: %d\n", nodesEvaluated);
        if (move == 2) {
            printf("[PASS] Test 1: AI completed immediate win at index 2.\n");
            passed++;
        } else {
            printf("[FAIL] Test 1: Got move %d, expected 2.\n", move);
        }
    }

    {
        char testBoard[9] = {
            'X', 'X', ' ',
            ' ', 'O', ' ',
            ' ', ' ', ' '
        };
        int move = getBestMove(testBoard, 'O', 'X');
        printf("Nodes evaluated: %d\n", nodesEvaluated);
        if (move == 2) {
            printf("[PASS] Test 2: AI blocked opponent's win at index 2.\n");
            passed++;
        } else {
            printf("[FAIL] Test 2: Got move %d, expected 2.\n", move);
        }
    }

    {
        char testBoard[9] = {
            'X', ' ', ' ',
            ' ', 'O', ' ',
            ' ', ' ', 'X'
        };
        int move = getBestMove(testBoard, 'O', 'X');
        printf("Nodes evaluated: %d\n", nodesEvaluated);
        if (move == 1 || move == 3 || move == 5 || move == 7) {
            printf("[PASS] Test 3: AI selected a side cell (%d) to prevent forks using heuristic values.\n", move);
            passed++;
        } else {
            printf("[FAIL] Test 3: AI failed to choose a side cell. Got %d.\n", move);
        }
    }

    {
        char testBoard[9] = {
            'X', 'O', 'X',
            ' ', 'O', 'O',
            'O', 'X', ' '
        };
        int move = getBestMove(testBoard, 'X', 'O');
        printf("Nodes evaluated: %d\n", nodesEvaluated);
        if (move == 3) {
            printf("[PASS] Test 4: AI blocked win at index 3.\n");
            passed++;
        } else {
            printf("[FAIL] Test 4: Got move %d, expected 3.\n", move);
        }
    }

    printf("\nTest Results: %d/%d tests passed.\n", passed, total);
    if (passed == total) {
        printf(">>> HEURISTIC ALPHA-BETA VERIFICATION SUCCESSFUL! <<<\n\n");
    } else {
        printf(">>> HEURISTIC ALPHA-BETA VERIFICATION FAILED! <<<\n\n");
    }
}

void playInteractiveGame() {
    char board[BOARD_SIZE];
    initBoard(board);
    char human, ai;
    char choice;

    printf("\nChoose your symbol [X/O]: ");
    if (scanf(" %c", &choice) != 1) return;
    if (choice == 'x' || choice == 'X') {
        human = 'X';
        ai = 'O';
    } else {
        human = 'O';
        ai = 'X';
    }

    char currentTurn = 'X';
    printf("\n--- Starting Game: You are %c, AI is %c (Max Depth = %d) ---\n", human, ai, HEURISTIC_MAX_DEPTH);
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
                printf("Invalid move.\n");
            }
            currentTurn = ai;
        } else {
            printf("AI is thinking...\n");
            int move = getBestMove(board, ai, human);
            board[move] = ai;
            printf("AI plays at position %d (explored %d states up to depth %d)\n", move + 1, nodesEvaluated, HEURISTIC_MAX_DEPTH);
            currentTurn = human;
        }
        printBoard(board);
    }

    if (checkWin(board, human)) {
        printf("Congratulations! You won!\n");
    } else if (checkWin(board, ai)) {
        printf("AI wins!\n");
    } else {
        printf("It's a draw!\n");
    }
}

int main() {
    int choice = 0;
    while (1) {
        printf("=========================================\n");
        printf(" TIC-TAC-TOE HEURISTIC ALPHA-BETA SEARCH \n");
        printf("=========================================\n");
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
