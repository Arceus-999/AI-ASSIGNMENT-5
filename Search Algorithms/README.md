# Tic-Tac-Toe Search Algorithms

This folder contains four different implementations of Tic-Tac-Toe AI using search algorithms in Artificial Intelligence.
The project demonstrates how different search techniques make decisions, optimize performance, and evaluate game states in adversarial environments.

Implemented Algorithms:

1. **Minimax Search** 
2. **Alpha-Beta Pruning**
3. **Heuristic Alpha-Beta Search**
4. **Monte-Carlo Tree Search (MCTS)** 

---

## 1. Minimax Search 

This implementation uses the classical Minimax algorithm to explore every possible future game state before making a move.

The algorithm assumes:

* The AI always plays optimally
* The opponent also plays optimally and the search recursively evaluates all possible board configurations until terminal states are reached.

### Key Concept

The algorithm tries to:

* maximize the AI score
* minimize the opponent’s score

Because Tic-Tac-Toe has a relatively small search space, Minimax can fully explore the game tree efficiently.

---

## 2. Alpha-Beta Pruning (`alphabeta.c`)

This version improves Minimax by adding Alpha-Beta pruning.

Instead of exploring every branch, the algorithm skips branches that cannot affect the final decision and it is much faster than standard Minimax

### Key Concept

Two values are maintained:

* **Alpha (α)** → best value found for maximizer
* **Beta (β)** → best value found for minimizer

Whenever:
β ≤ α

the remaining subtree is pruned.

This significantly reduces search time while preserving correctness.

---

## 3. Heuristic Alpha-Beta Search 

This implementation introduces a depth-limited search combined with heuristic evaluation.

Instead of exploring until the end of the game every time, the search stops after a fixed depth and estimates the board quality using a heuristic function.

### Key Concept

The evaluation function analyzes:

* rows
* columns
* diagonals

Scoring examples:

* +10 → two AI symbols and one empty space
* -10 → two opponent symbols and one empty space

The AI therefore learns to:

* create winning opportunities
* block dangerous opponent positions
* prioritize stronger board control

This approach demonstrates how real-world game AIs manage computational complexity.

---

## 4. Monte-Carlo Tree Search 

This implementation uses Monte-Carlo Tree Search (MCTS), a probabilistic search algorithm widely used in modern game AI.

Instead of fully searching the game tree, MCTS performs many randomized simulations and statistically estimates the best move.

### Main Stages

### 1. Selection

The algorithm selects promising nodes using the UCT formula to balance:

* exploration
* exploitation

### 2. Expansion

New child nodes are added for unexplored moves.

### 3. Simulation 

The game is played randomly until completion.

### 4. Backpropagation

Simulation results are propagated back through the tree to update node statistics.


# Test Cases Included

Each implementation contains automated test cases to verify correctness and behavior.

The test suite checks the following scenarios:

## 1. Immediate Winning Move

Verifies that the AI chooses a direct winning move whenever available.

## 2. Immediate Defensive Block

Checks whether the AI correctly blocks an opponent’s winning opportunity.

## 3. Fork Prevention

Tests whether the AI can prevent situations where the opponent creates multiple simultaneous threats.

## 4. Endgame Draw Situation

Ensures the AI selects moves that force a draw when winning is no longer possible.
