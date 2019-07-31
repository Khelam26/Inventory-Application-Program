// Inventory Application Program 
// Creates an array of 100 Inventory Item objects and support the some interactive command
// By Khelan Modi
// Created on July 10th, 2019. 

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>
#include "InventoryItems.h" 
// Header file that has a inventory Class, consisting of a int, a double, and a string 
using namespace std;

const string DELIMITER = "|"; // Global constants for the delimiters that are found in the file
const int SIZE = 100; // Maximum size of the array

void quitProgram(int exitStatus); // quits the program
void printHelpMenu(); // Prints Command help menu
int splitLineToArray(string inputText, string DELIMITER,
	string outputFieldArray[]); // Store each datafield in an indiviual array element, separated by the delimiter
int getOuputFile(string& outputFilename, ofstream& outFile, InventoryItems[], int lineCount);
// Validates the name of the output file and then prints data to a file

int getInputFile(string& inputFilename, ifstream& inFile, InventoryItems item[], int lineCount);
// validates the input file and extracts data from it

void printInventoryList(InventoryItems item[], int lineCount);
// prints the data that is stored in the inventory class object

void addItem(InventoryItems item[], int lineCount);
// adds quantity to the object, cannot exceed 30

int newInventoryItem(InventoryItems item[], int lineCount);
// Adds a new item to the object, quanity of items cannot exceed 30

int removeParts(InventoryItems item[], int lineCount);
// removes quantity from the object, quantity cannot become negative

int main() {

	string command, inputFilename, outputFilename;
	ifstream inFile; // Input file for extracting data from it
	ofstream outFile; // prints data to an output file.
	InventoryItems item[SIZE]; // class object, default constructor store 0 in units, 0.0 in cost and a blank string in description
	int lineCount = 0, // lines read from the file
		recordsLoaded; // total no of records loaded in the array(cannot exceed 100)

	system("color 3f");
	system("title Project 3 - Inventory Application Program By Khelan");

	printHelpMenu();

	while (true) {

		// initial prompt 
		cout << "Command: ";
		getline(cin, command);

		if (command == "a" || command == "A") {
			addItem(item, lineCount); // Adds quantity to the existing item in the object
		}
		else if (command == "h" || command == "H") {
			printHelpMenu(); // prints the help menu on the screen
		}
		else if (command == "i" || command == "I") {
			recordsLoaded = getInputFile(inputFilename, inFile, item, lineCount); // elements read from the file
			lineCount += recordsLoaded; // total elements loaded in the array

										// prints the statistic 
			cout << recordsLoaded << " records loaded to array.\n";
			cout << "Total Records in the array: " << lineCount << endl << endl;

			if (lineCount > SIZE) // total array must not exceed 100, i.e. the maximum size of the array
				cout << "The maximum size of the array is " << SIZE << endl
				<< "You Cannot add anymore than that.\n";

			inFile.close(); // closing the input file
		}
		else if (command == "p" || command == "P") {
			printInventoryList(item, lineCount); // prints the contents of the object
			cout << lineCount << " records.\n";
		}
		else if (command == "n" || command == "N") {
			// new inventory item
			// adds a new item to the object
			// returns the linecount of where the object was stored
			lineCount = newInventoryItem(item, lineCount);

			cout << "Announcing a new inventory item: " << item[lineCount].getDescription() << endl;
			// prints the total elements in the array
			cout << "We now have " << lineCount << " different inventory items in stock!\n";
		}
		else if (command == "o" || command == "O") {
			// prints data to an output file
			// returns the number of elements that were written to the file
			lineCount = getOuputFile(outputFilename, outFile, item, lineCount);
			cout << lineCount << " records written to a file.\n";

			outFile.close(); // closing the output file after use
		}
		else if (command == "q" || command == "Q") {
			// ENDs the program 
			quitProgram(0);
		}
		else if (command == "r" || command == "R") {
			// returns the total number of elements that are stored in the array
			lineCount = removeParts(item, lineCount); // removes specified number of parts from the object.
		}
		else // Prompts the user to enter a valid command
			cout << "Invalid Command. Try another ";
	}
	return 0;
	system("pause");
}


/*=============================================================================
*	Function:	quitProgram  -	 Exit the program, returning status from caller
*
*  Inputs:
*      exitStatus =         Exit code to be returned to operating system.
*
*  Outputs:
*      exits the program, passing status value from caller
*
*
*  Desciption:
*		Exit the program
*
*---------------------------------------------------------------------------*/
void quitProgram(int exitStatus)
{
	cout << "Exitting program with status = " << exitStatus << endl;
	system("pause");
	exit(exitStatus);

} // (end function 'quitProgram')

