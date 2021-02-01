using namespace std;

int gcd(int a, int b) {
	if (a < b) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	else if (a == b) return a;

	return gcd(b, a - b);

}

long long solution(int w, int h) {
	long long answer = 1;
	int divide = gcd(w, h);
	answer = (long)w * (long)h - ((w / divide + h / divide - 1) * divide);
	return answer;
}