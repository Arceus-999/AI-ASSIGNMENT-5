#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTITIES 100
#define MAX_RELATIONS 50
#define MAX_TRIPLES 200
#define NAME_LEN 50

typedef struct {
    int subjectId;
    int predicateId;
    int objectId;
} Triple;

char entities[MAX_ENTITIES][NAME_LEN];
int entityCount = 0;

char relations[MAX_RELATIONS][NAME_LEN];
int relationCount = 0;

Triple triples[MAX_TRIPLES];
int tripleCount = 0;

int getOrAddEntity(const char* name) {
    for (int i = 0; i < entityCount; i++) {
        if (strcmp(entities[i], name) == 0) {
            return i;
        }
    }
    if (entityCount < MAX_ENTITIES) {
        strcpy(entities[entityCount], name);
        return entityCount++;
    }
    return -1;
}

int getOrAddRelation(const char* name) {
    for (int i = 0; i < relationCount; i++) {
        if (strcmp(relations[i], name) == 0) {
            return i;
        }
    }
    if (relationCount < MAX_RELATIONS) {
        strcpy(relations[relationCount], name);
        return relationCount++;
    }
    return -1;
}

void addTriple(const char* subj, const char* pred, const char* obj) {
    int sId = getOrAddEntity(subj);
    int pId = getOrAddRelation(pred);
    int oId = getOrAddEntity(obj);

    if (sId != -1 && pId != -1 && oId != -1 && tripleCount < MAX_TRIPLES) {
        triples[tripleCount].subjectId = sId;
        triples[tripleCount].predicateId = pId;
        triples[tripleCount].objectId = oId;
        tripleCount++;
    }
}

void initDefaultGraph() {
    addTriple("Google", "developed", "TensorFlow");
    addTriple("Google", "acquired", "YouTube");
    addTriple("YouTube", "founded_by", "Steve_Chen");
    addTriple("Steve_Chen", "worked_at", "PayPal");
    addTriple("Elon_Musk", "co_founded", "PayPal");
    addTriple("Elon_Musk", "founded", "SpaceX");
    addTriple("SpaceX", "manufactures", "Falcon_9");
    addTriple("Falcon_9", "uses", "Merlin_Engine");
    addTriple("Tesla", "founded_by", "Elon_Musk");
    addTriple("Tesla", "manufactures", "Model_S");
}

void printAllTriples() {
    printf("\n=== KNOWLEDGE GRAPH TRIPLES ===\n");
    for (int i = 0; i < tripleCount; i++) {
        printf(" (%s, %s, %s)\n", 
               entities[triples[i].subjectId], 
               relations[triples[i].predicateId], 
               entities[triples[i].objectId]);
    }
    printf("================================\n\n");
}

void queryEntity(const char* name) {
    int eId = -1;
    for (int i = 0; i < entityCount; i++) {
        if (strcmp(entities[i], name) == 0) {
            eId = i;
            break;
        }
    }
    if (eId == -1) {
        printf("Entity '%s' not found in graph.\n", name);
        return;
    }

    printf("\n=== Semantic Facts for '%s' ===\n", name);
    int found = 0;
    for (int i = 0; i < tripleCount; i++) {
        if (triples[i].subjectId == eId) {
            printf("  %s --[%s]--> %s\n", name, relations[triples[i].predicateId], entities[triples[i].objectId]);
            found = 1;
        }
        if (triples[i].objectId == eId) {
            printf("  %s <--[%s]-- %s\n", name, relations[triples[i].predicateId], entities[triples[i].subjectId]);
            found = 1;
        }
    }
    if (!found) {
        printf("No connections found.\n");
    }
    printf("===============================\n\n");
}

int findPathDFS(int current, int target, int visited[], int path[], int edgePath[], int depth) {
    if (current == target) {
        return depth;
    }
    visited[current] = 1;
    for (int i = 0; i < tripleCount; i++) {
        if (triples[i].subjectId == current) {
            int next = triples[i].objectId;
            if (!visited[next]) {
                path[depth] = next;
                edgePath[depth] = triples[i].predicateId;
                int len = findPathDFS(next, target, visited, path, edgePath, depth + 1);
                if (len > 0) return len;
            }
        }
    }
    return 0;
}

void queryPath(const char* startName, const char* endName) {
    int startId = -1, endId = -1;
    for (int i = 0; i < entityCount; i++) {
        if (strcmp(entities[i], startName) == 0) startId = i;
        if (strcmp(entities[i], endName) == 0) endId = i;
    }
    if (startId == -1 || endId == -1) {
        printf("Error: One or both entities not found.\n");
        return;
    }

    int visited[MAX_ENTITIES] = {0};
    int path[MAX_ENTITIES];
    int edgePath[MAX_ENTITIES];

    int length = findPathDFS(startId, endId, visited, path, edgePath, 0);

    if (length > 0) {
        printf("\nSemantic Path Found:\n");
        printf("  %s", entities[startId]);
        for (int i = 0; i < length; i++) {
            printf(" --[%s]--> %s", relations[edgePath[i]], entities[path[i]]);
        }
        printf("\n\n");
    } else {
        printf("\nNo directed semantic path found between '%s' and '%s'.\n\n", startName, endName);
    }
}

int main() {
    initDefaultGraph();
    int choice = 0;
    char name1[NAME_LEN];
    char name2[NAME_LEN];

    while (1) {
        printf("==================================\n");
        printf("    IN-MEMORY KNOWLEDGE GRAPH     \n");
        printf("==================================\n");
        printf("1. View All Triples\n");
        printf("2. Query Entity Connections\n");
        printf("3. Find Semantic Relationship Path\n");
        printf("4. Exit\n");
        printf("Enter selection (1-4): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid selection.\n");
            continue;
        }

        if (choice == 1) {
            printAllTriples();
        } else if (choice == 2) {
            printf("Enter entity name (e.g. Google, Elon_Musk): ");
            scanf("%s", name1);
            queryEntity(name1);
        } else if (choice == 3) {
            printf("Enter start entity (e.g. Elon_Musk): ");
            scanf("%s", name1);
            printf("Enter target entity (e.g. Merlin_Engine): ");
            scanf("%s", name2);
            queryPath(name1, name2);
        } else if (choice == 4) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
