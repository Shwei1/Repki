#include <stdio.h>
#include <string.h>
#define N 2
#define M 20

typedef struct Person{
    int name_index;
    char gender;
    double height;
}Person;

double average_height_F(Person p[N]) {
    double height_sum = 0;
    int F_count = 0;
    for (int i = 0; i < N; i++) {
        if (p[i].gender == 'F') {
            height_sum += p[i].height;
            F_count++;
        }
    }
    if (F_count == 0) {
        printf("There are no women in your list.\n");
    return -1;
    }
    else {
        return height_sum / F_count;
    }
}

void tallest_M(Person p[N], char names[][M]){
    int tallest_index = -1;
    for (int i = 0; i < N; i++){
        if (tallest_index == -1 && p[i].gender == 'M'){
            tallest_index = i;
          continue;
        }
        if (tallest_index != -1 && p[i].gender == 'M' && p[i].height > p[tallest_index].height)
            tallest_index = i;
    }
    if (tallest_index != -1)
        printf("The tallest man is %s with height %lf\n", names[tallest_index], p[tallest_index].height);
    else
        printf("There are no men in your list.\n");
}

int main(){
    char names[N][M];
    Person people[N];

    printf("Enter %d names, for each enter person's gender (M or F) and height:\n", N);
    for (int i = 0; i < N; i++){
        scanf("%s %c %lf", names[i], &people[i].gender, &people[i].height);
        people[i].name_index = i;
    }

//    printf("%s %c %lf\n", names[0], people[0].gender, people[0].height);

    printf("The average height of women is %lf\n", average_height_F(people));

    tallest_M(people, names);


}

