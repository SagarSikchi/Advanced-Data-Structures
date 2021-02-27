// Directory Based

#include <stdlib.h>
#include <stdio.h>

int a[10][2];
int flag[10] = {0};
int i, j;
int main(){
   int n, hashKey, eRow = 2, count = -1, choice, key = 0;
   for(i = 0; i < eRow; i++)
       flag[i] = 1;
   while(count){
     printf("Enter Your Choice :\n");
     printf("1. Enter a 3 digit number\n");
     printf("2. Exit\n");
     scanf("%d", &choice);
     switch(choice){
       case 1: printf("Enter Your Number : ");
               scanf("%d", &n);
               printf("\n");
               hashKey = n % 10;
               i = eRow;
               while(eRow <= hashKey){
                 eRow *= 2;
                 for(; i < eRow; i++)
                   flag[i] = 1;
               }
               for(j = 0; j < 2; j++){
                 if(!a[hashKey][j]){
                   a[hashKey][j] = n;
                   key = 1;
                   break;
                 }
               }
               if(key == 0){
                 for(j = 0; j < 2; j++){
                   if(n < a[hashKey][j]){
                     a[hashKey][j] = n;
                     break;
                   }
                 }
                 printf("Cannot Enter the Number !\n");
               }
               for(i = 0; i < eRow; i++){
                 for(j= 0; j < 2; j++){
                   if(a[i][j])
                     printf("%d\t", a[i][j]);
                   else
                     printf("%d\t", -1);
                 }
                 printf("\n");
               }
               key = 0;
               printf("\n");
               break;
       case 2: count++;
               break;
       default : printf("Enter Valid Choice !\n");
                 break;
     }
   }
   return 0;
}
