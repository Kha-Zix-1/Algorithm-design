# 算法设计与分析综合项目

**18324061 文君逸**

## 题目描述

装箱问题(BPP)可以用一种非常简单的方式定义。
我们得到了n个物品，每个物品都有一个整数重量w<sub>j</sub>（j=1，…，n），以及无限数量的整数容量的相同箱子。
目的是将所有物品装入最少数量的箱子中，以使任何箱子中装入的总重量不超过容量。本项目不要求求出最优解，但要求求出最优近似解。

### 输入

物品的数量**n**,箱子的容量**c**,每件物品的重量**w<sub>j</sub>**

### 输出

本次题目设计的输出有：
+ 需要的最小箱子数
+ 每个箱子装的物品序号
+ 每个箱子的剩余容量

## 算法设计

### 动态规划



### 贪心算法

由于本次项目只要求近似解，我们可以利用贪心算法，在略微牺牲最优解的情况下追求时间效率。

#### 思路

贪心算法需要先将物品的重量**按从大到小排序**，对于每一件物品，从已经使用的第一个箱子开始遍历：
+ 如果发现这个物品可以装入箱子，那么就装入，并把对应的箱子剩余容量减去物品的重量
+ 如果对于所有已经使用的箱子都无法装入，那么新使用一个新的箱子，把新箱子容量减去物品的重量，并将已经使用的箱子数加1。

#### 算法分析

**为什么要把物品重量从大到小排序？**    
目的是为了让每个箱子的剩余空间尽量小。
+ 如果一个大物品可以恰好或勉强装入一个箱子的话，如果换装一个小物品的话，一定会使这个箱子的剩余未利用空间比装入大箱子多
+ 而把这个大物品装入后面本应装小物品的箱子会压缩本应装小物品箱子的剩余空间，从而使这个本能装下其他物品的箱子装不下其他物品造成空间浪费。

**为什么可能不是最优解？**       
没有考虑到两个或多个小物品重量相加后可能比一件大物品更适合放入箱子。    
例如：一个箱子有6个单位的剩余空间，此时剩下的物品重量为**5 2 2 2**, 按照贪心算法，第一个重量为5的物品会被装入，但实际上装入后面3个重量为2的物品是更优的选择。在后面的算法对比中我们便会看到这一点。

## 附录: 源代码

### 贪心算法

``` C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define SIZE 10005

int bin[SIZE] = { 0 }, item[SIZE];
int num, capacity, result = 0, i, j;

typedef struct record {
	int num, r[SIZE];
	record() : num(0) {}
}Record;

Record rec[SIZE];

bool comp(int x, int y) {
	return x > y;
}

void print() {
	printf("\nresult: %d\n\n", result);

	for (i = 1; i <= result; i++) {
		printf("bin %d loads: ", i);
		for (j = 1; j <= rec[i].num; j++) {
			printf("%d ", rec[i].r[j]);
		}
		printf("\nbin %d space left:%d\n\n", i, capacity - bin[i]);
	}
}

int main() {

	scanf("%d%d", &num, &capacity);
	for (i = 1; i <= num; i++) {
		scanf("%d", &item[i]);
	}

	sort(item + 1, item + 1 + num, comp);

	for (i = 1; i <= num; i++) {
		for (j = 1; j <= result; j++) {
			if (capacity - bin[j] >= item[i]) {
				bin[j] += item[i];
				rec[j].r[++rec[j].num] = i;
				break;
			}
		}

		if (j > result) {
			bin[++result] += item[i];
			rec[result].r[++rec[result].num] = i;
		}
	}

	print();

	return 0;
}
```