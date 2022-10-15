#include<stdio.h>
#include<string.h>
#include<math.h>

int main(){
    for(;;){
        int n,l;
        long long count = 0;

        if(scanf("%d %d",&n,&l)!=EOF){

        char arr[n][l];

        for(int i = 0 ; i < n ; i++){
            scanf("%s",arr[i]);
            int len = strlen(arr[i]);

            count += 1;

            int other = l - len ;
            long otherLen = 1;
            for(int j = len+1 ; j <= l ; j++){
                otherLen *= 26;
                count += otherLen * 2 - 1;//只有开头和结尾
            }

            count %= (int)pow(2,64);

        }

        printf("%lld\n",count);
        }else{
            return 0;
        }
    }
}