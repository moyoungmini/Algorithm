	
#include <iostream>
#include <string.h>
#include <limits.h>
using namespace std;

int n;
int map[21][21];

int calculate(int value[5]) {
	int max = value[0];
	int min = value[0];

	for (int i = 1; i < 5; i++) {
		if (max < value[i]) max = value[i];
		if (min > value[i]) min = value[i];
	}

	return max - min;
}

int solve(int x, int y, int d1, int d2) {
	bool check[21][21];
	memset(check, false, sizeof(check));

	for (int i = 0; i <= d1; i++) check[x + i][y - i] = true;
	for (int i = 0; i <= d2; i++) check[x + i][y + i] = true;
	for (int i = 0; i <= d2; i++) check[x + d1 + i][y - d1 + i] = true;
	for (int i = 0; i <= d1; i++) check[x + d2 + i][y + d2 - i] = true;

	int value[5] = { 0, 0, 0, 0, 0 };

	for (int r = 1; r < x + d1; r++) {
		for (int c = 1; c <= y; c++) {
			if (check[r][c]) break;

			value[0] += map[r][c];
		}
	}
	for (int r = 1; r <= x + d2; r++) {
		for (int c = n; c >= y + 1; c--) {
			if (check[r][c]) break;

			value[1] += map[r][c];
			check[r][c] = true;
		}
	}
	for (int r = x + d1; r <= n; r++) {
		for (int c = 1; c < y - d1 + d2; c++) {
			if (check[r][c]) break;

			value[2] += map[r][c];
			check[r][c] = true;
		}
	}
	for (int r = x + d2 + 1; r <= n; r++) {
		for (int c = n; c >= y - d1 + d2; c--) {
			if (check[r][c]) break;

			value[3] += map[r][c];
			check[r][c] = true;
		}
	}

	int sum = 0;
	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= n; c++) {
			sum += map[r][c];
		}
	}
	value[4] = sum - (value[0] + value[1] + value[2] + value[3]);

	return calculate(value);
}

int main() {
	cin >> n;
	int result = INT_MAX;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n; y++) {

			for (int d1 = 1; d1 <= n; d1++) {
				for (int d2 = 1; d2 <= n; d2++) {
					if (x + d1 + d2 > n)	continue;
					if (y - d1 < 1)			continue;
					if (y + d2 > n)			continue;

					int value = solve(x, y, d1, d2);

					if (result > value) result = value;
				}
			}
		}
	}


	cout << result << endl;
}