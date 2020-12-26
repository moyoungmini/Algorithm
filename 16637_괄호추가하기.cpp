#include <iostream>
#include <string>
#include <limits.h>
using namespace std;

int n;
int result = INT_MIN;
string input;

void init() {
	cin >> n >> input;
	input = "0+" + input;
	n += 2;
}

int calculate(int n1, int n2, char oper) {
	if (oper == '+') {
		return n1 + n2;
	}
	else if (oper == '-') {
		return n1 - n2;
	}
	else if (oper == '*') {
		return n1 * n2;
	}
}

void solution(int index, int number) {
	if (index >= n) {
		if (result < number) {
			result = number;
		}

		return;
	}

	solution(index + 2, calculate(number, input[index] - '0', input[index - 1]));

	if (index + 2 < n) {
		int tmp = calculate(input[index] - '0', input[index + 2] - '0', input[index + 1]);
		solution(index + 4, calculate(number, tmp, input[index - 1]));
	}
}

int main() {
	init();
	solution(2, 0);
	cout << result << endl;
}