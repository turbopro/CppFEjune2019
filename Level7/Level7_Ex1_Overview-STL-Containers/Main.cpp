/* Main.cpp
Level7_Ex1: Overview of the Standard Template Library - STL Containers

Test program for the STL -- built upon the previous work done thus far

 STL tests as follows:
 · 
 · 
   : use a loop with an index multiplier to create Point object coordinates
 · 
 · 
   : get user input for the array size
   : use a loop with an index multiplier to create Point object coordinates
 · 
 · 
   : copy the constructor Array
 · 
 · 
 · 
 · 
 · 
 · 
 · 
 

*/

#define _USE_MATH_DEFINES	// for PI

#include <iostream>
#include <string>			// for string operations
#include <iomanip>			// set fixed and precision for cout/cin
#include <cmath>			// for PI
#include "Point.h"			// Point class declaration
#include "Line.h"			// Line class declaration
#include "Circle.h"			// Circle class declaration
#include "Array.h"			// Array class declaration
#include "Shape.h"			// Shape class declaration
#include "ArrayException.h"	// ArrayException class declaration
#include "NumericArray.h"	// NumericArray class declaration
#include "PointArray.h"		// PointArray class declaration
#include "Stack.h"			// Stack class declaration
#include "StackException.h"	// StackException class declaration

// STL
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

// declaration for user_input_geom() function
bool user_input_geom(double& geom_value, const string& geom_id, const string& geom_description);

// declaration for user_input_array() function
bool user_input_array(unsigned int& array_size);


