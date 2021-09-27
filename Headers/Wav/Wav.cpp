#include "Wav.h"
#include "FileReader.h"
#include<memory>
namespace Wav {
	void Wav::megaultrasuperxzdlachegoconvert()
	{
		convert(header.Chunk_ID);
		convert(header.Format);               
		convert(header.SubChunkID1);
		convert(header.SubChunkID2);
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
		unsigned char ChunkID[5];
		unsigned char HeaderFormat[7];
		memcpy(HeaderFormat, &header.Format, sizeof(int)+3);
		memcpy(ChunkID, &header.Chunk_ID, sizeof(int)+1);
		std::cout << ChunkID << " " << HeaderFormat << std::endl;
	}
}