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
    void (*RotateRight)(struct list *, size_t);
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

void Print_(list *self){
    node *current = self->head;
    while(current){
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

size_t size(list *lst){
    size_t s = 0;
    node *current = lst->head;
    while (current){
        s++;
        current = current->next;
    }
    return s;
}

void RotateRight_(list *self, size_t k){
    k = k % size(self);
    for (size_t i = 0; i < k; i++){
        node *pretail = self->head;
        while (pretail && pretail->next != self->tail){
            pretail = pretail->next;
        }
        node *temp1 = self->tail;
        self->tail = pretail;
        self->tail->next = NULL;
        temp1->next = self->head;
        self->head = temp1;
    }

}

void init(list *self){
    self->head = self->tail = NULL;
    self->addToTail = addToTail_;
    self->Print = Print_;
    self->RotateRight = RotateRight_;
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
    size_t k;

    while (scanf("%zu", &k) != EOF){
        lst.RotateRight(&lst, k);
        lst.Print(&lst);
    }
    destroy(&lst);
    return 0;
}

