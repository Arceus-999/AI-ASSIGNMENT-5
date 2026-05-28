#include <stdio.h>
#include <stdlib.h>

double getJointProb(int r, int s, int w) {
    double pR = r ? 0.2 : 0.8;
    double pS;
    if (r) {
        pS = s ? 0.01 : 0.99;
    } else {
        pS = s ? 0.40 : 0.60;
    }
    double pW;
    if (s && r) pW = w ? 0.99 : 0.01;
    else if (s && !r) pW = w ? 0.90 : 0.10;
    else if (!s && r) pW = w ? 0.80 : 0.20;
    else pW = w ? 0.00 : 1.00;

    return pR * pS * pW;
}

void printTables() {
    printf("\n=== CONDITIONAL PROBABILITY TABLES (CPT) ===\n");
    printf("P(Rain = True) = 0.2\n\n");
    printf("P(Sprinkler = True | Rain):\n");
    printf("  P(S=T | R=T) = 0.01\n");
    printf("  P(S=T | R=F) = 0.40\n\n");
    printf("P(WetGrass = True | Sprinkler, Rain):\n");
    printf("  P(W=T | S=T, R=T) = 0.99\n");
    printf("  P(W=T | S=T, R=F) = 0.90\n");
    printf("  P(W=T | S=F, R=T) = 0.80\n");
    printf("  P(W=T | S=F, R=F) = 0.00\n");

    printf("\n=== JOINT DISTRIBUTION P(R, S, W) ===\n");
    for (int r = 1; r >= 0; r--) {
        for (int s = 1; s >= 0; s--) {
            for (int w = 1; w >= 0; w--) {
                printf("  P(R=%c, S=%c, W=%c) = %.5f\n", 
                       r ? 'T' : 'F', s ? 'T' : 'F', w ? 'T' : 'F', 
                       getJointProb(r, s, w));
            }
        }
    }
    printf("\n");
}

void queryRainGivenWet() {
    double numerator = 0.0;
    double denominator = 0.0;

    for (int s = 0; s <= 1; s++) {
        numerator += getJointProb(1, s, 1);
    }
    for (int r = 0; r <= 1; r++) {
        for (int s = 0; s <= 1; s++) {
            denominator += getJointProb(r, s, 1);
        }
    }
    printf("\nQuery: P(Rain = True | WetGrass = True)\n");
    printf("  Formula: P(R=T, W=T) / P(W=T)\n");
    printf("  P(R=T, W=T) = %.5f\n", numerator);
    printf("  P(W=T)      = %.5f\n", denominator);
    printf("  Result      = %.4f (%.2f%%)\n\n", numerator / denominator, (numerator / denominator) * 100.0);
}

void querySprinklerGivenWet() {
    double numerator = 0.0;
    double denominator = 0.0;

    for (int r = 0; r <= 1; r++) {
        numerator += getJointProb(r, 1, 1);
    }
    for (int r = 0; r <= 1; r++) {
        for (int s = 0; s <= 1; s++) {
            denominator += getJointProb(r, s, 1);
        }
    }
    printf("\nQuery: P(Sprinkler = True | WetGrass = True)\n");
    printf("  Formula: P(S=T, W=T) / P(W=T)\n");
    printf("  P(S=T, W=T) = %.5f\n", numerator);
    printf("  P(W=T)      = %.5f\n", denominator);
    printf("  Result      = %.4f (%.2f%%)\n\n", numerator / denominator, (numerator / denominator) * 100.0);
}

void queryRainGivenWetAndSprinkler() {
    double numerator = getJointProb(1, 1, 1);
    double denominator = 0.0;

    for (int r = 0; r <= 1; r++) {
        denominator += getJointProb(r, 1, 1);
    }
    printf("\nQuery: P(Rain = True | WetGrass = True, Sprinkler = True)\n");
    printf("  Formula: P(R=T, S=T, W=T) / P(S=T, W=T)\n");
    printf("  P(R=T, S=T, W=T) = %.5f\n", numerator);
    printf("  P(S=T, W=T)      = %.5f\n", denominator);
    printf("  Result           = %.5f (%.3f%%)\n", numerator / denominator, (numerator / denominator) * 100.0);
    printf("  (Note the explaining away effect: knowing the sprinkler was on drastically reduces the probability of rain!)\n\n");
}

int main() {
    int choice = 0;
    while (1) {
        printf("==================================\n");
        printf("   BAYESIAN NETWORK INFERENCE     \n");
        printf("   (Wet Grass Caused by S or R)   \n");
        printf("==================================\n");
        printf("1. View Network Tables & Joint Probabilities\n");
        printf("2. Query P(Rain | Wet Grass)\n");
        printf("3. Query P(Sprinkler | Wet Grass)\n");
        printf("4. Query P(Rain | Wet Grass, Sprinkler)\n");
        printf("5. Exit\n");
        printf("Enter selection (1-5): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid selection.\n");
            continue;
        }

        if (choice == 1) {
            printTables();
        } else if (choice == 2) {
            queryRainGivenWet();
        } else if (choice == 3) {
            querySprinklerGivenWet();
        } else if (choice == 4) {
            queryRainGivenWetAndSprinkler();
        } else if (choice == 5) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}

