/*
ID: Karl Liang
TASK: ride
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

#define MAGIC_NUM 47
#define BASE 'A'

using namespace std;

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string comet, group;
    int sum_of_comet, sum_of_group;

    fin >> comet >> group;
    /* cout << comet << endl << group << endl; */

    sum_of_comet = 1;
    for (int i = 0; i < comet.length(); i++) {
	/* cout << "i=" << i << ": " <<  sum_of_comet << endl; */
	sum_of_comet *= (comet.at(i) - BASE + 1);
    }
    /* cout << sum_of_comet << endl; */

    sum_of_group = 1;
    for (int i = 0; i < group.length(); i++) {
	/* cout << "i=" << i << ": " <<  sum_of_group << endl; */
	sum_of_group *= (group.at(i) - BASE + 1);
    }
    /* cout << sum_of_group << endl; */

    if (sum_of_group % MAGIC_NUM == sum_of_comet % MAGIC_NUM)
	fout << "GO" << endl;
    else
	fout << "STAY" << endl;

    return 0;
}
