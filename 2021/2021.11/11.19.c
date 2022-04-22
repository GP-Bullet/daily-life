/*   *
    ***
   *****
  *******

行    空格    *
0      3     1
1      2     3
2      1     5
3      0     7
            */
#if 0
#include<stdio.h>
int main(){
    int i,j,k;
    for(i=0;i<4;i++){
        for(j=0;j<3-i;j++)
        {printf("%c",' ');}
        for(k=0;k<2*i+1;k++)
        {printf("%c",'*');}
        printf("\n");
    }
    return 0;
    
}
#endif




/*   A
    BBB
   CCCCC
  DDDDDDD*/

#if 0
#include<stdio.h>
int main(){
    int i,j,k;
    char a='A';
    for(i=0;i<4;i++){
        for(j=0;j<3-i;j++)
        {printf("%c",' ');}
        for(k=0;k<2*i+1;k++)
        {printf("%c",a);}
        a++;
        printf("\n");
    }
}
#endif



/*   A
    ABA
   ABCBA
  ABCDCBA*/

#if 0
#include<stdio.h>
int main(){
    int i,j,k;
    char a='A';
    for(i=0;i<4;i++){
        for(j=0;j<3-i;j++)
        {printf("%c",' ');}
        for(k=0;k<2*i+1;k++)
        {printf("%c",a);
        if(k>=(2*i+1)/2){
            a--;
        }else{a++;}
        }
        printf("\n");
        a='A';
    }
    return 0;

}
#endif



//最大公约数和最小公倍数


//共用体
#include<stdio.h>

