#include <iostream>
#include <string>
#include <queue>
#include <functional>

using namespace std;
int Ccompare(string a, string b);
bool isAlphabet(char a);
int main() 
{
	string k = "FRANCE";
	string q = "french";
	cout << Ccompare(k, q) << endl;
	k = "handshake";
	q = "shake hands";
	cout << Ccompare(k, q) << endl;
	k = "aa1+aa2";
	q = "AAAA12";
	cout << Ccompare(k, q) << endl;
	k = "E=M*C^2";
	q = "e=m*c^2";
	cout << Ccompare(k, q) << endl;
	return 0;
}
int Ccompare(string a, string b) {
	unsigned int i, k;
	int sum = 0, same_sum = 0;
	priority_queue<string, vector<string>, greater<string>> arr1, arr2;
	for (k = 0; k < a.length(); k++) {
		a.at(k) = toupper(a.at(k));
	}
	for (k = 0; k < b.length(); k++) {
		b.at(k) = toupper(b.at(k));
	}

	for (i = 0; i < a.length() - 1; i++) {
		if ((isAlphabet(a.at(i))) && (isAlphabet(a.at(i + 1)))) arr1.push(a.substr(i, 2));
	}
	for (i = 0; i < b.length() - 1; i++) {
		if ((isAlphabet(b.at(i))) && (isAlphabet(b.at(i + 1)))) arr2.push(b.substr(i, 2));
	}
	while (true) {
		if (strcmp(arr1.top().c_str(), arr2.top().c_str()) == 0) {
			same_sum++;
			sum++;
			arr1.pop();
			arr2.pop();
		}
		else if (strcmp(arr1.top().c_str(), arr2.top().c_str()) > 0) {
			sum++;
			arr2.pop();
		}
		else {
			sum++;
			arr1.pop();
		}
		if (arr1.empty()||arr2.empty()) {
			sum = sum + arr2.size() + arr1.size();
			break;
		}
	}
	return 65536*same_sum/sum;
}

bool isAlphabet(char a) {
	if ((a < 65) || (a > 97)) return false;
	else return true;
}