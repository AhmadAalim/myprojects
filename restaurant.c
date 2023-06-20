#define _CRT_SECURE_NO_WARNINGS
// restaurant.c

#include "restaurant.h"
#include <stdlib.h> // for malloc and free

void createProducts(MenuItem** menuHead) {
    FILE* file = fopen("Manot.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    MenuItem* lastItem = NULL;
    while (!feof(file)) {
        MenuItem* newItem = (MenuItem*)malloc(sizeof(MenuItem));
        if (fscanf(file, "%s %d %d", newItem->name, &newItem->price, &newItem->quantity) != 3) {
            free(newItem);
            continue;
        }

        newItem->next = NULL;
        if (lastItem == NULL) {
            *menuHead = newItem;
        }
        else {
            lastItem->next = newItem;
        }
        lastItem = newItem;
    }

    fclose(file);
    printf("The kitchen was created\n");
}

void addItems(MenuItem* menuHead, char* name, int quantity) {
    if (quantity <= 0) {
        printf("Error: Quantity must be a positive number\n");
        return;
    }

    MenuItem* current = menuHead;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->quantity += quantity;
            printf("%d %s were added to the kitchen\n", quantity, name);
            return;
        }
        current = current->next;
    }

    printf("We don’t have %s, sorry!\n", name);
}

void orderItem(Table tables[], int tableCount, int tableNumber, char* name, int quantity) {
    if (tableNumber < 0 || tableNumber >= tableCount) {
        printf("Error: Invalid table number\n");
        return;
    }

    if (quantity <= 0) {
        printf("Error: Quantity must be a positive number\n");
        return;
    }

    MenuItem* menuHead = tables[tableNumber].orders;
    MenuItem* current = menuHead;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->quantity < quantity) {
                printf("Error: Not enough quantity in stock for %s\n", name);
                return;
            }

            MenuItem* newOrder = (MenuItem*)malloc(sizeof(MenuItem));
            strcpy(newOrder->name, name);
            newOrder->quantity = quantity;
            newOrder->price = current->price;
            newOrder->next = tables[tableNumber].orders;
            tables[tableNumber].orders = newOrder;

            current->quantity -= quantity;
            printf("%d %s were added to the table number %d\n", quantity, name, tableNumber);
            return;
        }
        current = current->next;
    }

    printf("We don’t have %s, sorry!\n", name);
}

void removeItem(Table tables[], int tableCount, int tableNumber, char* name, int quantity) {
    if (tableNumber < 0 || tableNumber >= tableCount) {
        printf("Error: Invalid table number\n");
        return;
    }

    if (quantity <= 0) {
        printf("Error: Quantity must be a positive number\n");
        return;
    }

    MenuItem** current = &tables[tableNumber].orders;
    while (*current != NULL) {
        if (strcmp((*current)->name, name) == 0) {
            if ((*current)->quantity < quantity) {
                printf("Error: Not enough quantity in order for %s\n", name);
                return;
            }

            (*current)->quantity -= quantity;
            if ((*current)->quantity == 0) {
                MenuItem* toDelete = *current;
                *current = (*current)->next;
                free(toDelete);
            }
            printf("%d %s was returned to the kitchen from table number %d\n", quantity, name, tableNumber);
            return;
        }
        current = &(*current)->next;
    }

    printf("Error: Item %s not found in orders\n", name);
}

void removeTable(Table tables[], int* tableCount, int tableNumber) {
    if (tableNumber < 0 || tableNumber >= *tableCount) {
        printf("Error: Invalid table number\n");
        return;
    }

    MenuItem* current = tables[tableNumber].orders;
    if (current == NULL) {
        printf("The table number %d is not ordered yet\n", tableNumber);
        return;
    }

    int total = 0;
    while (current != NULL) {
        total += current->quantity * current->price;
        MenuItem* toDelete = current;
        current = current->next;
        free(toDelete);
    }

    printf("%d Pasta. %d nis+%d nis for tips, please!\n", total / 30, total, total / 10);

    // shift the tables down to fill the gap
    for (int i = tableNumber + 1; i < *tableCount; i++) {
        tables[i - 1] = tables[i];
    }
    (*tableCount)--;
}
