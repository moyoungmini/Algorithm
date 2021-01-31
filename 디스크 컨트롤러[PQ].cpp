#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct node {
	int start;
	int length;
};

struct compare {
	bool operator()(node & a, node & b) {
		if (a.length > b.length) return true;
		else if (a.length == b.length) {
			if (a.start > b.start) return true;
		}
		return false;
	}
};

bool cmp(vector<int> a, vector<int> b) {
	if (a[0] < b[0]) return true;
	return false;
}

int solution(vector<vector<int>> jobs) {
	int answer = 0;
	sort(jobs.begin(), jobs.end(), cmp);
	priority_queue<node, vector<node>, compare> pq;

	int length = jobs.size();
	int time = 0;
	int index = 0;

	while (true) {
		if (index == length && pq.empty()) break;

		if (index != length && time >= jobs[index][0]) {
			node newNode;
			newNode.start = jobs[index][0];
			newNode.length = jobs[index][1];
			pq.push(newNode);
			index++;
			continue;
		}

		if (index != length && pq.empty()) {
			time = jobs[index][0];
			continue;
		}
		//jobs push in pq

		node front = pq.top(); pq.pop();
		time += front.length;
		answer += (time - front.start);
		cout << front.start << " " << front.length << endl;
	}
	return answer / length;
}