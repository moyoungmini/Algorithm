#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
	for (int i = 0; i < k; i++) {
		int removeIndex = 0;
		bool flag = true;
		for (int j = 0; j < number.size() - 1; j++) {
			if (number[j] < number[j + 1]) {
				removeIndex = j;
				flag = false;
				break;
			}
		}
		if (flag) number = number.substr(0, number.size() - 1);
		else number = number.substr(0, removeIndex) + number.substr(removeIndex + 1, number.size() - removeIndex - 1);
	}

	return number;
}