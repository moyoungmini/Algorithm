#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	map<string, int> m;

	m.insert(make_pair("test01", 1));
	m.insert(make_pair("test02", 2));
	m["test03"] = 3; // also possible
	//INSERT

	m.erase("test01");
	// ERASE

	cout << m["test03"] << endl; // 있으면 값 / 없으면 0
	if (m.count("test03") == 0) {
		// NOT EXIST
	}
	else {
		cout << m["test03"] << endl;
	}
	// SELECT


	for (auto it = m.begin(); it != m.end(); it++) {
		cout << "Key : " << it->first << " Value : " << it->second << endl;
	}
	// TRAVERSAL

	return 0;
}