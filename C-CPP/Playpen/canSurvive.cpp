#include <iostream>
#include <vector>

using namespace std;

// http://www.mitbbs.com/article_t1/JobHunting/32978937_0_1.html

class Solution {
private:
	//nextDay[k][n] : 第k天，第n个房间小偷是否可以survive
	//nextDay[i][j] = (nextDay[i-1][j-1] or nextDay[i-1][j+1]) && strategy[i] != j
	// O(n*k) time, O(n) space
	//vector<bool> nextDay;

public:
	bool canCatchTheft(int n, vector<int> strategy) {
		int k = strategy.size();
		// nextDay[i] means theft can survive in spot i or not on this day
		vector<bool> nextDay(n, true);
		bool canSurvive, pre, a, b;
		// init the first day
		nextDay[strategy[0]] = false;
		for (int i = 1; i < k; i++) {
			canSurvive = false; pre = false;
			for (int j = 0; j < n; j++) {
				a = j == 0 ? false : pre;
				b = j == n - 1 ? false : nextDay[j + 1];
				pre = nextDay[j]; // store current day for the next round
				nextDay[j] = ((a || b) && strategy[i] != j) ? true : false;
				if (nextDay[j] == true) canSurvive = true;
			}

			if (!canSurvive) return true;  
		}
		return false;
	}
	bool alibaba(int n, vector<int> strategy) {
		// survival[i] means theft can be in spot i or not on this day
		vector<bool> survival(n + 2, true);

		// init the first day
		// 在头尾加一个房间，且小偷不可能出现在这两个房间（为了处理下面j - 1和j + 1越界的情况）
		survival[0] = false;
		survival[n + 1] = false;
		survival[strategy[0]] = false;

		for (int i = 1; i < strategy.size(); i++) {
			for (int j = 1; j < n + 1; j++) {
				survival[j] = ((survival[j - 1] || survival[j + 1]) && strategy[i] != j) ? true : false;
			}
		}

		// 最后survival数组保存小偷可能出现的房间，如果都为false表示经过这个strategy寻找后小偷不可能在任何一个房间
		for (int i = 1; i < n + 1; i++) {
			if (survival[i]) return false;
		}
		return true;
	}
};

int main() {
	Solution sol;
	vector<int> strategy = {1, 2, 3, 4, 4, 3, 2, 1};
	cout << sol.canCatchTheft(4, strategy) << endl;
	cout << sol.alibaba(4, strategy) << endl;
}