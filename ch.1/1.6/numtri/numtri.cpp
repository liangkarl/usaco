/*
ID: karl liang
TASK: numtri
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <queue>
#include <complex>

#define __NAME__ "numtri"
#define INPUT_FILE string(__NAME__).append(".in")
#define OUTPUT_FILE string(__NAME__).append(".out")

using namespace std;

class Numtri {
	static const int MAX_NODE_VAL = 100;
	static const int MAX_R_VAL = 1000;

	queue<int> tree;
	const int R;
	int prev_sum[MAX_R_VAL] = {0};
	int cur_val[MAX_R_VAL] = {0};
	int ans;

	void visit_nodes(int lv);

	public:
	Numtri(queue<int> &tree, int r) : tree(tree), R(r) {}
	void solve();
	string answer();
};


// start from lvl = 2
void Numtri::visit_nodes(int lv) {
	int val;

	// go through each node in the lvl
	for (int base = 0; base < lv; base++) {
		val = tree.front();
		if (base == 0) {
			val += prev_sum[0];
		} else {
			if (prev_sum[base] >= prev_sum[base-1])
				val += prev_sum[base];
			else
				val += prev_sum[base-1];
		}
		cur_val[base] = val;
		tree.pop();
	}
}

void Numtri::solve() {
	int lv;
	prev_sum[0] = tree.front();
	tree.pop();

	// BFS much better
	// go through lvl
	for (lv = 2; lv <= R; lv++) {
		visit_nodes(lv);

		// copy cur_val to prev_sum
		for (int i = 0; i < lv; i++)
			prev_sum[i] = cur_val[i];
	}

	// no need to use qsort since O(nlogn) > O(n)
	ans = 0;
	for (int i = 0; i < R; i++)
		if (cur_val[i] > ans)
			ans = cur_val[i];
}

string Numtri::answer() {
	return to_string(ans);
}


int main() {
	ifstream fin (INPUT_FILE);
	ofstream fout (OUTPUT_FILE);

	int r;
	fin >> r;
	queue<int> tree;

	int node;
	for (int row = 1; row <= r; row++) {
		for (int item = 1; item <= row; item++) {
			fin >> node;
			tree.push(node);
			// printf("%d ", node);
		}
		// puts("");
	}

	Numtri program(tree, r);
	program.solve();

	fout << program.answer() << '\n';
	return 0;
}
