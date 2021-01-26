#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> genreMap;

class Node {
public:
	string genre;
	int play;
	int index;
public:
	Node(string genre, int play, int index) {
		this->genre = genre;
		this->play = play;
		this->index = index;
	}

	Node() {}

	bool operator <(Node & node) {
		if (genreMap[this->genre] > genreMap[node.genre]) {
			return true;
		}
		else if (genreMap[this->genre] < genreMap[node.genre]) {
			return false;
		}
		else {
			if (this->play > node.play) {
				return true;
			}
			else if (this->play < node.play) {
				return false;
			}
			else {
				if (this->index < node.index) return true;
				return false;
			}
		}
	}

};

vector<int> solution(vector<string> genres, vector<int> plays) {
	vector<int> answer;
	vector<Node> v;

	int length = genres.size();
	for (int i = 0; i < length; i++) {
		if (genreMap.count(genres[i]) == 0) {
			genreMap[genres[i]] = plays[i];
		}
		else {
			genreMap[genres[i]] += plays[i];
		}
	}

	for (int i = 0; i < length; i++) {
		Node node(genres[i], plays[i], i);
		v.push_back(node);
	}
	sort(v.begin(), v.end());

	string genre = v[0].genre;
	int count = 0;
	for (int i = 0; i < length; i++) {
		if (genre == v[i].genre) {
			if (count == 2) continue;
			answer.push_back(v[i].index);
			count++;
		}
		else {
			count = 1;
			genre = v[i].genre;
			answer.push_back(v[i].index);
		}
	}

	return answer;
}