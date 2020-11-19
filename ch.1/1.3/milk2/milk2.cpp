/*
ID: B9532025
TASK: milk2
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

class farmer {
	int start;
	int end;
};

int main() {
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");

	string str_n;
	int n;
	fin >> str_n;
	n = std::stoi(str_n);

	list<farmer> list;
	for(int i = 0; i < n; i++) {
		if (!list.empty()) {

		} else {
		}
	}
    return 0;
}
