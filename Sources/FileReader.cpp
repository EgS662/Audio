#include "..\Headers\FileReader.h"
#include "Exceptions/Exceptions.h"
#include<memory>
unsigned long long FileReader::size()
{
	if (file == nullptr) {
		throw Exception{ "Cant open file",__FUNCTION__ };
	}
	fseek(file.get(), 0L, SEEK_END);
	long int ans = ftell(file.get());
	fseek(file.get(), 0, SEEK_SET);
	return ans;
}
FileReader::FileReader(std::string filename_):file{fopen(filename_.c_str(),"rb+")},filename{filename_}
{
	if(file == nullptr) {
		throw Exception{"Cant open file",__FUNCTION__};
		return;
	}
}

FileReader::~FileReader()
{
	if (file != nullptr) {
		fclose(file.get());
		file = nullptr;
	}
}

std::unique_ptr<unsigned char[]> FileReader::GetBytes()
{
	auto FileSize{ size() };
	unsigned char* bytes = new unsigned char[FileSize];
	fread(bytes, sizeof(unsigned char), FileSize, file.get());
	std::unique_ptr<unsigned char[]> buffer_data{ std::move(bytes) };
	return buffer_data;
}

//void FileReader::save_bytes( char* bytes,std::string fileNAME)
//{
//	unsigned char arr[] = "234";
//	filename = fileNAME;
//	FILE* f = fopen(fileNAME.c_str(), "w+");
//	//file.reset(fopen(fileNAME.c_str(),"wb+"));
//	//auto SIze = size();
//	auto z = fwrite(arr, sizeof(arr[0]), 3, f);
//	std::cout << z;
//	fclose(f);
//}
