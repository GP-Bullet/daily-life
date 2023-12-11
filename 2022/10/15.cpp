#include<stdio.h>
#include <bits/stdc++.h>
using namespace std;


const int N = 50000;
int arr[N];

int merge(int arr[],int l,int mid,int r){
	int help[r-l+1];
	int p1 = l;
	int p2 = mid+1;
	int i = 0;
	int sum = 0;
	
	while(p1 <= mid&&p2 <= r){
		if(arr[p1] < arr[p2]){
			help[i++] = arr[p1++];
		}else if(arr[p1] > arr[p2]){
			help[i++] = arr[p2++];

			sum += mid-p1+1;
		}else{
			help[i++] = arr[p2++];
		}
	}
	
	while(p1 <= mid){
		help[i++] = arr[p1++];
	}
	
	while(p2 <= r){
		help[i++] = arr[p2++];
	}
	
	i = 0;
	for(p1 = l;p1 < p2;p1++){
		arr[p1] = help[i++];
	}
	
	return sum;
}

int process(int arr[],int l,int r){
	if(l == r){
		return 0; 
	}
	int mid = l + ((r - l)>>1);
	int sum = 0;
	int end = process(arr,l,mid);

	sum = end;
	end = process(arr,mid+1,r);

	sum += end;
	return sum+merge(arr,l,mid,r);
}

int SUM(int *arr,int num){
	int sum = process(arr,0,num);
	return sum;
}
int main(){
    
	for(;;){
		int N,i,j;
		scanf("%d",&N);
		int a[N][N];
		int b[1000];
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				scanf("%d",&a[i][j]);
			}
		}
		int flag=0;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				b[flag++]=a[i][j];
			}
		}
		if(N==0)return 0;
		if(N%2==0&&N!=0){
			if(SUM(b,N*N-1)%2==1){
				printf("YES\n");
			}else{
				printf("NO\n");
			}
		}
		if(N%2==1){
			if(SUM(b,N*N-1)%2==0){
				printf("YES\n");
			}else{
				printf("NO\n");
			}
		}
	}
}