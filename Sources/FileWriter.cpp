#include "..\Headers\FileWriter.h"
#include "Exceptions\Exceptions.h"
#include<iostream>


FileWriter::~FileWriter()
{
	//file.close();
}

FileWriter& FileWriter::getInstance()
{
	static FileWriter instance;
	return instance;
}

void FileWriter::WriteToFile(std::string location, size_t size, std::unique_ptr<unsigned char[]> buffer)
{
	FILE* file{fopen(location.c_str(),"wb+")};
	if (file == nullptr) {
		throw Exception("Cant open file", __FUNCTION__);
	}
	fclose(file);
	file = fopen(location.c_str(), "wb+");
	fwrite(buffer.get(), sizeof(unsigned char),size,file);
	fclose(file);
	/*for (int i = 0; i < size; i++) {
		std::cout << buffer.get()[i] << " ";
	}*/
}


//через fstream

