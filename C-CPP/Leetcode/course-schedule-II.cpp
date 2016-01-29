class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        int len = prerequisites.size();
        vector<int> order;
        
        if(prerequisites.empty()) {
            for (int i = 0; i < numCourses; i++) {
                order.push_back(i);
            }
            return order;
        }
        vector<bool> visited(numCourses, false);
        vector<bool> mark(numCourses, false);
        
        vector<vector<int>> graph(numCourses, vector<int>());
        for(int i = 0; i < len; i++) {
            graph[prerequisites[i].first].push_back(prerequisites[i].second);
        }
        
        for (int i = 0; i < numCourses; i++) {
            if (visited[i]) continue;
            if (DFSHasCircle(graph, visited, mark, i, order)) return vector<int>();
        }
        return order;
    }
    
    bool DFSHasCircle(vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& mark, int current, vector<int>& order) {       
        if (visited[current]) return true;
        if (mark[current]) return false;
        //mark[current] = false;
        visited[current] = true;
        
        for (auto it = graph[current].begin(); it != graph[current].end(); it++) {
            if (!visited[*it])
                if (DFSHasCircle(graph, visited, mark, *it, order)) return true;
            if (!mark[*it]) return true;
        }
        mark[current] = true;
        //visited[current] = false;
        order.push_back(current);
        return false;
    }
};