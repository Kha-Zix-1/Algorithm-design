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