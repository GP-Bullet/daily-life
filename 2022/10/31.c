#include<stdio.h>

int main(int argc, char **argv)
{
  int arr[5][5];
  int a = 0;
  for (int i = 0; i < 5; i++) {
    int *temp = *(arr+i);
    for(; temp < arr[5]; temp++) {
      *temp = a++;
    }
      for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      printf("%d\t", arr[i][j]);
    }
    printf("\n");
  }
  }


}
