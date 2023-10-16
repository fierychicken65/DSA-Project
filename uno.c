#include<stdio.h>
#include<stdlib.h>

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
struct Stack * push(struct Stack * top,char color,char num){
    if(isFull(top)){
        printf("Stack Overflow\n");
    }else{
        struct Stack * ptr = malloc(sizeof(struct Stack));
        ptr->num = num;
        ptr->color = color;
        ptr->next = top;
        top = ptr;
        return top;
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


void displayStack(struct Stack  * top){
    struct Stack * p = top;
    while (p != NULL)
    {
        printf("%c%c ",p->color,p->num);
        p = p->next;
    }
    printf("\n");
    
}

void fillNumberedUnoDeck(struct Stack **deck) {
    char colors[] = {'Y','B','G','R'};
    char numbers[] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // Fill the deck with numbered cards
    for (int i = 0; i < 4; i++) { // Loop through colors
            *deck = push(*deck,colors[i],numbers[0]);
        for (int j = 1; j < 10; j++) { // Loop through numbers (1-9)
            *deck = push(*deck, colors[i], numbers[j]);
            *deck = push(*deck, colors[i], numbers[j]);
        }
    }
}

int traverseNode(struct Player * ptr ){
    while(ptr!= NULL){
        printf("%c%c ",ptr->color,ptr->num);
        ptr = ptr->next;
    }
 }

void DropCardFunc(struct Player * head, struct Stack ** deck) {
    struct Player * ptr = head;
    char num, color;
    for (int i = 1; i <= 7; i++) {
        pop(deck, &num, &color);
        ptr->num = num;
        ptr->color = color;
        ptr = ptr->next;
    }
}

void DistributeFunc(struct Player * head1,struct Player * head2,struct Stack ** deck,struct Stack ** dep){
    char num,color;
    pop(deck,&num,&color);
    char num1 = num;
    char color1 = color;
    *dep = push(*dep,color1,num1);
    DropCardFunc(head1,deck);
    DropCardFunc(head2,deck);

}

struct Player * initializePlayer() {
    struct Player * head = NULL;
    struct Player * current = NULL;

    for (int i = 0; i < 35; i++) {
        struct Player * newNode = (struct Player *)malloc(sizeof(struct Player));
        newNode->num = '\0'; // Initialize num to something appropriate
        newNode->color = '\0'; // Initialize color to something appropriate
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    return head;
}
struct Stack * initializeDepStack() {
    struct Stack * head = NULL;
    struct Stack * current = NULL;

    for (int i = 0; i < 12; i++) {
        struct Stack * newNode = (struct Stack *)malloc(sizeof(struct Stack));
        newNode->num = '\0'; // Initialize num to something appropriate
        newNode->color = '\0'; // Initialize color to something appropriate
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    return head;
}




int main() {
    struct Stack *deck = NULL; 
    struct Stack * dep = initializeDepStack();
    struct Player * head1 = initializePlayer();
    struct Player * head2 = initializePlayer();
    fillNumberedUnoDeck(&deck); 
    displayStack(deck);
    DistributeFunc(head1,head2,&deck,&dep);
    printf("\n\n");
    traverseNode(head1);
    printf("\n\n");
    traverseNode(head2);
    printf("\n\n");
    displayStack(deck);
    printf("\n");
    displayStack(dep);
    dep = push(dep,'R','3');
    displayStack(dep);
}