#if 1
#include<stdio.h> //experiment 5 part 1-7 wrong
#include<string.h>
void  input(char a[][50], int r)
    {
        printf("Enter please\n");
        for(int i = 0; i < r; ++i){
            scanf("%s", a[i]);
        }
    }


void sort(char a[][50], int r)
{char t[50] = {0};
        for(int i = 0; i < r - 1; ++i){
            for(int ii = 0; ii < r - 1 - i; ++ii){
                if(strcmp(a[ii], a[ii + 1]) > 0){
                    
                    strcpy(t, a[ii]);
                    strcpy(a[ii], a[ii + 1]);
                    strcpy(a[ii + 1], t);
                }
            }
        }
    }
    

void print(char a[][50], int r)
    {
        for(int i = 0; i < r; ++i){
            printf("%s\n", a[i]);
        }
    }
int main()
    {
        char a[6][50] = {0};
        input(a, 6);
        sort(a, 6);
        print(a, 6);
        return 0;
    }
#endif