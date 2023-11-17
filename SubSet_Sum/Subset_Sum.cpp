#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void solution(vector<int>& elements);
int func(const vector<int>& elements, vector<vector<int>>& PlusSumMat, vector<vector<int>>& MinusSumMat, int index, int Sum);
vector<int> ShowSet(const vector<int>& elements, int index, float sum, int middlesum, vector<int> arr);

int main() {
	string count;

	while (true) {

		cin >> count;

		if (count == "EOI" || count == "eoi")
			return 0;
		int elements_Count = stoi(count);
		vector<int> elements(elements_Count);

		for (int i = 0; i < elements_Count; i++) {
			cin >> elements[i];
		}
		sort(elements.begin(), elements.end());
		solution(elements);
	}

	return 0;
}

void solution(vector<int>& elements) {

	int Sum = 0;
	int PlusSum = 0;
	int MinusSum = 0;
	unsigned long long count = 0;

	vector<int> Example1(1);
	vector<int> Example2;

	for (int i = 0; i < elements.size(); i++) {
		if (elements[i] >= 0)
			PlusSum += elements[i];
		else
			MinusSum += elements[i];
	}
	Sum = PlusSum + MinusSum;

	if (Sum % 2 == 0) {

		int Subset_Sum = Sum / 2;

		vector<vector<int>> PlusSumMat(elements.size() + 1, vector<int>(2*abs(Subset_Sum - MinusSum) + 1, -1));
		vector<vector<int>> MinusSumMat(elements.size() + 1, vector<int>(2*abs(Subset_Sum - PlusSum) + 1, -1));

		
		for (int i = 1; i < PlusSumMat[0].size(); i++)
			PlusSumMat[0][i] = 0;
		
		for (int i = 1; i < MinusSumMat[0].size(); i++)
			MinusSumMat[0][i] = 0;
		
		// it means that if there is no elements it can make a 0
		PlusSumMat[0][0] = 1;
		
		//if first index is 1 and second index is element[0], it can count 1, because first index can only make a element[0] 
		if (elements[0] >= 0)
			PlusSumMat[1][elements[0]] = 1;
		else if(elements[0] < 0)
			MinusSumMat[1][-elements[0]] = 1;

		count = func(elements, PlusSumMat,MinusSumMat, elements.size(), Subset_Sum);
	}
	if (count > (1ull << 32) - 1)
		cout << "numerous";
	else
		cout << count;

	cout << endl;

	Example1 = ShowSet(elements, 0, Sum, 0, Example1);

	for (int i = 0; i < elements.size(); i++) {
		bool exclude = false;
		for (int j = 1; j < Example1.size(); j++) {
			if (elements[i] == Example1[j]) {
				exclude = true;
				break;
			}
		}
		if (!exclude) {
			Example2.push_back(elements[i]);
		}
	}

	cout << "{";
	for (int i = 0; i < Example2.size(); i++) {
		if (i == Example2.size() - 1)
			cout << Example2[i];
		else
			cout << Example2[i] << ",";
	}
	if (Example2.size() == 0)
		cout << " ";
	cout << "},{";
	for (int i = 1; i < Example1.size(); i++) {
		if (i == Example1.size() - 1)
			cout << Example1[i];
		else
			cout << Example1[i] << ",";
	}
	if (Example1.size() == 1)
		cout << " ";
	cout << "}";
	cout << endl;
	

}

vector<int> ShowSet(const vector<int>& elements,int index , float sum, int middlesum, vector<int> arr) {
	
	if (index == elements.size()) {
		arr[0] = abs(sum - 2 * middlesum);
		return arr;
	}
		
	int result=0;

	vector<int> arr_notindex = arr;
	arr.push_back(elements[index]);

	vector<int> temp_Include = ShowSet(elements, index + 1, sum, middlesum + elements[index], arr);
	vector<int> temp_notInclude = ShowSet(elements, index + 1, sum, middlesum, arr_notindex);

	return temp_notInclude[0] > temp_Include[0] ? temp_Include : temp_notInclude;
}




int func(const vector<int>& elements, vector<vector<int>>& PlusSumMat, vector<vector<int>>& MinusSumMat, int index, int Sum) {

	if (index == -1)
		return 0;

	if (Sum < 0) {
		int MinusSum = -Sum;

		if (MinusSumMat[index][MinusSum] != -1)
			return MinusSumMat[index][MinusSum];

		if (index == 1 && Sum != elements[0])
			return 0;
	}

	else {
		if (PlusSumMat[index][Sum] != -1)
			return PlusSumMat[index][Sum];

		if(index == 1 && Sum != elements[0])
			return 0;

	}
	
	int result = 0;
	result = func(elements, PlusSumMat,MinusSumMat, index - 1, Sum) + func(elements, PlusSumMat, MinusSumMat, index - 1, Sum - elements[index - 1]);
	
	if (Sum >= 0)
		PlusSumMat[index][Sum] = result;
	else if (Sum < 0)
		MinusSumMat[index][-Sum] = result;

	return result;

}



