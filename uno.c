#include<stdio.h>
#include<stdlib.h>

//Main deck containing all the cards
struct  DeckStack
{
    char num;
    char color;
    struct Deckstack * next;
};

//Stack to Deposit cards
struct DepStack
{
    char num;
    char color;
    struct DepStack * next;   
};

//Player 1
struct Player{
    char num;
    char color;
    struct Player * next;   
};  

struct Computer{
    char num;
    char color;
    struct Computer * next;   
};