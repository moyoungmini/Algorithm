#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <math.h>
using namespace std;

class Cordinate {
public:
	int y;
	int x;
public:
	Cordinate(int y, int x) {
		this->y = y;
		this->x = x;
	}
};

int n, l, r;
int map[50][50];
bool check[50][50];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
vector<Cordinate> v;

void print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void input() {
	cin >> n >> l >> r;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n && x >= 0 && x < n) return true;

	return false;
}

void bfs(int y, int x) {
	queue<Cordinate> q;
	Cordinate init(y, x);
	check[y][x] = true;
	v.push_back(init);
	q.push(init);

	while (!q.empty()) {
		Cordinate front = q.front();	q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = front.y + dy[i];
			int nx = front.x + dx[i];

			if (exceptionHandling(ny, nx) && !check[ny][nx] && abs(map[front.y][front.x] - map[ny][nx]) >= l && abs(map[front.y][front.x] - map[ny][nx]) <= r) {
				check[ny][nx] = true;
				Cordinate newValue(ny, nx);
				q.push(newValue);
				v.push_back(newValue);
			}
		}
	}
}

void combine() {
	int sum = 0;

	int count = v.size();
	for (int i = 0; i < count; i++) {
		sum += map[v[i].y][v[i].x];
	}

	for (int i = 0; i < count; i++) {
		map[v[i].y][v[i].x] = sum / count;
	}
}

int solve() {
	for (int t = 0;; t++) {
		memset(check, false, sizeof(check));
		bool flag = false;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!check[i][j]) {
					bfs(i, j);
					combine();
					if (v.size() != 1) flag = true;
					v.clear();
				}
			}
		}

		if (!flag) return t;
	}
}

int main() {
	input();
	cout << solve() << endl;
}