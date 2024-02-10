int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int d[n][m][1 << 6];
        memset(d, -1, sizeof(d));
        queue<tuple<int, int, int>> q;
        int k = 0;  // num of keys

        // find the starting point
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '@') {
                    q.push({i, j, 0});
                    d[i][j][0] = 0;
                }
                if (grid[i][j] >= 'a' && grid[i][j] <= 'z') {
                    k++;
                }
            }
        }


        // bfs
        while (!q.empty()) {
            // (x, y) with key state and steps
            int x, y, state, step;
            tie(x, y, state) = q.front();
            q.pop();
            step = d[x][y][state];

            if (state == (1 << k) - 1) {
                return step;
            }
            // cout << x << " " << y << " " << state << " " << step << endl;

            for (int i = 0; i < 4; i++) {
                int xx = x + dx[i];
                int yy = y + dy[i];
                int ss = state;
                if (xx < 0 || yy < 0 || xx >= n || yy >= m) continue;
                if (grid[xx][yy] == '#') continue;
                // empty cell
                if (grid[xx][yy] == '.' || grid[xx][yy] == '@') {
                    if (d[xx][yy][ss] == -1) {
                        d[xx][yy][ss] = step + 1;
                        q.push({xx, yy, ss});
                    }
                }
                // key
                else if (grid[xx][yy] >= 'a' && grid[xx][yy] <= 'z') {
                    ss |= (1 << (grid[xx][yy] - 'a'));
                    if (d[xx][yy][ss] == -1) {
                        d[xx][yy][ss] = step + 1;
                        q.push({xx, yy, ss});
                    }
                }
                // lock
                else { 
                    int x = grid[xx][yy] - 'A';
                    if (ss & (1 << x)) {
                        if (d[xx][yy][ss] == -1) {
                            d[xx][yy][ss] = step + 1;
                            q.push({xx, yy, ss});
                        }
                    }
                }
            }
        }
        return -1;
    }
};