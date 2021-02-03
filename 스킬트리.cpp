#include <string>
#include <vector>
#include <map>
#include <string.h>
using namespace std;

int solution(string skill, vector<string> skill_trees) {
	int answer = 0;
	bool check[26];
	map<char, char> m;
	int length = skill.size();

	for (int i = 1; i < length; i++) {
		m[skill[i]] = skill[i - 1];
	}
	length = skill_trees.size();

	for (int i = 0; i < length; i++) {
		memset(check, false, sizeof(check));
		bool flag = true;
		for (int j = 0; j < skill_trees[i].size(); j++) {
			if (m.count(skill_trees[i][j]) == 0) {
				check[skill_trees[i][j] - 'A'] = true;
			}
			else {
				char pre_skill = m[skill_trees[i][j]];
				if (check[pre_skill - 'A']) {
					check[skill_trees[i][j] - 'A'] = true;
				}
				else {
					flag = false;
					break;
				}
			}
		}

		if (flag) answer++;
	}

	return answer;
}