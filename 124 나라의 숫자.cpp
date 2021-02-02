#include <string>
#include <vector>
#include <math.h>
using namespace std;

string solution(int n) {
	string answer = "";
	int tmp;
	int idx = 1;
	while (true) {
		if (n - (int)pow(3, idx) <= 0) break;
		n -= (int)pow(3, idx);
		idx++;
	}

	while (idx != 0) {
		idx--;
		if (n % (int)pow(3, idx) == 0) {
			tmp = n / (int)pow(3, idx) - 1;
		}
		else {
			tmp = n / (int)pow(3, idx);
		}

		if (tmp == 0) tmp = 1;
		else if (tmp == 1) tmp = 2;
		else tmp = 4;

		n %= (int)pow(3, idx);
		answer += (char)('0' + tmp);
	}

	return answer;
}