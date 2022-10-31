#include <stdio.h>
#include<string.h>
#include<stdlib.h>
char* convertAndMerge();
int main(void){
    char words[2][20] = {"Welcome to Xiyou","Linux Group 2022"};
    printf("%s\n",words[0]);
    printf("%s\n",words[1]);
    char* str = convertAndMerge(words);
    printf("str=%s\n",str);
    free(str);
}
//char* convertAndMerge(char str1[2][20]){
//char* convertAndMerge(char str1[][20]){
char* convertAndMerge(char (*str1)[20]){
    char*s=(char*)malloc(sizeof(char)*40);
    //strcat(s,str1[0]);
    //strcat(s,str1[1]);
    // strcat(s,*str1);
    // strcat(s,*(str1+1));
    strcat(s,&str1[0][0]);
    strcat(s,&str1[1][0]);
    for(int i=0;s[i]!='\0';i++){
        if(s[i]>='a'&&s[i]<='z') 
            s[i]-=32;
        else if(s[i]>='A'&&s[i]<='Z') 
            s[i]+=32;
    }
    return s;
}

// char* convertAndMerge(char *str1){
//         char*s=(char*)malloc(sizeof(char)*40);
//     strcat(s,&str1[0]);
//     strcat(s,&str1[1]);
//     for(int i=0;s[i]!='\0';i++){
//         if(s[i]>='a'&&s[i]<='z') 
//             s[i]-=32;
//         else if(s[i]>='A'&&s[i]<='Z') 
//             s[i]+=32;
//     }
//     return s;
// }
