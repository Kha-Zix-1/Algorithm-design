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