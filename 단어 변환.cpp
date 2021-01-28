#include <string>
#include <vector>
#include <string.h>
#include <limits.h>

using namespace std;
int result = INT_MAX;

bool flag(string a, string b) {
	int length = a.size();
	int count = 0;

	for (int i = 0; i < length; i++) {
		if (a[i] != b[i]) count++;
	}

	if (count == 1) return true;
	return false;
}

void dfs(string strPresent, string target, vector<string> words, bool check[], int sum) {
	if (strPresent == target) {
		if (result > sum) result = sum;
		return;
	}
	for (int i = 0; i < words.size(); i++) {
		if (!check[i] && flag(strPresent, words[i])) {
			check[i] = true;
			dfs(words[i], target, words, check, sum + 1);
			check[i] = false;
		}
	}
}

int solution(string begin, string target, vector<string> words) {
	bool check[50];
	memset(check, false, sizeof(check));
	dfs(begin, target, words, check, 0);
	if (result == INT_MAX) result = 0;

	return result;
}