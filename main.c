#include<stdio.h>
#include <string.h>


void checkchar(char word[], char ch){
    for (int i=0; word[i] != '\0'; i++){
        if (word[i]== ch) {
            printf("character is present! \n");
            return;
        }
    }
printf("character is not present; \n");
}

int main () {
    int age = 22;
    printf(" address : %u \n", &age);

 int marks = 81;
    marks>= 80? printf("good \n"): printf("bad \n");

    float price [3];
    printf("enter 3 prices :");
    scanf("%f", &price[0]);
    scanf("%f", &price[1]);
    scanf("%f", &price[2]);

    printf("total price 1 : %f\n", price[0]+(0.18*price[0]));
    printf("total price 2 : %f\n", price[1]+(0.18*price[1]));
    printf("total price 3 : %f\n", price[2]+(0.18*price[2]));

    // 2 x 3
 int arr [2] [3]; // _ _ _ | _ _ _
    arr [0][0] = 90;
    arr [0][1] = 89;
    arr [0][2] = 78;

    arr [1][0] = 90;
    arr [1][1] = 89;
    arr [1][2] = 78;
    printf("%d \n", arr[0][1]);

    int n =2;
    for(int i=5; i>=1; i--){
    printf("%d \t", i);
}
printf("\n");

for(int i=1; i<=10; i++){
    printf("%d \t", n*i);
}
printf("\n");

char str[100];
printf("enter a sentence: ");
getchar();
fgets(str, 100, stdin);
puts(str);

char name[] = "Varun Anil Patil";
int length = strlen(name);
printf(" length is : %d \n", length);

char word[]= "patil";
char ch = 'p';
checkchar (word, ch);

struct student {
    int roll;
    float cgpa;
    char name[1000];
};

struct student s1;
s1.roll= 1800;
s1.cgpa= 9.2;
strcpy(s1.name, "varun");

printf("student name = %s \n", s1.name);
printf("student roll no = %d \n", s1.roll);
printf("student cgpa = %f \n", s1.cgpa);

//gap seprator
printf("\n\n---------\n\n");

struct address {
int house_no;
int block;
char city[100];
char state [100];
};

struct address a1 = { 1800, 18, "chopda", "maharatra"};

printf("house_no %d \n", a1.house_no);
printf("block %d \n", a1.block);
printf("city %s \n ", a1.city);
printf("state %s \n", a1.state);

typedef struct bankaccount {
    int accountno;
    char name[100];
} acc;

acc acc1 = {123,"varun"};
acc acc2 = {124, "chintu"};
acc acc3 = {125, "pratham"};

printf("acc no = %d \n", acc2.accountno);
printf("name = %s \n", acc2.name);

return 0;
}