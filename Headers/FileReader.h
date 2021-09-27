#pragma once
#include<iostream>
class FileReader {
	std::string filename;
	std::unique_ptr<FILE> file{ nullptr };
public:
	unsigned long long size();
	FileReader() = delete;
	FileReader(std::string filename_);
	FileReader(const FileReader& copy) = delete;
	FileReader(FileReader&& copy) = delete;
	~FileReader();
	std::unique_ptr<unsigned char[]> GetBytes();
};

//waw h