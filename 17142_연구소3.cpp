#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <string.h>
using namespace std;

class cordinate {
public:
	int x;
	int y;
public:
	cordinate(int y, int x) {
		this->y = y;
		this->x = x;
	}
};

int n, m;
int map[50][50];
int check[50][50];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int result = INT_MAX;
vector<int> indexList;
vector<cordinate> virusList;

void input() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];

			if (map[i][j] == 2) {
				cordinate init(i, j);
				virusList.push_back(init);
			}
		}
	}
}

bool checkException(int y, int x) {
	if (x >= 0 && x < n && y >= 0 && y < n) return true;

	return false;
}

int solveTime() {
	int value = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 0 && check[i][j] == -1) {
				return -1;
			}
			else if (map[i][j] == 0 && check[i][j] != -1) {
				if (value < check[i][j]) {
					value = check[i][j];
				}
			}
		}
	}
	return value;
}

void solve() {
	memset(check, -1, sizeof(check));
	queue<cordinate> q;

	for (int i = 0; i < m; i++) {
		q.push(virusList[indexList[i]]);
		check[virusList[indexList[i]].y][virusList[indexList[i]].x] = 0;
	}

	while (!q.empty()) {
		cordinate front = q.front();	q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = front.y + dy[i];
			int nx = front.x + dx[i];

			if (checkException(ny, nx) && map[ny][nx] != 1 && check[ny][nx] == -1) {
				cordinate newValue(ny, nx);
				check[ny][nx] = check[front.y][front.x] + 1;
				q.push(newValue);
			}
		}
	}

	int value = solveTime();
	if (value != -1 && value < result) {
		result = value;
	}
}

void brouteForce(int index) {
	if (indexList.size() == m) {
		solve();
		return;
	}

	if (index == virusList.size()) {
		return;
	}

	indexList.push_back(index);
	brouteForce(index + 1);
	indexList.pop_back();

	brouteForce(index + 1);
}

int main() {
	input();
	brouteForce(0);
	if (result == INT_MAX) result = -1;
	cout << result << endl;
}