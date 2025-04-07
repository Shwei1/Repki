#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct list{
    node *tail, *head;
    void (*addToTail)(struct list *, int);
    void (*Print)(struct list *);
    void (*ReorderList)(struct list *);
} list;

void addToTail_(list *self, int value){
    node *new_node = (node *) malloc(sizeof(node));
    new_node->value = value;
    new_node->next = NULL;
    if (self->tail){
        self->tail->next = new_node;
        self->tail = self->tail->next;
    }
    else
        self->head = self->tail = new_node;
}

void addToHead_(list *self, int value){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->value = value;
    new_node->next = self->head;
    if (self->head){
        self->head = new_node;
    }
    else
        self->tail = self->head = new_node;
}

void ReorderList_(list *self){

    if (!self->head || !self->head->next)
        return;

    node *middle = self->head;
    node *iterator = self->head;
    while (iterator->next && iterator->next->next){
        middle = middle->next;
        iterator = iterator->next->next;
    }

    node *second = middle->next;
    middle->next = NULL;

    node *prev = NULL;
    node *current = second;
    node *next = NULL;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }


    node *first = self->head;
    second = prev;
    while (second) {
        node *tmp1 = first->next;
        node *tmp2 = second->next;
        first->next = second;
        second->next = tmp1;
        first = tmp1;
        second = tmp2;
    }
}

void Print_(list *self){
    node *current = self->head;
    while(current){
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void init(list *self){
    self->head = self->tail = NULL;
    self->addToTail = addToTail_;
    self->Print = Print_;
    self->ReorderList = ReorderList_;
}

void destroy(list *self){
    node *current = self->head;
    while (current){
        node *temp = self->head;
        self->head = self->head->next;
        current = current->next;
        free(temp);
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
    lst.ReorderList(&lst);
    lst.Print(&lst);
    destroy(&lst);
    return 0;
}

