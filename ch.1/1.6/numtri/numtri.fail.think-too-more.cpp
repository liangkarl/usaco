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

	int get_loop_times(int base, int lvl);
	void visit_nodes(int lvl);

	public:
	Numtri(queue<int> &tree, int r) : tree(tree), R(r) {}
	void solve();
	string answer();
};

int Numtri::get_loop_times(int base, int lvl) {
	int quot, min, div;
	// we need to loop such times in each tree.node
	//       1   1
	//     1   2   1
	//   1   3   3   1
	// 1   4   6   4   1
	// [Reference](https://zh.wikipedia.org/wiki/%E6%9D%A8%E8%BE%89%E4%B8%89%E8%A7%92%E5%BD%A2#%E6%80%A7%E8%B3%AA)
	if (lvl - base >= base)
		min = base;
	else
		min = lvl - base;

	quot = 1;
	div = 1;
	for (int dec = lvl, inc = 1; inc <= min; dec--, inc++) {
		quot *= dec;
		div *= inc;
	}

	return quot / div;
}

// start from lvl = 1
void Numtri::visit_nodes(int lvl) {
	int last_node;
	int index, times, max, val;

	last_node = lvl + 1;
	// go through each node in the lvl
	for (int base = 0; base < last_node; base++) {
		// change tree value while reaching loop count
		// find the max value in the loop
		times = get_loop_times(base, lvl);
		max = 0;
		val = 0;
		printf("t(%d), b(%d):\n", times, base);
		for (int offset = 0; offset < times; offset++) {
			index = base + offset;
			val = tree.front() + prev_sum[base/2];
			printf("(%d+%d)%d ", tree.front(), prev_sum[base/2], val);
			if (val > max)
				max = val;
		}
		puts("");
		cur_val[base] = max;
		tree.pop();
	}
}

void Numtri::solve() {
	int lvl, last_node;
	prev_sum[0] = tree.front();
	tree.pop();

	// BFS much better
	// go through lvl
	for(lvl = 1; lvl < R; lvl++) {
		visit_nodes(lvl);
		puts("");

		last_node = pow(2, lvl);
		// copy cur_val to prev_sum
		for (int i = 0; i < last_node; i++)
			prev_sum[i] = cur_val[i];
	}

	// no need to use qsort since O(nlogn) > O(n)
	ans = 0;
	last_node = lvl * 2;
	for (int i = 0; i < lvl * 2; i++)
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
			printf("%d ", node);
		}
		puts("");
	}

	Numtri program(tree, r);
	program.solve();

	fout << program.answer() << '\n';
	return 0;
}
