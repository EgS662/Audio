#pragma once
#include<string>
#include<memory>
#include<vector>
#include<fstream>
class FileWriter {
FileWriter() = default;
public:
	~FileWriter();
	static FileWriter& getInstance();
	void WriteToFile(std::string location,size_t size,std::unique_ptr<unsigned char[]> buffer);
};
