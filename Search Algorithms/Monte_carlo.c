#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define BOARD_SIZE 9
#define MCTS_ITERATIONS 5000
#define MAX_CHILDREN 9
#define MAX_NODES 100000

char opponentOf(char player) {
    return (player == 'X') ? 'O' : 'X';
}

typedef struct MCTSNode {
    char board[BOARD_SIZE];
    char playerToMove;
    int moveIndex;
    int visits;
    double wins;
    struct MCTSNode* parent;
    struct MCTSNode* children[MAX_CHILDREN];
    int childCount;
} MCTSNode;

MCTSNode nodePool[MAX_NODES];
int poolIndex = 0;

MCTSNode* createNode(const char board[BOARD_SIZE], char playerToMove, int moveIndex, MCTSNode* parent) {
    if (poolIndex >= MAX_NODES) {
        return NULL;
    }
    MCTSNode* node = &nodePool[poolIndex++];
    memcpy(node->board, board, BOARD_SIZE);
    node->playerToMove = playerToMove;
    node->moveIndex = moveIndex;
    node->visits = 0;
    node->wins = 0.0;
    node->parent = parent;
    node->childCount = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void resetNodePool() {
    poolIndex = 0;
}

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

int isTerminal(MCTSNode* node) {
    return checkWin(node->board, 'X') || checkWin(node->board, 'O') || isBoardFull(node->board);
}

double getUCTValue(MCTSNode* node, double explorationConstant) {
    if (node->visits == 0) {
        return 1e9;
    }
    double averageScore = node->wins / node->visits;
    double explorationPart = explorationConstant * sqrt(log(node->parent->visits) / node->visits);
    return averageScore + explorationPart;
}

MCTSNode* selectBestUCTChild(MCTSNode* parent, double explorationConstant) {
    MCTSNode* bestChild = NULL;
    double bestValue = -1e18;
    for (int i = 0; i < parent->childCount; i++) {
        double val = getUCTValue(parent->children[i], explorationConstant);
        if (val > bestValue) {
            bestValue = val;
            bestChild = parent->children[i];
        }
    }
    return bestChild;
}

int getBestMoveMCTS(char board[BOARD_SIZE], char aiPlayer, char opponent, int iterations) {
    resetNodePool();
    MCTSNode* root = createNode(board, aiPlayer, -1, NULL);
    if (!root) return -1;

    for (int iter = 0; iter < iterations; iter++) {
        MCTSNode* curr = root;
        while (curr->childCount > 0 && !isTerminal(curr)) {
            int legalMovesCount = 0;
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (curr->board[i] == ' ') {
                    legalMovesCount++;
                }
            }

            if (curr->childCount == legalMovesCount) {
                curr = selectBestUCTChild(curr, sqrt(2.0));
            } else {
                break;
            }
        }

        MCTSNode* expanded = curr;
        if (!isTerminal(curr)) {
            int legalMoves[BOARD_SIZE];
            int numLegal = 0;
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (curr->board[i] == ' ') {
                    legalMoves[numLegal++] = i;
                }
            }

            int unexpandedMoves[BOARD_SIZE];
            int numUnexpanded = 0;
            for (int i = 0; i < numLegal; i++) {
                int move = legalMoves[i];
                int alreadyExpanded = 0;
                for (int j = 0; j < curr->childCount; j++) {
                    if (curr->children[j]->moveIndex == move) {
                        alreadyExpanded = 1;
                        break;
                    }
                }
                if (!alreadyExpanded) {
                    unexpandedMoves[numUnexpanded++] = move;
                }
            }

            if (numUnexpanded > 0) {
                int randIdx = rand() % numUnexpanded;
                int chosenMove = unexpandedMoves[randIdx];

                char nextBoard[BOARD_SIZE];
                memcpy(nextBoard, curr->board, BOARD_SIZE);
                nextBoard[chosenMove] = curr->playerToMove;

                MCTSNode* child = createNode(nextBoard, opponentOf(curr->playerToMove), chosenMove, curr);
                if (child) {
                    curr->children[curr->childCount++] = child;
                    expanded = child;
                }
            }
        }

        char rolloutBoard[BOARD_SIZE];
        memcpy(rolloutBoard, expanded->board, BOARD_SIZE);
        char turn = expanded->playerToMove;

        while (!checkWin(rolloutBoard, 'X') && !checkWin(rolloutBoard, 'O') && !isBoardFull(rolloutBoard)) {
            int moves[BOARD_SIZE];
            int count = 0;
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (rolloutBoard[i] == ' ') {
                    moves[count++] = i;
                }
            }
            int rIdx = rand() % count;
            rolloutBoard[moves[rIdx]] = turn;
            turn = opponentOf(turn);
        }

        char winner = ' ';
        if (checkWin(rolloutBoard, 'X')) winner = 'X';
        else if (checkWin(rolloutBoard, 'O')) winner = 'O';

        MCTSNode* bNode = expanded;
        while (bNode != NULL) {
            bNode->visits++;
            if (winner == ' ') {
                bNode->wins += 0.5;
            } else {
                char nodePlayer = opponentOf(bNode->playerToMove);
                if (winner == nodePlayer) {
                    bNode->wins += 1.0;
                }
            }
            bNode = bNode->parent;
        }
    }

    int bestMove = -1;
    int maxVisits = -1;
    for (int i = 0; i < root->childCount; i++) {
        if (root->children[i]->visits > maxVisits) {
            maxVisits = root->children[i]->visits;
            bestMove = root->children[i]->moveIndex;
        }
    }
    return bestMove;
}

