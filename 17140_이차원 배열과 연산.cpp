#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

class Node {
public:
	int number;
	int count;
public:
	Node(int number, int count) {
		this->number = number;
		this->count = count;
	}
	Node() {}

	bool operator < (Node & node) {
		if (this->count < node.count) {
			return true;
		}
		else if (this->count > node.count) {
			return false;
		}
		else {
			if (this->number < node.number) {
				return true;
			}
			return false;
		}
	}
};

int map[100][100];
int countValue[101];
int n, m;
int r, c, k;

void change() {
	int tmp[100][100];
	int length = n;
	if (length < m) length = m;

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			tmp[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			map[j][i] = tmp[i][j];
		}
	}
}

void calculate(bool flag) {
	int newLength = 0;

	int length;
	if (n >= m)length = n;
	else length = m;

	for (int i = 0; i < length; i++) {
		memset(countValue, 0, sizeof(countValue));

		for (int j = 0; j < length; j++) {
			if (map[i][j] != 0) {
				countValue[map[i][j]]++;
				map[i][j] = 0;
			}
		}

		vector<Node> v;
		for (int j = 0; j <= 100; j++) {
			if (countValue[j] != 0) {
				Node node(j, countValue[j]);
				v.push_back(node);
			}
		}

		sort(v.begin(), v.end());

		int index = 0;
		for (int j = 0; j < v.size(); j++) {
			map[i][index] = v[j].number;

			if (index + 1 == 100) break;
			map[i][index + 1] = v[j].count;

			index += 2;
			if (index >= 100) break;
		}

		if (newLength < index) newLength = index;
	}

	if (flag) m = newLength;
	else n = newLength;
}

void solution() {
	if (n >= m) {
		calculate(true);
	}
	else {
		change();
		calculate(false);
		change();
	}
}

void input() {
	memset(map, 0, sizeof(map));
	n = 3;	m = 3;

	cin >> r >> c >> k;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> map[i][j];
		}
	}
}

int main() {
	input();
	for (int i = 0; i <= 100; i++) {
		if (map[r - 1][c - 1] == k) {
			cout << i << endl;
			return 0;
		}

		solution();
	}

	cout << -1 << endl;
}