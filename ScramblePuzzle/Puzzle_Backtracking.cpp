#include <iostream>
#include <vector>

using namespace std;

// Piece 구조체 정의, 각 조각은 id, rotation 그리고 가장자리에 대한 정보를 가집니다.
struct Piece {
    int id;
    int rotation;
    vector<int> edges;
};

// 두 가장자리가 일치하는지 확인하는 함수
bool match(int a, int b) {
    return ((a == 1 && b == 2) || (a == 2 && b == 1) || 
            (a == 3 && b == 4) || (a == 4 && b == 3) ||
            (a == 5 && b == 6) || (a == 6 && b == 5) ||
            (a == 7 && b == 8) || (a == 8 && b == 7));
}

// 조각을 회전하는 함수
void rotate(Piece& p) {
    p.rotation = (p.rotation + 1) % 4;
    rotate(p.edges.begin(), p.edges.begin() + 1, p.edges.end());
}

// 3x3 그리드를 초기화
vector<vector<Piece>> grid(3, vector<Piece>(3));
vector<Piece> piece(9);
vector<bool> used(9, false);

int solutionsCount = 0;
vector<vector<vector<Piece>>> solutions;

// 백트래킹을 사용하여 가능한 모든 솔루션을 찾는 함수
void backtrack(int row, int col) {
    if (row == 3) {
        ++solutionsCount;
        solutions.push_back(grid);
    } else if (col == 3) {
        backtrack(row + 1, 0);
    } else {
        for (int i = 0; i < 9; ++i) {
            if (!used[i]) {
                for (int j = 0; j < 4; ++j) {
                    if ((row == 0 || match(grid[row - 1][col].edges[2], piece[i].edges[0])) &&
                        (col == 0 || match(grid[row][col - 1].edges[1], piece[i].edges[3]))) {
                        grid[row][col] = piece[i];
                        used[i] = true;
                        backtrack(row, col + 1);
                        used[i] = false;
                    }
                    rotate(piece[i]);
                }
            }
        }
    }
}

int main() { // 사용자로부터 조각에 대한 입력을 받음
    for (int i = 0; i < 9; ++i) {
        piece[i].id = i + 1;
        piece[i].rotation = 0;
        piece[i].edges.resize(4);
        for (int j = 0; j < 4; ++j) {
            cin >> piece[i].edges[j];
        }
    }

    backtrack(0, 0);
    cout << solutionsCount << "\n";

    for (const auto& solution : solutions) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << solution[i][j].id << "(" << solution[i][j].rotation << ") ";
            }
        }
        cout << "\n";
    }

    return 0;
}
