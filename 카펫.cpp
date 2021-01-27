#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
	vector<int> answer;

	for (int i = 3; i <= brown; i++) {
		int j = (brown - 2 * i) / 2;
		j += 2;
		cout << i << " " << j << endl;
		if (yellow == i * j - 2 * (i + j) + 4) {
			answer.push_back(j);
			answer.push_back(i);
			break;
		}
	}
	return answer;
}