#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ATTRACTIONS 8

typedef struct {
    char name[100];
    char type[30];
    char desc[200];
} Attraction;

typedef struct {
    char name[100];
    char grapes[100];
    char profile[250];
    char standard_pairing[150];
    char vegetarian_pairing[150];
    char vegan_pairing[150];
    char gluten_free_pairing[150];
} WineOntology;

typedef struct {
    char name[30];
    double multiplier;
    Attraction attractions[MAX_ATTRACTIONS];
    WineOntology wine;
} Destination;

Destination destinations[4] = {
    {
        "Tuscany",
        1.0,
        {
            {"Florence Cathedral (Duomo)", "sightseeing", "Marvel at Brunelleschi's red-tiled dome and Giotto's bell tower."},
            {"Uffizi Gallery", "history", "Behold Renaissance masterpieces by Botticelli and Michelangelo."},
            {"Val d'Orcia Scenic Drive", "nature", "Roam through rolling golden wheat fields and cypress-lined driveways."},
            {"Siena's Piazza del Campo", "history", "Visit the shell-shaped square, home of the Palio horse race."},
            {"San Gimignano Towers", "history", "Walk through the medieval walled town famous for its stone towers."},
            {"Montalcino Vineyard Estates", "wine", "Tour historic cellars and sample prestigious Brunello di Montalcino."},
            {"Chianti Classico Hills", "wine", "Drive past ancient castles, olive groves, and vineyards."},
            {"Apuan Alps Hiking", "adventure", "Trek along peaks where Michelangelo sourced white marble."}
        },
        {
            "Chianti Classico DOCG",
            "Sangiovese, Canaiolo",
            "Bright ruby red, high acidity, firm tannins with aromas of sour cherry and oregano.",
            "Bistecca alla Fiorentina (T-bone steak grilled over charcoal with Tuscan olive oil)",
            "Pappardelle al Tartufo (Fresh egg pasta tossed in wild black truffle butter)",
            "Ribollita Toscana (Hearty bread, cannellini bean, and black cabbage stew)",
            "Risotto ai Funghi Porcini (Creamy arborio rice with fresh wild porcini mushrooms)"
        }
    },
    {
        "Bordeaux",
        1.15,
        {
            {"Place de la Bourse", "sightseeing", "Photograph the 18th-century palace reflected in the Water Mirror."},
            {"La Cite du Vin", "gastronomy", "Explore the modern interactive museum dedicated to wine heritage."},
            {"Saint-Emilion Village", "history", "Wander through alleys and visit the monolithic church carved in solid rock."},
            {"Dune of Pilat Climb", "nature", "Ascend Europe's tallest sand dune for a sunset over the Atlantic."},
            {"Medoc Wine Road (D2)", "wine", "Drive past legendary Chateaux like Margaux and Latour."},
            {"Cap Ferret Oyster Farms", "gastronomy", "Savour fresh oysters right at local fishermen cabins."},
            {"Bordeaux Public Gardens", "nature", "Stroll through English-style botanical gardens with historic glasshouses."},
            {"Garonne River Kayaking", "adventure", "Paddle under Bordeaux's iconic stone bridges at twilight."}
        },
        {
            "Pauillac Grand Cru",
            "Cabernet Sauvignon, Merlot, Cabernet Franc",
            "Deep ruby-black, full-bodied with structured tannins, tobacco leaf, and cedar wood notes.",
            "Magret de Canard (Pan-seared duck breast with a rich red wine reduction)",
            "Cepes a la Bordelaise (Pan-roasted local porcini mushrooms with garlic)",
            "Lentilles du Puy (French green lentils braised with carrots and thyme)",
            "Entrecote Sauce Marchand de Vin (Gluten-free pan-seared steak in red wine shallot sauce)"
        }
    },
    {
        "Napa Valley",
        1.35,
        {
            {"Oxbow Public Market", "gastronomy", "Graze on local oysters, organic pizzas, and artisanal charcuterie."},
            {"Castello di Amorosa", "wine", "Tour an authentic 121,000 square foot medieval castle replica."},
            {"Napa Valley Wine Train", "sightseeing", "Dine in restored vintage Pullman cars rolling past vineyards."},
            {"Skyline Wilderness Park Trail", "adventure", "Hike past wild oaks to viewpoints overlooking the valley floor."},
            {"Calistoga Geothermal Hot Springs", "nature", "Rejuvenate in volcanic mineral mud baths and thermal spring waters."},
            {"Robert Mondavi Winery", "wine", "Tour the famous winery that pioneered modern California winemaking."},
            {"Yountville Art Walk", "sightseeing", "Stroll past outdoor sculptures in Napa's culinary capital."},
            {"Lake Berryessa Watersports", "adventure", "Rent a paddleboard or kayak on California's largest lake."}
        },
        {
            "Oakville Cabernet Sauvignon",
            "Cabernet Sauvignon, Merlot",
            "Rich purple, bold velvet tannins, luxurious aromas of blackberry and cocoa.",
            "Prime Dry-Aged Ribeye Steak grilled with fresh rosemary and garlic butter",
            "Portobello Mushroom Steak caps grilled with balsamic glaze and blue cheese",
            "Smoky Barbecue Tempeh steaks accompanied by fire-roasted tomatoes",
            "Red-Wine Braised Short Ribs served over creamy stone-ground polenta"
        }
    },
    {
        "Kyoto",
        0.95,
        {
            {"Fushimi Inari Shrine", "sightseeing", "Hike up the mountain paths under thousands of red Torii gates."},
            {"Kinkaku-ji (Golden Pavilion)", "history", "View the Zen temple whose top two floors are covered in pure gold leaf."},
            {"Arashiyama Bamboo Grove", "nature", "Listen to the wind rustling through soaring, emerald-green bamboo."},
            {"Kiyomizu-dera Temple", "history", "Stand on the wooden stage built without nails, overlooking cherry trees."},
            {"Gion Geisha District", "sightseeing", "Walk past traditional wooden machiya houses illuminated by lanterns."},
            {"Fushimi Sake District Tour", "wine", "Visit traditional breweries alongside willow-lined canals."},
            {"Nishiki Market Culinary Tour", "gastronomy", "Taste Kyoto specialties like octopus skewers and matcha."},
            {"Hozugawa River Rafting", "adventure", "Navigate rapids in a traditional wooden boat through gorges."}
        },
        {
            "Junmai Daiginjo Sake",
            "Yamada Nishiki Sake Rice",
            "Light and aromatic with notes of white peach, melon, and a dry umami finish.",
            "Kyoto Kaiseki (Traditional course feast featuring seasonal sushi and wagyu beef)",
            "Yudofu (Silken tofu simmered in a kelp broth with ginger and scallions)",
            "Shojin Ryori (Buddhist temple cuisine featuring tempura and sesame tofu)",
            "Saikyo Yaki (Sablefish marinated in sweet white miso and grilled)"
        }
    }
};

