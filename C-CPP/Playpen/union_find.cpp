#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
 };


class Solution {
public:
    /**
     * @param n an integer
     * @param m an integer
     * @param operators an array of point
     * @return an integer array
     */
    
    class UnionFind {
    private:
        unordered_map<int, int> father;
    public:
        UnionFind(int n, int m) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    int id = converttoId(i, j, m);
                    father[id] = id;
                }
            }
        }
        
        int find (int x) {
            int parent = father[x];
            while(parent != father[parent]) {
                parent = father[parent];
            }
            return parent;
        }
        
        int compress_find(int x) {
            int parent = father[x];
            while(parent != father[parent]) {
                parent = father[parent];
            }
            
            int tmp = -1;
            int fa = father[x];
            while(fa != father[fa]) {
                tmp = father[fa];
                father[fa] = parent;
                fa = tmp;
            }
            return parent;
        }
        
        void unions(int x, int y) {
            int fa_x = find(x);
            int fa_y = find(y);
            if (fa_x != fa_y) {
                father[fa_x] = fa_y;
            }
        }
    };
    
    static int converttoId(int x, int y, int m) {
        return x * m + y;
    }
    
    vector<int> numIslands2(int n, int m, vector<Point>& operators) {
        // Write your code here
        int dx[] = {0, -1, 0, 1};
        int dy[] = {1, 0, -1, 0};
        
        vector<vector<int>> island(n, vector<int>(m, 0));
        vector<int> res;
        UnionFind uf(n, m);
        int count = 0;
        if (!operators.empty()) {
            for (int i = 0; i < operators.size(); i++) {
                count++;
                int x = operators[i].x;
                int y = operators[i].y;
                if (island[x][y] != 1) {
                    island[x][y] = 1;
                    int id = converttoId(x, y, m);
                    for (int j = 0; j < 4; j++) {
                        int nx = x + dx[j];
                        int ny = y + dy[j];
                        if (0 <= nx && nx < n && 0 <= ny && ny < m && island[nx][ny] == 1) {
                            int nid = converttoId(nx, ny, m);
                            
                            int fa = uf.find(id);
                            int nfa = uf.find(nid);
                            if (fa != nfa) {
                                count--;
                                uf.unions(id, nid);
                            }
                        }
                    }
                }
                res.push_back(count);
            }
        }
        return res;
    }
};


int main() {
    Solution sol;
    std::cout << "done!" << std::endl;
    
}
