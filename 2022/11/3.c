#include<stdio.h>
#include<stdlib.h>  //qsort所需头文件
int cmp(const void *p1,const void *p2);

struct Node{
    char s[101];
    int a;
}node[1000000];

int main(void)
{
    int n;
    scanf("%d",&n);
    int i;
    if(n==0){printf("%d\n",0);return 0;}
    for(i=0;i<n;i++){
        scanf("%s %d",node[i].s,&node[i].a);
    }
    qsort(node,n,sizeof(node[0]),cmp);  
    for(i=0;i<n;i++){
        printf("%s ",node[i].s);  
    }
    printf("\n");
    int count=0;
    for(i=0;i<n;i++){
        if(node[i].a<60){
            count++;
        }
    }
    printf("%d\n",count);
    return 0;
}
int cmp(const void *p1,const void *p2)
{
    struct Node *m=(struct Node*)p1;
    struct Node *n=(struct Node*)p2;
    return n->a-m->a;    
}
