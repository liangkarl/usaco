/*
ID: karl liang
TASK: milk3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <queue>

#define __NAME__ "milk3"
#define INPUT_FILE string(__NAME__).append(".in")
#define OUTPUT_FILE string(__NAME__).append(".out")

using namespace std;

class solve_milk3 {
	enum ID {
		MILK_A = 0,
		MILK_B,
		MILK_C,
		MAX_MILKS,
	};

	union state {
		uint8_t milks[MAX_MILKS + 1] = {0}; // 1 for dummy
		uint32_t state;
	};

	union state vol;
	int now_state;

	set<int> states, ans;
	queue<int> tree;

	public:
	solve_milk3(int a, int b, int c) {
		vol.milks[MILK_A] = a;
		vol.milks[MILK_B] = b;
		vol.milks[MILK_C] = c;
	}

	void solve() {
		union state now;
		int next_id, rest_milk;
		now.milks[MILK_A] = 0;
		now.milks[MILK_B] = 0;
		now.milks[MILK_C] = vol.milks[MILK_C];

		states.insert(now.state);
		tree.push(now.state);
		// use BFS to discover every nodes
		while (!tree.empty()) {
			now_state = tree.front();
			now.state = now_state;
			// give milk to others
			for (int id = MILK_A; id <= MILK_C; id++) {
				// go next if current milk is empty
				if (now.milks[id] == 0)
					continue;

				// save state if milk a is empty
				if (now.milks[MILK_A] == 0) {
					ans.insert(now.milks[MILK_C]);
				}

				for (int offset = 1; offset <= 2; offset++) {
					next_id = (id + offset) % MAX_MILKS;
					rest_milk = now.milks[id] + now.milks[next_id] - vol.milks[next_id];
					if (rest_milk <= 0) {
						now.milks[next_id] += now.milks[id];
						now.milks[id] = 0;
					} else {
						now.milks[next_id] = vol.milks[next_id];
						now.milks[id] = rest_milk;
					}

					// save result if it's new state
					if (states.find(now.state) == states.end()) {
						states.insert(now.state);
						tree.push(now.state);
					}

					// reset state
					now.state = now_state;
				}
			}
			tree.pop();
		}
	}

	string answer() {
		string out = "";
		for (int num : ans) {
			out.append(to_string(num)).append(" ");
		}
		if (out.size() != 0) {
			out.resize(out.size()-1);
		}
		return out;
	}
};


int main() {
	ifstream fin (INPUT_FILE);
	ofstream fout (OUTPUT_FILE);

	int a, b, c;
	fin >> a >> b >> c;
	solve_milk3 program(a, b, c);
	program.solve();
	fout << program.answer() << '\n';

	return 0;
}
