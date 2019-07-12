#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int MAX_SIZE = 20;

struct node {
  int p1R, p1C, p2R,
      p2C;         // p1R = Player1's row, p1C = Player1's column position
  int stepsTaken;  // The current number of steps we have taken to reach these
                   // positions
};

class PathFinding {
 private:
  bool visited[MAX_SIZE][MAX_SIZE][MAX_SIZE][MAX_SIZE];
  void markVisited(const node &v);
  const node findStartNode(const vector<string> &board);
  bool isInvalidPosition(const node &v, const vector<string> &board);
  bool reachedGoal(const node &top, const node &start);

 public:
  int minTurns(vector<string> board);
};

// returns true if the player's position is invalid i.e if a player is  out of
// bounds or in a 'X' cell
bool PathFinding::isInvalidPosition(const node &v,
                                    const vector<string> &board) {
  const int numRows = static_cast<int>(board.size());
  const int numColumns = static_cast<int>(board[0].size());

  if (v.p1R < 0 || v.p1R >= numRows || v.p1C < 0 || v.p1C >= numColumns ||
      v.p2R < 0 || v.p2R >= numRows || v.p2C < 0 || v.p2C >= numColumns ||
      (v.p1R == v.p2R &&
       v.p1C == v.p2C) ||  // p1 and p2 can't be on top of each other
      board[v.p1R][v.p1C] == 'X' ||
      board[v.p2R][v.p2C] == 'X')
    return true;
  return false;
}

bool PathFinding::reachedGoal(const node &top, const node &start) {
  if (top.p1R == start.p2R && top.p1C == start.p2C && top.p2R == start.p1R &&
      top.p2C == start.p1C)
    return true;
  return false;
}

void PathFinding::markVisited(const node &v) {
  if (visited[v.p1R][v.p1C][v.p2R][v.p2C]) return;
  visited[v.p1R][v.p1C][v.p2R][v.p2C] = true;
}

const node PathFinding::findStartNode(const vector<string> &board) {
  node start;
  int rows = static_cast<int>(board.size());
  int columns = static_cast<int>(board[0].size());

  int p1r = -1, p1c = -1, p2r = -1, p2c = -1;
  for (int row = 0; row < rows; row++)
    for (int column = 0; column < columns; column++) {
      if (board[row][column] == 'A') {
        p1r = row;
        p1c = column;
      }
      if (board[row][column] == 'B') {
        p2r = row;
        p2c = column;
      }
    }
  start.p1R = p1r;
  start.p1C = p1c;
  start.p2R = p2r;
  start.p2C = p2c;
  start.stepsTaken = 0;
  return start;
}

int PathFinding::minTurns(vector<string> board) {
  memset(visited, 0, sizeof(visited));
  node start = findStartNode(board);
  queue<node> q;
  q.push(start);
  //   pushToQueueAndMarkVisited(q, start);

  while (q.empty() == false) {
    node top = q.front();
    q.pop();
    // Check if the current positions of A and B are the opposite of what they
    // were in start. If they are we have exchanged positions and are finished!
    if (reachedGoal(top, start)) return top.stepsTaken;
    // Check if player 1 or player 2 is out of bounds, or on an X square,
    // if so continue Check if player 1 or player 2 is on top ofeach
    // other, if so continue
    if (isInvalidPosition(top, board)) continue;
    // if this node is already visited continue
    if (visited[top.p1R][top.p1C][top.p2R][top.p2C]) continue;
    markVisited(top);
    // Now we need to generate all of the transitions between nodes, we can do
    // this quite easily using some nested for loops, one for each direction
    // that it is possible for one player to move. Since we need to generate the
    // following deltas: (-1,-1), (-1,0), (-1,1), (0,-1), (0,0), (0,1), (1,-1),
    // (1,0), (1,1) we can use a for loop from -1 to 1 to do exactly that.
    for (int p1dr = -1; p1dr <= 1; p1dr++)
      for (int p1dc = -1; p1dc <= 1; p1dc++)
        for (int p2dr = -1; p2dr <= 1; p2dr++)
          for (int p2dc = -1; p2dc <= 1; p2dc++) {
            // Careful though! We have to make sure that player 1 and 2 did not
            // swap positions on this turn
            if (top.p1R == top.p2R + p2dr && top.p1C == top.p2C + p2dc &&
                top.p2R == top.p1R + p1dr && top.p2C == top.p1C + p1dc)
              continue;
            node n;
            n.p1R = top.p1R + p1dr;
            n.p1C = top.p1C + p1dc;
            n.p2R = top.p2R + p2dr;
            n.p2C = top.p2C + p2dc;
            n.stepsTaken = top.stepsTaken + 1;
            q.push(n);
          }
  }
  return -1;
}