void runTests() {
    printf("\n=== Running Monte-Carlo Tree Search (MCTS) Tests ===\n");
    int passed = 0;
    int total = 4;

    {
        char testBoard[9] = {
            'X', 'X', ' ',
            'O', ' ', ' ',
            'O', ' ', ' '
        };
        int move = getBestMoveMCTS(testBoard, 'X', 'O', MCTS_ITERATIONS);
        if (move == 2) {
            printf("[PASS] Test 1: MCTS chose winning cell at index 2.\n");
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
        int move = getBestMoveMCTS(testBoard, 'O', 'X', MCTS_ITERATIONS);
        if (move == 2) {
            printf("[PASS] Test 2: MCTS blocked opponent's win at index 2.\n");
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
        int move = getBestMoveMCTS(testBoard, 'O', 'X', MCTS_ITERATIONS);
        if (move == 1 || move == 3 || move == 5 || move == 7) {
            printf("[PASS] Test 3: MCTS chose defensive side cell (%d) to prevent forks.\n", move);
            passed++;
        } else {
            printf("[FAIL] Test 3: Got move %d, expected side cell (1, 3, 5, or 7).\n", move);
        }
    }

    {
        char testBoard[9] = {
            'X', 'O', 'X',
            ' ', 'O', 'O',
            'O', 'X', ' '
        };
        int move = getBestMoveMCTS(testBoard, 'X', 'O', MCTS_ITERATIONS);
        if (move == 3) {
            printf("[PASS] Test 4: MCTS blocked win at index 3.\n");
            passed++;
        } else {
            printf("[FAIL] Test 4: Got move %d, expected 3.\n", move);
        }
    }

    printf("\nTest Results: %d/%d tests passed.\n", passed, total);
    if (passed == total) {
        printf(">>> MCTS VERIFICATION SUCCESSFUL! <<<\n\n");
    } else {
        printf(">>> MCTS VERIFICATION FAILED! <<<\n\n");
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
    printf("\n--- Starting Game: You are %c, AI is %c (MCTS Iterations = %d) ---\n", human, ai, MCTS_ITERATIONS);
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
            printf("MCTS is running %d rollouts...\n", MCTS_ITERATIONS);
            clock_t start = clock();
            int move = getBestMoveMCTS(board, ai, human, MCTS_ITERATIONS);
            clock_t end = clock();
            double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;

            board[move] = ai;
            printf("AI plays at position %d (time: %.3f seconds)\n", move + 1, timeSpent);
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
    srand((unsigned int)time(NULL));

    int choice = 0;
    while (1) {
        printf("=========================================\n");
        printf("  TIC-TAC-TOE MONTE-CARLO TREE SEARCH \n");
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
