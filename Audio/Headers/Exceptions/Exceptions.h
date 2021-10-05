#pragma once
#include<exception>
class Exception :public std::exception {
	const char* What;
public:
	Exception(const char* message);
	~Exception();
	 const char* what();
};