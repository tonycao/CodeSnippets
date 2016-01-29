class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        int len = prerequisites.size();
        if (len == 0) return true;
        
        vector<vector<int>> graph(numCourses, vector<int>());
        for (int i = 0; i < len; i++) {
            graph[prerequisites[i].second].push_back(prerequisites[i].first);
        }
        
        vector<bool> visit(numCourses, false);
        //memset(visit, 0, numCourses * sizeof(bool));
        vector<bool> path(numCourses, false);
        //memset(mark, 0, numCourses * sizeof(bool));
        
        for (int i = 0; i < numCourses; i++) {
            //if (visit[i]) return false;
            if (DFSHasCircle(graph, visit, path, i)) {
                return false;
            }
        }
        return true;
    }
    
    bool DFSHasCircle(vector<vector<int>>& graph, vector<bool>& visit, vector<bool>& path, int current) {
        if (visit[current]) return true;
        if (path[current]) return false;
        visit[current] = true;
        
        for (int i = 0; i < graph[current].size(); i++) {
            if (DFSHasCircle(graph, visit, path, graph[current][i])) return true;
        }
        
        path[current] = true;
        visit[current] = false;
        return false;
    }
};