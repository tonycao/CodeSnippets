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
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        // Time ~ O(N), Space ~ O(N)
        vector<Interval> res;
        int n = intervals.size();
        for (int i = 0;  i < n; i++) {
            if (intervals[i].end < newInterval.start) {
                res.push_back(intervals[i]);
            } else if (intervals[i].start > newInterval.end) {
                res.push_back(newInterval);
                for (int j = i; j < n; j++)
                    res.push_back(intervals[j]);
                return res;
            } else {
                newInterval.start = min(intervals[i].start, newInterval.start);
                newInterval.end = max(intervals[i].end, newInterval.end);
            }
        }
        res.push_back(newInterval);
        return res;
    }
};