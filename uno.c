#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

//Main deck containing all the cards
struct  Stack
{
    char num;
    char color;
    struct Stack * next;
};

//Player 1
struct Player{
    char num;
    char color;
    struct Player * next;   
};


// global variables :

int draw_cards_count = 0;
int play_special_card = 0;
char wildcard_color = 'R';
struct Player * head1 = NULL; //computer
struct Player * head2 = NULL; // player

void computerDep(struct Player ** head, struct Stack ** Dep,struct Stack ** Deck, char color, char Number);
void PlayerDep(struct Player ** head, struct Stack ** Dep,struct Stack ** Deck, char color, char Number);


int isEmpty(struct Stack * top){
    if(top == NULL){
        return 1;
    }else{
        return 0;
    }

}

int isFull(struct Stack * top){
    struct Stack * p = malloc(sizeof(struct Stack));
    if(p==NULL){
        return 1;
    }else{
        free(p);
        return 0;
    }
}

void push(struct Stack ** top,char color,char num){
    if(isFull(*top)){
        printf("Stack Overflow\n");
    }else{
        struct Stack * ptr = malloc(sizeof(struct Stack));
        ptr->num = num;
        ptr->color = color;
        ptr->next = *top;
        *top = ptr;
    }
}

void pop(struct Stack **top, char *num, char *color) {
    if (isEmpty(*top)) {
        printf("Stack Underflow\n");
    } else {
        struct Stack *p = *top;
        *top = (*top)->next;
        *num = p->num;
        *color = p->color;
        free(p);
    }
}

void DropCardFunc(struct Player ** head, struct Stack ** deck) {
    char num, color;
    for (int i = 1; i <= 7; i++) {
        struct Player * ptr = malloc(sizeof(struct Player));
        pop(deck, &num, &color);
        ptr->num = num;
        ptr->color = color;
        if(*head == NULL)
        {
            ptr -> next = NULL;
            *head = ptr;
        }
        else
        {
            struct Player *q = *head;
            while(q -> next != NULL)
            {
                q = q -> next;
            }
            ptr -> next = NULL;
            q -> next = ptr;
        }
    }
}

void move_first_to_last(struct Stack **top)
{
    struct Stack *ptr = *top;
    struct Stack *q = *top;
    while(ptr->next != NULL)
    {
        ptr = ptr -> next;
    }
    ptr -> next = q;
    *top = q -> next;
    q -> next = NULL;
}

void DistributeFunc(struct Player ** head1,struct Player ** head2,struct Stack ** deck,struct Stack ** dep){
    char num,color;
    while((*deck)->color == 'K' || (*deck)->num == 'S' || (*deck)->num == 'R' || (*deck)->num == '+')
    {
        move_first_to_last(deck);
    }
    pop(deck,&num,&color);
    char num1 = num;
    char color1 = color;
    push(dep,color1,num1);
    DropCardFunc(head1,deck);
    DropCardFunc(head2,deck);

}

