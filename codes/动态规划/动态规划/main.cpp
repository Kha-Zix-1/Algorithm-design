#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

#define SIZE 10005
#define MAX_CAPACITY 100005

int dp[MAX_CAPACITY], item[SIZE], nxt[MAX_CAPACITY], current[MAX_CAPACITY];
int num, capacity, result = 0, i, j, load_num = 0;

bool comp(int x, int y) {
	return x > y;
}

void print() {
	int temp = dp[capacity];
	printf("bin %d loads: ", result);

	while (temp != 0) {
		for (i = 1; i <= num; i++) {
			if (item[i] != -1 && temp - item[i] >= 0 && dp[temp - item[i]] == dp[temp] - item[i]) {
				printf("%d ", i);
				load_num++;
				temp = temp - item[i];
				item[i] = -1;
				break;
			}
		}

		if (i > num) {
			break;
		}
	}
	printf("\nbin %d space left:%d\n\n", result, capacity - dp[capacity]);

}

int main() {

	scanf("%d%d", &num, &capacity);
	for (i = 1; i <= num; i++) {
		scanf("%d", &item[i]);
	}

	while (load_num < num) {
		result++;
		memset(dp, 0, sizeof(dp));
		memset(nxt, 0, sizeof(nxt));
		memset(current, 0, sizeof(current));

		for (i = 1; i <= num; i++) {
			if (item[i] != -1) {
				for (j = capacity; j >= item[i]; j--) {
					if (dp[j - item[i]] + item[i] >= dp[j]) {
						current[j] = i;
						nxt[j] = j - item[i];
						dp[j] = dp[j - item[i]] + item[i];
					}

				}

			}
			
		}

		print();
	}

	printf("\nresult: %d\n", result);

	return 0;
}