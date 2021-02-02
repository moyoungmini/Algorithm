#include <string>
#include <vector>
#include <string.h>
using namespace std;

int solution(int n, vector<vector<int>> results) {
	int answer = 0;
	bool map[100][100];
	memset(map, false, sizeof(map));
	int length = results.size();
	for (int i = 0; i < length; i++) {
		map[results[i][0] - 1][results[i][1] - 1] = true;
	}
	// Input

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!map[i][j] && map[i][k] && map[k][j]) {
					map[i][j] = true;
				}
			}
		}
	}
	// Floyd Warshall

	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int j = 0; j < n; j++) {
			if (map[i][j]) count++;
			if (map[j][i]) count++;
		}

		if (count == n - 1) answer++;
	}
	// Incomming + Outgoing Edge == n-1 node ++

	return answer;
}