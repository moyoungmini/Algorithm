#include <iostream>
using namespace std;

int n;
int t[15];
int p[15];
int result = 0;

void brouteForce(int date, int sum) {
	if (date == n) {
		if (result < sum) {
			result = sum;
		}
		return;
	}

	if (date + t[date] <= n) {
		brouteForce(date + t[date], sum + p[date]);
	}

	brouteForce(date + 1, sum);
}

int main() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> t[i] >> p[i];
	}

	brouteForce(0, 0);
	cout << result << endl;
}