#include "..\..\Headers\Exceptions\Exceptions.h"
#include<cstring>
Exception::Exception(const char* message) :std::exception{ message }, What{ new char[strlen(message) + 1]{} } {
	
}
const char* Exception::what()
{
	return What;
}
//const in clas in