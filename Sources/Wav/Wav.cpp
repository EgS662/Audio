#include "Wav/Wav.h"
#include "FileReader.h"
#include "Exceptions/Exceptions.h"
#include "FileWriter.h"
#include<memory>
namespace Wav {
	void Wav::save(std::string filename)
	{
		unsigned char* bytes = new unsigned char[size] {};
		convert(header.Chunk_Size);
		convert(header.SubChunkSize1);
		convert(header.AudioFile);
		convert(header.NumChannels);
		convert(header.SampleRate);
		convert(header.ByteRate);
		convert(header.BlockAligin);
		convert(header.BitsPerSample);
		convert(header.SubChunkSize2);
		memcpy(bytes, &header, sizeof(header));
		memcpy(bytes, data.get(), size - sizeof(header));
		FileWriter obj_{filename};
		std::vector<unsigned char> Data;
		for (auto i = 0; i < size; i++) {
			Data.push_back(bytes[i]);
		}
		//std::unique_ptr<unsigned char[]> res{ bytes };
		obj_.WriteToFile(Data);
	}
	unsigned long long Wav::getSize()
	{
		return size;
	}
	Wav::Wav(std::string filename) :Filename{ filename }
	{
		getDataFromFile();
	}

	Wav::Wav(const Wav& obj)
	{
	}

	Wav::Wav(Wav&& obj)
	{

	}

	void Wav::getDataFromFile()
	{
		FileReader obj{Filename};
		size = obj.size();
		std::unique_ptr<unsigned char[]> tmp{ std::move(obj.GetBytes()) };
		memcpy(&header, tmp.get(), sizeof(WavHeader));
		convert(header.Chunk_Size);
		convert(header.SubChunkSize1);
		convert(header.AudioFile);
		convert(header.NumChannels);
		convert(header.SampleRate);
		convert(header.ByteRate);
		convert(header.BlockAligin);
		convert(header.BitsPerSample);
		convert(header.SubChunkSize2);
        char ChunkID[5];
		char HeaderFormat[8];
		memcpy(HeaderFormat, &header.Format, sizeof(int)+3);
		memcpy(ChunkID, &header.Chunk_ID, sizeof(int)+1);
		ChunkID[4] = 0;
		HeaderFormat[7] = 0;
	/*	if (strcmp(ChunkID, "RIFF") != 0) {
			throw Exception("Its not wav file",__FUNCTION__);
		}
		if (strcmp(HeaderFormat, "WAVEfmt") != 0) {
			throw Exception("Its not wav file", __FUNCTION__);
		}*/
		unsigned char* tmp1 = new unsigned char[size - sizeof(header)]{};
		memcpy(tmp1,tmp.get() + sizeof(header),size - sizeof(header));
		data.reset(tmp1);
	}
}