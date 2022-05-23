#include <stdio.h>

void input (int a[],int *num_a,int b[],int *num_b);
void merge (int a[],int *num_a,int b[],int *num_b,int c[],int* num_c);
void put (int c[], int* num_c);

int main (void)
{
    int a[100];
    int b[100];
    int c[100];
    int num_a = 0,num_b = 0,num_c = 0;
    input(a,&num_a,b,&num_b);
    merge (a,&num_a,b,&num_b,c,&num_c);
    put(c,&num_c);
    return 0;
}
void input (int a[],int *num_a,int b[],int *num_b)
{
    do{
        scanf("%d",&a[(*num_a)++]);
    } while (getchar() != '\n');

    do{
        scanf("%d",&b[(*num_b)++]);
    } while (getchar() != '\n');
}
void merge (int a[],int* num_a,int b[],int* num_b,int c[],int* num_c)
{
    int m = *num_a-1;
    int n = *num_b-1;
    for(int i=0; i<*num_a+*num_b; i++)
    {
        if (m >= 0 && n >= 0)
        {
            if(a[m] > b[n])
                c[i] = a[m--];
            else
                c[i] = b[n--];
        }
        else if(m != -1)
            c[i] = a[m--];
        else if(n != -1)
            c[i] = b[n--];
    }
    *num_c = *num_a + *num_b;
}
void put (int c[],int* num_c)
{
    for(int i=0; i<*num_c; i++)
    {
        printf("%d",c[i]);
        if(i != *num_c-1)
            printf(" ");
        else
            printf("\n");
    }
}