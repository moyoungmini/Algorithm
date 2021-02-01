#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int solution(vector<int> priorities, int location) {
	int answer = 0;
	queue<int> valueQ;
	queue<int> idxQ;
	int length = priorities.size();
	for (int i = 0; i < length; i++) {
		valueQ.push(priorities[i]);
		idxQ.push(i);
	}
	sort(priorities.begin(), priorities.end(), greater<int>());

	for (int idx = 0; idx < length; idx++) {
		int removeValue = priorities[idx];

		while (true) {
			int frontValue = valueQ.front();    valueQ.pop();
			int frontIdx = idxQ.front();        idxQ.pop();

			if (frontValue == removeValue) {
				if (frontIdx == location) return idx + 1;
				break;
			}
			else {
				valueQ.push(frontValue);
				idxQ.push(frontIdx);
			}
		}
	}

	return -1;
}