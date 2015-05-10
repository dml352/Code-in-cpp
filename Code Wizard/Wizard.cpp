/**
Source file.
Wizard class will generate C++ header files and source files, given the class name
@Author: Duc Minh Le
@Date: 2/12/2015
@Version One
***/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Wizard.h"
using namespace std;


//Constructor
Wizard::Wizard()
{
	className = "";
	variableName = vector<string>();
	variableType = vector<string>();
}

Wizard::Wizard(const Wizard & mirror)
{
	className = mirror.className;
	variableName = mirror.variableName;
	variableType = mirror.variableType;
}

Wizard::Wizard(string name, string writer, string date, string vers)
{
	className = name;
	author = writer;
	dateCreated = date;
	version = vers;
}

Wizard::Wizard(string name, vector<string> variable, vector<string> type, string writer, string date, string vers, 
				vector<string> header)
{
	className = name;
	variableName = variable;
	variableType = type;
	author = writer;
	dateCreated = date;
	version = vers;
	headerFile = header;
}

Wizard::Wizard(string inputFile)
{
	ifstream readFile(inputFile);
	//read in header file
	string header;
	getline(readFile, header);
	while (header != "$$$$")
	{
		headerFile.push_back(header);
		getline(readFile, header);
	}
	getline(readFile, author);
	getline(readFile, dateCreated);
	getline(readFile, version);
	getline(readFile, className);
	string varName, varType;
	while (getline(readFile, varType, ' '))
	{
		getline(readFile, varName);
		addVariable(varName, varType);
	}
}




//Inspector
string Wizard::getClassName()
{
	return className;
}

vector<string> Wizard::getVariableName()
{
	return variableName;
}

vector<string> Wizard::getVariableType()
{
	return variableType;
}

string Wizard::getVariable(int i)
{
	return variableType[i] + " " + variableName[i];
}



//Mutator
void Wizard::setClassName(string name)
{
	className = name;
}

void Wizard::addVariable(string name, string type)
{
	variableName.push_back(name);
	variableType.push_back(type);
}

void Wizard::addHeaderFile(string fileName)
{
	headerFile.push_back(fileName);
}

//Destructor
Wizard::~Wizard()
{
	className = "";
	variableName.clear();
	variableType.clear();
}

//Facilitator
string Wizard::copyrightComment()
{
	string s = "/** \n @Author: " + author + "\n";
	s = s + "@Date created: " + dateCreated + "\n";
	s = s + "@Version: " + version + "\n";
	s = s + "This file was automatically generated by the Wizard class. \n **/ \n";
	return s;
}

void Wizard::headerOutput(string outputFile)
{
	string fileName = getClassName() + ".h";
	ofstream header(fileName);


	//comment and header sections
	header << copyrightComment();
	for (unsigned int i = 0; i < headerFile.size(); i++)
	{
		string add = "#include " + headerFile[i] + "\n";
		header << add;
	}
	header << "using namespace std;" << endl;
	header << "#ifndef _" + className + "_" << endl << "#define _" + className + "_" << endl << endl;
	header << "class " + className << "  {" << endl;

	// variables 
	header << "private: " << endl;
	for (unsigned int i = 0; i < variableName.size(); i++)
	{
		header << "\t" + getVariable(i) + ";" << endl;
	}

	// constructor
	header << "public: " << endl;
	header << "\t//Constructor" << endl;
	header << "\t" + className + "();" << endl;
	header << "\t" + className + "(const " + className + " & mirror);" << endl << endl;

	//Inspector
	header << "//Inspector" << endl;
	for (unsigned int i = 0; i < variableName.size(); i++)
	{
		header << "\t" + variableType[i] + " get" + variableName[i] + "();" << endl;
	}
	header << endl;

	//Mutator
	header << "//Mutator" << endl;
	for (unsigned int i = 0; i < variableName.size(); i++)
	{
		header << "\t void set" + variableName[i] + "(" + variableType[i] + " makeChange);" << endl;
	}
	header << endl;

	//Facilitator
	header << "//Facilitator" << endl;
	header << "string toString();" << endl << endl;

	//Destructor
	header << "//Destructor" << endl;
	header << "~" + className + "();" << endl;
	header << "};" << endl;
	header << "#endif" << endl;
}

void Wizard::sourceOutput(string outputFile)
{
	string fileName = getClassName() + ".cpp";
	ofstream source(fileName);


	//comment and header sections
	source << copyrightComment();
	for (unsigned int i = 0; i < headerFile.size(); i++)
	{
		string add = "#include " + headerFile[i] + "\n";
		source << add;
	}
	source << "#include \"" + className + ".h\"" << endl;
	source << "using namespace std;" << endl << endl;

	//Constructor
	source << "//Constructor" << endl;
	source << className + "::" + className + "()" << endl;  //default constructor
	source << "{" << endl << "}" << endl;

	source << className + "::" + className + "(const " + className + " & mirror)" << endl; // copy constructor
	source << "{" << endl;
	for (unsigned int i = 0; i < variableName.size(); i++)
	{
		source << "\t" + variableName[i] + " = mirror." + variableName[i] + ";" << endl;
	}
	source << "}" << endl;

	//Inspector
	source << "//Inspector" << endl;
	for (unsigned int i = 0; i < variableName.size(); i++)
	{
		source << "\t" + variableType[i] + " " + className + "::get" + variableName[i] + "()" << endl;
		source << "\t{" << endl;
		source << "\t\t return " + variableName[i] + ";" << endl << "\t}" << endl;
	}
	source << endl;

	//Mutator
	source << "//Mutator" << endl;
	for (unsigned int i = 0; i < variableName.size(); i++)
	{
		source << "\tvoid " + className + "::set" + variableName[i] + "(" + variableType[i] + " mirror)" << endl;
		source << "\t{" << endl;
		source << "\t\t" + variableName[i] + " = mirror;" << endl;
		source << "\t}" << endl;
	}
	source << endl;

	//Facilitator
	source << "//Facilitator" << endl;
	source << "\tstring " + className + "::toString()" << endl;
	source << "\t{" << endl;
	source << "\t return \"\";" << endl;
	source << "\t}" << endl << endl;

	//Destructor
	source << "//Destructor" << endl;
	source << className + "::~" + className + "(){};" << endl;
}