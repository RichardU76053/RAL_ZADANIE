#include <iostream>
#include <vector>
#include <NTL/GF2X.h>

NTL_CLIENT

vector<int> printDivisors(int n){
    vector<int> v;
	for (int i=1;i<=n;i++)
        if (n%i==0)
        	v.push_back(i);
	return v;
}

int main(int argc, char** argv) {
	int n;
	
	cout << "Zadajte vstupne cislo n: ";
	cin >> n;
	cout << "Zadali ste : n = " << n << endl;
	
	vector<int> v = printDivisors(n);
	for(vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    	cout << *it << endl;
	}
	
	system("pause");
	return 0;
}
