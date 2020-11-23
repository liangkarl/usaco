/*
ID: B9532025
TASK: milk2
LANG: C++
*/
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/cdefs.h>

//60*60*24
#define TIME_SLOT 86400

using namespace std;

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");

	int n;
	fin >> n;

	// index 0 -> 1 sec
	char time_map[TIME_SLOT] = {0};
	int begin, end;
	int earliest, latest;

	earliest = TIME_SLOT;
	latest = 0;
	for(int i = 0; i < n; i++) {
		fin >> begin >> end;

		cout << "begin: " << begin << ", end: " << end << endl;
		if (begin >= TIME_SLOT)
			begin %= TIME_SLOT;
		if (end >= TIME_SLOT)
			end %= TIME_SLOT;

		// assume end > begin
		if (earliest > begin)
			earliest = begin;
		if (latest < end)
			latest = end;

		// (begin - 1) to index, index + 1 to next position, so map[index]
		if (end < begin) { // begin at night and end at day
			memset(&time_map[begin], 1, (TIME_SLOT - begin) * sizeof(char));
			memset(&time_map, 1, end * sizeof(char));
		} else if (end > begin) {
			memset(&time_map[begin], 1,
					sizeof(char) * (end - begin));
		}
	}

	for(int i = 0; i < TIME_SLOT; i += 20) {
		printf("%06d: ", i);
		for(int j = 0; j < 20; j++) {
			printf("%d", time_map[i + j]);
		}
		cout << endl;
	}

	int longest_idle_time, longest_working_time;
	int idle_time, working_time;

	cout << "earliest: " << earliest << ", "
		<< "latest: " << latest << endl;
	idle_time = 0;
	working_time = 0;
	if (time_map[earliest] == 0)
		idle_time++;
	else
		working_time++;
	longest_idle_time = idle_time;
	longest_working_time = working_time;
	for(int i = earliest + 1; i < latest; i++) {
		if (time_map[i] == 0)
			idle_time++;
		else // == 1
			working_time++;

		if (time_map[i] != time_map[i-1]) { // ...10 or ...01
			cout << "changed at " << i << endl;
			if (time_map[i] == 0) {
				if (working_time > longest_working_time)
					longest_working_time = working_time;
				working_time = 0;
			} else {
				if (idle_time > longest_idle_time)
					longest_idle_time = idle_time;
				idle_time = 0;
			}
			cout << "longest work: " << longest_working_time
				<< ", idle: " << longest_idle_time << endl;
		}
	}

			cout << "work: " << working_time
				<< ", idle: " << idle_time << endl;
			cout << "longest work: " << longest_working_time
				<< ", idle: " << longest_idle_time << endl;
	if (working_time > longest_working_time)
		longest_working_time = working_time;
	if (idle_time > longest_idle_time)
		longest_idle_time = idle_time;

	fout << longest_working_time << " " << longest_idle_time << endl;
    return 0;
}
