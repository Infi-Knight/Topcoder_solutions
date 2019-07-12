#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

const int ROWS = 400;
const int COLUMNS = 600;
bool visited[400][600] = {false};

class grafixMask {
 public:
  vector<int> result;

  vector<int> sortedAreas(vector<string> rectangles) {
    for (auto rec : rectangles) {
      istringstream ss(rec);
      int r1, c1, r2, c2;
      ss >> r1 >> c1 >> r2 >> c2;
      for (int i = r1; i <= r2; i++)
        for (int j = c1; j <= c2; j++) {
          visited[i][j] = true;
        }
    }

    for (int row = 0; row < ROWS; row++)
      for (int column = 0; column < COLUMNS; column++)
        if (!visited[row][column]) {
          result.push_back(doFill(row, column));
        }

    sort(result.begin(), result.end());
    return result;
  }

  int doFill(int row, int column) {
    int res = 0;
    stack<pair<int, int> > s;
    s.push(make_pair(row, column));

    while (s.empty() == false) {
      pair<int, int> p = s.top();
      int r = p.first;
      int c = p.second;
      s.pop();

      if (r < 0 || r >= 400 || c < 0 || c >= 600 || visited[r][c]) continue;

      visited[r][c] = true;
      res++;

      int dirRow[] = {1, -1, 0, 0};
      int dirCol[] = {0, 0, 1, -1};

      for (int i = 0; i < 4; i++) {
        int newRow = r + dirRow[i];
        int newCol = c + dirCol[i];
        if (newRow >= 0 && newRow < 400 && newCol >= 0 && newCol < 600 &&
            !visited[newRow][newCol]) {
          s.push(make_pair(newRow, newCol));
        }
      }
    }
    return res;
  }
};