void display(struct Player **player, struct Player **computer, struct Stack **deck, struct Stack **dep)
{
    printf("\n");
    printf("\n");

    // creating computer cards : 

    int n = 0;
    struct Player *count1 = *computer;
    while(count1 -> next != NULL)
    {
        count1 = count1 -> next;
        ++n;
    }
    ++n;
    int m = (6 * n) - 1;
    char a[5][m];
    for(int i = 0; i < 5; ++i)
    {
        struct Player *computercopy = *computer;
        for(int j = 0; j < m; ++j)
        {
            if(i == 0 || i == 4)
            {
                if((j + 1) % 6 == 0) a[i][j] = ' ';
                else a[i][j] = '*';
            }
            else if(i == 1)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) a[i][j] = '*';
                else if((j + 4) % 6 == 0)
                {
                    a[i][j] = computercopy -> color;
                    computercopy = computercopy -> next;
                }
                else a[i][j] = ' ';
            }
            else if(i == 3)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) a[i][j] = '*';
                else if((j + 4) % 6 == 0)
                {
                    a[i][j] = computercopy -> num;
                    computercopy = computercopy -> next;
                }
                else a[i][j] = ' ';
            }
            else if(i == 2)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) a[i][j] = '*';
                //else if((j + 4) % 6 == 0) a[i][j] = 'N';
                else a[i][j] = ' ';
            }
        }
    }
    Sleep(1000);

    // displaying computer cards :

    for(int i = 0; i < 5; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                printf("%c ",a[i][j]);
            }
            printf("\n");
        }

    printf("\n");
    printf("\n");
    printf("\n");

    for(int i = 0; i < 36; ++i)
    {
        printf(" ");
    }

    // creating depstack :


    m = 5;
    char b[5][m];
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(i == 0 || i == 4)
            {
                if((j + 1) % 6 == 0) b[i][j] = ' ';
                else b[i][j] = '*';
            }
            else if(i == 1)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) b[i][j] = '*';
                else if((j + 4) % 6 == 0)
                {
                    b[i][j] = (*dep) -> color;
                }
                else b[i][j] = ' ';
            }
            else if(i == 3)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) b[i][j] = '*';
                else if((j + 4) % 6 == 0)
                {
                    b[i][j] = (*dep) -> num;
                }
                else b[i][j] = ' ';
            }
            else if(i == 2)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) b[i][j] = '*';
                else b[i][j] = ' ';
            }
        }
    }

    // creating deckstack :

    m = 5;
    char d[5][m];
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(i == 0 || i == 4)
            {
                if((j + 1) % 6 == 0) d[i][j] = ' ';
                else d[i][j] = '*';
            }
            else if(i == 1)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) d[i][j] = '*';
                else if((j + 4) % 6 == 0) d[i][j] = 'U';
                else d[i][j] = ' ';
            }
            else if(i == 3)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) d[i][j] = '*';
                else if((j + 4) % 6 == 0) d[i][j] = 'O';
                else d[i][j] = ' ';
            }
            else if(i == 2)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) d[i][j] = '*';
                else if((j + 4) % 6 == 0) d[i][j] = 'N';
                else d[i][j] = ' ';
            }
        }
    }    

    Sleep(1000);

    // printing depstack and deckstack :

    for(int i = 0; i < 5; ++i)
    {
        struct Stack *colorvalue = *dep;
        int ct = 6;
        for(int j = 0; j < m; ++j)
        {
            if(ct == 0)
                {
                    ct = 6;
                    colorvalue = colorvalue -> next;
                }
                if(colorvalue -> color == 'R')
                {
                    printf("\033[0;31m");
                    --ct;
                }
                else if(colorvalue -> color == 'G')
                {
                    printf("\033[0;32m");
                    --ct;
                }
                else if(colorvalue -> color == 'B')
                {
                    printf("\033[0;34m");
                    --ct;
                }
                else if(colorvalue -> color == 'Y')
                {
                    printf("\033[0;33m");
                    --ct;
                }
                else if(colorvalue -> color == 'K')
                {
                    printf("\033[0;30m");
                    --ct;
                }
            printf("%c ",b[i][j]);
        }
        printf("\033[0m");
        for(int i = 0; i < 48; ++i)
        {
            printf(" ");
        }
        for(int j = 0; j < m; ++j)
        {
            printf("%c ",d[i][j]);
        }
        printf("\n");
        for(int i = 0; i < 36; ++i)
        {
            printf(" ");
        }
    }
    printf("\n");
    printf("\n");
    printf("\n");

    // creating player cards :

    n = 0;
    struct Player *count2 = *player;
    while(count2 -> next != NULL)
    {
        count2 = count2 -> next;
        ++n;
    }
    ++n;
    m = (6 * n) - 1;
    char c[5][m];
    for(int i = 0; i < 5; ++i)
    {
        struct Player *playercopy = *player;
        for(int j = 0; j < m; ++j)
        {
            if(i == 0 || i == 4)
            {
                if((j + 1) % 6 == 0) c[i][j] = ' ';
                else c[i][j] = '*';
            }
            else if(i == 1)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) c[i][j] = '*';
                else if((j + 4) % 6 == 0) 
                {
                    c[i][j] = playercopy -> color;
                    playercopy = playercopy -> next;
                }   
                else c[i][j] = ' ';
            }
            else if(i == 3)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) c[i][j] = '*';
                else if((j + 4) % 6 == 0) 
                {
                    c[i][j] = playercopy -> num;
                    playercopy = playercopy -> next;
                }
                else c[i][j] = ' ';
            }
            else if(i == 2)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) c[i][j] = '*';
                else c[i][j] = ' ';
            }
        }
    }

    Sleep(1000);

    // displaying player cards :

    for(int i = 0; i < 5; ++i)
        {
            struct Player *colorvalue = *player;
            int ct = 6;
            for(int j = 0; j < m; ++j)
            {
                if(ct == 0)
                {
                    ct = 6;
                    colorvalue = colorvalue -> next;
                }
                if(colorvalue -> color == 'R')
                {
                    printf("\033[0;31m");
                    --ct;
                }
                else if(colorvalue -> color == 'G')
                {
                    printf("\033[0;32m");
                    --ct;
                }
                else if(colorvalue -> color == 'B')
                {
                    printf("\033[0;34m");
                    --ct;
                }
                else if(colorvalue -> color == 'Y')
                {
                    printf("\033[0;33m");
                    --ct;
                }
                else if(colorvalue -> color == 'K')
                {
                    printf("\033[0;30m");
                    --ct;
                }
                printf("%c ",c[i][j]);
            }
            printf("\n");
        }
        printf("\033[0m");


    printf("\n");
    printf("\n");
}