void runPlanner() {
    int destChoice = 0;
    int duration = 3;
    int budgetChoice = 1;
    int dietChoice = 0;
    int interestChoice = 0;

    printf("\n=== AETHERIA TRAVEL PLANNER CONSOLE ===\n");
    printf("1. Tuscany, Italy\n");
    printf("2. Bordeaux, France\n");
    printf("3. Napa Valley, USA\n");
    printf("4. Kyoto, Japan\n");
    printf("Select Destination (1-4): ");
    if (scanf("%d", &destChoice) != 1) return;
    destChoice--;
    if (destChoice < 0 || destChoice > 3) {
        printf("Invalid destination.\n");
        return;
    }

    printf("\nEnter Trip Duration in Days (1-5): ");
    if (scanf("%d", &duration) != 1) return;
    if (duration < 1 || duration > 5) {
        printf("Invalid duration.\n");
        return;
    }

    printf("\nBudget Assessment Tiers:\n");
    printf("1. Budget\n");
    printf("2. Balanced\n");
    printf("3. Luxury\n");
    printf("Select Budget (1-3): ");
    if (scanf("%d", &budgetChoice) != 1) return;
    budgetChoice--;

    printf("\nDietary Preferences:\n");
    printf("1. Standard (No Restrictions)\n");
    printf("2. Vegetarian\n");
    printf("3. Vegan\n");
    printf("4. Gluten-Free\n");
    printf("Select Diet (1-4): ");
    if (scanf("%d", &dietChoice) != 1) return;
    dietChoice--;

    printf("\nAI Core Focus Areas:\n");
    printf("1. Sightseeing & Landmarks\n");
    printf("2. Food & Gastronomy\n");
    printf("3. Wine Tasting & Chateaux\n");
    printf("4. Outdoor Adventure\n");
    printf("Select Primary Focus (1-4): ");
    if (scanf("%d", &interestChoice) != 1) return;
    interestChoice--;

    char focusType[30];
    if (interestChoice == 0) strcpy(focusType, "sightseeing");
    else if (interestChoice == 1) strcpy(focusType, "gastronomy");
    else if (interestChoice == 2) strcpy(focusType, "wine");
    else if (interestChoice == 3) strcpy(focusType, "adventure");
    else strcpy(focusType, "sightseeing");

    Destination dest = destinations[destChoice];

    Attraction pool[MAX_ATTRACTIONS];
    int poolCount = 0;

    for (int i = 0; i < MAX_ATTRACTIONS; i++) {
        if (strcmp(dest.attractions[i].type, focusType) == 0) {
            pool[poolCount++] = dest.attractions[i];
        }
    }
    for (int i = 0; i < MAX_ATTRACTIONS; i++) {
        if (strcmp(dest.attractions[i].type, focusType) != 0) {
            pool[poolCount++] = dest.attractions[i];
        }
    }

    printf("\n==================================================\n");
    printf("          GENERATED PERSONALIZED ITINERARY        \n");
    printf("==================================================\n");
    printf("Destination : %s Region\n", dest.name);
    printf("Duration    : %d Days\n", duration);
    printf("Budget Level: %s\n", (budgetChoice == 0) ? "Budget" : (budgetChoice == 1) ? "Balanced" : "Luxury");
    printf("Diet        : %s\n", (dietChoice == 0) ? "Standard" : (dietChoice == 1) ? "Vegetarian" : (dietChoice == 2) ? "Vegan" : "Gluten-Free");
    printf("--------------------------------------------------\n");

    int poolIdx = 0;
    char dish[150];
    if (dietChoice == 1) strcpy(dish, dest.wine.vegetarian_pairing);
    else if (dietChoice == 2) strcpy(dish, dest.wine.vegan_pairing);
    else if (dietChoice == 3) strcpy(dish, dest.wine.gluten_free_pairing);
    else strcpy(dish, dest.wine.standard_pairing);

    for (int d = 1; d <= duration; d++) {
        Attraction morning = pool[poolIdx++];
        Attraction afternoon = pool[poolIdx++];

        char mPrefix[30] = "";
        char aPrefix[30] = "";
        if (budgetChoice == 0) {
            strcpy(mPrefix, "Self-guided: ");
            strcpy(aPrefix, "Free walk: ");
        } else if (budgetChoice == 2) {
            strcpy(mPrefix, "Private VIP visit: ");
            strcpy(aPrefix, "Chauffeured tour: ");
        }

        printf("[DAY %d]\n", d);
        printf("  10:00 AM : %s%s\n", mPrefix, morning.name);
        printf("             (%s)\n", morning.desc);
        printf("  02:30 PM : %s%s\n", aPrefix, afternoon.name);
        printf("             (%s)\n", afternoon.desc);
        printf("  07:30 PM : Gastronomic Pairing Dinner\n");
        printf("             Signature Dish: %s\n", dish);
        printf("             Beverage Match: %s\n", dest.wine.name);
        printf("             Tasting Profile: %s\n", dest.wine.profile);
        printf("\n");
    }

    double baseLodging = (budgetChoice == 0) ? 60.0 : (budgetChoice == 1) ? 160.0 : 480.0;
    double baseFood = (budgetChoice == 0) ? 35.0 : (budgetChoice == 1) ? 85.0 : 240.0;
    double baseActivities = (budgetChoice == 0) ? 20.0 : (budgetChoice == 1) ? 60.0 : 220.0;
    double baseTransit = (budgetChoice == 0) ? 15.0 : (budgetChoice == 1) ? 35.0 : 130.0;

    double mult = dest.multiplier;
    double costLodging = baseLodging * duration * mult;
    double costFood = baseFood * duration * mult;
    double costActivities = baseActivities * duration * mult;
    double costTransit = baseTransit * duration * mult;
    double totalCost = costLodging + costFood + costActivities + costTransit;

    printf("==================================================\n");
    printf("               COST ASSESSMENT ANALYSIS           \n");
    printf("==================================================\n");
    printf("  Accommodation Tariff        : $%.0f\n", costLodging);
    printf("  Gastronomy & Beverage Match : $%.0f\n", costFood);
    printf("  Activities & Tours          : $%.0f\n", costActivities);
    printf("  Transit & Logistics         : $%.0f\n", costTransit);
    printf("  ----------------------------------------------\n");
    printf("  Total Projected Cost        : $%.0f\n", totalCost);
    printf("==================================================\n");

    printf("\n==================================================\n");
    printf("           KNOWLEDGE ONTOLOGY GRAPH MAP           \n");
    printf("==================================================\n");
    printf(" [%s Region Context]\n", dest.name);
    printf("        |\n");
    printf("        +---> [Attractions Linked: %s, %s]\n", pool[0].name, pool[1].name);
    printf("        |\n");
    printf("        +---> [Gastronomy Recommendation: %s]\n", dish);
    printf("                   |\n");
    printf("                   v (Pairs With Region's Wine Node)\n");
    printf("              [Wine: %s (Grapes: %s)]\n", dest.wine.name, dest.wine.grapes);
    printf("==================================================\n\n");
}

int main() {
    srand((unsigned int)time(NULL));
    int menuChoice = 0;
    while (1) {
        printf("===============================\n");
        printf("       AETHERIA AI TRAVEL      \n");
        printf("===============================\n");
        printf("1. Create New Tour Plan\n");
        printf("2. Exit\n");
        printf("Enter choice (1-2): ");
        if (scanf("%d", &menuChoice) != 1) {
            while (getchar() != '\n');
            printf("Invalid selection.\n");
            continue;
        }

        if (menuChoice == 1) {
            runPlanner();
        } else if (menuChoice == 2) {
            printf("Exiting planner.\n");
            break;
        } else {
            printf("Invalid selection.\n");
        }
    }
    return 0;
}
