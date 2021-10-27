#include "..\Headers\FileWriter.h"
#include "Exceptions\Exceptions.h"
#include<iostream>
FileWriter::FileWriter(std::string Filename):filename{Filename},file{ filename,std::ios::out | std::ios::app | std::ios::binary }
{
	if (!file) {
		throw Exception{ "Cant open file",__FUNCTION__ };
	}
}

FileWriter::~FileWriter()
{
	//file.close();
}

void FileWriter::WriteToFile(std::vector<unsigned char> data)
{

	/*if (!file.is_open()) {
		throw Exception{ "Cant open file",__FUNCTION__ };
	}*/
	for (int i = 0; i < data.size(); i++) {
		file << data[i];
		/*file.write(reinterpret_cast<const char*>(data.data()), data.size());*/
		file.flush();
	}
	file.close();
}
//через fstream

