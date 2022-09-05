/*
 * Jen Nadeau
 * CS 210 
 * Module Six Assignment: Integrating Languages
 * 6/11/2022
 * Source.cpp
 */

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

int menuChoice;
int x;
int mainMenu();
int validMenuChoice();
int validIntInput();

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{
	// Do while loop to select multiplication table, double a number, or exit the program
	do
	{
		system("cls");
		mainMenu();
		switch (menuChoice)
		{
			// Multiplication table option
			case 1:
				cout << "Please enter a number you would like to create a multiplication table for: ";
				x = validIntInput();
				cout << callIntFunc("MultiplicationTable", x) << endl;
				cout << endl;
				system("PAUSE");
				break;
			// Double a value option
			case 2:
				cout << "Please enter a number you would like to double: ";
				x = validIntInput();
				cout << x << " doubled equals " << callIntFunc("DoubleValue", x) << endl;
				cout << endl;
				system("PAUSE");
				break;
			// Exit the program option
			case 3:
				break;
			// Handles input of integer not 1, 2, or 3
			default:
				cout << "Invalid selection." << endl;
				system("PAUSE");
				break;
		}

	} while (menuChoice != 3);

}

// Displays main menu 
int mainMenu()
{
	cout << "Main Menu" << endl << endl;
	cout << "1: Display a Multiplication Table" << endl;
	cout << "2: Double a Value" << endl;
	cout << "3: Exit" << endl;
	cout << "Enter your seletion as a number 1, 2, or 3: ";
	menuChoice = validMenuChoice();
	cout << endl;

	return menuChoice;
}

// User input validation to make sure input is an integer for menu choice
int validMenuChoice() {
	int x;

	while (1) {
		if (cin >> x) 
		{
			// valid number
			break;
		}
		else 
		{
			// not a valid number
			cout << "Invalid Input! Please enter 1, 2, or 3: ";
			cin.clear();
			while (cin.get() != '\n');
		}
	}

	return x;
}

// User input validation to make sure input is an integer for math function
int validIntInput() 
{
	int x;

	while (1) {
		if (cin >> x)
		{
			// valid number
			break;
		}
		else
		{
			// not a valid number
			cout << "Invalid Input! Please enter a whole number: ";
			cin.clear();
			while (cin.get() != '\n');
		}
	}

	return x;
}