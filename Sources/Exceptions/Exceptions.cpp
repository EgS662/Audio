#include "..\..\Headers\Exceptions\Exceptions.h"
#include<cstring>
Exception::Exception(const char* message, const char* type_) :std::exception{ message }, What{ new char[strlen(message) + 1]{} }, type{ type_ } {
	type.append(" ");
	type.append(message);
}
Exception::~Exception()
{
	delete[] What;
}
const char* Exception::what()
{
	return type.c_str();
}
//const in clas in