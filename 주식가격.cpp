#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> prices) {
	vector<int> answer;

	for (int i = 0; i < prices.size(); i++) {
		int count = 1;
		bool flag = true;

		for (int j = i + 1; j < prices.size(); j++) {
			if (prices[i] <= prices[j]) count++;
			else {
				flag = false;
				break;
			}
		}
		if (flag) count--;
		answer.push_back(count);
	}
	return answer;
}