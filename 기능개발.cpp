#include <string>
#include <vector>
#include <queue>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;
	queue<int> q;
	int length = progresses.size();
	for (int i = 0; i < length; i++) {
		int time;
		if ((100 - progresses[i]) % speeds[i] == 0) {
			time = (100 - progresses[i]) / speeds[i];
		}
		else {
			time = (100 - progresses[i]) / speeds[i] + 1;
		}

		q.push(time);
	}

	int time = q.front();   q.pop();
	int count = 1;
	while (!q.empty()) {
		int front = q.front();   q.pop();
		if (front <= time) count++;
		else {
			time = front;
			answer.push_back(count);
			count = 1;
		}
	}
	answer.push_back(count);

	return answer;
}