#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Command {
	int index;
	int direction;
};

const int gearCount = 4;
int gear[gearCount][8];

int calculate() {
	int sum = 0;
	if (gear[0][0] == 1) sum += 1;
	if (gear[1][0] == 1) sum += 2;
	if (gear[2][0] == 1) sum += 4;
	if (gear[3][0] == 1) sum += 8;

	return sum;
}

void rotate(int num, int direction) {
	int tmp[8];
	for (int i = 0; i < 8; i++) {
		tmp[i] = gear[num][i];
	}

	int index;
	if (direction == 1) index = 7;
	else index = 1;

	for (int i = 0; i < 8; i++) {
		gear[num][i] = tmp[index];
		index = (index + 1) % 8;
	}
}

void solve(int num, int direction) {
	vector<Command> com;
	Command init;
	init.index = num;
	init.direction = direction;
	com.push_back(init);

	int nowDirection = direction;
	for (int distance = 1;; distance++) {
		if (num - distance >= 0 && gear[num - distance][2] != gear[num - distance + 1][6]) {
			Command newValue;
			newValue.index = num - distance;
			if (nowDirection == 1) {
				newValue.direction = -1;
				nowDirection = -1;
			}
			else {
				newValue.direction = 1;
				nowDirection = 1;
			}
			com.push_back(newValue);
		}
		else {
			break;
		}
	}

	nowDirection = direction;
	for (int distance = 1;; distance++) {
		if (num + distance < gearCount &&  gear[num + distance - 1][2] != gear[num + distance][6]) {
			Command newValue;
			newValue.index = num + distance;
			if (nowDirection == 1) {
				newValue.direction = -1;
				nowDirection = -1;
			}
			else {
				newValue.direction = 1;
				nowDirection = 1;
			}
			com.push_back(newValue);
		}
		else {
			break;
		}
	}

	for (int i = 0; i < com.size(); i++) {
		rotate(com[i].index, com[i].direction);
	}
}

void input() {
	string strInput;
	for (int i = 0; i < gearCount; i++) {
		cin >> strInput;
		for (int j = 0; j < 8; j++) {
			gear[i][j] = strInput[j] - '0';
		}
	}
}

int main() {
	input();

	int n, num, direction;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num >> direction;

		solve(num - 1, direction);
	}

	cout << calculate() << endl;
}