void insertatend(struct Player **head,char num,char color)
{
    struct Player *p = *head;
    struct Player *newnode = malloc(sizeof(struct Player));
    newnode -> color = color;
    newnode -> num = num;
    if(*head == NULL)
    {
        newnode -> next = NULL;
        *head = newnode;   
    }
    else
    {
        while(p -> next != NULL)
        {
            p = p -> next;
        }
        newnode -> next = NULL;
        p -> next = newnode;
    }

}

void shuffle(struct Player **head,struct Stack **deck,int size)
{
    srand(time(NULL));

    int random_number = (rand() % size) + 1;
    if(random_number == 1)
    {
        struct Player *q = *head;
        *head = (*head) -> next;
        push(deck,q -> color, q -> num);
        free(q);
        return;
    }
    struct Player *q = (*head) -> next;
    struct Player *p = *head;
    for(int i = 0; i < random_number - 2; ++i)
    {
        p = p -> next;
        q = q -> next;
    }
    p -> next = q -> next;
    push(deck,q -> color, q -> num);
    free(q);
    
}

void creatcards(struct Player **head)
{

    // red cards :

    insertatend(head , '0','R');
    for(int i = 1; i <= 9; ++i)
    {
        insertatend(head ,(char) i + 48 ,'R');
        insertatend(head , (char)i + 48,'R');
    }
    insertatend(head , 'S','R');
    insertatend(head , 'S','R');
    insertatend(head , 'R','R');
    insertatend(head , 'R','R');
    insertatend(head , '+','R');
    insertatend(head , '+','R');

    //blue cards
        insertatend(head , '0','B');
    for(int i = 1; i <= 9; ++i)
    {
        insertatend(head ,(char) i + 48 ,'B');
        insertatend(head , (char)i + 48,'B');
    }
    insertatend(head , 'R','B');
    insertatend(head , 'R','B');
    insertatend(head , 'S','B');
    insertatend(head , 'S','B');
    insertatend(head , '+','B');
    insertatend(head , '+','B');

    //yellow cards

        insertatend(head , '0','Y');
    for(int i = 1; i <= 9; ++i)
    {
        insertatend(head ,(char) i + 48 ,'Y');
        insertatend(head , (char)i + 48,'Y');
        
    }
    insertatend(head , 'S','Y');
    insertatend(head , 'S','Y');
    insertatend(head , 'R','Y');
    insertatend(head , 'R','Y');
    insertatend(head , '+','Y');
    insertatend(head , '+','Y');
        
    //green cards
        insertatend(head , '0','G');
    for(int i = 1; i <= 9; ++i)
    {
        insertatend(head ,(char)i + 48 ,'G');
        insertatend(head ,(char)i + 48, 'G');
    }   
    insertatend(head , 'S','G');
    insertatend(head , 'S','G');
    insertatend(head , 'R','G');
    insertatend(head , 'R','G');
    insertatend(head , '+','G');
    insertatend(head , '+','G');

    //8 black cards
    insertatend(head , 'W','K');
    insertatend(head , 'W','K');
    insertatend(head , 'W','K');
    insertatend(head , 'W','K');
    insertatend(head , '+','K');
    insertatend(head , '+','K');
    insertatend(head , '+','K');
    insertatend(head , '+','K');

}

