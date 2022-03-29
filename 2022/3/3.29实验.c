//1
#if 0
#include<stdio.h>
int main(){
	float s=0;
	int n=1;
	while(s<=15){
		s+=1.0/n;
		n++;
	}
	printf("%f %d",s,n);
	return 0;
}
#endif

//2
#if 1
#include<stdio.h>

int main(){

    int a=-1,n=2,b;
    double s=0;
    double c=1;
	while(c>1e-6){
        s+=c;
        a*=-1;
        for(b=1;b<=n;b++){
            b=b*b++;
        }
        c=a/(float)b;
        
        
        n++;
    }
    printf("%lf",s);
	return 0;
}
#endif



//3
#if 0
#include<stdio.h>
int sushu(int a){
	for(int i=2;i<=a/2.0;i++){
		if(a%i==0) return 0;
	}
	return 1;
}

int main(){
	int i;int j=0;
	int a[100];
	for(i=100;i<=200;i++){
		
		if(i%2!=0){
			a[j++]=i;
		}
	}
	for(int k=0;k<=j-1;k++){
		
		if(sushu(a[k])&&sushu(a[k++])){
			printf("%d %d\n",a[k],a[k++]);
		}
	}
	return 0;
}

#endif


//4
#if 0
#include<stdio.h>
int main(){
	
	int a[1000][1000];
	for(int i=1;i<=1000;i++){
		for(int j=0;j<1000;j++){
			if(i%++j==0){
				a[i][j]=
			}
			
		}	
	}
	
	
	
	return 0;
}
#endif


//7
#if 0
#include<stdio.h>
int main(){
	int a;
	scanf("%d",&a);
	if(a==1){
		printf("*");	
		printf("*");
	}
	if(a>1){
		printf();
	}
	
	
}

#endif
