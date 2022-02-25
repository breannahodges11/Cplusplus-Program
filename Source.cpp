#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

//this function is used to read a file and output a list
void ReadFile(string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonFile");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

// this function searches a product and returns the number of times it was bought
int SelectItem(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());
	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());
	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;

	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	Py_DECREF(pModule);
	Py_Finalize();

	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}
// this function creates a new file and writes the contents of the products list to it
void CreateFile(string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonFile");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

// displays the menu and the menu options
void MenuDisplay() {
	cout << "\x1b[36m|===============================================================================|" << endl;
	cout << "\x1b[36m|                        Welcome to the Corner Grocer!                          \x1b[36m|" << endl;
	cout << "|                                                                               |" << endl;
	cout << "|===============================================================================|" << endl;
	cout << "|                             MENU SELECTION OPTIONS                            |" << endl;
	cout << "|===============================================================================|" << endl;
	cout << "|                                                                               |" << endl;
	cout << "|                      (1) All Purchased Items                                  |" << endl;
	cout << "|                      (2) Search For a Specific Item                           |" << endl;
	cout << "|                      (3) Create a File and Histogram For All Items            |" << endl;
	cout << "|                      (4) Exit the Program                                     |" << endl;
	cout << "|                                                                               |" << endl;
	cout << "|===============================================================================|\x1b[97m" << endl;
}
// takes a user input for the menu options and calls a function based off that input
void MenuInput() {
	// declared variables
	int userInput = 0;
	int itemAmount = 0;
	string selectedItem;
	ifstream fileInput;
	string item;
	int amount = 0;
	int padding = 0;
	bool exitLoop;
	// do while loop used to run the menu until a valid input is given
	do {
		system("cls"); // clears the screen
		MenuDisplay(); // calls the menu display function
		cout << "ENTER YOUR SELECTION: "; // prompts the user for input
		exitLoop = false; // sets valid input to false to keep loop running 
		cin >> userInput; // gets user input
		cin.clear(); // clears the input stream
		cin.ignore(INT_MAX, '\n'); // ignores the remainder of the stream 
		// switch statement used to validate user input
		switch (userInput) {
		case 1: // calls the ReadFile function to display the file from python
			system("cls");
			cout << "\x1b[96m";
			ReadFile("CountAll");
			system("pause");
			break;
		case 2: // calls the SelectItem function
			system("cls");
			cout << "What item would you like to search? ";
			std::cin >> selectedItem; //get input for function param
			if (SelectItem("CountInstances", selectedItem) != 0) { //print display and return
				cout << setfill(' ') << setw(62) << right << "\x1b[95m|=================================|" << endl;
				cout << setfill(' ') << setw(57) << right << "|  Selected Item Purchased Today  |" << endl;
				cout << setfill(' ') << setw(57) << right << "|=================================|" << endl;
				cout << setfill(' ') << setw(41) << right << "|  Item of Choice: " << setfill(' ') << setw(15) << left << selectedItem << "|" << endl;
				cout << setfill(' ') << setw(57) << right << "|---------------------------------|" << endl;
				cout << setfill(' ') << setw(57) << right << "|     ITEM      |    QUANTITY     |" << endl;
				cout << setfill(' ') << setw(57) << right << "|---------------|-----------------|" << endl;
				cout << setfill(' ') << setw(25) << right << "|  " << setfill(' ') << setw(13) << left << selectedItem << "|" << setfill(' ') << setw(9) << right << SelectItem("CountInstances", selectedItem) << "        |" << endl;
				cout << setfill(' ') << setw(62) << right << "|---------------------------------|\x1b[97m" << endl;
			}
			else {
				cout << endl;
				cout << setfill(' ') << setw(64) << right << "|==============================================|" << endl;
				cout << setfill(' ') << setw(74) << right << "|\x1b[91m        Item Has Not Been Purchased Today     \x1b[97m|" << endl;
				cout << setfill(' ') << setw(64) << right << "|==============================================|" << endl;
				cout << endl;
			}

			system("pause");
			break;
		case 3: // creates a new file in Python and then reads the file in C++
			system("cls");
			ReadFile("CollectData");
			fileInput.open("frequency.dat");
			fileInput >> selectedItem;
			fileInput >> itemAmount;
			// opens the file frequency.dat (created by the python script after selcting option 3)
			//fileInput.open("frequency.dat");
			if (!fileInput.is_open()) {
				// verifies the file is open else sends an error message
				cout << "\x1b[91mERROR: PLEASE TRY AGAIN" << endl;
			}
			else {
				// prints out a list of items purchased and the histogram if file is open
				cout << setfill(' ') << setw(62) << right << "\x1b[92m|=================================|" << endl;
				cout << setfill(' ') << setw(57) << right << "|    Items Purchased Histogram    |" << endl;
				cout << setfill(' ') << setw(57) << right << "|=================================|" << endl;
				cout << setfill(' ') << setw(57) << right << "|     ITEM      |    QUANTITY     |" << endl;
				cout << setfill(' ') << setw(57) << right << "|---------------|-----------------|" << endl;
				// iterates through the file while the stream is good and prints out the item and the amount in histogram form
				while (!fileInput.eof() && fileInput.good()) {
					fileInput >> item;
					fileInput >> amount;

					if (!fileInput.fail()) {
						cout << setfill(' ') << setw(25) << right << "|  " << setfill(' ') << setw(13) << right << item << "\x1b[92m| ";
						for (int i = 0; i < amount; ++i) {
							cout << "\x1b[33m*\x1b[92m";
						}
						padding = (17 - amount);
						cout << setfill(' ') << setw(padding) << right << "|" << endl;
					}
				}
				cout << setfill(' ') << setw(62) << right << "|---------------------------------|\x1b[97m" << endl;
			}
			fileInput.close();
			system("pause");
			break;
		case 4: // exits the program
			system("cls");
			MenuDisplay();
			cout << endl;
			cout << "\x1b[36m" << "\x1b[1m" <<     "Thank you for choosing Corner Grocer!" << endl;
			exitLoop = true;
			break;
		default: // runs if input is invalid
			cout << "\x1b[91mERROR: INPUT INVALID" << endl;
			Sleep(1000);
			break;
		}
	} while (!exitLoop); // open until case 4 is reached and exitLoop is true 
	return;
}
// starts the menu input loop
void main() {
	MenuInput();
}
