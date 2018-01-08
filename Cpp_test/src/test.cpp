#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "function.h"
#include "sampleClass.h"
using namespace std;

int main( int argc, const char** argv)
{
	//Declare two TestClass objects, 2nd is a pointer.
	TestClass t1; 	//This is on the stack, so no delete.  Will go when out of scope.
	TestClass *t2;	//This is in the heap, so will stay unless deleted.

	//This works.  Dangerous to use the t2 though.
	TestClass *t3;
	t3 = new TestClass();

	TestClass *t4 = new TestClass();

	//delete
	double corr1 = 11.22;
	double corr2 = 22.33;
	
	double output = sqrt(corr1 + corr2 + 4);

	cout << "First value: " << &corr1 << endl;
	cout << "Second value: " << (&corr1+sizeof(corr1)) << endl;
	cout << "Output: " << corr2 << endl;
	
	for (int i=0; i<10; ++i)
	{
		cout << "This is: " << i << endl;
	}
	
	//Wait for any key press
	//waitKey(0);

	printStuff();

	t1.printname();
	//t2->printname();
	t3->printname();
	t4->printname();
	
	//Delete t2 because it is in the heap.
	//delete t2;
	delete t3;
	delete t4;

	return 0;
}

