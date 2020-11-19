/*
ID: B9532021
TASK: beads
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#define RED 'r'
#define BLUE 'b'
#define WHITE 'w'

using namespace std;

// return the length of same color (include white)
// could be "wwrr", "rrww", "rrwwrr" ...
int get_same_color_beads_len(string &beads, int start) {
	char color, request;
	int len;

	len = 0;
	request = beads.at(start);
	for (int i = start; i < beads.length(); i++) {
		color = beads.at(i);
		/* cout << "pos: " << i << " " */
		/*	<< "current: " << color << " " */
		/*	<< "request: " << request << endl; */

		if (color == WHITE || color == request) {
			// "w/b/r -> w" or "r/b -> r/b"
			len++;
		} else { // color != WHITE && color != request
			if (request == WHITE) {
				len++;
				request = color;
				// "w -> b" or "w -> r" here
				continue;
			}
			// "r -> b" or "b -> r" here
			break;
		}
	}
	return len;
}

int main() {
	ofstream fout("beads.out");
	ifstream fin("beads.in");

	int beads_len;
	int len, pos;
	string beads, beads_head;

	fin >> beads_len >> beads;
	/* cout << "beads: " << beads << endl; */
	pos = 0;
	len = get_same_color_beads_len(beads, pos);
	/* cout << "get first len: " << len << endl; */

	if (pos + len >= beads.length()) {
		/* cout << "reach string end: " << pos + len << endl; */
		fout << len << endl;
		return 0;
	}

	len += get_same_color_beads_len(beads, pos + len);
	/* cout << "get total len: " << len << endl; */

	beads_head = beads.substr(0, len);
	beads.append(beads_head);
	/* cout << "concat beads: " << beads << endl; */

	// Prepare search
	int max_len, next_pos;

	pos = 0;
	max_len = 1;
	while (pos < beads.length()) {
        len = get_same_color_beads_len(beads, pos);
		/* cout << "get first section len: " << len << endl; */
		next_pos = pos + len;

		if (next_pos >= beads.length()) {
			if (max_len < len)
				max_len = len;
			/* cout << "reach string end: " << next_pos << endl; */
			break;
		}

		len += get_same_color_beads_len(beads, next_pos);
		/* cout << "get total len: " << len << endl; */

		if (max_len < len)
			max_len = len;

		char color = beads.at(pos);
		while (pos < beads.length()) {
			if (color == WHITE) {
				if (beads.at(pos) != WHITE)
					color = beads.at(pos);
			} else { // color != WHITE
				if (color != beads.at(pos))
					break;
			}
			pos++;
		}
		/* cout << "pos: " << pos << endl; */
	}
	if (max_len > beads_len)
		max_len = beads_len;

	fout << max_len << endl;
	return 0;
}
