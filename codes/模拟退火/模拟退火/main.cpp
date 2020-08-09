#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
using namespace std;

#define INIT_TEM 100.0
#define MIN_TEM 0.1
#define cold_speed 0.97
#define k 0.01
#define SIZE 10005
#define SWAP_NUM 1000

int bin[SIZE] = { 0 }, item[SIZE], temp[SIZE];
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

	for (i = 1; i <= SWAP_NUM; i++) {
		pos1 = rand() % num + 1;
		pos2 = rand() % num + 1;

		if (pos1 != pos2) {
			swap(item[pos1], item[pos2]);
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

	srand((unsigned)(time(NULL)));
	current_tem = INIT_TEM;

	sort(item + 1, item + 1 + num, comp);

	first_fit();
	best_result = result;
	before = best_result;

	printf("Initial best result: %d\n\n", result);

	while (current_tem >= MIN_TEM) {
		save();
		rand_swap();
		first_fit();
		dE = result - best_result;

		printf("Iteration %d:\ntem: %.2lf\nresult: %d\n\n",++total, current_tem, result);

		if (dE <= 0) {
			best_result = result;
		}
		else if (exp(-dE / (current_tem * k)) > random(0.0, 1.0)) {
			best_result = result;
		}
		else {
			back();
		}

		current_tem = cold_speed * current_tem;
	}

	printf("\nbefore SA result: %d\nafter SA result: %d\n", before, best_result);
}