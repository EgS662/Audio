#include "..\Headers\FileReader.h"
#include<memory>
unsigned long long FileReader::size()
{
	if (file == nullptr) {
		std::cout << "Fail to open file\n";
		return 0;
	}
	fseek(file.get(), 0L, SEEK_END);
	long int ans = ftell(file.get());
	fseek(file.get(), 0, SEEK_SET);
	return ans;
}
FileReader::FileReader(std::string filename_):file{fopen(filename_.c_str(),"rb+")},filename{filename_}
{
	if(file == nullptr) {
		std::cout << "Fail to open file\n";
		return;
	}
}

FileReader::~FileReader()
{
	fclose(file.get());
}

std::unique_ptr<unsigned char[]> FileReader::GetBytes()
{
	auto FileSize{ size() };
	unsigned char* bytes = new unsigned char[FileSize];
	fread(bytes, sizeof(unsigned char), FileSize, file.get());
	std::unique_ptr<unsigned char[]> buffer_data{ std::move(bytes) };
	return buffer_data;
}
