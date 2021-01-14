#include <iostream>
#include <vector>
using namespace std;

struct Ball {
	int y;
	int x;
	int direction;
	int weight;
	int speed;
};

struct Node {
	int weight = 0;
	int count = 0;
	int speed = 0;
	vector<int> directionList;
};

int n;
vector<Ball> v;
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

void command() {
	Node map[50][50];

	int length = v.size();
	for (int i = 0; i < length; i++) {
		int speed = v[i].speed%n;
		int ny = (v[i].y + (n + speed * dy[v[i].direction])) % n;
		int nx = (v[i].x + (n + speed * dx[v[i].direction])) % n;

		map[ny][nx].count++;
		map[ny][nx].weight += v[i].weight;
		map[ny][nx].directionList.push_back(v[i].direction);
		map[ny][nx].speed += v[i].speed;
	}

	v.clear();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j].count == 1) {
				Ball newBall;
				newBall.y = i;
				newBall.x = j;
				newBall.weight = map[i][j].weight;
				newBall.speed = map[i][j].speed;
				newBall.direction = map[i][j].directionList[0];
				v.push_back(newBall);
			}
			else if (map[i][j].count > 1) {
				int weight = map[i][j].weight / 5;
				if (weight > 0) {
					int speed = map[i][j].speed / map[i][j].count;

					bool oddFlag = false;
					bool evenFlag = false;

					for (int k = 0; k < map[i][j].directionList.size(); k++) {
						if (map[i][j].directionList[k] % 2 == 0) {
							evenFlag = true;
						}
						else {
							oddFlag = true;
						}
					}

					if ((evenFlag && !oddFlag) || (!evenFlag && oddFlag)) {
						for (int k = 0; k < 4; k++) {
							Ball newBall;
							newBall.y = i;
							newBall.x = j;
							newBall.weight = weight;
							newBall.speed = speed;
							newBall.direction = 2 * k;
							v.push_back(newBall);
						}
					}
					else {
						for (int k = 0; k < 4; k++) {
							Ball newBall;
							newBall.y = i;
							newBall.x = j;
							newBall.weight = weight;
							newBall.speed = speed;
							newBall.direction = 2 * k + 1;
							v.push_back(newBall);
						}
					}
				}
			}
		}
	}
}

int calculate() {
	int length = v.size();
	int sum = 0;

	for (int i = 0; i < length; i++) {
		sum += v[i].weight;
	}

	return sum;
}

int main() {
	int m, k, r, c, w, s, d;

	cin >> n >> m >> k;

	for (int i = 0; i < m; i++) {
		cin >> r >> c >> w >> s >> d;
		Ball newBall;
		newBall.y = r - 1;
		newBall.x = c - 1;
		newBall.weight = w;
		newBall.speed = s;
		newBall.direction = d;
		v.push_back(newBall);
	}

	for (int i = 0; i < k; i++) {
		command();
	}

	cout << calculate() << endl;
}