#pragma once
#include <iostream>
#include <exception>
#include <string>
#include "ErrorTypes.h"

using namespace std;

class Exception : public exception
{
public:
	Exception(int type, string extraMsg1 = " ");
	const char* what() const throw();
	const int GetErrorType() const;
private:
	string errorMsg;
	int errorType;
	ErrorTypes err;
};