void PlayerDep(struct Player ** head, struct Stack ** Dep,struct Stack ** Deck, char color, char Number) {
    struct Player * ptr = (*head)->next;
    struct Player * q = *head;


    if(play_special_card)
    {
        // draw 2 :

        if((*Dep) -> color != 'K' && (*Dep) -> num == '+')
        {
            int draw2_present = 0;
            if(q == *head)
                {
                    if(q -> color != 'K' && q -> num == '+')
                    {
                        draw2_present = 1;
                    }
                }
            while(ptr != NULL && !draw2_present)
            {
                if(ptr -> color != 'K' && ptr -> num == '+')
                {
                    draw2_present = 1;
                    break;
                }
                ptr = ptr -> next;
                q = q -> next;
            }
            if(!draw2_present)
            {
                printf("Drawcount = %d\n",draw_cards_count);
                for(int i = 0; i < draw_cards_count; ++i)
                {
                    char num;
                    char col;
                    pop(Deck,&num,&col);
                    insertatend(head,num,col);
                }
                play_special_card = 0;
                draw_cards_count = 0;
                return;
            }
        }

        // skip :

        if((*Dep) -> num == 'S')
        {
            int skip_present = 0;
            if(q == *head)
                {
                    if(q -> num == 'S')
                    {
                        skip_present = 1;
                    }
                }
            while(ptr != NULL && !skip_present)
            {
                if(ptr -> num == 'S')
                {
                    skip_present = 1;
                    break;
                }
                ptr = ptr -> next;
                q = q -> next;
            }
            if(!skip_present)
            {
                printf("skipped \n");
                play_special_card = 0;
                return;
            }
        }

        // reverse :

        if((*Dep) -> num == 'R')
        {
            int reverse_present = 0;
            if(q == *head)
                {
                    if(q -> num == 'R')
                    {
                        reverse_present = 1;
                    }
                }
            while(ptr != NULL && !reverse_present)
            {
                if(ptr -> num == 'R')
                {
                    reverse_present = 1;
                    break;
                }
                ptr = ptr -> next;
                q = q -> next;
            }
            if(!reverse_present)
            {
                printf("reversed \n");
                play_special_card = 0;
                return;
            }
        }

        // draw 4 :

        if((*Dep) -> color == 'K' && (*Dep) -> num == '+')
        {
            int draw4_present = 0;
            if(q == *head)
                {
                    if(q -> color == 'K' && q -> num == '+')
                    {
                        draw4_present = 1;
                    }
                }
            while(ptr != NULL && !draw4_present)
            {
                if(ptr -> color == 'K' && ptr -> num == '+')
                {
                    draw4_present = 1;
                    break;
                }
                ptr = ptr -> next;
                q = q -> next;
            }
            if(!draw4_present)
            {
                printf("Drawcount = %d\n",draw_cards_count);
                for(int i = 0; i < draw_cards_count; ++i)
                {
                    char num;
                    char col;
                    pop(Deck,&num,&col);
                    insertatend(head,num,col);
                }
                play_special_card = 0;
                draw_cards_count = 0;
                return;
            }
        }
    }

    printf("ENTER CARD:\n");
    scanf(" %c", &color);
    scanf(" %c", &Number);

    if((*Dep)->color == 'K' && (*Dep)->num == '+' && play_special_card)
    {
        while(color != 'K' && Number != '+')
        {
            printf("invalid choice! please enter again: \n");
            printf("ENTER CARD:\n");
            scanf(" %c", &color);
            scanf(" %c", &Number);
        }
    }

    if((*Dep)->color == 'K' && (*Dep)->num == 'W')
    {
        while(!(color == 'K' && Number == 'W') && color != wildcard_color && !(color == 'D' && Number == 'R'))
        {
            printf("invalid choice! please enter again: \n");
            printf("ENTER CARD:\n");
            scanf(" %c", &color);
            scanf(" %c", &Number);
        }
    }

    while(play_special_card && Number != (*Dep) -> num)
    {
        printf("invalid choice! please enter again: \n");
        printf("ENTER CARD:\n");
        scanf(" %c", &color);
        scanf(" %c", &Number);
    }


    while (ptr != NULL) {
        if (((*Dep)->color==color || (*Dep)->num==Number) || ((*Dep)->color == 'K' && (*Dep)->num == '+'))
        {
            if(q == *head)
            {
                if(q -> color == color && q -> num == Number)
                {
                    *head = ptr;
                    push(Dep, q->color, q->num);
                    free(q);
                    if(color != 'K' && Number == '+')
                    {
                        draw_cards_count += 2;
                        play_special_card = 1;
                    }
                    else if(Number == 'S')
                    {
                        play_special_card = 1;
                    }
                    else if(Number == 'R')
                    {
                        play_special_card = 1;
                    }
                    else if(color == 'K' && Number == '+')
                    {
                        draw_cards_count += 4;
                        play_special_card = 1;
                    }
                    return;
                }
            }
            if (ptr->color == color && ptr->num == Number) {
                q->next = ptr->next;
                push(Dep, ptr->color, ptr->num);
                free(ptr);
                if(color != 'K' && Number == '+')
                {
                    draw_cards_count += 2;
                    play_special_card = 1;
                }
                else if(Number == 'S')
                {
                    play_special_card = 1;
                }
                else if(Number == 'R')
                {
                    play_special_card = 1;
                }
                else if(color == 'K' && Number == '+')
                {
                    draw_cards_count += 4;
                    play_special_card = 1;
                }
                return;
            }
        }

        else if(color == 'K' && Number == '+')
        {
            if(q == *head)
            {
                if(q->color == 'K' && q->num == '+')
                {
                    *head = ptr;
                    push(Dep, q->color, q->num);
                    free(q);
                    draw_cards_count += 4;
                    play_special_card = 1;
                    return;
                }
            }
            if(ptr->color == 'K' && ptr->num == '+')
            {
                q->next = ptr->next;
                push(Dep, ptr->color, ptr->num);
                free(ptr);
                draw_cards_count += 4;
                play_special_card = 1;
                return;
            }
        }

        else if(color == 'K' && Number == 'W')
        {
            if(q == *head)
            {
                if(q->color == 'K' && q->num == 'W')
                {
                    *head = ptr;
                    push(Dep, q->color, q->num);
                    free(q);
                    play_special_card = 1;
                    printf("enter colour : ");
                    scanf(" %c",&wildcard_color);
                    return;
                }
            }
            if(ptr->color == 'K' && ptr->num == 'W')
            {
                q->next = ptr->next;
                push(Dep, ptr->color, ptr->num);
                free(ptr);
                play_special_card = 1;
                printf("enter colour : ");
                scanf(" %c",&wildcard_color);
                return;
            }
        }
        if (((*Dep)->color == 'K' && (*Dep)->num == 'W') && color == wildcard_color)
        {
            if(q == *head)
            {
                if(q -> color == color && q -> num == Number)
                {
                    *head = ptr;
                    push(Dep, q->color, q->num);
                    free(q);
                    if(color != 'K' && Number == '+')
                    {
                        draw_cards_count += 2;
                        play_special_card = 1;
                    }
                    else if(Number == 'S')
                    {
                        play_special_card = 1;
                    }
                    else if(Number == 'R')
                    {
                        play_special_card = 1;
                    }
                    return;
                }
            }
            if (ptr->color == color && ptr->num == Number) {
                q->next = ptr->next;
                push(Dep, ptr->color, ptr->num);
                free(ptr);
                if(color != 'K' && Number == '+')
                {
                    draw_cards_count += 2;
                    play_special_card = 1;
                }
                else if(Number == 'S')
                {
                    play_special_card = 1;
                }
                else if(Number == 'R')
                {
                    play_special_card = 1;
                }
                return;
            }
        }

        ptr = ptr->next;
        q = q->next;
    }
    if (color=='D' && Number=='R'){
        char num;
        char col;
        pop(Deck,&num,&col);
        insertatend(head,num,col);
        if((*Dep)->color == 'K' && (*Dep)->num == 'W') play_special_card = 1;
        return;
    }

    // if one card is remaining :

    if(q == *head && ptr == NULL)
    {
        if ((*Dep)->color==color || (*Dep)->num==Number)
        {
            push(Dep, q->color, q->num);
            *head = NULL;
            free(q);
            if(color != 'K' && Number == '+')
            {
                draw_cards_count += 2;
                play_special_card = 1;
            }
            return;
        }
    }
    
    printf("invalid choice! please enter again: \n\n");
    PlayerDep(head,Dep,Deck,color,Number);
}

