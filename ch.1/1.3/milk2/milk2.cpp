/*
ID: B9532025
TASK: milk2
LANG: C++
*/
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>

using namespace std;

class farmer {
   public:
	int start, finished;
};

bool is_included(farmer &you, farmer &she) {
	// graphic like this: ( you  [ she ] ) or [( she, you )]
	if (you.start <= she.start && you.finished >= she.finished)
		return true;

	// graphic like this: [ she ( you ) ] or [( she, you )]
	if (she.start <= you.start && she.finished >= you.finished)
		return true;

	return false;
}

bool is_overlaped(farmer &you, farmer &she) {
	// graphic like this: [ she ( ] you )
	if (she.start < you.start && she.finished < you.finished &&
			she.finished >= you.start)
	return true;

	// graphic like this: ( you [ ) she ]
	if (you.start < she.finished && you.finished < she.finished &&
			you.finished >= she.start)
	return true;

	return false;
}

int compare(const void *a, const void *b) {
	farmer *pa, *pb;
	pa = (farmer *)a;
	pb = (farmer *)b;
	return pa->start - pb->start;
}

int main() {
	ofstream fout("milk2.out");
	ifstream fin("milk2.in");

	int n;
	fin >> n;

	farmer list[n];
	for (int i = 0; i < n; i++) fin >> list[i].start >> list[i].finished;

	qsort(list, n, sizeof(farmer), compare);

	farmer earlier_farmer;
	int work_time, idle_time;
	int max_work_time, max_idle_time;

	earlier_farmer = list[0];
	work_time = earlier_farmer.finished - earlier_farmer.start;
	idle_time = 0;
	max_work_time = work_time;
	max_idle_time = idle_time;
	for (int i = 1; i < n; i++) {
		// cout << "farmer " << i << ": " << list[i].start << " "
		//	 << list[i].finished << endl;
		if (is_included(earlier_farmer, list[i]))
			continue;

		// cout << "check overlap... : " << earlier_farmer.start << " "
		//	 << earlier_farmer.finished;
		if (is_overlaped(earlier_farmer, list[i])) {
			// cout << " -> overlaped" << endl;
			work_time += (list[i].finished - earlier_farmer.finished);
			// cout << "max work_time: " << max_work_time << ", "
			// << "work_time: " << work_time << endl;
			if (work_time > max_work_time) max_work_time = work_time;
		} else {  // no overlap
			// cout << " -> not overlaped" << endl;
			work_time = list[i].finished - list[i].start;
			idle_time = list[i].start - earlier_farmer.finished;
			// cout << "max idle_time: " << max_idle_time << ", "
			// << "idle_time: " << idle_time << endl;
			if (idle_time >= max_idle_time)
				max_idle_time = idle_time;
			else
				idle_time = 0;
		}
		earlier_farmer = list[i];
		// cout << "work: " << work_time << ", "
		//	 << "idle: " << idle_time << ", " << endl;
	}

	fout << max_work_time << " " << max_idle_time << endl;
	return 0;
}
