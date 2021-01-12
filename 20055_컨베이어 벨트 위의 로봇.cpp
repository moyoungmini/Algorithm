#include <iostream>
#include <string.h>
using namespace std;

int n, k;
int rail[2001];
bool check[2001];

int solve() {
	int start = 0;
	int end = n - 1;
	int zeroCount = 0;
	int step = 1;
	bool flag;
	int index;
	memset(check, false, sizeof(check));

	while (true) {
		index = end;
		flag = false;

		start = (start - 1 + 2 * n) % (2 * n);
		end = (end - 1 + 2 * n) % (2 * n);

		if (check[end]) {
			check[end] = false;
		}
		// È¸Àü

		index = end;
		flag = false;
		while (true) {
			if (index == start) flag = true;

			if (check[index]) {
				int next = (index + 1) % (2 * n);

				if (!check[next] && rail[next] > 0) {
					check[index] = false;
					check[next] = true;
					rail[next]--;

					if (rail[next] == 0) zeroCount++;
					if (zeroCount == k) return step;

					if (next == end) check[next] = false;
				}
			}

			index = (2 * n + index - 1) % (2 * n);
			if (flag) break;
		}
		// ·Îº¿ ÀÌµ¿

		if (!check[start] && rail[start] > 0) {
			check[start] = true;
			rail[start]--;
			if (rail[start] == 0) zeroCount++;
			if (zeroCount == k) return step;
		}
		// ·Îº¿ 0ÀÎµ¦½º¿¡ ¿Ã¸°´Ù

		step++;
	}
}

int main() {
	cin >> n >> k;
	for (int i = 0; i < 2 * n; i++) {
		cin >> rail[i];
	}

	cout << solve() << endl;
}