// =========================================================================================================
// *Function: printHelpMenu - Prints the help Menu / Commands that are supported by the program
// *Inputs: none
// *Outputs: none
// *Desciption:
//			Commands that are supported by the program, either lowercase or uppercase is valid
//			Each command is unique and has its own function
// =========================================================================================================
void printHelpMenu() {

	cout
		<< "\n\t a               Add parts.           "
		<< "\n\t h               print Help text.     "
		<< "\n\t i               Input inventory data from a file.      "
		<< "\n\t p               Print inventory list.  "
		<< "\n\t n               New inventory Item. "
		<< "\n\t o               Output inventory data to a file.  "
		<< "\n\t q               quit (end the program)."
		<< "\n\t r               Remove parts.\n\n";
}

// =========================================================================================================
// *Function: addItem - Adds the quantity to the existing array object 
// *Inputs: Inventory class object, passed as a array
//			lineCount, total number of lines that are read into the array
// *Outputs: none
// *Desciption:
//			Starting at the beginning, it prompts the user to enter the item index nunmber
//			validates if the index number is between the lineCount and 0
//			Asks the quantity that they want to the list
//			program validates that the quantity does not  exceed 30
//			if not then it adds the quantity to the unit member function of the object array
// =========================================================================================================
void addItem(InventoryItems item[], int lineCount) {

	int itemNumber,		// index number for adding the quantity
		additionalParts, // parts to add
		unitsInArray; // units that is already in the array.

	cout << " Choose a Item Number: ";
	cin >> itemNumber;
	cin.ignore(100, '\n');

	while (!(itemNumber < lineCount && itemNumber >= 0)) {
		cout << itemNumber << " is not a valid item Number.";
		cout << " Choose a Item Number: ";
		cin >> itemNumber;
		cin.ignore(100, '\n');
	}
	unitsInArray = item[itemNumber].getUnits();

	cout << " How many parts to add? ";
	cin >> additionalParts;
	cin.ignore(100, '\n');

	while ((unitsInArray + additionalParts) > 30)
	{
		cout << "\n\aERROR: The item can only hold 30 parts.\n";
		cout << " How many parts to add? ";
		cin >> additionalParts;
		cin.ignore(100, '\n');
	}
	unitsInArray += additionalParts;
	item[itemNumber].setUnits(unitsInArray);
}

// =========================================================================================================
// *Function: printInventoryItem - Prints the content of the array
// *Inputs: Inventory class obejct, passed as a array
//			lineCount, total number of lines that are read into the array
// *Outputs: none
// *Desciption:
//			Starting at the beginning are all the titles of the different sections that are in the array
//			The contents of the array are printed on each line with the use of for loop(which iterates till the last element has been read)
//			the stream manipulators are used to print the data in a readable manner
// =========================================================================================================
void printInventoryList(InventoryItems item[], int lineCount) {

	cout << setw(5) << "\nItem Num\t\t"				// Titles 
		<< left << setw(50) << " Description "
		<< setw(10) << " Cost "
		<< setw(10) << " Quantity"

		<< setw(4) << "\n_________\t\t"
		<< setw(30) << "_____________\t\t\t"
		<< setw(4) << "\t  ______"
		<< setw(4) << "    _________\n";

	for (int x = 0; x < lineCount; x++) {
		cout << setw(5) << right << x << "\t\t\t"
			<< left << setw(50) << item[x].getDescription() << " "
			<< setw(10) << showpoint << fixed << setprecision(2) << item[x].getCost() << " "
			<< setw(10) << item[x].getUnits() << endl;
	}
	cout << endl;
}

