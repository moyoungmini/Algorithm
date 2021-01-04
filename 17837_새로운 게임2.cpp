#include <iostream>
#include <vector>
using namespace std;

class Cordinate {
public:
	int y;
	int x;
	int direction;
public:
	Cordinate(int y, int x, int direction) {
		this->y = y;
		this->x = x;
		this->direction = direction;
	}
	Cordinate() {}
};

int n, k;
vector<int> horseMap[12][12];
int inputMap[12][12];
vector<Cordinate> horseList;
int dy[] = { 0, 0, -1, 1 };
int dx[] = { 1, -1, 0, 0 };

void input() {
	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> inputMap[i][j];
		}
	}

	int y, x, d;
	for (int i = 0; i < k; i++) {
		cin >> y >> x >> d;

		Cordinate init(y - 1, x - 1, d - 1);
		horseList.push_back(init);
		horseMap[y - 1][x - 1].push_back(i);
	}
}

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n && x >= 0 && x < n) return true;

	return false;
}

int moveWhite(int y, int x, int ny, int nx, int index) {
	vector<int> stopHorse;
	vector<int> moveHorse;

	for (int i = 0; i < horseMap[y][x].size(); i++) {
		if (horseMap[y][x][i] == index) {
			for (int j = i; j < horseMap[y][x].size(); j++) {
				moveHorse.push_back(horseMap[y][x][j]);
			}
			break;
		}

		stopHorse.push_back(horseMap[y][x][i]);
	}

	horseMap[y][x] = stopHorse;
	for (int i = 0; i < moveHorse.size(); i++) {
		horseMap[ny][nx].push_back(moveHorse[i]);
		horseList[moveHorse[i]].y = ny;
		horseList[moveHorse[i]].x = nx;
	}

	return horseMap[ny][nx].size();
}

int moveRed(int y, int x, int ny, int nx, int index) {
	vector<int> stopHorse;
	vector<int> moveHorse;

	for (int i = 0; i < horseMap[y][x].size(); i++) {
		if (horseMap[y][x][i] == index) {
			for (int j = horseMap[y][x].size() - 1; j >= i; j--) {
				moveHorse.push_back(horseMap[y][x][j]);
			}
			break;
		}

		stopHorse.push_back(horseMap[y][x][i]);
	}

	horseMap[y][x] = stopHorse;
	for (int i = 0; i < moveHorse.size(); i++) {
		horseMap[ny][nx].push_back(moveHorse[i]);
		horseList[moveHorse[i]].y = ny;
		horseList[moveHorse[i]].x = nx;
	}

	return horseMap[ny][nx].size();
}

int move() {
	int length = horseList.size();
	int result = 0;

	for (int i = 0; i < length; i++) {
		int y = horseList[i].y;
		int x = horseList[i].x;
		int direction = horseList[i].direction;
		int ny = y + dy[direction];
		int nx = x + dx[direction];

		bool blueFlag = false;
		if (exceptionHandling(ny, nx)) {
			if (inputMap[ny][nx] == 0) {
				int value = moveWhite(y, x, ny, nx, i);
				if (value > result) result = value;
			}
			else if (inputMap[ny][nx] == 1) {
				int value = moveRed(y, x, ny, nx, i);
				if (value > result) result = value;
			}
			else blueFlag = true;
		}
		else blueFlag = true;

		if (blueFlag) {
			if (direction == 0) direction = 1;
			else if (direction == 1) direction = 0;
			else if (direction == 2) direction = 3;
			else direction = 2;
			horseList[i].direction = direction;

			ny = y + dy[direction];
			nx = x + dx[direction];

			if (exceptionHandling(ny, nx)) {
				if (inputMap[ny][nx] == 0) {
					int value = moveWhite(y, x, ny, nx, i);
					if (value > result) result = value;
				}
				else if (inputMap[ny][nx] == 1) {
					int value = moveRed(y, x, ny, nx, i);
					if (value > result) result = value;
				}
				else blueFlag = true;
			}
		}
	}

	return result;
}

int solve() {
	for (int time = 1; time <= 1000; time++) {
		if (move() >= 4) return time;
	}

	return -1;
}

int main() {
	input();
	cout << solve() << endl;
}