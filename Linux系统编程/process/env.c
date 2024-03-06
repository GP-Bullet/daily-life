#include<stdio.h>
#include<stdlib.h>

/*
int main(){
    extern char **environ;
    int i;
    for(i=0;environ[i]!=NULL;i++){
        printf("%s\n",environ[i]);
        return 0;
    }eturn 0;
    }
}


*/


int main(){
    printf("PATH=%s\n",getenv("PATH"));
    setenv("PATH","hello",1);
    printf("PATH=%s\n",getenv("PATH"));
    return 0;
}



