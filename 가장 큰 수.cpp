#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
	string number;
public:
	Node(string number) {
		this->number = number;
	}

	bool operator < (Node & node) {
		int n1 = stoi(this->number + node.number);
		int n2 = stoi(node.number + this->number);
		if (n1 > n2) return true;
		return false;
	}
};

string solution(vector<int> numbers) {
	string answer = "";
	vector<Node> v;
	int length = numbers.size();
	for (int i = 0; i < length; i++) {
		Node node(to_string(numbers[i]));
		v.push_back(node);
	}
	sort(v.begin(), v.end());

	bool flag = true;
	for (int i = 0; i < length; i++) {
		if (flag) {
			if (v[i].number == "0") continue;
			else flag = false;
		}
		answer += v[i].number;
	}
	if (answer.size() == 0) answer = "0";
	return answer;
}