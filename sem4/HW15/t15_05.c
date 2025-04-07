#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *next;
} node;

typedef struct list{
    node *tail, *head;
    void (*addToTail)(struct list *, int);
    void (*Print)(struct list *);
    void (*PrintReverse)(struct list *);
} list;

void addToTail_(list *self, int value){
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = value;
    new_node->next = NULL;
    if (self->tail){
        //node *temp = self->tail;
        self->tail->next = new_node;
        self->tail = self->tail->next;
    }
    else
        self->head = self->tail = new_node;
}

void Print_(list *self){
    node *current = self->head;
    while(current){
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void PrintReverse__(list *self, node *current){
    if (!current){
        return;
    }
    if (current->next){
        PrintReverse__(self, current->next);
    }
    printf("%d ", current->value);
}


void PrintReverse_(list *self){
    PrintReverse__(self, self->head);
}

void init(list *self){
    self->head = self->tail = NULL;
    self->addToTail = addToTail_;
    self->Print = Print_;
    self->PrintReverse = PrintReverse_;
}

void destroy(list *self){
    node *current = self->head;
    while (current){
        node *temp = self->head;
        self->head = self->head->next;
        free(temp);
        current = current->next;
    }
}

int main(void){
    list lst;
    init(&lst);
    size_t n;
    scanf("%zu", &n);
    for (size_t i = 0; i < n; i++){
        int value;
        scanf("%d", &value);
        lst.addToTail(&lst, value);
    }
    lst.Print(&lst);
    lst.PrintReverse(&lst);
    return 0;
}

