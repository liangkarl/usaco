/*
ID: B9532025
TASK: milk
LANG: C++
*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Milk {
	public:
	int price;
	int unit;
};

int compare(const void *a, const void *b) {
	Milk *pa = (Milk *)a;
	Milk *pb = (Milk *)b;
	return pa->price - pb->price;
}

int main() {
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");

	int need, n;
	fin >> need >> n;

	Milk list[n];
	for (int num = 0; num < n; num++) {
		fin >> list[num].price >> list[num].unit;
	}

	qsort(list, n, sizeof(Milk), compare);

	int amount, cost;
	cost = 0;
	for (int i = 0; need > 0; i++) {
		if (need > list[i].unit) {
			amount = list[i].price * list[i].unit;
			need -= list[i].unit;
		} else {
			amount = need * list[i].price;
			need -= need;
		}
		cost += amount;
	}

	fout << cost << endl;
    return 0;
}
