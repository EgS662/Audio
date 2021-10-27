#pragma once
#include<iostream>
class FileReader {
	std::string filename;
	std::unique_ptr<FILE> file{ nullptr };
public:
	unsigned long long size();
	FileReader() = default;
	FileReader(std::string filename_);
	FileReader(const FileReader& copy) = delete;
	FileReader(FileReader&& copy) = delete;
	~FileReader();
	std::unique_ptr<unsigned char[]> GetBytes();
	void save_bytes(char*  bytes, std::string fileNAME);
};

//waw h