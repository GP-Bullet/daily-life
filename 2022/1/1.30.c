//连续数的和
//如果为奇数就除以2
//如果为偶数就找
#include<stdio.h>
#if 0
int main(){
    long long a[10001];
    int n;
    long long l[10001];
    long long r[10001];
    scanf("%d",&n);
    int i;
    for(i=0;i<n;i++){
        scanf("%lld",&a[i]);
    }
    for(i=0;i<n;i++){
        if(a[i]==1){
            l[i]=0;
            r[i]=1;
        }
        if(a[i]!=1&&a[i]%2){
            l[i]=a[i]/2;
            r[i]=l[i]+1;
        }
        if(!(a[i]%2)){
            l[i]=-a[i]+1;
            r[i]=a[i];
        }
    }
    for(i=0;i<n;i++){
        printf("%lld %lld\n",l[i],r[i]);
    }
    return 0;
}
#endif
#if 1
int main(){
    int p,q;
    int i,T;
    int a[10001];
    char a[10001];
    int b[10001];
    char b[10001];
    for(i=0;i<T;i++){
        
}








}
#endif
