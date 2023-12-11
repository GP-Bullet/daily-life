//奇怪的输出
/*#include<stdio.h>
int main(void){
    int data[]={0X636c6557,0X20656d6f,0X78206f74,
                0X756f7969,0X6e694c20,0X67207875,
                0X70756f72,0X32303220,0X00000a31};

    puts((const char*)data);
}*/

//!大小端

//!啊哈算法

//!x86架构
//*敲一敲排序吧

//冒泡

//a[j+1]

#if 0
#include<stdio.h>

int main(){
    int a[]={4,5,4,7,1,3,2};
    int n=sizeof(a)/sizeof(a[0]);
    int i,j,t;

    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(a[j]<a[j+1]){
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }

    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }

    return 0;
}
#endif

//选择
#if 0
//不知道啥玩意
#include<stdio.h>
int main(){
    int a[]={1,6,9,4,2,6,5,8};
    int n=sizeof(a)/sizeof(a[0]);
    int i,j,t;
    int max;
    
    for(i=0;i<n;i++){
        max=i;
        for(j=0;j<n;j++){
            if(a[max]<a[j]){
                max=j;
            }
        if(max!=i){
                t=a[max];
                a[max]=a[j];
                a[j]=t;
        } 
            }
        
    }
    for(i=0;i<n;i++){
        printf("%d",a[i]);
    }

    return 0;

    
}
#endif

#include<stdio.h>
int main(){
    int a[]={1,9,4,6,8,2,7};
    int n=sizeof(a)/sizeof(a[0]);
    int i,j,t;
    int max;

    for(i=0;i<n;i++){
        max=i;
        for(j=i+1;j<n;j++){
            if(a[max]<a[j]){
                max=j;
            }
        }
        if(max!=i){
        t=a[max];
        a[max]=a[i];
        a[i]=t;
        }
    }
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    return 0;
}