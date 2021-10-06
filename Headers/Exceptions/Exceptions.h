#pragma once
#include<exception>
#include<string>
class Exception :public std::exception {
	const char* What;
	std::string type{};
public:
	Exception(const char* message,const char* type_);
	~Exception();
	 const char* what();
};