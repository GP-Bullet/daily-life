#include<stdio.h> //PTA 7-1
struct stu
{
    int num; //学号
    float grade; //成绩
};

void sort(struct stu *ps, int n)
{
    struct stu t;
    for(int i = 0; i < n - 1; ++i){ 
        for(int ii = i; ii < n; ++ii){
            if(ps[i].grade < ps[ii].grade){
                t = ps[i]; ps[i] = ps[ii]; ps[ii] = t;
            }
        }
    }
    //output
    
    int rank = 0; 
    for(int i = 0; i < n; ++i){ 
        if(ps[i].grade != ps[i - 1].grade){
            rank = i;
            printf("%d %d %.2f\n", rank + 1, ps[i].num, ps[i].grade);
        }
        else printf("%d %d %.2f\n", rank + 1, ps[i].num, ps[i].grade);
    }
    

}
int main() 
{
    struct stu ps[100];
    int n; //学生人数
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%d", &ps[i].num);
        scanf("%f", &ps[i].grade);
    }
    sort(&ps, n);
    return 0;
}
