#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <string.h>
using namespace std;

class monster {
public:
	int x;
	int y;
	bool exist;
public:
	monster(int y, int x) {
		this->y = y;
		this->x = x;
		exist = true;
	}
};

int n, m, d;
int map[15][15];
vector<int> indexList;
vector<monster> monsterList;
bool check[15];
int result = 0;

void input() {
	cin >> n >> m >> d;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				monster newMosnter(i, j);
				monsterList.push_back(newMosnter);
			}
		}
	}

	memset(check, false, sizeof(check));
}

int calculateLength(int y1, int x1, int y2, int x2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

void solve() {
	int tmpResult = 0;

	monsterList.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 1) {
				monster newMosnter(i, j);
				monsterList.push_back(newMosnter);
			}
		}
	}

	for (int t = 0; t < n; t++) {
		int index[3] = { -1, -1, -1 }; // 삭제할 몬스터
		int distance[3] = { INT_MAX, INT_MAX, INT_MAX };

		for (int i = 0; i < monsterList.size(); i++) {
			if (monsterList[i].exist) {
				for (int j = 0; j < 3; j++) {
					int tmpDistance = calculateLength(monsterList[i].y, monsterList[i].x, n, indexList[j]);
					if (tmpDistance <= d && tmpDistance < distance[j]) {
						distance[j] = tmpDistance;
						index[j] = i;
					}
					else if (tmpDistance <= d && tmpDistance == distance[j] && monsterList[index[j]].x > monsterList[i].x) {
						distance[j] = tmpDistance;
						index[j] = i;
					}
				}
			}
		}
		// 삭제할 몬스터 뽑는다.

		for (int i = 0; i < 3; i++) {
			if (index[i] != -1 && monsterList[index[i]].exist) {
				tmpResult++;
				monsterList[index[i]].exist = false;
			}
		}
		// 삭제


		for (int i = 0; i < monsterList.size(); i++) {
			if (monsterList[i].exist) {
				monsterList[i].y++;
				if (monsterList[i].y >= n) {
					monsterList[i].exist = false;
				}
			}
		}
		// 이동
	}

	if (result < tmpResult) {
		result = tmpResult;
	}
}

void brouteForce(int index) {
	if (indexList.size() == 3) {
		solve();
		return;
	}

	for (int i = index; i < m; i++) {
		if (!check[i]) {
			check[i] = true;
			indexList.push_back(i);

			brouteForce(i + 1);

			check[i] = false;
			indexList.pop_back();
		}
	}
}

int main() {
	input();
	brouteForce(0);
	cout << result << endl;
}