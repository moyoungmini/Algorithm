#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(vector<vector<string>> clothes) {
	int answer = 0;
	map<string, int> m;

	int length = clothes.size();
	for (int i = 0; i < length; i++) {
		if (m.count(clothes[i][1]) == 0) {
			m[clothes[i][1]] = 1;
		}
		else {
			m[clothes[i][1]]++;
		}
	}

	answer = 1;
	for (auto it = m.begin(); it != m.end(); it++) {
		answer *= it->second + 1;
	}

	answer--;
	return answer;
}