int main(void)
{
	using namespace Turbopro::Containers;		// namespace directive
	using namespace Turbopro::CAD;				// namespace directive
	using Turbopro::CAD::Line;					// namespace declaration
	namespace TCad = Turbopro::CAD;				// namespace alias


	const string x_coord{ "x-coordinate" };		// for user input: set geom_description
	const string y_coord{ "y-coordinate" };
	const string  radius{ "radius" };

	double x{ 0.0 }, y{ 0.0 }, r{ 0.0 };		// declare/initialise geom_values
	int arr_size{ 0 };					// array size should be positive only
	const int stack_size = 3;

	/*
	cout << "\n\n"
		<< "|========================================|\n"
		<< "|    STACKS with Value Template Args:    |\n"
		<< "|========================================|\n\n";		

	// create int Stack
	//const int stack_size = 3;
	cout << "\nCreate an int Stack:\n";
	Stack<int, stack_size> stint0;
	cout << "\nstint0 size: " << stint0.Size() << endl;
	cout << "stint0 m_index: " << stint0.GetIndex() << endl << endl;

	// assign stint0 to stint1
	cout << "\nAssign stint0 to stint1:\n";
	Stack<int, stack_size> stint1;
	stint1 = stint0;
	cout << "\nstint1 size: " << stint1.Size() << endl;
	cout << "stint1 m_index: " << stint1.GetIndex() << endl << endl;

	// push pseudo random integer values onto stint1
	cout << "\nPush random int values onto stint1\n";
	for (int i = 0; i < stack_size; i++)
	{
		stint1.push(rand() % 10);
		cout << "stint1 m_index: " << stint1.GetIndex() << endl;
	}	

	// create OutOfBoundsException
	cout << "\nCreate OutOfBoundsException: push random int value onto stint1\n";
	try { stint1.push(rand() % 10); }
	catch (StackException& error_msg) { cout << error_msg.GetMessage() << endl; }
	//catch (ArrayException& error_msg) { cout << error_msg.GetMessage() << endl; }
	cout << "stint1 m_index: " << stint1.GetIndex() << endl << endl;
		
	// copy stint1 to stint2
	cout << "\nCopy stint1 to stint2" << endl;
	Stack<int, stack_size> stint2(stint1);
	cout << "\nstint2 size: " << stint2.Size() << endl;
	cout << "stint2 m_index: " << stint2.GetIndex() << endl << endl;

	// assign stint2 to stint3
	cout << "\nAssign stint2 to stint3" << endl;
	Stack<int, stack_size> stint3 = stint2;
	cout << "\nstint3 size: " << stint3.Size() << endl;
	cout << "stint3 m_index: " << stint3.GetIndex() << endl << endl;

	// create OutOfBoundsException
	cout << "\nCreate OutOfBoundsException:\n";
	cout << "\nstint3 m_index: " << stint3.GetIndex() << endl;
	cout << "\nPush random int value onto stint3\n";
	try { stint3.push(rand() % 10); }
	catch (StackException& error_msg) { cout << error_msg.GetMessage() << endl; }
	cout << "stint3 m_index: " << stint3.GetIndex() << endl << endl;

	// try push again
	cout << "\nCreate OutOfBoundsException:\n";
	cout << "\nstint3 m_index: " << stint3.GetIndex() << endl;
	cout << "\nPush random int value onto stint3\n";
	try { stint3.push(rand() % 10); }
	catch (StackException& error_msg) { cout << error_msg.GetMessage() << endl; }
	cout << "stint3 m_index: " << stint3.GetIndex() << endl << endl;

	// pop elements off of stint3
	cout << "\nPop elements off of stint3 until we create an Array exception:\n";
	int pop0;
	for (int i = 0; i < stack_size; i++)
	{
		pop0 = stint3.pop();
		cout << "pop0: " << pop0 << endl;
		cout << "stint3 m_index: " << stint3.GetIndex() << endl << endl;
	}
		
	// create OutOfBoundsException
	cout << "\nCreate OutOfBoundsException: pop stint3\n";
	try { pop0 = stint3.pop(); }
	catch (StackException& error_msg) { cout << error_msg.GetMessage() << endl; }
	cout << "stint3 m_index: " << stint3.GetIndex() << endl;

	// pop once more for good measure
	cout << "\nCreate OutOfBoundsException: pop stint3\n";
	try { pop0 = stint3.pop(); }
	catch (StackException& error_msg) { cout << error_msg.GetMessage() << endl; }
	cout << "stint3 m_index: " << stint3.GetIndex() << endl;
	
	
	cout << "\n\n"
		<< "|============================|\n"
		<< "|     STACK & POINTARRAY:    |\n"
		<< "|============================|\n\n";
	
	// Stack and PointArray: push() / pop()
	// create Point Stack
	cout << "\nCreate Point Stack:\n";
	Stack<Point, stack_size> stpt0;
	cout << "\nstpt0 size: " << stpt0.Size() << endl;
	cout << "stpt0 m_index: " << stpt0.GetIndex() << endl << endl;

	cout << "\nCreate and set Points for PointArray to push onto stpt0:\n";
	PointArray parr0(stack_size);
	for (int i = 0; i < stack_size; i++)
	{
		parr0[i] = Point{ 0.5 * (rand() % 10), 1.15 * (rand() % 10) };
		cout << "parr0[" << i << "]: " << parr0[i] << endl;
	}

	// push Points stored in PointArray parr0 onto Stack stpt0
	cout << "\nPush parr0 onto stpt0:\n"
		<< "stpt0 m_index: " << stpt0.GetIndex() << endl;
	for (int i = 0; i < stack_size; i++)
	{
		cout << "\nPushing: " << parr0[i] << "..." << endl;
		stpt0.push(parr0[i]);
		cout << "stpt0 m_current: " << stpt0.GetIndex() << endl;
	}
	*/

	// STL algorithm copy()
	cout << "\nCreate vector of Points:\n";
	vector<int> vpt0[7];
	int myints[] = { 10,20,30,40,50,60,70 };
	//Array<Point> parr0(stack_size);
	//for (int i = 0; i < stack_size; i++)
	//{
		//parr0[i] = Point{ 0.5 * (rand() % 10), 1.15 * (rand() % 10) };
		//cout << "parr0[" << i << "]: " << parr0[i] << endl;
	//}
	copy(myints, myints+7, vpt0->begin());

	// set cout to print vector info
	//cout << "\nSet ostream_iterator to print vector info:\n";
	//ostream_iterator<int, char> out_iter(cout, " ");

	// print vpt0 info
	cout << "\nvpt0 has:\n";
	for (auto pt : vpt0) cout << endl;
	//copy(vpt0->begin(), vpt0->end(), out_iter);
	cout << endl;
	//copy(parr0, parr0 + stack_size, vpt0->begin());
	// print vtp0
	//for (auto pt : vpt0) cout << endl;
	//cout << vpt0[0] << endl;
	

	/*
	// create OutOfBoundsException
	cout << "\nCreate OutOfBoundsException: push another Point onto stpt0:\n";
	try { stpt0.push(Point()); }
	catch (StackException& error_msg) { cout << error_msg.GetMessage() << endl; }
	cout << "stpt0 m_index: " << stpt0.GetIndex() << endl << endl;

	// pop Points off of stpt0
	cout << "\nPop Points off of stpt0:\n"
		<< "stpt0 m_index: " << stpt0.GetIndex() << endl;
	for (int i = 0; i < stack_size; i++)
	{
		cout << "\nPopping: " << stpt0.pop() << "..." << endl;
		cout << "stpt0 m_current: " << stpt0.GetIndex() << endl;
	}
	
	// create OutOfBoundsException
	cout << "\nCreate OutOfBoundsException: pop one more time\n";
	try { Point p = stpt0.pop(); }	
	catch (StackException& error_msg) { cout << error_msg.GetMessage() << endl; }
	cout << "stpt0 m_index: " << stpt0.GetIndex() << endl;

	cout << endl;

	
	cout << "\n\n"
		<< "|============================|\n"
		<< "|      TEMPLATE ARRAYS       |\n"
		<< "|============================|\n\n";

	// Create intArray1, intArray2, doubleArray
	// use Array Template Class default constructor"
	try
	{
		cout << "Step 1a:\nCreate an int Array, double Array, int NumericArray, and double NumericArray:\n"
			<< "Use default constructor:\n\n";
		Array<int> intArr;
		Array<double> dblArr;
		NumericArray<int> intNumArr;
		NumericArray<double> dblNumArr;

		cout << "intArr DefaultSize:    " << intArr.DefaultSize() << endl
			<< "dblArr DefaultSize:    " << dblArr.DefaultSize() << endl
			<< "intNumArr DefaultSize: " << intNumArr.DefaultSize() << endl
			<< "dblNumArr DefaultSize: " << dblNumArr.DefaultSize() << endl;

		cout << "\nStep 1b:\nSet DefaultSize for all Arrays and NumArrays to 3:\n";
		arr_size = 3;
		intArr.DefaultSize(arr_size);
		dblArr.DefaultSize(arr_size);
		intNumArr.DefaultSize(arr_size);
		dblNumArr.DefaultSize(arr_size);
		
		cout << "intArr DefaultSize:    " << intArr.DefaultSize() << endl
			<< "dblArr DefaultSize:    " << dblArr.DefaultSize() << endl
			<< "intNumArr DefaultSize: " << intNumArr.DefaultSize() << endl
			<< "dblNumArr DefaultSize: " << dblNumArr.DefaultSize() << endl;
		

		cout << "\nStep 2:\nCreate new Arrays and NumericArrays with new DefaultSize 3:\n";
		Array<int> intArr0;
		Array<double> dblArr0;
		NumericArray<int> intNumArr0;
		NumericArray<double> dblNumArr0;

		cout << "intArr0 DefaultSize:    " << intArr0.DefaultSize() << endl
			<< "dblArr0 DefaultSize:    " << dblArr0.DefaultSize() << endl
			<< "intNumArr0 DefaultSize: " << intNumArr0.DefaultSize() << endl
			<< "dblNumArr0 DefaultSize: " << dblNumArr0.DefaultSize() << endl;

		// Array<TArray> Tests
		// set values for intArr0
		cout << "Step 3a:\nSet element values for intArr0\n";
		for (int i = 0; i < intArr0.Size(); i++)
		{
			intArr0[i] = rand() % 10;
			cout << "intArr0[" << i << "]: " << intArr0[i] << endl;
		}

		// copy intArr0 to intArr1
		cout << "\nStep 3b:\nCreate new intArr1: use copy constructor to copy intArr0:\n";
		Array<int> intArr1(intArr0);
		for (int i = 0; i < intArr1.Size(); i++)
		{
			cout << "intArr1[" << i << "]: " << intArr1.GetElement(i) << endl;
		}

		// assign intArr1 to new intArr2
		cout << "\nStep 3c:\nCreate new intArr2: assign intArr0 to intArr1:\n";
		Array<int> intArr2 = intArr1;
		for (int i = 0; i < intArr1.Size(); i++)
		{
			cout << "intArr2[" << i << "]: " << intArr2.GetElement(i) << endl;
		}
		
		
		// NumericArray<TNum> Tests
		// set values for intNumArr0
		cout << "\nStep 4a:\nSet element values for intNumArr0\n";
		for (int i = 0; i < intNumArr0.Size(); i++)
		{
			intNumArr0[i] = rand() % 10;
			cout << "intNumArray0[" << i << "]: " << intNumArr0.GetElement(i) << endl;
		}

		// create and set values for new intNumArr1
		cout << "\nStep 4b:\nCreate new intNumArr1, and set values:\n";
		NumericArray<int> intNumArr1;
		for (int i = 0; i < intNumArr1.Size(); i++)
		{
			intNumArr1.SetElement((rand() % 10), i);
			cout << "intNumArray1[" << i << "]: " << intNumArr1[i] << endl;
		}

		// assign intNumArr1 to new intNumArr2
		cout << "\nStep 4c:\nAssign intNumArr1 to new intNumArr2:\n";
		NumericArray<int> intNumArr2 = intNumArr1;
		for (int i = 0; i < intNumArr2.Size(); i++)
		{
			cout << "intNumArr2[" << i << "]: " << intNumArr2[i] << endl;
		}

		// create new intNumArr3 from addition of intNumArr0 and intNumArr1
		cout << "\nStep 4d:\nCreate new intNumArr3, and set = intNumArr0 + intNumArr1:\n";
		NumericArray<int> intNumArr3 = intNumArr0 + intNumArr1;
		for (int i = 0; i < intNumArr3.Size(); i++)
		{
			cout << "intNumArr3[" << i << "]: " << intNumArr3[i] << endl;
		}

		// assign scaled intNumArr3 to new intNumArr4
		cout << "\nStep 4e:\nCreate new intNumArr4, and assign intNumArr3 * 3 to intNumArr4:\n";
		NumericArray<int> intNumArr4 = intNumArr3 * 3;
		for (int i = 0; i < intNumArr4.Size(); i++)
		{
			cout << "intNumArr4[" << i << "]: " << intNumArr4[i] << endl;
		}

		// copy intNumArr4 to new intNumArr5
		cout << "\nStep 4f:\nCreate new intNumArr5: use copy constructor, copy intNumArr4:\n";
		NumericArray<int> intNumArr5(intNumArr4);
		for (int i = 0; i < intNumArr5.Size(); i++)
		{
			cout << "intNumArr5[" << i << "]: " << intNumArr5[i] << endl;
		}

		// create new intNumArr6 of size 5, and set values
		cout << "\nStep 5a:\nCreate new intNumArr6 of size 5, set values:\n";
		arr_size = 5;
		NumericArray<int> intNumArr6(arr_size);
		for (int i = 0; i < intNumArr6.Size(); i++)
		{
			intNumArr6.SetElement((rand() % 10), i);
			cout << "intNumArr6[" << i << "]: " << intNumArr6[i] << endl;
		}

		// try to add intNumArr0 and intNumArr6
		cout << "\nStep 5b:\nSet intNumArr2 = intNumArr0 + intNumArr6:\n";
		intNumArr2 = intNumArr0 + intNumArr6;
	}
	catch (ArrayException& error_msg)
	{
		cout << error_msg.GetMessage() << endl;
	}
	
	
	try
	{
		// OutOfBoundsException Tests
		cout << "\nStep 6a:\nCreate intNumArr10, set values:\n";
		NumericArray<int> intNumArr10;
		for (int i = 0; i < intNumArr10.Size(); i++)
		{
			intNumArr10[i] = rand() % 10;
			cout << "intNumArray10[" << i << "]: " << intNumArr10.GetElement(i) << endl;
		}

		cout << "\nStep 6b:\nSet intNumArr10[10] to 10:\n";
		intNumArr10[10] = 10;

		cout << endl;
	}
	catch (ArrayException& error_msg)
	{
		cout << error_msg.GetMessage() << endl;
	}

	cout << "\nStep 7a:\nCreate new intNumArr11 and intNumArr12:\n";
	NumericArray<int> intNumArr11(3);
	NumericArray<int> intNumArr12(3);
	cout << "\nSet values to intNumArr11 and intNumArr12:\n";
	for (int i = 0; i < intNumArr11.Size(); i++)
	{
		intNumArr11[i] = rand() % 10;
		intNumArr12[i] = rand() % 10;
		cout << "intNumArray11[" << i << "]: " << intNumArr11.GetElement(i) << endl;
		cout << "intNumArray12[" << i << "]: " << intNumArr12.GetElement(i) << endl;
	}

	cout << "\nStep 7b:\nCalculate the dot product of intNumArr11 and intNumArr12:\n";
	int dot_prod = intNumArr11.DotProd(intNumArr12);
	cout << "Dot Product of intNumArr11 and intNumArr12 = " << dot_prod << endl;
	
	
	// more Array tests
	cout << "Testing Array, NumericArray and PointArray\n";

	// create Array and populate
	cout << "Create Array, arr0, with 3 elements:\n";
	arr_size = 3;
	Array<Point> arr0(arr_size);
	for (int i = 0; i < arr_size; i++)
	{
		arr0[i] = Point(i * 2.2, i * 1.5);
		cout << "arr0[" << i << "]: " << arr0[i].ToString() << endl;
	}
	cout << "\n";

	Point P0{ 2, 3 };


	// create NumericArray and populate
	cout << "Create NumericArray, numarr0, with 3 elements:\n";
	arr_size = 3;
	NumericArray<Point> numarr0(arr_size);
	for (int i = 0; i < arr_size; i++)
	{
		numarr0[i] = Point(rand() % 10, rand() % 10);
		cout << "numarr0[" << i << "]: " << numarr0[i].ToString() << endl;
	}
	cout << "\n";

		
	// create PointArray and populate
	cout << "Create PointArray, parr0, with 3 elements:\n";
	arr_size = 3;
	PointArray parr10(arr_size);
	for (int i = 0; i < arr_size; i++)
	{
		parr10[i] = Point(rand() % 10, rand() % 10);
		cout << "parr10[" << i << "]: " << parr10[i].ToString() << endl;
	}
	cout << "\n";	

	*/


	return 0;
}
