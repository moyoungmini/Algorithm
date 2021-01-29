#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> citations) {
	int answer = 0;
	sort(citations.begin(), citations.end(), greater<int>());

	for (answer = 0; answer < citations.size(); answer++) {
		if (answer >= citations[answer]) return answer;
	}

	return answer;
}