#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
	int time = 0;
	int present_weight = 0;
	int truck_index = 0;
	int length = truck_weights.size();
	queue<int> q;

	while (true) {
		time++;
		if (q.size() == bridge_length) {
			present_weight -= q.front();
			q.pop();
		}

		if (present_weight + truck_weights[truck_index] <= weight) {
			q.push(truck_weights[truck_index]);
			present_weight += truck_weights[truck_index];
			truck_index++;

			if (truck_index == length) {
				time += bridge_length;
				break;
			}
		}
		else {
			q.push(0);
		}

	}


	return time;
}