/*
ID: Karl Liang
TASK: transform
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

#define TO_INDEX(x) ((x)-1)

int n;
inline bool check_rotate_90(char before[][10], char symbol, int y, int x) {
	// cout << "check rot 90: " << symbol << " == "
	// 	<< before[x][TO_INDEX(n)-y] << "?" << endl;
	return symbol == before[TO_INDEX(n)-x][y];
}

inline bool check_rotate_180(char before[][10], char symbol, int y, int x) {
	// cout << "check rot 180: " << symbol << " == "
	// 	<< before[TO_INDEX(n)-y][TO_INDEX(n)-x] << "?" << endl;
	return symbol == before[TO_INDEX(n)-y][TO_INDEX(n)-x];
}

inline bool check_rotate_270(char before[][10], char symbol, int y, int x) {
	// cout << "check rot 270: " << symbol << " == "
	// 	<< before[TO_INDEX(n)-x][y] << "?" << endl;
	return symbol == before[x][TO_INDEX(n)-y];
}

inline bool check_reflected(char before[][10], char symbol, int y, int x) {
	// cout << "check ref: " << symbol << " == "
	// 	<< before[y][TO_INDEX(n)-x] << "?" << endl;
	return symbol == before[y][TO_INDEX(n)-x];
}

inline bool check_no_changed(char before[][10], char symbol, int y, int x) {
	// cout << "check no changed: " << symbol << " == "
	// 	<< before[y][x] << "?" << endl;
	return symbol == before[y][x];
}

inline bool check_reflected_and_rotate_270(char before[][10], char symbol, int y, int x) {
	// cout << "check ref + rot 270: " << symbol << " == "
	// 	<< before[TO_INDEX(n)-x][TO_INDEX(n)-y] << "?" << endl;
	return symbol == before[TO_INDEX(n)-x][TO_INDEX(n)-y];
}

inline bool check_reflected_and_rotate_180(char before[][10], char symbol, int y, int x) {
	// cout << "check ref + rot 180: " << symbol << " == "
	// 	<< before[y][TO_INDEX(n)-x] << "?" << endl;
	return symbol == before[TO_INDEX(n)-y][x];
}

inline bool check_reflected_and_rotate_90(char before[][10], char symbol, int y, int x) {
	// cout << "check ref + rot 90: " << symbol << " == "
	// 	<< before[x][y] << "?" << endl;
	return symbol == before[x][y];
}

int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");

	fin >> n;

	char before[10][10] = {0};
	char after[10][10] = {0};

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fin >> before[i][j];

	bool is_rotate_90, is_rotate_180, is_rotate_270;
	bool is_reflected, is_no_changed;
	bool is_ref_and_rot_90, is_ref_and_rot_180, is_ref_and_rot_270;
	is_rotate_90 = true;
	is_rotate_180 = true;
	is_rotate_270 = true;
	is_reflected = true;
	is_no_changed = true;
	is_ref_and_rot_90 = true;
	is_ref_and_rot_180 = true;
	is_ref_and_rot_270 = true;
	char sym;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			fin >> sym;
			// cout << "i=" << i << ", " << "j=" << j << endl;
			if (is_rotate_90 == true)
				is_rotate_90 = check_rotate_90(before, sym, i, j);

			if (is_rotate_180 == true)
				is_rotate_180 = check_rotate_180(before, sym, i, j);

			if (is_rotate_270 == true)
				is_rotate_270 = check_rotate_270(before, sym, i, j);

			if (is_reflected == true)
				is_reflected = check_reflected(before, sym, i, j);

			if (is_no_changed == true)
				is_no_changed = check_no_changed(before, sym, i, j);

			if (is_ref_and_rot_90 == true) {
				is_ref_and_rot_90 = check_reflected_and_rotate_90(before, sym, i, j);
			}
			if (is_ref_and_rot_180 == true) {
				is_ref_and_rot_180 = check_reflected_and_rotate_180(before, sym, i, j);
			}
			if (is_ref_and_rot_270 == true) {
				is_ref_and_rot_270 = check_reflected_and_rotate_270(before, sym, i, j);
			}
		}

	if (is_rotate_90)
		fout << 1 << endl;
	else if (is_rotate_180)
		fout << 2 << endl;
	else if (is_rotate_270)
		fout << 3 << endl;
	else if (is_reflected)
		fout << 4 << endl;
	else if (is_ref_and_rot_90 || is_ref_and_rot_180 || is_ref_and_rot_270)
		fout << 5 << endl;
	else if (is_no_changed)
		fout << 6 << endl;
	else
		fout << 7 << endl;
    return 0;
}
