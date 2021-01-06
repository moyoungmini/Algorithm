#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;

class Node {
public:
	int y;
	int x;
	int length;
	int count;
public:
	Node(int y, int x, int length) {
		this->y = y;
		this->x = x;
		this->length = length;
		this->count = 0;
	}
	Node() {}
};

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int n;
int map[20][20];
Node shark;

void input() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				shark.y = i;
				shark.x = j;
				shark.length = 2;
				map[i][j] = 0;
			}
		}
	}
}

int bfs() {
	int check[20][20];
	queue<Node> q;
	q.push(shark);
	memset(check, -1, sizeof(check));
	check[shark.y][shark.x] = 0;

	while (!q.empty()) {
		Node front = q.front();	q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = front.y + dy[i];
			int nx = front.x + dx[i];

			if (ny >= 0 && ny < n && nx >= 0 && nx < n) {
				if (map[ny][nx] <= front.length && check[ny][nx] == -1) {
					Node newNode(ny, nx, front.length);
					q.push(newNode);
					check[ny][nx] = check[front.y][front.x] + 1;
				}
			}
		}
	}

	int y, x, distance;
	distance = n * n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (check[i][j] != -1 && map[i][j] >=1 && map[i][j]<=6 && shark.length > map[i][j]) {
				bool flag = false;
				if (distance > check[i][j]) {
					flag = true;
				}
				else if (distance == check[i][j]) {
					if (y > i) flag = true;
					else if (y == i) {
						if (x > j) flag = true;
					}
				}

				if (flag) {
					distance = check[i][j];
					y = i;
					x = j;
				}
			}
		}
	}

	if (distance == n * n) return -1;

	shark.y = y;
	shark.x = x;
	shark.count++;
	map[y][x] = 0;
	if (shark.count == shark.length) {
		shark.length++;
		shark.count = 0;
	}

	return distance;
}

int solve() {
	int time = 0;
	while(true) {
		int value = bfs();
		if (value == -1) return time;

		time += value;
	}
}

int main() {
	input();
	cout << solve() << endl;
}