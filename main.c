// main.c
#define _CRT_SECURE_NO_WARNINGS
#include "restaurant.h"
#define K 50 // define the maximum number of tables

int main() {
    MenuItem* menu = NULL;

    Table tables[K]; // use K as the maximum number of tables
    int tableCount = K; // initialize all tables

    for (int i = 0; i < tableCount; i++) {
        tables[i].tableNumber = i;
        tables[i].orders = NULL;
        tables[i].orderCount = 0;
    }

    FILE* file = fopen("Instructions.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int command;
    while (fscanf(file, "%d", &command) == 1) {
        switch (command) {
        case 1: {
            createProducts(&menu);
            break;
        }
        case 2: {
            char name[50];
            int quantity;
            fscanf(file, "%s %d", name, &quantity);
            addItems(menu, name, quantity);
            break;
        }
        case 3: {
            int tableNumber;
            char name[50];
            int quantity;
            fscanf(file, "%d %s %d", &tableNumber, name, &quantity);
            orderItem(tables, tableCount, tableNumber - 1, name, quantity); // subtract 1 from tableNumber
            break;
        }
        case 4: {
            int tableNumber;
            char name[50];
            int quantity;
            fscanf(file, "%d %s %d", &tableNumber, name, &quantity);
            removeItem(tables, tableCount, tableNumber - 1, name, quantity); // subtract 1 from tableNumber
            break;
        }
        case 5: {
            int tableNumber;
            fscanf(file, "%d", &tableNumber);
            removeTable(tables, &tableCount, tableNumber - 1); // subtract 1 from tableNumber
            break;
        }
        default: {
            printf("Invalid command\n");
            break;
        }
        }
    }

    fclose(file);
    return 0;
}

