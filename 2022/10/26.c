// 分析：

// 字符串中只有'V'和'K'两种字符，共有4种组合：

// 'VK'，满足'VK'，直接count++；
// 'KV'，就算改变一个字符，也不能变成'VK'，舍去；
// 'KK'，改变第一个字符，变为'VK'，count++；
// 'VV'，改变第二个字符，变为'VK'，count++；
// 思路：

// 读取字符串的长度n，与字符串s，count用来记录'VK'的个数。

// 遍历字符串。

// 先计算出'VK'的个数，count++；
// 同时'VK'清空，为'..'，防止重复读取。
// 再遍历一遍字符串。
// 若满足'KK'的情况，变为'VK'，count++;
// 若满足'VV'的情况，变为'VK'，count++;
// 输出count的值。
#include <stdio.h>

int main(void)
{
	int n;			//字符串的长度
	char s[101];		//字符串
	int count = 0;		//CV的个数

	scanf("%d", &n);
	scanf("%s", s);

	for (int i = 0; i < n - 1; i++)
	{
		if (s[i] == 'C' && s[i + 1] == 'V')
		{
			count++;
			s[i] = '.';
			s[i + 1] = '.';
		}
	}

	for (int i = 0; i < n - 1; i++)
	{
		if (s[i] == 'C' && s[i + 1] == 'C')
		{
			count++;
			s[i + 1] = 'V';
			break;
		}
		if (s[i] == 'V' && s[i + 1] == 'V')
		{
			count++;
			s[i] = 'C';
			break;
		}
	}

	printf("%d\n", count);

	return 0;
}