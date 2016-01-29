/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    // Time ~ O(NlogN), space O(N)
    static bool cmp(Interval a, Interval b) {
        return a.start < b.start;
    }
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> result;
        if (intervals.empty()) return result;
        
        sort(intervals.begin(), intervals.end(), cmp);
        result.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            int prevend = result.back().end;
            if (prevend < intervals[i].start) {
                result.push_back(intervals[i]);
            } else if (prevend < intervals[i].end){
                result.back().end = intervals[i].end;
            }
        }
        return result;
    }
};