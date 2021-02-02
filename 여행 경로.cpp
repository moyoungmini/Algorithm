#include <string>
#include <vector>
#include <string.h>

using namespace std;
string result = "";
int length;

void dfs(vector<vector<string>> tickets, bool check[], string ans, string present, int count) {
	if (count == length) {
		if (result == "") result = ans;
		if (result > ans) result = ans;

		return;
	}

	for (int i = 0; i < length; i++) {
		if (tickets[i][0] == present && !check[i]) {
			check[i] = true;
			dfs(tickets, check, ans + tickets[i][1], tickets[i][1], count + 1);
			check[i] = false;
		}
	}
}

vector<string> solution(vector<vector<string>> tickets) {
	vector<string> answer;
	length = tickets.size();
	bool check[10000];
	memset(check, false, sizeof(check));
	dfs(tickets, check, "ICN", "ICN", 0);

	for (int i = 0; i < result.size(); i += 3) {
		answer.push_back(result.substr(i, 3));
	}
	return answer;
}