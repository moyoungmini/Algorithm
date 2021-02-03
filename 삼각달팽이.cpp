#include <string>
#include <vector>
#include <string.h>
using namespace std;

struct node {
	int y;
	int x;
};

int dy[] = { 1, 0, -1 };
int dx[] = { 0, 1, -1 };
int map[1000][1000];

bool exceptionCheck(int y, int x, int n) {
	if (y >= 0 && y < n && x >= 0 && x < n && y >= x) return true;

	return false;
}


vector<int> solution(int n) {
	vector<int> answer;

	int y = 0;
	int x = 0;
	int direction = 0;
	int number = 1;
	memset(map, -1, sizeof(map));
	map[0][0] = number;

	while (true) {
		if (number == n * (n + 1) / 2) break;
		number++;
		y += dy[direction];
		x += dx[direction];

		if (exceptionCheck(y, x, n) && map[y][x] == -1) {
			map[y][x] = number;
		}
		else {
			y -= dy[direction];
			x -= dx[direction];
			number--;
			direction = (direction + 1) % 3;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			answer.push_back(map[i][j]);
		}
	}

	return answer;
}