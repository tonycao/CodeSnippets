#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Racer {
public:
	int id;
	int start;
	int end;
	int score;

	Racer(int id_, int start_, int end_): id(id_), start(start_), end(end_){ 
		score = 0;
	}

	bool operator<(Racer& b) const {
		return start < b.start;
	}
};





class Solution {
private:
	vector<Racer*> tmp;
public:

// http://www.mitbbs.com/article_t/JobHunting/32573375.html
// http://codeanytime.blogspot.com/2013/05/score-of-racers.html
// http://www.geeksforgeeks.org/counting-inversions/
// merge sort: 
// 先按照start time sort; 
// 然后按照 end time merge sort;
// 类似inverse count
// 复杂度 nlogn

	class cmp
	{
	public:
		bool operator()(Racer *a, Racer *b)
		{
			return a->start < b->start;
		}
	};

	void mergesort(vector<Racer*> &racers) {
		cout << "start" << endl;
		tmp.resize(racers.size(), nullptr);
		sort(racers.begin(), racers.end(), cmp());

		for (int i = 0 ; i < racers.size(); i++) {
			cout << racers[i]->id << " ";
		}
		cout << endl;

		mergesort_help(racers, tmp, 0, racers.size() - 1);
	}


	void mergesort_help(vector<Racer*> &racers, vector<Racer*> &tmp, int left, int right) {

		int mid;
		if (left < right) {
			mid = left + (right - left) / 2;

			mergesort_help(racers, tmp, left, mid);
			mergesort_help(racers, tmp, mid + 1, right);

			merge(racers, tmp, left, mid + 1, right);
		}

	}
	void merge(vector<Racer*> &racers, vector<Racer*> tmp, int low, int mid, int high)
	{
		int p1 = low;
		int p2 = mid+1;
    //vector<Racer*> tmp(high-low+1);
		int k=0;
		while(p1 <= mid || p2 <= high){
			if(p1>mid || (p1<=mid && p2<=high && racers[p2]->end < racers[p1]->end)){
				tmp[k] = racers[p2];
				p2++;
			}	else if (p2>high || (p1<=mid && p2<=high && racers[p2]->end > racers[p1]->end) ) {
				tmp[k] = racers[p1];
				racers[p1]->score += (p2-mid-1);
				p1++;
			}
			k++;
		}

  //－－－－－－－省略－－－－
	}

};

int main() {

	vector<Racer*> racers = {new Racer(2, 100, 200), new Racer(3, 110, 190), new Racer(4, 105, 145), 
		new Racer(1, 90, 150), new Racer(5, 102, 198)};
		Solution sol;
		sol.mergesort(racers);

		for (int i = 0; i < racers.size(); i++) {
			cout << "score for " << i << " : " << racers[i]->score << endl;
		}

		return 0;
	}
