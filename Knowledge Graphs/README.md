# Knowledge Graphs

This project is a console-based implementation of an **In-Memory Knowledge Graph System** .

The application stores semantic relationships between entities using the concept of **triples**:

```text
(Subject, Predicate, Object)
```

Example:

```text
(Google, developed, TensorFlow)
```

The program allows users to:

* view all stored semantic triples
* query relationships of entities
* discover semantic paths between connected entities


# Core Concept

The project models information as a graph where:

* **Entities** represent objects or concepts
* **Relations** describe how entities are connected
* **Triples** store semantic facts

Each triple follows the structure:

```text
(Subject, Predicate, Object)
```

Example:

```text
(Elon_Musk, founded, SpaceX)
```

This means:

* Subject → Elon_Musk
* Predicate → founded
* Object → SpaceX

---

# Data Structures Used

The project uses the following structures:

## 1. Triple Structure

Stores one semantic relationship.

```c
typedef struct {
    int subjectId;
    int predicateId;
    int objectId;
} Triple;
```

---

## 2. Entity Storage

Stores all unique entities.

Examples:

* Google
* SpaceX
* Tesla
* TensorFlow

---

## 3. Relation Storage

Stores relationship types.

Examples:

* developed
* founded
* acquired
* manufactures

---

# Default Knowledge Graph

The graph is automatically initialized with predefined semantic relationships.

Examples include:

| Subject   | Relation   | Object        |
| --------- | ---------- | ------------- |
| Google    | developed  | TensorFlow    |
| Google    | acquired   | YouTube       |
| Elon_Musk | founded    | SpaceX        |
| Tesla     | founded_by | Elon_Musk     |
| Falcon_9  | uses       | Merlin_Engine |


---

# Program Functionalities

## 1. View All Triples

Displays every semantic relationship stored in the graph.

Example:

```text
(Google, developed, TensorFlow)
```

---

## 2. Query Entity Connections

Allows users to search for all incoming and outgoing relationships of a specific entity.

Example query:

```text
Google
```

Output:

```text
Google --[developed]--> TensorFlow
Google --[acquired]--> YouTube
```

---

## 3. Find Semantic Relationship Path

The system can discover relationship paths between two entities using **Depth-First Search (DFS)**.

Example:

```text
Elon_Musk → Merlin_Engine
```

Discovered Path:

```text
Elon_Musk
   ↓ founded
SpaceX
   ↓ manufactures
Falcon_9
   ↓ uses
Merlin_Engine
```

---

# Algorithm Used

## Depth-First Search (DFS)

The project uses DFS to discover directed semantic paths between entities.

### DFS Process

1. Start from source entity
2. Explore connected nodes recursively
3. Track visited entities
4. Stop when target entity is reached

---

# Output

## Main Menu

```text
==================================
    IN-MEMORY KNOWLEDGE GRAPH     
==================================

1. View All Triples
2. Query Entity Connections
3. Find Semantic Relationship Path
4. Exit

Enter selection (1-4):
```

---

## Viewing All Triples

```text
=== KNOWLEDGE GRAPH TRIPLES ===

(Google, developed, TensorFlow)
(Google, acquired, YouTube)
(YouTube, founded_by, Steve_Chen)
(Steve_Chen, worked_at, PayPal)
(Elon_Musk, co_founded, PayPal)
(Elon_Musk, founded, SpaceX)
(SpaceX, manufactures, Falcon_9)
(Falcon_9, uses, Merlin_Engine)
(Tesla, founded_by, Elon_Musk)
(Tesla, manufactures, Model_S)

================================
```

---

## Query Entity Example

Input:

```text
Google
```

Output:

```text
=== Semantic Facts for 'Google' ===

Google --[developed]--> TensorFlow
Google --[acquired]--> YouTube

===============================
```

---

## Semantic Path Example

Input:

```text
Start Entity : Elon_Musk
Target Entity: Merlin_Engine
```

Output:

```text
Semantic Path Found:

Elon_Musk --[founded]--> SpaceX
SpaceX --[manufactures]--> Falcon_9
Falcon_9 --[uses]--> Merlin_Engine
```

