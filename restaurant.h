// restaurant.h
#define _CRT_SECURE_NO_WARNINGS
// restaurant.h

#include <stdio.h>
#include <string.h>

typedef struct MenuItem {
    char name[50];
    int price;
    int quantity;
    struct MenuItem* next;
} MenuItem;

typedef struct {
    int tableNumber;
    MenuItem* orders; // now a linked list of orders
    int orderCount;
} Table;

void createProducts(MenuItem** menuHead);
void addItems(MenuItem* menuHead, char* name, int quantity);
void orderItem(Table tables[], int tableCount, int tableNumber, char* name, int quantity);
void removeItem(Table tables[], int tableCount, int tableNumber, char* name, int quantity);
void removeTable(Table tables[], int* tableCount, int tableNumber);
