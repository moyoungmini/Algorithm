#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
	int x1;
	int y1;
	int x2;
	int y2;
	int direction;
public:
	Node(int x1, int y1, int x2, int y2, int direction) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		this->direction = direction;
	}
};

int n;
int map[16][16];

void input() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

bool checkException(int y, int x) {
	if (x >= 0 && x < n && y >= 0 && y < n) {
		return true;
	}

	return false;
}

int solution() {
	int sum = 0;
	Node init(0, 0, 1, 0, 0);
	queue<Node> q;
	q.push(init);
	int nx1, nx2, ny1, ny2;

	while (!q.empty()) {
		Node front = q.front();	q.pop();

		if (front.y2 == n - 1 && front.x2 == n - 1) {
			sum++;
			continue;
		}

		if (front.direction == 0) {
			nx1 = front.x2;
			ny1 = front.y2;
			nx2 = front.x2 + 1;
			ny2 = front.y2;

			if (checkException(ny2, nx2) && map[ny2][nx2] == 0) {
				Node newNode(nx1, ny1, nx2, ny2, front.direction);
				q.push(newNode);
			}

			nx1 = front.x2;
			ny1 = front.y2;
			nx2 = front.x2 + 1;
			ny2 = front.y2 + 1;

			if (checkException(ny2, nx2) && map[ny1 + 1][nx1] == 0 && map[ny1][nx1 + 1] == 0 && map[ny2][nx2] == 0) {
				Node newNode(nx1, ny1, nx2, ny2, 2);
				q.push(newNode);
			}
		}
		else if (front.direction == 1) {
			nx1 = front.x2;
			ny1 = front.y2;
			nx2 = front.x2;
			ny2 = front.y2 + 1;

			if (checkException(ny2, nx2) && map[ny2][nx2] == 0) {
				Node newNode(nx1, ny1, nx2, ny2, front.direction);
				q.push(newNode);
			}

			nx1 = front.x2;
			ny1 = front.y2;
			nx2 = front.x2 + 1;
			ny2 = front.y2 + 1;

			if (checkException(ny2, nx2) && map[ny1 + 1][nx1] == 0 && map[ny1][nx1 + 1] == 0 && map[ny2][nx2] == 0) {
				Node newNode(nx1, ny1, nx2, ny2, 2);
				q.push(newNode);
			}
		}
		else if (front.direction == 2) {
			nx1 = front.x2;
			ny1 = front.y2;
			nx2 = front.x2 + 1;
			ny2 = front.y2;

			if (checkException(ny2, nx2) && map[ny2][nx2] == 0) {
				Node newNode(nx1, ny1, nx2, ny2, 0);
				q.push(newNode);
			}

			nx1 = front.x2;
			ny1 = front.y2;
			nx2 = front.x2;
			ny2 = front.y2 + 1;

			if (checkException(ny2, nx2) && map[ny2][nx2] == 0) {
				Node newNode(nx1, ny1, nx2, ny2, 1);
				q.push(newNode);
			}

			nx1 = front.x2;
			ny1 = front.y2;
			nx2 = front.x2 + 1;
			ny2 = front.y2 + 1;

			if (checkException(ny2, nx2) && map[ny1 + 1][nx1] == 0 && map[ny1][nx1 + 1] == 0 && map[ny2][nx2] == 0) {
				Node newNode(nx1, ny1, nx2, ny2, 2);
				q.push(newNode);
			}
		}
	}

	return sum;
}

int main() {
	input();
	cout << solution() << endl;
}