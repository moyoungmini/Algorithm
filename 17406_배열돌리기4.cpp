#include <iostream>
#include <vector>
#include <string.h>
#include <limits.h>
using namespace std;

struct command {
	int x;
	int y;
	int length;
};
int n, m, c;
int value[50][50];
int tmpValue[50][50];
bool check[6];
vector<int> indexList;
vector<command> v;
int result = INT_MAX;
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << value[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void input() {
	int q, w, e;
	cin >> n >> m >> c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> value[i][j];
		}
	}

	for (int i = 0; i < c; i++) {
		cin >> q >> w >> e;
		command newCommand;
		newCommand.length = 2 * e + 1;
		newCommand.x = w - e - 1;
		newCommand.y = q - e - 1;
		v.push_back(newCommand);
	}
}

void calculate() {
	int tmpMin = INT_MAX;
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < m; j++) {
			sum += value[i][j];
		}
		if (tmpMin > sum) tmpMin = sum;
	}

	if (tmpMin < result) result = tmpMin;
}

void solve() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tmpValue[i][j] = value[i][j];
		}
	}

	for (int i = 0; i < c; i++) {
		int x, y, length;
		int minX, minY, maxX, maxY;

		for (int a = 0; a < v[indexList[i]].length / 2; a++) {
			x = v[indexList[i]].x + a;
			y = v[indexList[i]].y + a;
			length = v[indexList[i]].length - 2 * a;
			minX = x;
			minY = y;
			maxX = x + length - 1;
			maxY = y + length - 1;

			int change = value[y][x];
			int tmp;
			int direction = 0;

			while (direction < 4) {
				y += dy[direction];
				x += dx[direction];
				if (x >= minX && x <= maxX && y >= minY && y <= maxY) {
					tmp = value[y][x];
					value[y][x] = change;
					change = tmp;
				}
				else {
					x -= dx[direction];
					y -= dy[direction];
					direction++;
				}
			}
		}
	}

	calculate();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			value[i][j] = tmpValue[i][j];
		}
	}
}

void reculsive() {
	if (indexList.size() == c) {
		solve();
		return;
	}

	for (int i = 0; i < c; i++) {
		if (!check[i]) {
			check[i] = true;
			indexList.push_back(i);
			reculsive();
			check[i] = false;
			indexList.pop_back();
		}
	}
}

int main() {
	input();
	reculsive();

	cout << result << endl;
}