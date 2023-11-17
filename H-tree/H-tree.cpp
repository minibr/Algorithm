#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

int V[4][2] = { { -1, 0 },{ 1, 0 },{ 0, 1 },{ 0, -1 } };

int center(int n) { return n <= 1 ? 0 : 2 * center(n / 4) + 1; }
int Depth(int n) { return n <= 7 ? 1 : 2 * Depth(n / 4); }

void rotated(vector<char> v, int i, int depth) {
	int w = 0;
	if (i < v.size())
	{
		rotated(v, 2 * i + 2, depth + 1);
		w = depth * 2 + 1;
		cout.width(w);
		cout << v[i] << endl;
		rotated(v, 2 * i + 1, depth + 1);
	}

}

void not_rotated(vector<char> v, int depth) {
	int j = 1;
	int w;
	for (int k = 0; k < v.size(); k++)
	{
		if (k == 0) {
			w = pow(2, depth);
			cout.width(w);
			cout << v[0] << endl;
			--depth;
		}
		else if (k == pow(2, j) - 1) {
			w = pow(2, depth);
			cout.width(w);
			cout << v[k];
		}
		else {
			w = pow(2, depth + 1);
			cout.width(w);
			cout << v[k];
			if (k == pow(2, j + 1) - 2) {
				cout << endl;
				++j; --depth;
			}
		}
	}
	cout << endl;
}

char** H_array(int size) {
	char** arr = new char* [size];
	for (int i = 0; i < size; ++i) {
		arr[i] = new char[size];
		memset(arr[i], 0, sizeof(char) * size);
	}
	return arr;
}

char** H(char** H_tree, vector<char>& v, int node, int i, int j, int d, int U, int D, int R, int L) {
	if (node > v.size()) return NULL;
	H_tree[i][j] = v[node - 1];
	if (2 * node <= v.size()) {
		H_tree[i + d * V[L][0]][j + d * V[L][1]] = v[2 * node - 1];
		H(H_tree, v, 4 * node, i + d * (V[L][0] + V[U][0]),
			j + d * (V[L][1] + V[U][1]), d / 2, D, U, L, R);
		H(H_tree, v, 4 * node + 1, i + d * (V[L][0] + V[D][0]),
			j + d * (V[L][1] + V[D][1]), d / 2, U, D, R, L);
	}
	if (2 * node + 1 <= v.size()) {
		H_tree[i + d * V[R][0]][j + d * V[R][1]] = v[2 * node];
		H(H_tree, v, 4 * node + 2, i + d * (V[R][0] + V[D][0]),
			j + d * (V[R][1] + V[D][1]), d / 2, U, D, R, L);
		H(H_tree, v, 4 * node + 3, i + d * (V[R][0] + V[U][0]),
			j + d * (V[R][1] + V[U][1]), d / 2, D, U, L, R);
	}
	return H_tree;
}


void h_tree(char**& H_tree, vector<char> v, int size) {
	
	char** htree = H(H_tree, v, 1, center(v.size()), center(v.size()), Depth(v.size()), 0, 1, 2, 3);
	
	for (int i = 0; i < size; ++i) {
		
		for (int j = 0; j < size; ++j) {
			if (j == 0)
				cout.width(1);
			else
				cout.width(2);
			cout << htree[i][j];
		}
		cout << endl;
	}
	
	for (int i = 0; i < size; ++i) { delete[] htree[i]; } delete[] htree;
}
int main(void) {
	char i;
	vector<char> v;
	string s;
	int num = 0;
	int depth = 1;
	int hSize = 1;
	int sSize = 0;
	while (cin >> s) {
		++num;
		if (s == "DEL" && v.size() != 0) {
			pop_heap(v.begin(), v.end());
			v.pop_back();
		}
		else if (s == "INS" && cin >> i)
		{
			if (((int)i > 47 && (int)i < 58) || ((int)i > 64 && (int)i < 91) || ((int)i > 96 && (int)i < 123) || (int)i == 63)
			{
				v.push_back(i);
				push_heap(v.begin(), v.end());
			}
		}
		else if (s == "EOI") {
			for (int k = 1; k < v.size(); k++)
				if (k == pow(2, depth) - 1) {
					++depth;
				}
			--depth;

			cout << "1. rotated form" << endl;
			rotated(v, 0, 0);
			cout << endl;
			cout << "2. not-rotated form" << endl;
			not_rotated(v, depth);
			cout << endl;
			cout << "3. H-tree form" << endl << endl;

			for (int k = 1; k < Depth(v.size()); k++)
				if (k == pow(2, hSize) - 1) {
					++hSize;
				}
			sSize = pow(2, hSize + 1) - 1;
			char** H_tree = H_array(sSize);
			h_tree(H_tree, v, sSize);

			break;
		}
		if (num == 200)
			break;
	}
	return 0;
}