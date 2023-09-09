#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 30

// Struct for Pokemon
typedef struct Pokemon {
    char name[MAX_NAME_LENGTH];
    char type[MAX_NAME_LENGTH];
    char ability[MAX_NAME_LENGTH];
    struct Pokemon* next;
} Pokemon;

// Struct for Players
typedef struct Player {
    char name[MAX_NAME_LENGTH];
    int pokemonCount;
    Pokemon** pokemonList; // Dynamic array of pointers to Pokemon
    struct Player* next;
} Player;

// Create new Pokemon
Pokemon* NewPokemon(char* name, char* type, char* ability) {
    Pokemon* newPokemon = (Pokemon*)malloc(sizeof(Pokemon));
    if (newPokemon != NULL) {
        strcpy(newPokemon->name, name);
        strcpy(newPokemon->type, type);
        strcpy(newPokemon->ability, ability);
        newPokemon->next = NULL;
    }
    return newPokemon;
}

// Add Pokemon to the Pokemon list
void AddPokemonToList(Pokemon** head_ref, char* name, char* type, char* ability) {
    if (*head_ref == NULL) {
        *head_ref = NewPokemon(name, type, ability);
    } else {
        Pokemon* current = *head_ref;
        while (current->next != NULL) {
            if (strcmp(name, current->name) == 0) {
                // Check for duplicates 
                return;
            }
            current = current->next;
        }
        // Add new Pokemon to the end of the list
        current->next = NewPokemon(name, type, ability);
    }
}

// Find Pokemon by name
Pokemon* FindPokemon(Pokemon* node, char* name) {
    while (node != NULL) {
        if (strcmp(name, node->name) == 0) {
            return node;
        }
        node = node->next;
    }
    return NULL; // Pokemon not found
}

// Display Pokemon details
void DisplayPokemonDetails(Pokemon* node, char* name) {
    Pokemon* foundPokemon = FindPokemon(node, name);
    if (foundPokemon != NULL) {
        printf("Pokemon Found!\n");
        printf("Pokemon name: %s\n", foundPokemon->name);
        printf("Pokemon type: %s\n", foundPokemon->type);
        printf("Pokemon ability: %s\n", foundPokemon->ability);
    } else {
        printf("Pokemon not found\n");
    }
}

// Create new Player
Player* NewPlayer(char* name) {
    Player* newPlayer = (Player*)malloc(sizeof(Player));
    if (newPlayer != NULL) {
        strcpy(newPlayer->name, name);
        newPlayer->pokemonCount = 0;
        newPlayer->pokemonList = NULL; // Initialize the dynamic array as NULL
        newPlayer->next = NULL;
    }
    return newPlayer;
}

// Add Player to the Player list
void AddPlayerToList(Player** head_ref, char* name) {
    if (*head_ref == NULL) {
        *head_ref = NewPlayer(name);
    } else {
        Player* current = *head_ref;
        while (current->next != NULL) {
            if (strcmp(name, current->name) == 0) {
                // Check for duplicates
                return;
            }
            current = current->next;
        }
        // Add new Player to the end of the list
        current->next = NewPlayer(name);
    }
}

// Find Player by name
Player* FindPlayer(Player* node, char* name) {
    while (node != NULL) {
        if (strcmp(name, node->name) == 0) {
            return node;
        }
        node = node->next;
    }
    return NULL; // Player not found
}

// Display Player details
void DisplayPlayerDetails(Player* node, char* name) {
    Player* foundPlayer = FindPlayer(node, name);
    if (foundPlayer != NULL) {
        printf("Player Found!\n");
        printf("Player name: %s\n", foundPlayer->name);
        printf("Pokemon owned: %d\n", foundPlayer->pokemonCount);
        if (foundPlayer->pokemonCount > 0) {
            printf("Pokemon owned:\n");
            for (int i = 0; i < foundPlayer->pokemonCount; i++) {
                printf("  %s\n", foundPlayer->pokemonList[i]->name);
            }
        }
    } else {
        printf("Player not found\n");
    }
}

