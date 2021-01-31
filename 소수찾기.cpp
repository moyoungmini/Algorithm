#include <string>
#include <vector>
#include <map>
#include <string.h>
using namespace std;

int length;
vector<char> value;
vector<char> result;
bool check[7];
map<int, bool> m;

void dfs() {
	if (result.size() != 0) {
		string strTmp = "";
		for (int i = 0; i < result.size(); i++) {
			strTmp += result[i];
		}
		int intTmp = stoi(strTmp);
		m.insert(make_pair(intTmp, true));
	}

	for (int i = 0; i < length; i++) {
		if (!check[i]) {
			check[i] = true;
			result.push_back(value[i]);
			dfs();
			check[i] = false;
			result.pop_back();
		}
	}
}

bool prime(int num) {
	if (num < 2) return false;

	for (int i = 2; i <= num / 2; i++) {
		if (num%i == 0) return false;
	}

	return true;
}

int calculate() {
	int result = 0;
	for (auto it = m.begin(); it != m.end(); it++) {
		if (prime(it->first)) result++;
	}

	return result;
}

int solution(string numbers) {
	memset(check, false, sizeof(check));
	length = numbers.size();
	for (int i = 0; i < length; i++) {
		value.push_back(numbers[i]);
	}

	dfs();

	return calculate();
}