#include "Wav/Wav.h"
#include "FileReader.h"
#include "Exceptions/Exceptions.h"
#include "FileWriter.h"
#include<memory>
namespace Wav {
	void Wav::save(std::string filename_)
	{
		unsigned char* bytes = new unsigned char[size] {};
		convert(header.Chunk_Size);
		convert(header.SubChunkSize1);
		header.AudioFile = _byteswap_ushort(header.AudioFile);
		header.NumChannels = _byteswap_ushort(header.NumChannels);
		convert(header.SampleRate);
		convert(header.ByteRate);
		header.BlockAligin = _byteswap_ushort(header.BlockAligin);
		header.BitsPerSample = _byteswap_ushort(header.BitsPerSample);
		convert(header.SubChunkSize2);
		memcpy(bytes, &header, sizeof(header));
		memcpy(bytes+sizeof(header), &data[0], size - sizeof(header));
		std::unique_ptr<unsigned char[]> res{ new unsigned char[size] };
		for (int i = 0; i < size; i++) {
			res.get()[i] = bytes[i];
		}
		FileWriter::getInstance().WriteToFile(filename_,size,std::move(res));
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

	void Wav::magnify()
	{
		for (int i = 0; i < data.size();i++) {
			data[i] *= 10;
		}
	}

	void Wav::getDataFromFile()
	{
		FileReader obj{Filename};
		size = obj.size();
		std::unique_ptr<unsigned char[]> tmp{ std::move(obj.GetBytes()) };
		memcpy(&header, tmp.get(), sizeof(WavHeader));
		convert(header.Chunk_Size);
		convert(header.SubChunkSize1);
		header.AudioFile = _byteswap_ushort(header.AudioFile);
		header.NumChannels = _byteswap_ushort(header.NumChannels);
		convert(header.SampleRate);
		convert(header.ByteRate);
		header.BlockAligin = _byteswap_ushort(header.BlockAligin);
		header.BitsPerSample = _byteswap_ushort(header.BitsPerSample);
		convert(header.SubChunkSize2);
        char ChunkID[5];
		char HeaderFormat[8];
		memcpy(HeaderFormat, &header.Format, sizeof(int)+3);
		memcpy(ChunkID, &header.Chunk_ID, sizeof(int)+1);
		ChunkID[4] = 0;
		HeaderFormat[7] = 0;
		if (strcmp(ChunkID, "RIFF") != 0) {
			throw Exception("Its not wav file",__FUNCTION__);
		}
		if (strcmp(HeaderFormat, "WAVEfmt") != 0) {
			throw Exception("Its not wav file", __FUNCTION__);
		}
		unsigned char* tmp1 = new unsigned char[size - sizeof(header)]{};
		memcpy(tmp1,tmp.get() + sizeof(header),size - sizeof(header));
		for (int i = 0; i < size - sizeof(header); i++) {
			data.push_back(tmp1[i]);
		}
		delete[] tmp1;
	}
}
//конец данных wav 
//алгоритмы обработки звука
//звук фильтры
// библиотеки для рисования графиков с++