//*****************************************************************************************************
// Function that asks the user to enter a valid file name, if it fails to open
// displays a error message and asking the user to enter a valid file name again
// does not return anything, takes two reference variables so that it can passed to a process array function
//*****************************************************************************************************
int getInputFile(string& inputFilename, ifstream& inFile, InventoryItems item[], int lineCount) {

	string
		stringCost, // data field that consists of cost
		stringUnits, // data field that consists of the unit
		description,  // Description data field 
		dataArray[SIZE], // string array that has a maximum size of 100
		dataField; // string that is between two delimiter

	int units,
		fieldCount,       // Fields in the array, which are separated by the delimiter
		recordsLoaded = 0;  // elements loaded in the array, cannot exceed 100

	double cost;		  // The cost of the item	

	cout << "Enter name of the input file: ";
	getline(cin, inputFilename);
	inFile.open(inputFilename); // Opens the file name, entered by the user

	while (inFile.fail()) // if the user enters a invalid filename
	{
		cout << "\a\n\t Cannot Open File. ";
		cout << "\n\nValid FileNames are: "
			<< "\n\t electrical.txt"
			<< "\n\t fastners.txt"
			<< "\n\t miscellaneous.txt"
			<< "\n\t plumbing.txt \nEnter name of a VALID input file: ";

		getline(cin, inputFilename);
		inFile.open(inputFilename);
	}

	while (getline(inFile, dataField) && lineCount < SIZE) // Runs until the end of the file has been encountered
	{
		fieldCount = splitLineToArray(dataField, DELIMITER, dataArray); // the value of field count is returned from the function
																		//This function also separates each data field.

		description = dataArray[fieldCount - 3]; // data that is between the 2nd and 3rd delimiter
		item[lineCount].setDescription(description); // store the value in object description member function

		stringCost = dataArray[fieldCount - 2]; // data between 3rd and 4th delimiter 
		cost = stof(stringCost); // converts sting into floating point number
		item[lineCount].setCost(cost); // stores it in the object cost member function

		stringUnits = dataArray[fieldCount - 1]; // data that is in the last data field
		units = stoi(stringUnits); // converts string to int
		item[lineCount].setUnits(units); // stores in unit member function

		lineCount++; // increments the line count, total lines read into the array
		recordsLoaded++; // number of elements recorded in the array
	}
	return recordsLoaded;
}// end of getinputfile function

 //*****************************************************************************************************
 // Function that asks the user to enter a valid file name, if it fails to open
 // displays a error message and asking the user to enter a valid file name again
 // does not return anything, takes two reference variables so that it can passed to a process array function
 //*****************************************************************************************************
int getOuputFile(string& outputFilename, ofstream& outFile, InventoryItems item[], int lineCount) {

	cout << "Enter name of the output file: ";
	getline(cin, outputFilename);
	outFile.open(outputFilename);

	while (outFile.fail())
	{
		cout << "\a\n\t Cannot Open File. Enter name of a VALID Output file: ";
		getline(cin, outputFilename);
		outFile.open(outputFilename);
	}
	// prints the data to a file, separated by the delimiter
	// Goes over the loop untill the last data is printed
	for (int x = 0; x < lineCount; x++) {
		outFile << x << DELIMITER << item[x].getDescription() << DELIMITER << item[x].getCost() << DELIMITER << item[x].getUnits() << endl;
	}
	return lineCount;
}// end of getOutputFile function

 // =========================================================================================================
 // *Function: splitLineToArray - Scan through one line of text, output fields to array.
 // *Inputs: inputText =  string containing one line of text.
 //          inputDelim = string containing the delimiter character (separates one data field from the next).
 //          maxFields =  Maximum number of fields
 // *Outputs: returns the number of fields found.
 //           outputFieldArray[] = array of strings containing output fields
 // *Desciption:
 //      Starting at the beginning of the inputText string, scan for each
 //      occurrence of the inputDelimiter character/string.  The first data field begins
 //      at the starting position and ends at the position before the delimiter
 //      character.
 //      The SECOND data field begins at the position AFTER the delimiter, and
 //      extends to the position before the NEXT ocurrence of the delimiter.
 //      If no delimiter is found, the the current data field extends to the
 //      end of the line.
 // =========================================================================================================

