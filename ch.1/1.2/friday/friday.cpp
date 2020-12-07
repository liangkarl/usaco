/*
ID: Karl Liang
TASK: friday
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

#define BASE_YEAR 1900
#define DAYS_A_WEEK 7
#define MONTHS 12

using namespace std;

// month 0 -> Jan
// month 11 -> Dec
int days_of_month(int month) {
	int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	return days[month];
}

bool check_leap_year(int year) {
	bool is_leap_year;

	if (year % 100 != 0) {
		// Every year evenly divisible by 4 is a leap year
		is_leap_year = year % 4 == 0 ? true : false;
	} else {
		// The rule above does not hold for century years.
		// Century years divisible by 400 are leap years, all others are not.
		is_leap_year = year % 400 == 0 ? true : false;
	}
	return is_leap_year;
}

// day 0 -> Sunday
// day 6 -> Saturday
int cal_days(int beg_day, int day_after) {
	int offset;

	offset = day_after % DAYS_A_WEEK;
	return beg_day + offset >= DAYS_A_WEEK ?
		(beg_day + offset) % DAYS_A_WEEK : beg_day + offset;
}

int main() {
	ofstream fout("friday.out");
	ifstream fin("friday.in");

	int thirteenth_days[MONTHS] = {0};
	int year, current_day, days;
	bool is_leap_year;
	int range;

	fin >> range;

	// January 1, 1900 was on a Monday.
	year = BASE_YEAR;
	days = days_of_month(0);
	current_day = 1;
	cout << "current_day: " << current_day << endl;
	for (int i = 0; i < range; i++) {
		is_leap_year = check_leap_year(year + i);
		cout << year + i << " is leap year? " << is_leap_year << endl;
		for (int j = 0; j < 12; j++) {
			days = days_of_month(j);
			if(is_leap_year && j == 1)
				days++;

			cout << "month " << j + 1 << ": " << days << endl;
			current_day = cal_days(current_day, 12);
			cout << "thirteenth: " << current_day << endl;
			thirteenth_days[current_day]++;
			current_day = cal_days(current_day, days - 12);
			cout << "begin day of next month: " << current_day << endl;
		}
	}

	// Order by Saturday, Sunday, Monday, Tuesday, ..., Friday.
	fout << thirteenth_days[6] << " "
		<< thirteenth_days[0] << " "
		<< thirteenth_days[1] << " "
		<< thirteenth_days[2] << " "
		<< thirteenth_days[3] << " "
		<< thirteenth_days[4] << " "
		<< thirteenth_days[5] << endl;
	return 0;
}
