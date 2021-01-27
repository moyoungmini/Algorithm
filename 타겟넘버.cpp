#include <string>
#include <vector>

using namespace std;

int result = 0;
void dfs(vector<int> & numbers, int index, int length, int sum, int target) {
	if (index == length) {
		if (sum == target) result++;
		return;
	}

	dfs(numbers, index + 1, length, sum + numbers[index], target);
	dfs(numbers, index + 1, length, sum - numbers[index], target);
}

int solution(vector<int> numbers, int target) {
	dfs(numbers, 0, numbers.size(), 0, target);

	return result;
}