#include <iostream>
using namespace std;

class Node {
public:
	int score;
	int redNextIndex;
	int blueNextIndex;
public:
	Node() {
		this->score = -1;
		this->redNextIndex = -1;
		this->blueNextIndex = -1;
	}
};

const int n = 10;
int dice[n];
Node map[33];
int result = 0;
int horse[4] = { 0, 0, 0, 0 };

void init() {
	for (int i = 0; i < 20; i++) {
		map[i].redNextIndex = i + 1;
		map[i].score = i * 2;
	}

	map[5].blueNextIndex = 21;
	map[21].redNextIndex = 22;
	map[21].score = 13;
	map[22].redNextIndex = 23;
	map[22].score = 16;
	map[23].redNextIndex = 24;
	map[23].score = 19;

	map[10].blueNextIndex = 25;
	map[25].redNextIndex = 26;
	map[25].score = 22;
	map[26].redNextIndex = 24;
	map[26].score = 24;

	map[15].blueNextIndex = 27;
	map[27].redNextIndex = 28;
	map[27].score = 28;
	map[28].redNextIndex = 29;
	map[28].score = 27;
	map[29].redNextIndex = 24;
	map[29].score = 26;

	map[24].redNextIndex = 30;
	map[24].score = 25;
	map[30].redNextIndex = 31;
	map[30].score = 30;
	map[31].redNextIndex = 20;
	map[31].score = 35;
	map[20].redNextIndex = 32;
	map[20].score = 40;

	map[32].redNextIndex = 32;
	map[32].score = 0;
}

void input() {
	for (int i = 0; i < n; i++) {
		cin >> dice[i];
	}
}

bool move(int index, int count) {
	int position = horse[index];

	if (map[position].blueNextIndex != -1) {
		position = map[position].blueNextIndex;
	}
	else {
		position = map[position].redNextIndex;
	}

	for (int i = 1; i < count; i++) {
		if (position == 32) break;

		position = map[position].redNextIndex;
	}

	for (int i = 0; i < 4; i++) {
		if (position == 32) break;
		if (i != index && position == horse[i]) {
			return false;
		}
	}
	horse[index] = position;

	return true;
}

void brouteForce(int index, int sum) {
	if (index == 10) {
		if (result < sum) result = sum;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (horse[i] != 32) {
			int prev = horse[i];
			if (move(i, dice[index])) {
				brouteForce(index + 1, sum + map[horse[i]].score);
				horse[i] = prev;
			}
		}
	}
}

int main() {
	input();
	init();
	brouteForce(0, 0);
	cout << result << endl;
}