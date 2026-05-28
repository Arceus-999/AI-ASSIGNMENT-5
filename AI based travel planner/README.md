# AI Based Travel Planner in C

The **AI Based Travel Planner** generates personalized travel itineraries using user preferences such as destination, budget, trip duration, dietary requirements, and travel interests based on user input.

The planner combines:

* tourism recommendation logic
* preference-based filtering
* itinerary generation
* cost estimation
* knowledge graph style output

to create a realistic AI-inspired travel planning experience.

---

# User Input Options

The planner asks the user to provide several preferences.

---

## 1. Destination Selection

Users choose one destination from the following options:

```text
1. Tuscany, Italy
2. Bordeaux, France
3. Napa Valley, USA
4. Kyoto, Japan
```

The selected destination determines:

* available attractions
* cuisine recommendations
* beverages/wines
* regional pricing multiplier

---

## 2. Trip Duration

Users select the number of travel days.

Allowed range:

```text
1 to 5 days
```

The itinerary is generated separately for each day.

---

## 3. Budget Selection

The planner supports three budget categories:

| Option | Budget Type |
| ------ | ----------- |
| 1      | Budget      |
| 2      | Balanced    |
| 3      | Luxury      |

### Budget Effects

The budget changes:

* lodging costs
* transportation quality
* activity style
* meal pricing

Example:

* Budget → self-guided tours
* Luxury → private VIP experiences

---

## 4. Dietary Preferences

Users can select food preferences:

| Option | Preference  |
| ------ | ----------- |
| 1      | Standard    |
| 2      | Vegetarian  |
| 3      | Vegan       |
| 4      | Gluten-Free |

The program automatically selects suitable meal pairings for the chosen destination.

---

## 5. Interest Selection

Users choose their main travel focus.

| Option | Interest Type           |
| ------ | ----------------------- |
| 1      | Sightseeing & Landmarks |
| 2      | Food & Gastronomy       |
| 3      | Wine Tasting            |
| 4      | Outdoor Adventure       |

The planner prioritizes attractions related to the selected category.

Example:

* Selecting “Adventure” prioritizes hiking, rafting, kayaking, etc.
* Selecting “Wine Tasting” prioritizes vineyards and winery tours.

---

# Generated Output

After collecting all user preferences, the planner generates a detailed travel report.

---

## 1. Personalized Itinerary

The itinerary includes:

* morning activity
* afternoon activity
* dinner recommendation
* beverage pairing
* attraction descriptions

Example:

```text
[DAY 1]
10:00 AM : Private VIP visit: Florence Cathedral
02:30 PM : Chauffeured tour: Uffizi Gallery
07:30 PM : Gastronomic Pairing Dinner
```

---

## 2. Gastronomy Recommendations

The planner suggests:

* signature regional dishes
* wine or beverage pairings
* tasting profiles

These recommendations depend on:

* destination
* dietary preference

---

## 3. Cost Assessment Analysis

The application calculates estimated expenses for:

* accommodation
* food
* activities
* transportation

The final projected trip cost is displayed at the end.

Example:

```text
Total Projected Cost : $2450
```
# Sample Output

```text
==================================================
          GENERATED PERSONALIZED ITINERARY        
==================================================
Destination : Bordeaux Region
Duration    : 3 Days
Budget Level: Balanced
Diet        : Standard
--------------------------------------------------

[DAY 1]
  10:00 AM : La Cite du Vin
             (Explore the modern interactive museum dedicated to wine heritage.)

  02:30 PM : Cap Ferret Oyster Farms
             (Savour fresh oysters right at local fishermen cabins.)

  07:30 PM : Gastronomic Pairing Dinner
             Signature Dish: Magret de Canard
             (Pan-seared duck breast with a rich red wine reduction)

             Beverage Match: Pauillac Grand Cru

             Tasting Profile:
             Deep ruby-black, full-bodied with structured tannins,
             tobacco leaf, and cedar wood notes.


[DAY 2]
  10:00 AM : Place de la Bourse
             (Photograph the 18th-century palace reflected in the Water Mirror.)

  02:30 PM : Saint-Emilion Village
             (Wander through alleys and visit the monolithic church carved in solid rock.)

  07:30 PM : Gastronomic Pairing Dinner
             Signature Dish: Magret de Canard
             (Pan-seared duck breast with a rich red wine reduction)

             Beverage Match: Pauillac Grand Cru

             Tasting Profile:
             Deep ruby-black, full-bodied with structured tannins,
             tobacco leaf, and cedar wood notes.


[DAY 3]
  10:00 AM : Dune of Pilat Climb
             (Ascend Europe's tallest sand dune for a sunset over the Atlantic.)

  02:30 PM : Medoc Wine Road (D2)
             (Drive past legendary Chateaux like Margaux and Latour.)

  07:30 PM : Gastronomic Pairing Dinner
             Signature Dish: Magret de Canard
             (Pan-seared duck breast with a rich red wine reduction)

             Beverage Match: Pauillac Grand Cru

             Tasting Profile:
             Deep ruby-black, full-bodied with structured tannins,
             tobacco leaf, and cedar wood notes.


==================================================
               COST ASSESSMENT ANALYSIS           
==================================================

Accommodation Tariff        : $552
Gastronomy & Beverage Match : $293
Activities & Tours          : $207
Transit & Logistics         : $121

----------------------------------------------

Total Projected Cost        : $1173

==================================================


==================================================
           KNOWLEDGE ONTOLOGY GRAPH MAP           
==================================================

[Bordeaux Region Context]
        |
        +---> [Attractions Linked:
                La Cite du Vin,
                Cap Ferret Oyster Farms]

        |
        +---> [Gastronomy Recommendation:
                Magret de Canard]

                   |
                   v

        [Wine: Pauillac Grand Cru
         (Grapes: Cabernet Sauvignon,
          Merlot, Cabernet Franc)]

==================================================


===============================
       AETHERIA AI TRAVEL      
===============================

1. Create New Tour Plan
2. Exit

Enter choice (1-2):
```