// Add Pokemon to Players collection
void AddPokemonToPlayer(Player* player, Pokemon* pokemon) {
    if (player != NULL && pokemon != NULL) {
        // Check if Pokemon already in Players collection
        for (int i = 0; i < player->pokemonCount; i++) {
            if (player->pokemonList[i] == pokemon) {
                printf("%s already exists in %s's collection.\n", pokemon->name, player->name);
                return;
            }
        }

        // Check if Players collection needs to be resized
        if (player->pokemonCount == 0 || player->pokemonList == NULL) {
            player->pokemonList = (Pokemon**)malloc(sizeof(Pokemon*));
        } else {
            player->pokemonList = (Pokemon**)realloc(player->pokemonList,
                                                      (player->pokemonCount + 1) * sizeof(Pokemon*));
        }

        if (player->pokemonList != NULL) {
            player->pokemonList[player->pokemonCount] = pokemon;
            player->pokemonCount++;
            printf("%s added to %s's collection!\n", pokemon->name, player->name);
        } else {
            printf("Memory allocation failed.\n");
        }
    }
}

int main() {
    Pokemon* pokemonHead = NULL;
    Player* playerHead = NULL;

    // Add Pokemon 
    AddPokemonToList(&pokemonHead, "Charizard", "Flame", "Blaze");
    AddPokemonToList(&pokemonHead, "Charazard", "Flame", "Blaze");
    AddPokemonToList(&pokemonHead, "Bulbasaur", "Seed", "Overgrow");
    AddPokemonToList(&pokemonHead, "Blastoise", "Shellfish", "Torrent");
    AddPokemonToList(&pokemonHead, "Pidgey", "Tiny Bird", "Keen Eye");
    AddPokemonToList(&pokemonHead, "Pikachu", "Mouse", "Static");
    AddPokemonToList(&pokemonHead, "Metapod", "Cocoon", "Shed Skin");
    AddPokemonToList(&pokemonHead, "Sandshrew", "Mouse", "Sand veil");
    AddPokemonToList(&pokemonHead, "Clefairy", "Fairy", "Magic Guard");
    AddPokemonToList(&pokemonHead, "Diglet", "Mole", "Arena Trap");

    // Add Players 
    AddPlayerToList(&playerHead, "Ash");
    AddPlayerToList(&playerHead, "Cynthia");
    AddPlayerToList(&playerHead, "Lance");
    AddPlayerToList(&playerHead, "Tobias");
    AddPlayerToList(&playerHead, "Alain");
    AddPlayerToList(&playerHead, "Leon");

    int choice;
    char nameInput[MAX_NAME_LENGTH];

    while (true) {
        printf("\nMenu:\n");
        printf("1. View Pokemon\n");
        printf("2. View Players\n");
        printf("3. Add Pokemon to Player\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1: // View Pokemon
                printf("\nEnter the name of the Pokemon you want to see: ");
                scanf("%s", nameInput);
                fflush(stdin);
                DisplayPokemonDetails(pokemonHead, nameInput);
                break;
            case 2: // View Players
                printf("\nEnter the name of the Player you want to see: ");
                scanf("%s", nameInput);
                fflush(stdin);
                DisplayPlayerDetails(playerHead, nameInput);
                break;
            case 3: // Add Pokemon to Player
                printf("\nEnter the name of the Player you want to add Pokemon to: ");
                scanf("%s", nameInput);
                fflush(stdin);
                Player* player = FindPlayer(playerHead, nameInput);

                if (player != NULL) {
                    printf("Enter the name of the Pokemon you want to add: ");
                    scanf("%s", nameInput);
                    fflush(stdin);
                    Pokemon* pokemon = FindPokemon(pokemonHead, nameInput);

                    if (pokemon != NULL) {
                        AddPokemonToPlayer(player, pokemon);
                        printf("%s added to %s's collection!\n", nameInput, player->name);
                    } else {
                        printf("Pokemon not found.\n");
                    }
                } else {
                    printf("Player not found.\n");
                }
                break;
            case 4: // Quit
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    // Free allocated memory before exiting
    while (pokemonHead != NULL) {
        Pokemon* temp = pokemonHead;
        pokemonHead = pokemonHead->next;
        free(temp);
    }

    while (playerHead != NULL) {
        Player* temp = playerHead;
        playerHead = playerHead->next;
        // Free the dynamic array of Pokemon
        for (int i = 0; i < temp->pokemonCount; i++) {
            free(temp->pokemonList[i]);
        }
        free(temp);
    }

    return 0;
}