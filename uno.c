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

void fillNumberedUnoDeck(struct Stack **deck) {
    char colors[] = {'Y','B','G','R'};
    char numbers[] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // Fill the deck with numbered cards
    for (int i = 0; i < 4; i++) { // Loop through colors
            push(deck,colors[i],numbers[0]);
        for (int j = 1; j < 10; j++) { // Loop through numbers (1-9)
            push(deck, colors[i], numbers[j]);
            push(deck, colors[i], numbers[j]);
        }
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

void DistributeFunc(struct Player ** head1,struct Player ** head2,struct Stack ** deck,struct Stack ** dep){
    char num,color;
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
                else if((j + 4) % 6 == 0) a[i][j] = 'U';
                else a[i][j] = ' ';
            }
            else if(i == 3)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) a[i][j] = '*';
                else if((j + 4) % 6 == 0) a[i][j] = 'O';
                else a[i][j] = ' ';
            }
            else if(i == 2)
            {
                if(j % 6 == 0 || (j + 2) % 6 == 0) a[i][j] = '*';
                else if((j + 4) % 6 == 0) a[i][j] = 'N';
                else a[i][j] = ' ';
            }
        }
    }
    Sleep(1000);

    // displaying computer cards :

    printf("\033[0;32m");

    for(int i = 0; i < 5; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                printf("%c ",a[i][j]);
            }
            printf("\n");
        }

    printf("\033[0m");

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
        for(int j = 0; j < m; ++j)
        {
            printf("%c ",b[i][j]);
        }
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
            for(int j = 0; j < m; ++j)
            {
                printf("%c ",c[i][j]);
            }
            printf("\n");
        }


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
        insertatend(head ,(char) i + 48 ,'G');
        insertatend(head , (char)i + 48,'G');
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



int main()
{
    struct Stack *deck = NULL; 
    struct Stack * dep = NULL;
    struct Player* head = NULL;
    struct Player * head1 = NULL; //computer
    struct Player * head2 = NULL; // player


    creatcards(&head);

    for(int i = 108; i > 0; --i)
    {
        shuffle(&head , &deck , i);
    }

    DistributeFunc(&head1,&head2,&deck,&dep);

    for(int i=0; i<4; i++)
    {
      printf(".....WELCOME TO UNO CARD GAME.....");
      Sleep(500);
      system("cls");
      Sleep(500);
    }

    struct Player *p1 = head1;
    struct Player *p2 = head2;

    display(&head2,&head1,&deck,&dep);
    
    return 0;
}   