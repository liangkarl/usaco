/*
ID: Karl Liang
TASK: wormhole
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <map>
#include <set>

using namespace std;

ofstream fout ("wormhole.out");
ifstream fin ("wormhole.in");

class hole {
	public:
		int x;
		int y;
		hole *link;

		hole() : x(0), y(0), link(nullptr) {}

		friend ostream &operator<<(ostream &out, const hole &h) {
			out << "(" << h.x << "," << h.y << ")";
			return out;
		}
};

map<hole *, hole *> right_on;

int exist_circle(hole holes[], int n) {
	// +x
	// cout << "linked list\n";
	// for (int i = 0; i < n; i++)
	// 	cout << "(" << holes[i].x << ","
	// 		<< holes[i].y << ") <-> "
	// 		<< "(" << holes[i].link->x << ","
	// 		<< holes[i].link->y << ")" << endl;
	// cout << '\n';

	// return 1;
	hole *cow_pos, *right_pos;
	set<hole*> path;
	bool no_loop;

	no_loop = true;
	for (int i = 0; i < n; i++) {
		cow_pos = &holes[i];
		// cout << i << ": cow at " << *cow_pos;
		// go through all of holes
		while (no_loop) {
			// cout << "\nenter " << *cow_pos;
			path.insert(cow_pos);
			cow_pos = cow_pos->link;
			// cout << " link to " << *cow_pos;
			// path.insert(cow_pos);
			right_pos = right_on[cow_pos];
			if (right_pos == nullptr) { // no loop
				// cout << '\n';
				break;
			}
			cow_pos = right_pos;
			// cout << " go next to " << *cow_pos << '\n';

			no_loop = path.find(cow_pos) == path.end();
			// cout << "no loop? " << no_loop << '\n';
			if (!no_loop) // find loop
				return 1;
		}
		// cout << "next entry\n";
		path.clear();
	}
	// exist circle
	return 0;
}

int solve(hole holes[], int n, int start, int paired) {
	if (paired == n)
		return exist_circle(holes, n);

	// TODO: can be improved
	// pair holes
	int count = 0;
	// cout << " in paired: " << paired << ", start: " << start << '\n';
	for (int i = start; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (holes[i].link == nullptr
					&& holes[j].link == nullptr) {
				holes[i].link = &holes[j];
				holes[j].link = &holes[i];

				// find next pair
				count += solve(holes, n, i+1, paired+2);

				// clean paired here
				holes[i].link = nullptr;
				holes[j].link = nullptr;
			}
		}
	}

	// no paired
	return count;
}

int solve2(hole holes[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (holes[i].link == nullptr)
			break;
	}

	if (i >= n)
		return exist_circle(holes, n);

	// cout << "find: " << i << " -> " << holes[i] << '\n';

	int count;
	count = 0;
	for (int j = i + 1; j < n; j++) {
		// pair holes here
		if (holes[j].link == nullptr) {
			holes[i].link = &holes[j];
			holes[j].link = &holes[i];
			// find next hole pair
			count += solve2(holes, n);

			// reset
			holes[i].link = holes[j].link = nullptr;
		}
	}
	return count;
}

int compare(const void *a, const void *b) {
	hole *ha, *hb;
	ha = (hole*)a;
	hb = (hole*)b;
	if (hb->y == ha->y)
		return ha->x - hb->x;
	else
		return ha->y - hb->y;
}

int main() {
	int n;
	fin >> n;

	hole holes[n];
	// vector<hole> holes(n);
	for (int i = 0; i < n; i++)
		fin >> holes[i].x >> holes[i].y;
	fin.close();

	qsort(holes, n, sizeof(hole), compare);
	hole *left, *right;
	for (int i = 1; i < n; i++) {
		left = &holes[i-1];
		right = &holes[i];
		// cout << *left << "...";
		if (left->y == right->y) {
			right_on[left] = right;
			// cout << *right_on[left] << '\n';
		} else {
			right_on[left] = nullptr;
			// cout << " x" << '\n';
		}
	}
	right_on[right] = nullptr;

	int ans;
	// ans = solve(holes, n, 0, 0);
	ans = solve2(holes, n);
	fout << ans << endl;
	return 0;
}
