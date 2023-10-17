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
            push(deck,colors[i],numbers[0]);
        for (int j = 1; j < 10; j++) { // Loop through numbers (1-9)
            push(deck, colors[i], numbers[j]);
            push(deck, colors[i], numbers[j]);
        }
    }
}

int traverseNode(struct Player * ptr ){
    while(ptr!= NULL){
        printf("%c%c ",ptr->color,ptr->num);
        ptr = ptr->next;
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


int main() {
    struct Stack *deck = NULL; 
    struct Stack * dep = NULL;
    struct Player * head1 = NULL;
    struct Player * head2 = NULL;
    fillNumberedUnoDeck(&deck); 
    displayStack(deck);
    DistributeFunc(&head1,&head2,&deck,&dep);
    printf("\n\n");
    traverseNode(head1);
    printf("\n\n");
    traverseNode(head2);
    printf("\n\n");
    displayStack(deck);
    printf("\n");
    displayStack(dep);
    push(&dep,'R','3');
    displayStack(dep);
}