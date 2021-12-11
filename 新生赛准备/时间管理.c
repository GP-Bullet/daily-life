#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmp(const void *p1,const void *p2);
struct Node{
    int a;
    int b;
}node[50000];
int main(){
    int n;
    scanf("%d",&n);
    int i;
    for(i=0;i<n;i++){
        scanf("%d%d",&node[i].a,&node[i].b);
    }
    qsort(node,n,sizeof(node[0]),cmp);
    int cnt=1;
    int time=0;
    for(i=0;i<n;i++){
        if(node[i].a>=time){
            time=node[i].b;
            cnt++;
        }
    }
    printf("%d",cnt);
    return 0;
}
int cmp(const void*p1,const void*p2){
    struct Node *m=(struct Node*)p1;
    struct Node *n=(struct Node*)p2;
    return m->b-n->b;
}