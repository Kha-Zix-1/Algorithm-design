#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
using namespace std;

#define SIZE 10005
#define SWAP_NUM 1000

int bin[SIZE] = { 0 }, item[SIZE], temp[SIZE], cnt[SIZE] = { 0 };
int num, capacity, result = 0, i, j, best_result;
double current_tem;

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

void first_fit() {
	result = 0;
	memset(bin, 0, sizeof(bin));

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

	//print();
}

void save() {
	for (i = 1; i <= num; i++) {
		temp[i] = item[i];
	}
}

void back() {
	for (i = 1; i <= num; i++) {
		item[i] = temp[i];
	}
}

void rand_swap() {
	int pos1, pos2;

	for (i = 1; i <= num; i++) {
		if (cnt[i] != 0) {
			cnt[i] = (cnt[i] + 1) % 3;
		}
	}

	for (i = 1; i <= num / 5; i++) {
		pos1 = rand() % num + 1;
		pos2 = rand() % num + 1;

		if (pos1 != pos2 && cnt[pos1] == 0 && cnt[pos2] == 0) {
			swap(item[pos1], item[pos2]);
			cnt[pos1] = cnt[pos2] = 1;
		}
		else {
			--i;
		}
	}

}

double random(double dblow, double dbhigh)//产生dblow-dbhigh之间随机数
{
	double dbtemp = rand() / ((double)RAND_MAX + 1.0);
	return dblow + dbtemp * (dbhigh - dblow);
}



int main() {
	int dE, before, total = 0;

	scanf("%d%d", &num, &capacity);
	for (i = 1; i <= num; i++) {
		scanf("%d", &item[i]);
	}

	clock_t time_start = clock();
	srand((unsigned)(time(NULL)));

	sort(item + 1, item + 1 + num, comp);

	first_fit();
	best_result = result;
	before = best_result;

	printf("Initial best result: %d\n\n", result);

	while (total <= 10000) {
		/*for (i = 1; i <= num; i++) {
			printf("%d ", item[i]);
		}
		puts("");*/

		save();
		rand_swap();
		first_fit();
		dE = result - best_result;

		printf("Iteration %d:\nresult: %d\n\n", ++total, result);

		if (dE <= 0) {
			best_result = result;
		}
		else {
			back();
		}

	}

	printf("\nbefore SA result: %d\nafter SA result: %d\n", before, best_result);
	clock_t time_end = clock();
	cout << "time use: " << 1000 * (time_end - time_start) / (double)CLOCKS_PER_SEC << "ms" << endl;
}