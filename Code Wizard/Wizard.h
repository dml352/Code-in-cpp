/**
Header file.
Wizard class will generate C++ header files and source files, given the class name
@Author: Duc Minh Le
@Date: 2/12/2015
@Version One
***/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Wizard
{
private:
	string className;
	string author, dateCreated, version;
	vector<string> variableName, variableType, headerFile;
public:
	//Constructor
	Wizard();
	Wizard(const Wizard & mirror);
	Wizard(string className, string author, string dateCreated, string version);
	Wizard(string className, vector<string> variableName, vector<string> variableType, string author,
			string dateCreated, string version, vector<string> header);
	Wizard(string inputFile);

	//Inspector
	string getClassName();
	vector<string> getVariableName();
	vector<string> getVariableType();
	string getVariable(int i);

	//Mutator
	void setClassName(string name);
	void addVariable(string variableName, string variableType);
	void addHeaderFile(string fileName);

	//Destructor
	~Wizard();

	//Facilitator
	string copyrightComment();
	void headerOutput(string outputFile);
	void sourceOutput(string outputFile);


};