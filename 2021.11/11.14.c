#if 1
//1主要元素
#include <stdio.h>
int main()
{
	int a[1000];
	int i = 0;
	int max = 0;
	int count = 0; //这个i要下面用所以在开始的时候就声明,也顺便标号
				   //不知道开多大
				   //while和for是都能相互转化吗
	/* for(int i=0;;i++){
        scanf("%d",&a[i]);
        if(scanf("%d",&a[i])==EOF)break;
    }*/

	//或者
	while (scanf("%d", &a[i]) != EOF)
	{
		i++;
	}
	//如何输出该元素呢
	for (int j = 0; j < i; j++)
	{
		for (int k = 0; k < i; k++)
		{
			if (a[k] == a[k++])
			{
				count++;
			}
			if (max < count)
			{
				max = count;
			}
			count = 0;
		}
	}

	if (max > i / 2)
	{
		printf("%d", count);
	}
	else
	{
		printf("%d", -1);
	}
	return 0;
}

/*使用摩尔投票法。摩尔投票法适用于找出一组数字序列中出现次数大于总数1/2的数字，
每次从数组中选择两个不相同的数字删掉（怎么删），剩下的数字就是就是出现次数超过一半的数字。
因为数字总数要大于1/2，所以不管数组是否乱序排列，总会存在出现最多的数字相邻排列以及该数字的总数要比该数组长度的一半要长，
并且只有一个符合这两个条件的数字。另外需要注意的是相同数字的相邻长度越长并不一定意味着是出现最多的数字，
比如[5,2,5,6,5,5,1,5,1]符合条件而[5,2,5,6,5,5,1,1,1]虽然1的相邻长度最长但并不满足长度占总长一半，所以不符合条件。

ctrl-c 发送 SIGINT 信号给前台进程组中的所有进程。常用于终止正在运行的程序。
ctrl-z 发送 SIGTSTP 信号给前台进程组中的所有进程，常用于挂起一个进程。
ctrl-d 不是发送信号，而是表示一个特殊的二进制值，表示 EOF。
ctrl-\ 发送 SIGQUIT 信号给前台进程组中的所有进程，终止前台进程并生成 core 文件。
*/

/*数组中各个元素在矩阵中对应的位置由二维数组的两个下标决定。
我们可以将定义的二维数组int arr[4][3]视为由arr[4]和int [3] 两部分构成，将arr[4]视为一个整型一维数组，
其中含有4个元素arr[0]、arr[1]、arr[2]、arr[3]，每个元素都是int[3]类型的，
也就是说，每个元素又是一个一维数组，每个一维数组含有3个元素，
如arr[0]含有arr[0][1]、arr[0][1]、arr[0][2]三个元素。
*/
#endif
#if 0 //为啥用个二维数组

#include <stdio.h>
int main()
{
	int a[50],Y[100][2],i=0,n,j,count=1,k,m;
	while(scanf("%d",&a[i]) != EOF)//建立一个数组并输入进任意个元素 
	{
		i++;
	}
	Y[0][0] = a[0];
	Y[0][1] = 1;
	for(n = 1;n<i;n++)/*将数组a中的每个元素都与二维数组Y中的元素比较，如果相同则该元素个数加一*/
	{
		for(j = 0;j<i;j++)
		{
			if(a[n] == Y[j][0])
			{
				Y[j][1]++;break;
			}
			else if(j == n-1)
			{
				Y[j+1][0] = a[n];
				Y[j+1][1] = 0;
				count++;
			}
		}
	} 
	int max = Y[0][0];//max储存最大的那个数 
	k = Y[0][1];//k储存最大数出现的次数 
	m = 0;//m储存最大元素在二维数组中排的位数 
	for(n = 1;n<count;n++)
	{
		if(Y[n][1] > k)
		{
			max = Y[n][0];
			m = n;
			k = Y[n][1];
		}
		if(Y[n][1] == k && n != m && n == count-1)
		{
			printf("-1");break;
		}
		if(n == count-1)
		{
            printf("%d",max);
		}
	}
	return 0; 
}
#endif

#if 0
#include <stdio.h>
#define size 9

//由题意知这个数组中最多有size/2个元素
//定义一个(size/2)*2数组，第1列存放不同元素，第2列存放这些元素的个数
int times[size / 2][2];

int findElement(int arr[]) {
	times[0][0] = arr[0];
	++times[0][1];
	//记录数组中不同元素出现的次数
	for (int i = 1; i < size; ++i) {
		for (int j = 0; j < size / 2; ++j) {
			if (arr[i] == times[j][0]) {
				++times[j][1];
				break;	//跳出内层循环
			}
			else if (times[j][0] == -1) {
				times[j][0] = arr[i];
				++times[j][1];
			}
			else
				continue;	//结束本轮循环	
		}
	}
	//寻找出现次数超过size/2的元素并将其返回
	for (int i = 0; i < size / 2; ++i) {
		if (times[i][1] >= size / 2)
			return times[i][0];
	}
}

int main() {
	//初始化times数组
	for (int i = 0; i < size / 2; ++i) {
		times[i][0] = -1;
		times[i][1] = 0;
	}
	int a[size];
	printf("Please enter an array: \n");
	for (int i = 0; i < size; ++i) {
		scanf("%d", &a[i]);
	}
	printf("The element is: %d.\n", findElement(a));
	return 0;
}

#endif

#if 0
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#define N 7 
int main() {
	int arr[N];
	for (int i = 0; i < N; ++i) {
		scanf("%d", &arr[i]);
	}
	int tmp = arr[0];
	int cnt = 1;
	for (int i = 1; i < N; ++i) {
		if (tmp == arr[i])
			++cnt;
		else {
			--cnt;
			if (cnt == 0) {
				tmp = arr[i];
				cnt = 1;
			}
		}
	}
	printf("The number is %d.\n", tmp);
}
#endif