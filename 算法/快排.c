#include<stdio.h>
int a[101],n;//定义全局变量，需要在子函数中使用

void quicksort(int left,int right){
    int i,j,t,temp;
    if(left>right)
    return;

    temp=a[left];//用来存基准数
    i=left;
    j=right;

    while(i!=j){
        //从右往左找
        while(a[j]>=temp&&i<j)
            j--;
        //从左往右找
        while(a[j]<=temp&&i<j)
            i++;
        
        //swap
        if(i<j){
            t=a[i];
            a[i]=a[j];
            a[j]=t;
        }
    }
    //基准数归位
    a[left]=a[i];
    a[i]=temp;

    quicksort(left,i-1);//递归
    quicksort(i+1,right);//递归

    return;

}
int main(){
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    quicksort(1,n);

    for(i=1;i<=n;i++){
        printf("%d ",a[i]);
    }
    //getchar();getchar();

    return 0;
}