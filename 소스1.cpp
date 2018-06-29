#define _CRT_SECURE_NO_WARNINGS
#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>
#include <iostream>
#include <set>

template<typename TKey, typename TValue>
class MinHeap
{
private:
	// array for the elements which should be heap-sorted
	std::vector<std::pair<TKey, TValue>> m_vec;

public:
	MinHeap() { this->m_vec.resize(0); }

	/// <summary>
	/// insert key-value pair
	/// </summary>
	///
	/// <param name="key">
	/// the key that is used for sorting
	/// </param>
	///
	/// <param name="value">
	/// the value that is managed in this heap
	/// </param>
	void Push(TKey key, TValue value) {
		this->m_vec.push_back(std::make_pair(key, value));
		int move = this->m_vec.size() - 1;
		if (move != 0) {
			std::pair<TKey, TValue> temp;
			while (this->m_vec.at(move).first < this->m_vec.at(move / 2).first) {
				temp = this->m_vec.at(move);
				this->m_vec.at(move) = this->m_vec.at(move/ 2);
				this->m_vec.at(move / 2) = temp;
				move = move / 2;
			}
		}
		return;
	}
	/// <summary>
	/// remove the minimum element
	/// </summary>
	void Pop() {
		int size = this->m_vec.size();
		if (size == 0) return;
		else if (size == 1) {
			this->m_vec.pop_back();
			return;
		}
		else {
			int num_0 = 0;
			this->m_vec.at(num_0) = this->m_vec.at(size - 1);
			this->m_vec.pop_back();
			int num_1 = 1, num_2 = 2;
			size = this->m_vec.size();
			std::pair<TKey, TValue> temp;
			while (num_0 * 2 + 2 <= size - 1) {//stop while child node is not twice
				if (this->m_vec.at(num_1).first >= this->m_vec.at(num_2).first) {
					temp = this->m_vec.at(num_2);
					this->m_vec.at(num_2) = this->m_vec.at(num_0);
					this->m_vec.at(num_0) = temp;
					num_0 = num_2;
				}
				else {
					temp = this->m_vec.at(num_1);
					this->m_vec.at(num_1) = this->m_vec.at(num_0);
					this->m_vec.at(num_0) = temp;
					num_0 = num_1;
				}
				num_1 = num_0 * 2 + 1;
				num_2 = num_1 + 1;
			}
			if (size - 1 < num_1) { // leaf node
				return;
			}
			else { // child node only one,  this->m_vec.at(num_1) != NULL
				temp = this->m_vec.at(num_1);
				this->m_vec.at(num_1) = this->m_vec.at(num_0);
				this->m_vec.at(num_0) = temp;
				return;
			}
		}
	}
	/// <summary>
	/// get the minimum element
	/// </summary>
	///
	/// <returns>
	/// the minimum element
	/// </returns>
	std::pair<TKey, TValue> Top() {
		return this->m_vec.front();
	}
	void Print() {
		int n = 0;
		while (n != m_vec.size()) {
			std::cout << m_vec.at(n).first << "   " << m_vec.at(n).second << std::endl;
			n++;
		}
		return;
	}
	/// <summary>
	/// get the key-value pair which the value is the same as the target
	/// </summary>
	///
	/// <returns>
	/// the key-value pair which the value is the same as the target
	/// </returns>
	std::pair<TKey, TValue> Get(TValue target) {
		int n = 0;
		while (this->m_vec.size() != n) {
			if (this->m_vec.at(n).second == target) {
				return this->m_vec.at(n);
			}
			n++;
		}
		return NULL;
	}
	/// <summary>
	/// check whether this heap is empty or not
	/// </summary>
	///
	/// <returns>
	/// true if this heap is empty
	/// </returns>
	bool IsEmpty() {
		if (this->m_vec.size() == 0) return true;
		else return false;
	}
	/// <summary>
	/// change the key of the node which the value is the target.<para/>
	/// In general, the newKey should be smaller than the old key.<para/>
	/// </summary>
	///
	/// <parma name="target">
	/// the target to change the key
	/// </param>
	///
	/// <param name="newKey">
	/// new key for the target
	/// </param>
	void DecKey(TValue target, TKey newKey) {
		int n = 0;
		while (this->m_vec.size() != n) {
			if (m_vec.at(n).second == target) {
				m_vec.at(n).first = newKey;
				break;
			}
			n++;
		}
		if (n == m_vec.size()) { //didn't change
			return;
		}
		int parent;
		std::pair<TKey, TValue> temp;
		while (n != 0) {
			parent = (n - 1) / 2;
			if (this->m_vec.at(n).first < this->m_vec.at(parent).first) {
				temp = this->m_vec.at(n);
				this->m_vec.at(n) = this->m_vec.at(parent);
				this->m_vec.at(parent) = temp;
			}
			else break;
			n = (n - 1) / 2;
		}
		return ;
	}

private:
	/// <summary>
	/// heap-sort, heapify.<para/>
	/// this function can be called recursively
	/// </summary>
	void Heapify(int index) {
		//make Pop function without using this function
	}
};

#endif

