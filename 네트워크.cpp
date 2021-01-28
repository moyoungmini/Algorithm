#include <string>
#include <vector>
#include <string.h>

using namespace std;

void dfs(int index, bool check[], int length, vector<vector<int>> & computers) {
	check[index] = true;

	for (int i = 0; i < length; i++) {
		if (computers[index][i] == 1 && index != i && !check[i]) {
			dfs(i, check, length, computers);
		}
	}
}

int solution(int n, vector<vector<int>> computers) {
	int answer = 0;
	int length = computers.size();

	bool check[200];
	memset(check, false, sizeof(check));
	for (int i = 0; i < length; i++) {
		if (!check[i]) {
			dfs(i, check, length, computers);
			answer++;
		}
	}
	return answer;
}