void computerDep(struct Player ** head, struct Stack ** Dep,struct Stack ** Deck, char color, char Number)
{
    printf("computer is playing : \n");

    if(play_special_card)
    {
        // draw 2 :

        if((*Dep)->color != 'K' && (*Dep)->num == '+')
        {
            struct Player *q = head1;
            struct Player *ptr = (head1) -> next;
            if(q == head1)
                {
                    if(q -> color != 'K' && q -> num == '+')
                    {
                        head1 = ptr;
                        push(Dep, q->color, q->num);
                        free(q);
                        draw_cards_count += 2;
                        return;
                    }
                }
            while(ptr != NULL)
            {
                if(ptr -> color != 'K' && ptr -> num == '+')
                {
                    q->next = ptr->next;
                    push(Dep, ptr->color, ptr->num);
                    free(ptr);
                    draw_cards_count += 2;
                    return;
                }
                ptr = ptr -> next;
                q = q -> next;
            }
            printf("Drawcount = %d\n",draw_cards_count);
            for(int i = 0; i < draw_cards_count; ++i)
            {
                char num;
                char col;
                pop(Deck,&num,&col);
                insertatend(&head1,num,col);
            }
            play_special_card = 0;
            draw_cards_count = 0;
            return;
        }

        // skip :

        if((*Dep)->num == 'S')
        {
            struct Player *q = head1;
            struct Player *ptr = (head1) -> next;
            if(q == head1)
                {
                    if(q -> num == 'S')
                    {
                        head1 = ptr;
                        push(Dep, q->color, q->num);
                        free(q);
                        return;
                    }
                }
            while(ptr != NULL)
            {
                if(ptr -> num == 'S')
                {
                    q->next = ptr->next;
                    push(Dep, ptr->color, ptr->num);
                    free(ptr);
                    return;
                }
                ptr = ptr -> next;
                q = q -> next;
            }
            printf("skipped \n");
            play_special_card = 0;
            return;
        }

        // reverse :

        if((*Dep)->num == 'R')
        {
            struct Player *q = head1;
            struct Player *ptr = (head1) -> next;
            if(q == head1)
                {
                    if(q -> num == 'R')
                    {
                        head1 = ptr;
                        push(Dep, q->color, q->num);
                        free(q);
                        return;
                    }
                }
            while(ptr != NULL)
            {
                if(ptr -> num == 'R')
                {
                    q->next = ptr->next;
                    push(Dep, ptr->color, ptr->num);
                    free(ptr);
                    return;
                }
                ptr = ptr -> next;
                q = q -> next;
            }
            printf("reversed \n");
            play_special_card = 0;
            return;
        }

        // draw 4:

        if((*Dep)->color == 'K' && (*Dep)->num == '+')
        {
            struct Player *q = head1;
            struct Player *ptr = (head1) -> next;
            if(q == head1)
                {
                    if(q -> color == 'K' && q -> num == '+')
                    {
                        head1 = ptr;
                        push(Dep, q->color, q->num);
                        free(q);
                        draw_cards_count += 4;
                        return;
                    }
                }
            while(ptr != NULL)
            {
                if(ptr -> color == 'K' && ptr -> num == '+')
                {
                    q->next = ptr->next;
                    push(Dep, ptr->color, ptr->num);
                    free(ptr);
                    draw_cards_count += 4;
                    return;
                }
                ptr = ptr -> next;
                q = q -> next;
            }
            printf("Drawcount = %d\n",draw_cards_count);
            for(int i = 0; i < draw_cards_count; ++i)
            {
                char num;
                char col;
                pop(Deck,&num,&col);
                insertatend(&head1,num,col);
            }
            play_special_card = 0;
            draw_cards_count = 0;
            return;
        }

        // wild card :

        if((*Dep)->color == 'K' && (*Dep)->num == 'W')
        {
            struct Player *q = head1;
            struct Player *ptr = (head1) -> next;
            if(q == head1)
                {
                    if(q -> color == 'K' && q -> num == 'W')
                    {
                        head1 = ptr;
                        push(Dep, q->color, q->num);
                        free(q);
                        while(ptr != NULL)
                        {
                            if(ptr -> color != 'K')
                            {
                                wildcard_color = ptr->color;
                                break;
                            }
                            ptr = ptr -> next;
                        }
                        printf("color chosen by computer : %c\n",wildcard_color);
                        play_special_card = 0;
                        return;
                    }
                }
            while(ptr != NULL)
            {
                if(ptr -> color == 'K' && ptr -> num == 'W')
                {
                    q->next = ptr->next;
                    push(Dep, ptr->color, ptr->num);
                    free(ptr);
                    while(q != NULL)
                        {
                            if(q -> color != 'K')
                            {
                                wildcard_color = q->color;
                                break;
                            }
                            q = q -> next;
                        }
                        printf("color chosen by computer : %c\n",wildcard_color);
                    play_special_card = 0;
                    return;
                }
                ptr = ptr -> next;
                q = q -> next;
            }

            q = head1;
            ptr = (head1)->next;
            if(q == head1)
                {
                    if(q -> color == wildcard_color)
                    {
                        head1 = ptr;
                        push(Dep, q->color, q->num);
                        free(q);
                        if(color != 'K' && Number == '+')
                        {
                            draw_cards_count += 2;
                            play_special_card = 1;
                        }
                        else if(Number == 'S')
                        {
                            play_special_card = 1;
                        }
                        else if(Number == 'R')
                        {
                            play_special_card = 1;
                        }
                        else play_special_card = 0;
                        return;
                     }
                }
            while(ptr != NULL)
            {
                if(ptr -> color == wildcard_color)
                {
                    q->next = ptr->next;
                    push(Dep, ptr->color, ptr->num);
                    free(ptr);
                    if(color != 'K' && Number == '+')
                        {
                            draw_cards_count += 2;
                            play_special_card = 1;
                        }
                        else if(Number == 'S')
                        {
                            play_special_card = 1;
                        }
                        else if(Number == 'R')
                        {
                            play_special_card = 1;
                        }
                        else play_special_card = 0;
                    return;
                }
                ptr = ptr -> next;
                q = q -> next;
            }
            char num;
            char col;
            printf("computer drawing card : \n");
            pop(Deck,&num,&col);
            insertatend(head,num,col);
            play_special_card = 0;
            draw_cards_count = 0;
            return;
        }


    }

    struct Player * ptr = (*head)->next;
    struct Player * q = *head;
    color = (*Dep)->color;
    Number = (*Dep)->num;


    while(ptr != NULL)
    {
        if(q == *head)
        {
            if((q -> color == color || q -> num == Number) || (q->color == 'K' && q->num == '+') || (color == 'K' && Number == '+') || (q->color == 'K' && q->num == 'W'))
            {
                *head = ptr;
                push(Dep, q->color, q->num);
                free(q);
                if(q->color != 'K' && q->num == '+')
                {
                    draw_cards_count += 2;
                    play_special_card = 1;
                }
                else if(q->num == 'S')
                {
                    play_special_card = 1;
                }
                else if(q->num == 'R')
                {
                    play_special_card = 1;
                }
                else if(q->color == 'K' && q->num == '+')
                {
                    draw_cards_count += 4;
                    play_special_card = 1;
                }
                else if(q->color == 'K' && q->num == 'W')
                {
                        while(ptr != NULL)
                        {
                            if(ptr -> color != 'K')
                            {
                                wildcard_color = ptr->color;
                                break;
                            }
                            ptr = ptr -> next;
                        }
                        printf("color chosen by computer : %c\n",wildcard_color);
                        play_special_card = 0;
                }
                return;
            }
        }
        if((ptr -> color == color || ptr -> num == Number) || (ptr->color == 'K' && ptr->num == '+') || (ptr->color == 'K' && ptr->num == 'W'))
        {
            q->next = ptr->next;
            push(Dep, ptr->color, ptr->num);
            free(ptr);
            if(ptr->color != 'K' && ptr->num == '+')
                {
                    draw_cards_count += 2;
                    play_special_card = 1;
                }
            else if(ptr->num == 'S')
                {
                    play_special_card = 1;
                }
            else if(ptr->num == 'R')
                {
                    play_special_card = 1;
                }
            else if(ptr->color == 'K' && ptr->num == '+')
            {
                draw_cards_count += 4;
                play_special_card = 1;
            }
            else if(ptr->color == 'K' && ptr->num == 'W')
            {
                while(q != NULL)
                    {
                        if(q -> color != 'K')
                        {
                            wildcard_color = q->color;
                            break;
                        }
                        q = q -> next;
                    }
                    printf("color chosen by computer : %c\n",wildcard_color);
                    play_special_card = 0;
            }
            return;
        }
        ptr = ptr -> next;
        q = q -> next;
    }

    // if one card is remaining :

    if(q == *head && ptr == NULL)
    {
        if ((*Dep)->color==q->color || (*Dep)->num==q->num)
        {
            push(Dep, q->color, q->num);
            *head = NULL;
            free(q);
            if((*Dep)->color != 'K' && (*Dep)->num == '+')
            {
                draw_cards_count += 2;
                play_special_card = 1;
            }
            return;
        }
    }

    char num;
    char col;
    printf("computer drawing card : \n");
    pop(Deck,&num,&col);
    insertatend(head,num,col);

}

