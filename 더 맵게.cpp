#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(vector<int> scoville, int K) {
	priority_queue<int, vector<int>, greater<int>> q;
	int length = scoville.size();
	for (int i = 0; i < length; i++) {
		q.push(scoville[i]);
	}

	int time = 0;
	while (true) {
		if (q.top() >= K) return time;

		if (q.empty()) return -1;
		int n1 = q.top();   q.pop();
		if (q.empty()) return -1;
		int n2 = q.top();   q.pop();
		int value = n1 + (2 * n2);
		q.push(value);

		time++;
	}
	return -1;
}