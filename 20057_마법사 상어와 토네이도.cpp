#include <iostream>
using namespace std;

int n;
int map[500][500];
int tmpMap[500][500];

int dy[] = { 0, 1, 0, -1 };
int dx[] = { -1, 0, 1, 0 };

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n&& x >= 0 && x < n) return true;

	return false;
}

int spreadSand(int y, int x) {
	int overSand = 0;
	int sum = 0;
	int select = map[y][x - 1];
	map[y][x - 1] = 0;

	if (exceptionHandling(y - 2, x - 1)) {
		map[y - 2][x - 1] += ((double)2 / (double)100) * select;
		sum += ((double)2 / (double)100) * select;
	}
	else {
		sum += ((double)2 / (double)100) * select;
		overSand += ((double)2 / (double)100) * select;
	}

	if (exceptionHandling(y - 1, x - 2)) {
		map[y - 1][x - 2] += ((double)10 / (double)100) * select;
		sum += ((double)10 / (double)100) * select;
	}
	else {
		sum += ((double)10 / (double)100) * select;
		overSand += ((double)10 / (double)100) * select;
	}

	if (exceptionHandling(y - 1, x - 1)) {
		map[y - 1][x - 1] += ((double)7 / (double)100) * select;
		sum += ((double)7 / (double)100) * select;
	}
	else {
		sum += ((double)7 / (double)100) * select;
		overSand += ((double)7 / (double)100) * select;
	}

	if (exceptionHandling(y - 1, x)) {
		map[y - 1][x] += ((double)1 / (double)100) * select;
		sum += ((double)1 / (double)100) * select;
	}
	else {
		sum += ((double)1 / (double)100) * select;
		overSand += ((double)1 / (double)100) * select;
	}


	/*-----------------*/

	if (exceptionHandling(y + 2, x - 1)) {
		map[y + 2][x - 1] += ((double)2 / (double)100) * select;
		sum += ((double)2 / (double)100) * select;
	}
	else {
		sum += ((double)2 / (double)100) * select;
		overSand += ((double)2 / (double)100) * select;
	}

	if (exceptionHandling(y + 1, x - 2)) {
		map[y + 1][x - 2] += ((double)10 / (double)100) * select;
		sum += ((double)10 / (double)100) * select;
	}
	else {
		sum += ((double)10 / (double)100) * select;
		overSand += ((double)10 / (double)100) * select;
	}

	if (exceptionHandling(y + 1, x - 1)) {
		map[y + 1][x - 1] += ((double)7 / (double)100) * select;
		sum += ((double)7 / (double)100) * select;
	}
	else {
		sum += ((double)7 / (double)100) * select;
		overSand += ((double)7 / (double)100) * select;
	}

	if (exceptionHandling(y + 1, x)) {
		map[y + 1][x] += ((double)1 / (double)100) * select;
		sum += ((double)1 / (double)100) * select;
	}
	else {
		sum += ((double)1 / (double)100) * select;
		overSand += ((double)1 / (double)100) * select;
	}

	if (exceptionHandling(y, x - 3)) {
		map[y][x - 3] += ((double)5 / (double)100) * select;
		sum += ((double)5 / (double)100) * select;
	}
	else {
		sum += ((double)5 / (double)100) * select;
		overSand += ((double)5 / (double)100) * select;
	}


	if (exceptionHandling(y, x - 2)) {
		map[y][x - 2] += select - sum;
	}
	else {
		overSand += select - sum;
	}

	return overSand;
}

void rotate() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmpMap[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[j][n - 1 - i] = tmpMap[i][j];
		}
	}
}

int solve() {
	int direction = 0;
	int length = 1;
	int y = n / 2;
	int x = n / 2;
	int tmp;
	int count = 0;
	int result = 0;

	while (true) {
		for (int i = 0; i < length; i++) {
			result += spreadSand(y, x);
			x--;
			count++;
			if (count == n * n - 1) {
				return result;
			}
		}

		tmp = y;
		y = x;
		x = n - 1 - tmp;
		rotate();

		for (int i = 0; i < length; i++) {
			result += spreadSand(y, x);
			x--;
			count++;
			if (count == n * n - 1) {
				return result;
			}
		}

		tmp = y;
		y = x;
		x = n - 1 - tmp;
		length++;
		rotate();
	}
}

void input() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

int main() {
	input();
	cout << solve() << endl;
}