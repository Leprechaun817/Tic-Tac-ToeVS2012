#include <iostream>
#include <exception>
#include <string>
#include "ErrorTypes.h"

using namespace std;

class Exception : public exception
{
public:
	Exception(int type, string extraMsg = " ");
	const char* what() const throw();
private:
	string errorMsg;
	ErrorTypes err;
};