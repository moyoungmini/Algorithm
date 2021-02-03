#include <vector>
#include <queue>
#include <string.h>
using namespace std;

struct node {
	int y;
	int x;
};

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
	int number_of_area = 0;
	int max_size_of_one_area = 0;

	queue<node> q;
	bool check[100][100];
	memset(check, false, sizeof(check));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (!check[i][j] && picture[i][j] != 0) {
				number_of_area++;
				check[i][j] = true;
				node init;
				int select = picture[i][j];
				int count = 1;
				init.y = i;   init.x = j;
				q.push(init);

				while (!q.empty()) {
					node front = q.front(); q.pop();

					for (int k = 0; k < 4; k++) {
						int ny = front.y + dy[k];
						int nx = front.x + dx[k];

						if (ny >= 0 && ny < m && nx >= 0 && nx < n) {
							if (!check[ny][nx] && picture[ny][nx] == select) {
								node newNode;
								newNode.y = ny;   newNode.x = nx;
								q.push(newNode);
								check[ny][nx] = true;
								count++;
							}
						}
					}
				}

				if (count > max_size_of_one_area) max_size_of_one_area = count;
			}
		}
	}

	vector<int> answer(2);
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;
	return answer;
}