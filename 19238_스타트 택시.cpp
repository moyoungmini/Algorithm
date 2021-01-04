#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

struct Cordinate {
	int y;
	int x;
};

struct Host {
	Cordinate start;
	Cordinate end;
};

struct Taxi {
	Cordinate position;
	int fuel;
};

int n, m;
int map[20][20];
int check[20][20];
Taxi taxi;
vector<Host> hostList;
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void input() {
	int k;
	int startY, startX, endY, endX;

	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];

			if (map[i][j] == 0) map[i][j] = -1;
			else if (map[i][j] == 1) map[i][j] = -2;
		}
	}

	cin >> startY >> startX;
	taxi.position.y = startY - 1;
	taxi.position.x = startX - 1;
	taxi.fuel = k;

	for (int i = 0; i < m; i++) {
		cin >> startY >> startX >> endY >> endX;
		Host host;
		host.start.y = startY - 1;	host.start.x = startX - 1;
		host.end.y = endY - 1;	host.end.x = endX - 1;
		hostList.push_back(host);
		map[startY - 1][startX - 1] = i;
	}
}

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n &&x >= 0 && x < n) return true;

	return false;
}

void bfs() {
	queue<Cordinate> q;
	Cordinate init;
	init.y = taxi.position.y;
	init.x = taxi.position.x;
	q.push(init);
	memset(check, -1, sizeof(check));
	check[init.y][init.x] = 0;

	while (!q.empty()) {
		Cordinate front = q.front();	q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = front.y + dy[i];
			int nx = front.x + dx[i];

			if (exceptionHandling(ny, nx) && map[ny][nx] != -2 && check[ny][nx] == -1) {
				Cordinate newValue;
				newValue.y = ny;
				newValue.x = nx;
				check[ny][nx] = check[front.y][front.x] + 1;
				q.push(newValue);
			}
		}
	}
}

int moveToHost() {
	bfs();

	int distance = n * n;
	int y, x;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] != -1 && map[i][j] != -2 && check[i][j] != -1) {
				bool flag = false;
				if (distance > check[i][j]) {
					flag = true;
				}
				else if (distance == check[i][j]) {
					if (y > i) {
						flag = true;
					}
					else if (y == i && x > j) {
						flag = true;
					}
				}

				if (flag) {
					distance = check[i][j];
					y = i;	x = j;
				}
			}
		}
	}

	if (distance == n * n || taxi.fuel <= distance) {
		return -1;
	}

	int returnValue = map[y][x];
	map[y][x] = -1;
	taxi.position.y = y;
	taxi.position.x = x;
	taxi.fuel -= distance;

	return returnValue;
}

bool moveDestination(int index) {
	bfs();
	int distance = check[hostList[index].end.y][hostList[index].end.x];
	if (distance == -1 || taxi.fuel < distance) return false;

	taxi.fuel += distance;
	taxi.position.y = hostList[index].end.y;
	taxi.position.x = hostList[index].end.x;

	return true;
}


bool solve() {
	for (int i = 0; i < m; i++) {
		int index = moveToHost();
		if (index == -1) return false;
		if (!moveDestination(index)) return false;
	}

	return true;
}

int main() {
	input();

	if (solve()) cout << taxi.fuel << endl;
	else cout << -1 << endl;
}