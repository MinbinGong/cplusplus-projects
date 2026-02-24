/*
 * Cat and Mouse
 *
 * A game on an undirected graph is played by two players, Mouse and Cat, who alternate turns.
 * 
 * The graph is given as follows: graph[a] is a list of all nodes b such that ab is an edge of the graph.
 * 
 * Mouse starts at node 1 and goes first, Cat starts at node 2 and goes second, and there is a Hole at node 0.
 * 
 * During each player's turn, they must travel along one edge of the graph that meets where they are.  For example, if the Mouse is at node 1, it must travel to any node in graph[1].
 * 
 * Additionally, it is not allowed for the Cat to travel to the Hole (node 0.)
 * 
 * Then, the game can end in 3 ways:
 * 
 * If ever the Cat occupies the same node as the Mouse, the Cat wins.
 * If ever the Mouse reaches the Hole, the Mouse wins.
 * If ever a position is repeated (ie. the players are in the same position as a previous turn, and it is the same player's turn to move), the game is a draw.
 * 
 * Note:
 * 1 <= graph.length <= 50
 * 0 <= graph[i].length < graph.length
 * 0 <= graph[i][j] < graph.length
 * graph[i][j] != i
 * graph[i] is unique.
 * The mouse and the cat can always move. 
 * 
 */
#include <vector>
using namespace std;

class Solution1 {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        // dp[k][i][j] 表示走了k步，老鼠在i，猫在j时的游戏结果
        // 值：0-未知/平局，1-老鼠赢，2-猫赢
        vector<vector<vector<int>>> dp(2 * n, vector<vector<int>>(n, vector<int>(n, -1)));
        return dfs(graph, dp, 0, 1, 2);
    }

private:
    int dfs(vector<vector<int>>& graph, vector<vector<vector<int>>>& dp, int k, int i, int j) {
        if (k >= 2 * graph.size()) return 0;          // 超过最大步数，平局
        if (i == j) return 2;                          // 猫抓到老鼠
        if (i == 0) return 1;                          // 老鼠进洞
        if (dp[k][i][j] != -1) return dp[k][i][j];     // 记忆化

        int res = 0;
        if (k % 2 == 0) { // 老鼠回合
            bool draw = false;
            for (int next : graph[i]) {
                int t = dfs(graph, dp, k + 1, next, j);
                if (t == 1) return dp[k][i][j] = 1;     // 存在必胜走法
                if (t == 0) draw = true;
            }
            if (draw) res = 0;
            else res = 2;
        } else { // 猫回合
            bool draw = false;
            for (int next : graph[j]) {
                if (next == 0) continue;               // 猫不能进洞
                int t = dfs(graph, dp, k + 1, i, next);
                if (t == 2) return dp[k][i][j] = 2;     // 猫存在必胜走法
                if (t == 0) draw = true;
            }
            if (draw) res = 0;
            else res = 1;
        }
        return dp[k][i][j] = res;
    }
};

class Solution2 {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        const int DRAW = 0, MOUSE = 1, CAT = 2;

        // color[m][c][turn]：0-未知，1-鼠赢，2-猫赢
        vector<vector<vector<int>>> color(n, vector<vector<int>>(n, vector<int>(3, DRAW)));
        // degree[m][c][turn]：当前状态还有多少个子状态未确定
        vector<vector<vector<int>>> degree(n, vector<vector<int>>(n, vector<int>(3, 0)));

        // 初始化每个状态的度
        for (int m = 0; m < n; ++m) {
            for (int c = 0; c < n; ++c) {
                degree[m][c][1] = graph[m].size();                 // 老鼠回合，子状态数是老鼠的邻居数
                degree[m][c][2] = graph[c].size();                 // 猫回合，子状态数是猫的邻居数
                for (int x : graph[c]) {
                    if (x == 0) {                                  // 猫不能进洞，减掉这个子状态
                        degree[m][c][2]--;
                        break;
                    }
                }
            }
        }

        queue<tuple<int, int, int>> q; // (老鼠位置, 猫位置, 当前谁动)
        // 初始化已知结果的状态入队
        for (int i = 0; i < n; ++i) {
            for (int turn = 1; turn <= 2; ++turn) {
                // 老鼠进洞 -> 鼠赢
                color[0][i][turn] = MOUSE;
                q.emplace(0, i, turn);
                if (i > 0) {
                    // 猫鼠相遇 -> 猫赢
                    color[i][i][turn] = CAT;
                    q.emplace(i, i, turn);
                }
            }
        }

        // BFS 拓扑排序
        while (!q.empty()) {
            auto [m, c, turn] = q.front();
            q.pop();
            int res = color[m][c][turn]; // 当前已确定的结果

            // 获取父状态（上一轮是谁动）
            if (turn == 1) { // 当前是老鼠动，则父状态是猫动
                for (int prevC : graph[c]) {
                    if (prevC == 0) continue; // 猫不能从洞来
                    if (color[m][prevC][2] == DRAW) {
                        if (res == CAT) { // 猫可以在父状态直接获胜
                            color[m][prevC][2] = CAT;
                            q.emplace(m, prevC, 2);
                        } else { // 减少一个可能平局的子状态
                            degree[m][prevC][2]--;
                            if (degree[m][prevC][2] == 0) {
                                color[m][prevC][2] = MOUSE;
                                q.emplace(m, prevC, 2);
                            }
                        }
                    }
                }
            } else { // 当前是猫动，父状态是老鼠动
                for (int prevM : graph[m]) {
                    if (color[prevM][c][1] == DRAW) {
                        if (res == MOUSE) {
                            color[prevM][c][1] = MOUSE;
                            q.emplace(prevM, c, 1);
                        } else {
                            degree[prevM][c][1]--;
                            if (degree[prevM][c][1] == 0) {
                                color[prevM][c][1] = CAT;
                                q.emplace(prevM, c, 1);
                            }
                        }
                    }
                }
            }
        }

        return color[1][2][1]; // 初始状态：老鼠先动
    }
};