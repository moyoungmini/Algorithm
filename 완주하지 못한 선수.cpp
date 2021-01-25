#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
	string answer = "";
	map<string, int> m;

	int length = participant.size();
	for (int i = 0; i < length; i++) {
		if (m.count(participant[i]) == 0) {
			m.insert(make_pair(participant[i], 1));
		}
		else {
			m[participant[i]]++;
		}
	}

	length = completion.size();
	for (int i = 0; i < length; i++) {
		m[completion[i]]--;
	}

	for (auto it = m.begin(); it != m.end(); it++) {
		if (it->second != 0) answer = it->first;
	}
	return answer;
}