int main()
{
	std::vector<int> v1, v2;
	v1.push_back(4);
	v1.push_back(7);
	v1.push_back(0);
	v2.push_back(4);
	v2.push_back(7);
	v2.push_back(0);
	if (v1 != v2) { std::cout << "not same!" << std::endl; }
	std::set<std::pair<int,int>> s;
	s.insert(std::make_pair(13, 2));
	s.insert(std::make_pair(5, 3));
	s.insert(std::make_pair(7, 1));
	s.insert(std::make_pair(17, 4));
	std::set<std::pair<int, int>> ::iterator it;
	for ((it = s.begin()); it != s.end(); it++) {
		std::cout << it->first << " ";
	}
	s.erase(std::make_pair(5, 3));
	std::cout << std::endl;
	it = s.begin();

	std::cout << std::endl;
	char k[100] = "BELLMANFORD 0 3";
	char* next_command = new char;
	char* integer1 = new char;
	char* integer2 = new char;
	char * command_name = strtok_s(k, " ", &next_command);

	integer1 = strtok(next_command, " ");
	if(integer1 !=NULL) integer2 = strtok(NULL, " ");
	std::cout << "command_name: " <<command_name << std::endl;
	std::cout << "next_command: " <<next_command << std::endl;
	if(integer1 != NULL) std::cout << "integer1: " << integer1 << std::endl;
	if(integer2 != NULL) std::cout << "integer2: " << integer2 << std::endl;
	std::cout << "char k: "<< k << std::endl;
	MinHeap<int, int> min;
	min.Push(1, 7);
	min.Push(3, 12);
	min.Push(9, 14);
	min.Push(2, 23);
	min.Push(32, 152);
	min.Push(19, 144);
	min.Push(20, 233);
	min.Push(5, 137);
	min.DecKey(23, 0);
	min.Print();
	std::cout << std::endl;
	min.Pop();
	min.Print();
	//Stack <int> s;
	//if (s.IsEmpty() == 1) cout << "empty!" << endl;
	//s.Push(5);
	//s.Push(3);
	//cout << s.Top() << endl;
	return 0;
}

/*
#include <iostream>

using namespace std;
#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif



template <typename T>
class Stack
{
private:
	class StackNode
	{
	public:
		T Data;
		StackNode* pNext;

		StackNode(T data, StackNode *next) : Data(data), pNext(next) {}
	};

private:
	// the head pointer of the stack
	StackNode* m_pTop;

public:
	Stack() { this->m_pTop = NULL; }
	~Stack() { this->m_pTop = NULL; }

	/// <summary>
	/// push the data into this stack
	/// </summary>
	///
	/// <param name="data">
	/// a data to push into this stack
	/// </param>
	void Push(T data) {
		StackNode *s = new StackNode(data, m_pTop);
		this->m_pTop = s;
	}
	/// <summary>
	/// pop(remove) the last-in data from this stack
	/// </summary>
	void Pop() {
		this->m_pTop = this->m_pTop->pNext;
	}
	/// <summary>
	/// get the last-in data of this stack
	/// </summary>
	/// 
	/// <returns>
	/// the last-in data of this stack
	/// </returns>
	T Top() {
		return m_pTop->Data;
	}
	/// <summary>
	/// check whether this stack is empty or not.
	/// </summary>
	///
	/// <returns>
	/// true if this stack is empty.
	/// false otherwise.
	/// </returns>
	bool IsEmpty() {
		if (this->m_pTop == NULL)return 1;
		else return 0;
	}
};

#endif
*/



/*
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

char* changenum(char* numb) {
cout << numb << endl;
if (strcmp(numb, "0000")==0) return "0";
else if (strcmp(numb, "0001") == 0) return "1";
else if (strcmp(numb, "0010") == 0) return "2";
else if (strcmp(numb, "0011") == 0) return "3";
else if (strcmp(numb, "0100") == 0) return "4";
else if (strcmp(numb, "0101") == 0) return "5";
else if (strcmp(numb, "0110") == 0) return "6";
else if (strcmp(numb, "0111") == 0) return "7";
else if (strcmp(numb, "1000") == 0) return "8";
else if (strcmp(numb, "1001") == 0) return "9";
else if (strcmp(numb, "1010") == 0) return "a";
else if (strcmp(numb, "1011") == 0) return "b";
else if (strcmp(numb, "1100") == 0) return "c";
else if (strcmp(numb, "1101") == 0) return "d";
else if (strcmp(numb, "1110") == 0) return "e";
else if (strcmp(numb, "1111") == 0) return "f";
else return false;
}

int main() {
ifstream infile("data1.txt");
string number;
char a[3] = "0",
b[3] = "0",
c[3] = "0",
d[3] = "0",
e[3] = "0",
f[3] = "0",
g[3] = "0",
h[3] = "0";
string h1, h2, h3, h4, h5, h6, h7, h8;
ofstream fout;
fout.open("log.txt", ofstream::app);
while (!infile.eof()) {
getline(infile, number);
cout << number << endl;
strcpy(a, number.substr(0, 4).c_str());
strcpy(b, number.substr(4, 4).c_str());
strcpy(c, number.substr(8, 4).c_str());
strcpy(d, number.substr(12, 4).c_str());
strcpy(e, number.substr(16, 4).c_str());
strcpy(f, number.substr(20, 4).c_str());
strcpy(g, number.substr(24, 4).c_str());
strcpy(h, number.substr(28, 4).c_str());

h1=changenum(a);
h2=changenum(b);
h3=changenum(c);
h4=changenum(d);
h5=changenum(e);
h6=changenum(f);
h7=changenum(g);
h8=changenum(h);
fout << '\t' << "dcd 0x" << h1 << h2 << h3 << h4 << h5 << h6 << h7 << h8 << endl;
}

fout.close();
infile.close();
}
*/
