#include<stdio.h> //PTA 7-3 
struct employee
{
    int num;
    char name[50];
    char sort;
    char part[50];
};
void input(struct employee school[], int n)
{
    for(int i = 0; i < n; ++i){
        scanf("%d %s %c", &school[i].num, school[i].name, &school[i].sort);
        gets(school[i].part);
    }
}
void sort(struct employee school[], int n)
{
    int a = 0, b = 0;
    for(int i = 0; i < n; ++i){
        if(school[i].sort == 't'){
            a++;
        }
        else if(school[i].sort == 'w'){
            b++;
        }
    }
    printf("tcount = %d, wcount = %d", a, b);
}
int main()
{
    struct employee school[50];
    int n;
    scanf("%d", &n);
    input(school, n);
    //output
    for(int i = 0; i < n; ++i){
        printf("%d ", school[i].num);
        printf("%s ", school[i].name);
        printf("%c", school[i].sort);
        printf("%s\n", school[i].part);
    }
    sort(school, n);
    return 0;
}