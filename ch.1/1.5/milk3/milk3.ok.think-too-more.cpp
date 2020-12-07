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
	static const int MAX_MILKS = 3;
	static const int MILK_A = 0;
	static const int MILK_B = 1;
	static const int MILK_C = 2;
	static const int DISTANCE = 5;

	int milks_vol[MAX_MILKS];
	int now_state;

	set<int> states;
	set<int> ans;
	queue<int> tree;

	inline int to_state(int *milks) {
		// for (int i = 0; i < 3; i++) {
		// 	printf("i(%d): %d, ", i, milks[i]);
		// }
		// puts("");
		return milks[MILK_A] + (milks[MILK_B] << DISTANCE)
			+ (milks[MILK_C] << (DISTANCE * 2));
	}

	int save_state(int *milks) {
		// a + b * 10^2 + c * 10^4, since max values are 1~20
		int state;
		state = to_state(milks);
		// printf("-> %d\n", state);
		states.insert(state);
		return state;
	}

	bool has_state(int *milks) {
		int state;
		state = to_state(milks);
		return states.find(state) != states.end();
	}

	void load_state(int state, int *milks) {
		const int mask = 0x1F;
		for (int id = MILK_A; id < MAX_MILKS; id++) {
			milks[id] = (state & (mask << (DISTANCE * id)))
				>> (DISTANCE * id);
		}
	}

	public:
	solve_milk3(int a, int b, int c) {
		milks_vol[MILK_A] = a;
		milks_vol[MILK_B] = b;
		milks_vol[MILK_C] = c;
	}

	void solve() {
		int milks[MAX_MILKS] = {0};
		int next_id, rest_milk;
		milks[MILK_A] = 0;
		milks[MILK_B] = 0;
		milks[MILK_C] = milks_vol[MILK_C];
		// now_state = to_state(milks);
		// printf("now: %d\n", now_state);
		// milks[0] = milks[1] = milks[2] = -1;
		// load_state(now_state, milks);
		// printf("%d %d %d\n", milks[0], milks[1], milks[2]);
		tree.push(save_state(milks));
		// use BFS to discover every nodes
		while (!tree.empty()) {
			now_state = tree.front();
			load_state(now_state, milks);
			printf("now: %d\n", now_state);
			// give milk to others
			for (int id = MILK_A; id <= MILK_C; id++) {
				// go next if current milk is empty
				if (milks[id] == 0)
					continue;

				// save state if milk a is empty
				if (milks[MILK_A] == 0) {
					ans.insert(milks[MILK_C]);
				}

				for (int offset = 1; offset <= 2; offset++) {
					next_id = (id + offset) % MAX_MILKS;
					rest_milk = milks[id] + milks[next_id] - milks_vol[next_id];
					if (rest_milk <= 0) {
						milks[next_id] += milks[id];
						milks[id] = 0;
					} else {
						milks[next_id] = milks_vol[next_id];
						milks[id] = rest_milk;
					}

					// save result if it's new state
					if (!has_state(milks)) {
						tree.push(save_state(milks));
					}

					// reset state
					load_state(now_state, milks);
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
