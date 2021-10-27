#pragma once
#include<string>
#include<memory>
#include<vector>
#include<fstream>
class FileWriter {
	std::string filename;
	std::ofstream file;
public:
	FileWriter() = delete;
	FileWriter(std::string Filename);
	~FileWriter();
	void WriteToFile(std::vector<unsigned char> data);
};