int splitLineToArray(string inputText, string inputDelim,
	string outputFieldArray[])
{
	//	Local Variables:
	int nextFieldPosition = 0;		//	Start position of data field.
	int foundPosition;				//  Position where delimiter was found,
	int fieldCount = 0;		        //  Number of data fields found so far,
	bool endOfLine = false;			//	Flag -- end of input line detected,
	string dataField;				//  Copy of the data field.


	while (!endOfLine)
	{
		foundPosition = inputText.find(inputDelim, nextFieldPosition);
		if (foundPosition == -1)
		{
			// (Here if the string 'find' function reached the end of the input string.)
			endOfLine = true;

			foundPosition = inputText.length();

			if (foundPosition > nextFieldPosition)
			{
				dataField = inputText.substr(nextFieldPosition,
					foundPosition - nextFieldPosition);

				fieldCount++;
			}
		}
		else
		{
			// (Here if 'inputDelim' was found in the input string.)
			// Copy the data field contents from the input string to the
			// 'dataField' local variable.
			dataField = inputText.substr(nextFieldPosition, foundPosition - nextFieldPosition);
			fieldCount++;

			// Adjust 'nextFieldPosition' as preparation for finding NEXT delimiter.
			nextFieldPosition = foundPosition + 1;
		}

		if (fieldCount > 0)
		{
			if (fieldCount > SIZE)
			{
				cout << "ERROR at line __LINE__: too many input fields, fieldCount="
					<< fieldCount << endl;
			}
			else
			{
				outputFieldArray[fieldCount - 1] = dataField;
			}
		}
	}// (end while)
	return fieldCount;
} // (end function splitLineToArray )

  // =========================================================================================================
  // *Function: newInventoryItem - Adds new item to the inventory list.
  // *Inputs: item - a class object of the InventoryItem class, passed an array
  //			linecount - index of the data thats in the array
  // *Outputs: the updated line count
  // *Desciption:
  //		Starting at the beginning, it asks the user for the description of the item
  //      Asks for the unit cost of the product, validates if it is greater than 0
  //		Prompts the user to enter the intial quantity, which cannot be more than 30 and less than 0
  //		After all the valid inputs have been entered, it is stored in the class object by calling the mutator functions
  //		updates the line count, then returns to the main function
  // =========================================================================================================
int newInventoryItem(InventoryItems item[], int lineCount)
{
	string description;
	double cost;
	int units;

	cout << "Enter description for new item: ";
	getline(cin, description);

	cout << "Enter unit cost for new item: ";
	cin >> cost;
	cin.ignore(100, '\n');

	while (cost < 0.0) {
		cout << "\aERROR: cost must be a positive number.\n";

		cout << "Enter unit cost for new item: ";
		cin >> cost;
		cin.ignore(100, '\n');
	}

	cout << "Enter initial quantity for the new item: ";
	cin >> units;
	cin.ignore(100, '\n');

	while (units < 0 || units > 30) {
		cout << "ERROR: initial quantity must be >= zero and <= 30.\n";
		cout << "Enter initial quantity for the new item: ";
		cin >> units;
		cin.ignore(100, '\n');
	}

	item[lineCount].setCost(cost);
	item[lineCount].setDescription(description);
	item[lineCount].setUnits(units);

	lineCount++;

	return lineCount;
} // end of newInventoryitem

  // =========================================================================================================
  // *Function: removeParts - removes specified number of parts from the object.
  //  *Inputs: item - a class object of the InventoryItem class, passed an array
  //			linecount - index of the data thats in the array
  // *Outputs: the updated line count
  // *Desciption:
  //      Ask the user for the index number of the item
  //		Prompts the user to enter number of quantity to be removed. 
  //		It should be less than the parts that the inventory current holds.
  //		after the valid input, it updates the object by simply substracting the parts to remove from the existing parts
  //		Mutator function is used to set the value of new unit member function
  // =========================================================================================================

int removeParts(InventoryItems item[], int lineCount) {

	int itemNumber,  // the index number of the item 
		partsToRemove; // number of parts to remove

	cout << "\nChoose a item Number: ";
	cin >> itemNumber;
	cin.ignore(100, '\n');

	cout << "How many parts to remove? ";
	cin >> partsToRemove;
	cin.ignore(100, '\n');

	while (partsToRemove > item[itemNumber].getUnits())
	{
		cout << "ERROR: You are attempting to remove more parts than the inventory currently holds.\n";
		return lineCount;
	}

	item[itemNumber].setUnits(item[itemNumber].getUnits() - partsToRemove);

	return lineCount;
}// end of removeParts function

 //================================================================================================================================
 /*											 "InventoryItem.h"  HEADER FILE CODE
 ==================================================================================================================================

 #ifndef INVENTORY_ITEMS_H
 #define INVENTORY_ITEMS_H
 #include<iostream>
 #include <string>
 using namespace std;

 class InventoryItems {
 private:
 string description;
 int units;
 double cost;
 public:
 InventoryItems() {
 description = "";
 units = 0;
 cost = 0.0;
 }

 InventoryItems(string desc)
 {
 description = desc;
 cost = 0.0;
 units = 0;
 }

 InventoryItems(string d, double c, int u) {
 description = d;
 units = u;
 cost = c;
 }

 void setDescription(string d) {
 description = d;
 }
 void setCost(double u) {
 cost = u;
 }
 void setUnits(int u) {
 units = u;
 }

 string getDescription()const {
 return description;
 }
 double getCost() const{
 return cost;
 }
 int getUnits() const {
 return units;
 }

 };

 #endif // !INVENTORY_ITEMS_H
 #pragma once

 */