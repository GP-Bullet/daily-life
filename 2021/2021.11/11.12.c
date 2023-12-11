/*#include<stdio.h>
#include<math.h>//绝对值

//要用到二维数组

int main(){
    int n;
    scanf("%d",&n);

    int a[n][3];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i][0]);
        scanf("%d",&a[i][1]);
        scanf("%d",&a[i][2]);
    }
    int count=0;
    //两个作比较两个循环
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++){
        int x=fabs(a[i][0]-a[j][0]);
        int y=fabs(a[i][1]-a[j][1]);
        int z=fabs(a[i][2]-a[j][2]);
        int w=fabs(a[i][0]+a[i][1]+a[i][2]-(a[j][0]+a[j][1]+a[j][2]));
            if(x<=5&&y<=5&&z<=5&&w<=10){
                count++;
            }
            

        }printf("%d",count);
    return 0;
}

//找最小值
#include<stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    
    int a[n];int count;
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }    
        count=a[0];
    
    for(int i=0;i<n;i++){
            if(count>a[i]){
            count=a[i];
            }
    }
        printf("%d",count);
    return 0;
}



//分类平均
#include<stdio.h>
int main(){
    int n,k;
    int sum1=0,sum2=0;
    int c1=0,c2=0;
    scanf("%d %d",&n,&k);

    for(int i=1;i<=n;i++){
        if(i%k==0){
            sum1=sum1+i;
            c1++;
        }
        else{
            sum2=sum2+i;
            c2++;
        }
    }
        printf("%.1lf %.1lf",(double)(sum1/c1),(double)(sum2/c2));
        return 0;
}


//一尺之棰
#include<stdio.h>
int main (){
    int n,count=0;
    scanf("%d",&n);
    
    while(n!=1){
        n=n/2;
        count++;
    }
    printf("%d",count+1);
    return 0;
}


//数字直角三角形
//每行输出的个数怎么控制--用i和j一起
//输出三角形--让j与i关联，不让j每次从零开始
//%02d宽度为2,不足补0
//无需用if
#include<stdio.h>
int main(){
    int n,a=1;
    scanf("%d",&n);

    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            printf("%02d",a);
            a++;
        }
        printf("\n");
    }
    return 0;
}



#include<stdio.h>
int main(){
    int n,sum;
    scanf("%d",&n);

    for(int i=1;i<=n;i++){
        sum=sum+i;
    }
    printf("%d",sum);
    return 0;

}*/