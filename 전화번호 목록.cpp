#include <string>
#include <vector>
#include <map>

using namespace std;

bool solution(vector<string> phone_book) {
	bool answer = true;
	map<string, bool> m;

	int length = phone_book.size();
	for (int i = 0; i < length; i++) {
		m[phone_book[i]] = true;
	}

	for (int i = 0; i < length; i++) {
		string str = "";

		for (int j = 0; j < phone_book[i].size(); j++) {
			str += phone_book[i][j];
			if (m.count(str) != 0 && str != phone_book[i]) return false;
		}
	}
	return true;
}