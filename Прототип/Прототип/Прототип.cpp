#include <iostream>
using namespace std;

class test
{
public:
	int *A, *B;
	test() {
		A = new int[10];
		B = new int[10];
		for (int i = 0; i<10; i++) {
			A[i] = rand() % 100;
			B[i] = rand() % 100;
		}
	}

	void show(test test1) {
		for (int i = 0; i<10; i++)
			cout << test1.A[i] << "\t" << test1.B[i] << endl;
	}

};


void main() {
	test CL;
	CL.show(CL);
}