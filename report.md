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
+ 每个箱子装的物品序号
+ 每个箱子的剩余容量
+ 需要的最小箱子数
+ 算法运行时间

## 算法设计

### 动态规划

#### 思路

**一种简单的装箱问题的另一种变式是**：    
给定一个固定容量的箱子，以及n件物品的重量，从这n件物品中选取若干件装入箱子，使得箱子剩余体积最小。    
        
我们先来求解这个问题，然后把选出来的这若干件物品去掉，对于剩下的物品再选取若干件装入箱子，使得箱子的剩余体积最小。重复这个求解过程，直到所有的物品都被装入箱子为止。每一次求解问题都会使用一个新的箱子，这样最终需要使用的箱子数是求解问题的次数。

#### 算法分析

**求解结果一定是最优解吗？**            
一定是最优解。每一次求解过程都能让新使用的这个箱子剩余体积最小，即每一次都能使箱子的空间利用率最大化。试想，如果一个箱子的空间利用率不是最大化，那么接下来的一个箱子空间势必要被上一个箱子未安排妥当的空间浪费，结果一定不是最优解。          
            
**算法时间复杂度如何？**             

首先我们分析一下求解过程和找到哪些物品被选出的过程。              
求解过程：
``` C++
/*求解箱子最多能放入多少重量的物品的过程*/
for (i = 1; i <= num; i++) {
	for (j = 1; j <= capacity; j++) {
		if (j < item[i] || item[i] == -1) {
			dp[i][j] = dp[i - 1][j];//放不下第i件物品或者第i件物品已经被用过
		}
		else {
			/*对于要不要放入第i件物品进行选择
			  若放入，问题变成在前i-1件物品中利用j-item[i]的空间所能装入的最大重量      
			  若不放入，问题变成在前i-1件物品中利用j的空间所能装入的最大重量 
			*/
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - item[i]] + item[i]);
			
		}

	}
			
}
```
         

回溯过程：
``` C++
int temp = dp[num][capacity], loc = num, sum = 0;

while (temp != 0) {
	/*
	逆序循环的原因是因为在求解过程中为正向循环
	如果第i件物品被选择，则无需考虑i+1及之后的物品
	从前i-1件物品中继续找哪些物品被选择即可
	*/
	for (i = loc; i >= 1; i--) {
		//找到哪一件物品被选择
		if (item[i] != -1 && temp - item[i] >= 0 && dp[i - 1][temp - item[i]] == dp[i][temp] - item[i]) {
			printf("%d ", i);
			load_num++;
			temp = temp - item[i];
			sum += item[i];		//加和本次求解选出的物品重量，与结果校验
			item[i] = -1;
			loc = i - 1;
			break;
		}
	}

}

assert(sum == dp[num][capacity]);	//防止回溯过程出错
```

以上是每一次求解过程都要经历的两个过程，其中求解过程的时间复杂度为 ***O(num\*capacity)*** ，其中 **num** 是物品的数量，**capacity**是箱子的最大容量。回溯过程的时间复杂度为 **O(num)** 。而根据输入的物品重量的不同，求解次数是不同的，因此求解的次数与算法的输入有关。

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

**算法时间复杂度如何？**    
最坏情况下，每一个箱子都恰好只能装下一个物品，那么时间复杂度为 ***O(num<sup>2</sup>)*** ,因为此时对于每一个物品都需要遍历到最后一个箱子发现装不下，并新使用一个新的箱子。这相比于动态规划的时间复杂度已经优化了很多，但牺牲的是解的最优性。

## 附录: 源代码

### 动态规划

``` C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <assert.h>
#include <ctime>
#include <cmath>
using namespace std;

#define SIZE 1005
#define MAX_CAPACITY 100005

int dp[SIZE][MAX_CAPACITY], item[SIZE], nxt[MAX_CAPACITY], current[MAX_CAPACITY];
int num, capacity, result = 0, i, j, load_num = 0;

bool comp(int x, int y) {
	return x > y;
}

void print() {
	int temp = dp[num][capacity], loc = num, sum = 0;
	printf("bin %d loads: ", result);

	while (temp != 0) {
		for (i = loc; i >= 1; i--) {
			if (item[i] != -1 && temp - item[i] >= 0 && dp[i - 1][temp - item[i]] == dp[i][temp] - item[i]) {
				printf("%d ", i);
				load_num++;
				temp = temp - item[i];
				sum += item[i];
				item[i] = -1;
				loc = i - 1;
				break;
			}
		}

		if (i > num) {
			break;
		}
	}

	assert(sum == dp[num][capacity]);	//防止回溯过程出错
	printf("\nbin %d space left:%d\n\n", result, capacity - dp[num][capacity]);
	

}

int main() {

	scanf("%d%d", &num, &capacity);
	for (i = 1; i <= num; i++) {
		scanf("%d", &item[i]);
	}

	/*for (i = 1; i <= num; i++) {
		printf("No.%d: %d\n", i, item[i]);
	}*/

	clock_t time_start = clock();
	while (load_num < num) {
		result++;
		memset(dp, 0, sizeof(dp));

		for (i = 1; i <= num; i++) {
			for (j = 1; j <= capacity; j++) {
				if (j < item[i] || item[i] == -1) {
					dp[i][j] = dp[i - 1][j];
				}
				else {
					dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - item[i]] + item[i]);
				}

			}
			
		}

		print();
	}

	printf("result: %d\n", result);
	clock_t time_end = clock();
	cout << "time use: " << 1000 * (time_end - time_start) / (double)CLOCKS_PER_SEC << "ms" << endl;
	return 0;
}
```

### 贪心算法

``` C++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
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
	
	for (i = 1; i <= result; i++) {
		printf("bin %d loads: ", i);
		for (j = 1; j <= rec[i].num; j++) {
			printf("%d ", rec[i].r[j]);
		}
		printf("\nbin %d space left:%d\n\n", i, capacity - bin[i]);
	}

	printf("\nresult: %d\n", result);
}

int main() {
	scanf("%d%d", &num, &capacity);
	for (i = 1; i <= num; i++) {
		scanf("%d", &item[i]);
	}

	clock_t time_start = clock();
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
	clock_t time_end = clock();
	cout << "time use: " << 1000 * (time_end - time_start) / (double)CLOCKS_PER_SEC << "ms" << endl;

	return 0;
}
```