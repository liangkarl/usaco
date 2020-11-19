/*
ID: B9532025
TASK: gift1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <map>

#define MAGIC_NUM 47
#define BASE 'A'

using namespace std;

class person {
public:
  string name;
  int fund = 0;
  int received = 0;
  // finally, fund - received = ouput value
  int ng = 0;
};

int main() {
    ofstream fout ("gift1.out");
    ifstream fin ("gift1.in");

    int np;
    fin >> np;

    map<string, person*> table;
    person list[np];
    for (int i = 0; i < np; i++) {
	fin >> list[i].name;
	/* cout << i << ": " << list[i].name << endl; */
	table[list[i].name] = &list[i];
    }

    string name;
    int fund;
    person *who;
    for (int i = 0; i < np; i++) {
	fin >> name; // dummy
	who = table[name];
	fin >> fund >> who->ng;
	/* cout << name << ": " << who->fund << " " << who->ng << endl; */

	int gift_value;
	if(who->ng == 0)
		continue;
	gift_value = fund / who->ng;
	who->fund -= fund;
	who->fund += (fund - gift_value * who->ng);
	/* cout << "after shared: " << who->fund << endl */
	/*	<< "each gift: " << gift_value << " to " << who->ng << endl; */

	person *receiver;
	for(int j = 0; j < who->ng; j++) {
		fin >> name;
		/* cout << i << ": " << name << endl; */
		receiver = table[name];
		receiver->received += gift_value;
		/* cout << "receiver's name: "<< receiver->name */
		/*	<< " got " << gift_value << endl */
		/*	<< "total get: " << receiver->received << endl; */
	}
    }

    for (int i = 0; i < np; i++)
	fout << list[i].name << " "
		<< list[i].fund + list[i].received
		<< endl;

    return 0;
}
