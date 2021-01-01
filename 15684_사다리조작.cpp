#include <iostream>
#include <string.h>
using namespace std;

int n, m;
int result = 4;
bool map[30][10];

void input() {
	memset(map, false, sizeof(map));
	int k, y, x;
	cin >> m >> k >> n;

	for (int i = 0; i < k; i++) {
		cin >> y >> x;
		map[y - 1][x - 1] = true;
	}
}

bool check() {
	for (int x = 0; x < m; x++) {
		int start = x;

		for (int y = 0; y < n; y++) {
			if (map[y][start]) {
				start++;
			}
			else if (start > 0 && map[y][start - 1]) {
				start--;
			}
		}

		if (start != x) return false;
	}

	return true;
}

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n && x >= 0 && x < m) {
		return true;
	}

	return false;
}

void brouteForce(int y, int x, int count) {
	if (check()) {
		if (result > count) {
			result = count;
		}

		return;
	}

	if (count >= 3) {
		return;
	}

	for (int i = y; i < n; i++) {
		int j;
		if (i == y) j = x;
		else j = 0;

		for (; j < m; j++) {
			if (!map[i][j]) {
				if (exceptionHandling(i, j + 1) && map[i][j + 1]) continue;
				if (exceptionHandling(i, j - 1) && map[i][j - 1]) continue;

				map[i][j] = true;
				brouteForce(i, j, count + 1);
				map[i][j] = false;
			}
		}
	}
}

int main() {
	input();
	brouteForce(0, 0, 0);
	if (result == 4) result = -1;
	cout << result << endl;
}