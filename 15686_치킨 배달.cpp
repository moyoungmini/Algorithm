#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
using namespace std;

class Cordinate {
public:
	int y;
	int x;
public:
	Cordinate(int y, int x) {
		this->y = y;
		this->x = x;
	}
};

int n, m, result;
vector<Cordinate> chickenList;
vector<Cordinate> houseList;
vector<int> indexList;

void input() {
	cin >> n >> m;

	int map;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map;

			if (map == 2) {
				Cordinate newChicken(i, j);
				chickenList.push_back(newChicken);
			}
			else if (map == 1) {
				Cordinate newHouse(i, j);
				houseList.push_back(newHouse);
			}
		}
	}

	result = INT_MAX;
}

void solve() {
	int sum = 0;

	for (int i = 0; i < houseList.size(); i++) {
		int distance = INT_MAX;
		int calculate;

		for (int j = 0; j < m; j++) {
			int index = indexList[j];
			calculate = abs(houseList[i].y - chickenList[index].y) + abs(houseList[i].x - chickenList[index].x);

			if (calculate < distance) distance = calculate;
		}

		sum += distance;
	}

	if (sum < result) result = sum;
}

void brouteForce(int index) {
	if (indexList.size() == m) {
		solve();
		return;
	}

	if (index == chickenList.size()) return;

	indexList.push_back(index);
	brouteForce(index + 1);
	indexList.pop_back();

	brouteForce(index + 1);
}

int main() {
	input();
	brouteForce(0);

	cout << result << endl;
}