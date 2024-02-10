class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        sort(target.begin(), target.end());
        for (auto& s : stickers) {
            sort(s.begin(), s.end());
        }
        queue<int> q;
        vector<int> d(1 << target.size(), -1);
        q.push(0);
        d[0] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto& s : stickers) {
                int y = x;
                int p1 = 0, p2 = 0;
                int n1 = target.size(), n2 = s.size();
                while (p1 < n1 && p2 < n2) {
                    if ((x >> p1) & 1) {
                        p1++;
                        continue;
                    }
                    if (target[p1] == s[p2]) {
                        y |= 1 << p1;
                        p1++;
                        p2++;
                    }
                    else if (target[p1] < s[p2])
                        p1++;
                    else p2++;
                }
                if (d[y] == -1) {
                    d[y] = d[x] + 1;
                    q.push(y);
                    if (y == (1 << target.size()) - 1) {
                        return d[y];
                    }
                }
            }
        }
        return -1;
    }
};