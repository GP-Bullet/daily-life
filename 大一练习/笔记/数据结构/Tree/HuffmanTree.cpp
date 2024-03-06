#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//已知某系统在通信网络中只可能出现八种字符，其概率分别为
//0.05，0.29，0.07，0.08，0.14，0.23，0.03，0.11
//试设计哈夫曼编码
typedef double DataType; //结点权值的数据类型

typedef struct HTNode //单个结点的信息
{
	DataType weight; //权值
	int parent; //父节点
	int lc, rc; //左右孩子
}*HuffmanTree;

typedef char **HuffmanCode; //字符指针数组中存储的元素类型

//在下标为1到i-1的范围找到权值最小的两个值的下标，其中s1的权值小于s2的权值
void Select(HuffmanTree& HT, int n, int& s1, int& s2)
{
	int min;
	//找第一个最小值
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight)
			min = i;
	}
	s1 = min; //第一个最小值给s1
	//找第二个最小值
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && i != s1)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight&&i != s1)
			min = i;
	}
	s2 = min; //第二个最小值给s2
}

//构建哈夫曼树
void CreateHuff(HuffmanTree& HT, DataType* w, int n)
{
	int m = 2 * n - 1; //哈夫曼树总结点数
	HT = (HuffmanTree)calloc(m + 1, sizeof(HTNode)); //开m+1个HTNode，因为下标为0的HTNode不存储数据
	for (int i = 1; i <= n; i++)
	{
		HT[i].weight = w[i - 1]; //赋权值给n个叶子结点
	}
	for (int i = n + 1; i <= m; i++) //构建哈夫曼树
	{
		//选择权值最小的s1和s2，生成它们的父结点
		int s1, s2;
		Select(HT, i - 1, s1, s2); //在下标为1到i-1的范围找到权值最小的两个值的下标，其中s1的权值小于s2的权值
		HT[i].weight = HT[s1].weight + HT[s2].weight; //i的权重是s1和s2的权重之和
		HT[s1].parent = i; //s1的父亲是i
		HT[s2].parent = i; //s2的父亲是i
		HT[i].lc = s1; //左孩子是s1
		HT[i].rc = s2; //右孩子是s2
	}
	//打印哈夫曼树中各结点之间的关系
	printf("哈夫曼树为:>\n");
	printf("下标   权值     父结点   左孩子   右孩子\n");
	printf("0                                  \n");
	for (int i = 1; i <= m; i++)
	{
		printf("%-4d   %-6.2lf   %-6d   %-6d   %-6d\n", i, HT[i].weight, HT[i].parent, HT[i].lc, HT[i].rc);
	}
	printf("\n");
}

//生成哈夫曼编码
void HuffCoding(HuffmanTree& HT, HuffmanCode& HC, int n)
{
	HC = (HuffmanCode)malloc(sizeof(char*)*(n + 1)); //开n+1个空间，因为下标为0的空间不用
	char* code = (char*)malloc(sizeof(char)*n); //辅助空间，编码最长为n(最长时，前n-1个用于存储数据，最后1个用于存放'\0')
	code[n - 1] = '\0'; //辅助空间最后一个位置为'\0'
	for (int i = 1; i <= n; i++)
	{
		int start = n - 1; //每次生成数据的哈夫曼编码之前，先将start指针指向'\0'
		int c = i; //正在进行的第i个数据的编码
		int p = HT[c].parent; //找到该数据的父结点
		while (p) //直到父结点为0，即父结点为根结点时，停止
		{
			if (HT[p].lc == c) //如果该结点是其父结点的左孩子，则编码为0，否则为1
				code[--start] = '0';
			else
				code[--start] = '1';
			c = p; //继续往上进行编码
			p = HT[c].parent; //c的父结点
		}
		HC[i] = (char*)malloc(sizeof(char)*(n - start)); //开辟用于存储编码的内存空间
		strcpy(HC[i], &code[start]); //将编码拷贝到字符指针数组中的相应位置
	}
	free(code); //释放辅助空间
}

//主函数
int main()
{
	int n = 0;
	printf("请输入数据个数:>");
	scanf("%d", &n);
	DataType* w = (DataType*)malloc(sizeof(DataType)*n);
	if (w == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	printf("请输入数据:>");
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &w[i]);
	}
	HuffmanTree HT;
	CreateHuff(HT, w, n); //构建哈夫曼树

	HuffmanCode HC;
	HuffCoding(HT, HC, n); //构建哈夫曼编码

	for (int i = 1; i <= n; i++) //打印哈夫曼编码
	{
		printf("数据%.2lf的编码为:%s\n", HT[i].weight, HC[i]);
	}
	free(w);
	return 0;
}