int main()
{
    struct Stack *deck = NULL; 
    struct Stack * dep = NULL;
    struct Player* head = NULL;
    int gameover = 0;


    creatcards(&head);

    for(int i = 108; i > 0; --i)
    {
        shuffle(&head , &deck , i);
    }

    DistributeFunc(&head1,&head2,&deck,&dep);

    /*for(int i=0; i<4; i++)
    {
      printf(".....WELCOME TO UNO CARD GAME.....\n");
      (3 - i > 0) ? printf("%d",3 - i) : printf("GOO!!!");
      Sleep(500);
      system("cls");
      Sleep(500);
    }*/

    display(&head2,&head1,&deck,&dep);
    int current_turn = 0; // 0 for player, 1 for computer
    do
    {
        if (current_turn == 0)
        {
            char num;
            char color;
            PlayerDep(&head2,&dep,&deck,color,num);
            //display(&head2,&head1,&deck,&dep);
            current_turn = 1;
        }else{
            char num;
            char color;
            computerDep(&head1,&dep,&deck,color,num);
            //display(&head2,&head1,&deck,&dep);
            current_turn = 0;
        }
        display(&head2,&head1,&deck,&dep);
        if(head1 == NULL || head2 == NULL)
        {
            gameover = 1;
        }
    } while (!gameover);

    printf("Game is over");
    return 0;
}   