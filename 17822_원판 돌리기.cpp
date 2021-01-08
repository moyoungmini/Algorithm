#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int n, m;
int board[50][50];

void rotate(int index, int count) {
	int tmp[50];
	for (int i = 0; i < m; i++) {
		tmp[i] = board[index][i];
	}

	int start = m - count;

	for (int i = 0; i < m; i++) {
		board[index][i] = tmp[start];
		start++;
		if (start == m)start = 0;
	}
}

void reArrange() {
	bool eraseBoard[50][50];
	double average = 0;
	int count = 0;

	memset(eraseBoard, false, sizeof(eraseBoard));

	bool flag = false;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == 0) continue;

			average += board[i][j];
			count++;

			int left = j - 1;
			int right = j + 1;
			int up = i - 1;
			int down = i + 1;

			if (left == -1) left = m - 1;
			if (right == m) right = 0;

			if (board[i][j] == board[i][left]) {
				eraseBoard[i][j] = true;
				eraseBoard[i][left] = true;
				flag = true;
			}

			if (board[i][j] == board[i][right]) {
				eraseBoard[i][j] = true;
				eraseBoard[i][right] = true;
				flag = true;
			}

			if (up >= 0 && board[i][j] == board[up][j]) {
				eraseBoard[i][j] = true;
				eraseBoard[up][j] = true;
				flag = true;
			}

			if (down < m && board[i][j] == board[down][j]) {
				eraseBoard[i][j] = true;
				eraseBoard[down][j] = true;
				flag = true;
			}
		}
	}

	if (flag) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (eraseBoard[i][j]) {
					board[i][j] = 0;
				}
			}
		}
	}
	else {
		average /= (double)count;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (board[i][j] != 0) {
					if (board[i][j] > average) {
						board[i][j]--;
					}
					else if (board[i][j] < average) {
						board[i][j]++;
					}
				}
			}
		}
	}
}

void solve() {
	int t;
	cin >> n >> m >> t;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}

	int a, b, c;
	for (int i = 0; i < t; i++) {
		cin >> a >> b >> c;
		if (b == 1) c = m - c;

		for (int j = a; j <= n; j += a) {
			rotate(j - 1, c);
		}
		reArrange();
	}

}

int calculate() {
	int sum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] != 0) sum += board[i][j];
		}
	}

	return sum;
}

int main() {
	solve();
	cout << calculate() << endl;
}