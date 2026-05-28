# Bayesian Networks
This project is a implementation of a **Bayesian Network Inference System** 

The program demonstrates how probabilistic reasoning can be performed using a Bayesian Network involving:

* Rain
* Sprinkler
* Wet Grass

The application calculates:

* conditional probabilities
* joint probabilities
* probabilistic inference queries

using Bayes’ Theorem and probability distributions.

The situation is:

* Grass may become wet because:

  * it rained
  * the sprinkler was turned on
  * or both

The AI system tries to infer:

* how likely it rained if the grass is wet
* how likely the sprinkler was on
* how evidence changes probabilities

---

# Bayesian Network Structure

The network contains three variables:

| Variable      | Meaning                      |
| ------------- | ---------------------------- |
| Rain (R)      | Whether it rained            |
| Sprinkler (S) | Whether the sprinkler was on |
| WetGrass (W)  | Whether the grass became wet |

---

# Dependency Relationships

The probabilistic dependencies are:

```text id="g1c4v9"
Rain  →  Sprinkler
Rain  →  WetGrass
Sprinkler → WetGrass
```

Meaning:

* Rain affects whether the sprinkler is used
* Rain can directly wet the grass
* Sprinklers can also wet the grass

---

# Conditional Probability Tables (CPT)

The program defines probability rules such as:

### Rain Probability

```text id="r88sq7"
P(Rain = True) = 0.2
```

---

### Sprinkler Probability Given Rain

```text id="gkby8m"
P(Sprinkler = True | Rain = True) = 0.01
P(Sprinkler = True | Rain = False) = 0.40
```

Meaning:

* If it is raining, sprinklers are rarely turned on
* If it is not raining, sprinklers are more likely to be used

---

### Wet Grass Probability

The probability of wet grass depends on both:

* rain
* sprinkler activity

Example:

```text id="2hzzsk"
P(WetGrass = True | Sprinkler = True, Rain = True) = 0.99
```

---

# Queries Supported

The program can answer the following probabilistic questions:

| Query                         | Meaning                                              |
| ----------------------------- | ---------------------------------------------------- |
| P(Rain | WetGrass)            | Probability it rained if grass is wet                |
| P(Sprinkler | WetGrass)       | Probability sprinkler was on if grass is wet         |
| P(Rain | WetGrass, Sprinkler) | Probability of rain when sprinkler evidence is known |

---

# Program Menu

The application provides the following menu:

```text id="nh5a4q"
1. View Network Tables & Joint Probabilities
2. Query P(Rain | Wet Grass)
3. Query P(Sprinkler | Wet Grass)
4. Query P(Rain | Wet Grass, Sprinkler)
5. Exit
```

---

# Sample Program Output

```text id="3yl8kx"
==================================
   BAYESIAN NETWORK INFERENCE     
   (Wet Grass Caused by S or R)   
==================================

1. View Network Tables & Joint Probabilities
2. Query P(Rain | Wet Grass)
3. Query P(Sprinkler | Wet Grass)
4. Query P(Rain | Wet Grass, Sprinkler)
5. Exit

Enter selection (1-5): 1


=== CONDITIONAL PROBABILITY TABLES (CPT) ===

P(Rain = True) = 0.2

P(Sprinkler = True | Rain):
  P(S=T | R=T) = 0.01
  P(S=T | R=F) = 0.40

P(WetGrass = True | Sprinkler, Rain):
  P(W=T | S=T, R=T) = 0.99
  P(W=T | S=T, R=F) = 0.90
  P(W=T | S=F, R=T) = 0.80
  P(W=T | S=F, R=F) = 0.00


=== JOINT DISTRIBUTION P(R, S, W) ===

P(R=T, S=T, W=T) = 0.00198
P(R=T, S=T, W=F) = 0.00002
P(R=T, S=F, W=T) = 0.15840
P(R=T, S=F, W=F) = 0.03960
P(R=F, S=T, W=T) = 0.28800
P(R=F, S=T, W=F) = 0.03200
P(R=F, S=F, W=T) = 0.00000
P(R=F, S=F, W=F) = 0.48000


==================================
   BAYESIAN NETWORK INFERENCE     
   (Wet Grass Caused by S or R)   
==================================

1. View Network Tables & Joint Probabilities
2. Query P(Rain | Wet Grass)
3. Query P(Sprinkler | Wet Grass)
4. Query P(Rain | Wet Grass, Sprinkler)
5. Exit

Enter selection (1-5): 2


Query: P(Rain = True | WetGrass = True)

Formula:
P(R=T, W=T) / P(W=T)

P(R=T, W=T) = 0.16038
P(W=T)      = 0.44838

Result      = 0.3577 (35.77%)


==================================
   BAYESIAN NETWORK INFERENCE     
   (Wet Grass Caused by S or R)   
==================================

1. View Network Tables & Joint Probabilities
2. Query P(Rain | Wet Grass)
3. Query P(Sprinkler | Wet Grass)
4. Query P(Rain | Wet Grass, Sprinkler)
5. Exit

Enter selection (1-5): 3


Query: P(Sprinkler = True | WetGrass = True)

Formula:
P(S=T, W=T) / P(W=T)

P(S=T, W=T) = 0.28998
P(W=T)      = 0.44838

Result      = 0.6467 (64.67%)


==================================
   BAYESIAN NETWORK INFERENCE     
   (Wet Grass Caused by S or R)   
==================================

1. View Network Tables & Joint Probabilities
2. Query P(Rain | Wet Grass)
3. Query P(Sprinkler | Wet Grass)
4. Query P(Rain | Wet Grass, Sprinkler)
5. Exit

Enter selection (1-5): 4


Query: P(Rain = True | WetGrass = True, Sprinkler = True)

Formula:
P(R=T, S=T, W=T) / P(S=T, W=T)

P(R=T, S=T, W=T) = 0.00198
P(S=T, W=T)      = 0.28998

Result = 0.00683 (0.683%)

(Note the explaining away effect:
knowing the sprinkler was ON drastically
reduces the probability of rain.)
```

---

