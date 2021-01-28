#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int max(int a, int b, int c) {
	int result = a;
	if (result < b) result = b;
	if (result < c) result = c;

	return result;
}

vector<int> solution(vector<int> answers) {
	vector<int> answer;

	int correct[3][10] = {
		{1,2,3,4,5, -1, -1, -1, -1, -1},
		{2,1,2,3,2,4,2,5, -1, -1},
		{3,3,1,1,2,2,4,4,5,5,}
	};
	int index[3] = { 0, 0, 0 };
	int count[3] = { 0, 0, 0 };
	int length[3] = { 5, 8, 10 };

	for (int i = 0; i < answers.size(); i++) {
		for (int j = 0; j < 3; j++) {
			if (answers[i] == correct[j][index[j]]) {
				if (j == 1) cout << i << endl;
				count[j]++;
			}
		}

		for (int j = 0; j < 3; j++) {
			index[j]++;
			if (index[j] == length[j]) index[j] = 0;
		}
	}

	int maxValue = max(count[0], count[1], count[2]);
	for (int i = 0; i < 3; i++) {
		if (maxValue == count[i]) answer.push_back(i + 1);
	}

	sort(answer.begin(), answer.end());
	return answer;
}