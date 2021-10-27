#pragma once
#include<Windows.h>
#include<memory>
#include<string>
#pragma comment(lib,"Ws2_32.lib")
#pragma pack(1)
namespace Wav {
	struct WavHeader {
		unsigned int Chunk_ID;
		unsigned int Chunk_Size;
		unsigned int Format;
		unsigned int SubChunkID1;
		unsigned int SubChunkSize1;
		unsigned short AudioFile;
		unsigned short NumChannels;
		unsigned int SampleRate;
		unsigned int ByteRate;
		unsigned short BlockAligin;
		unsigned short BitsPerSample;
		unsigned int SubChunkID2;
		unsigned int SubChunkSize2;
	};
	class Wav {
		std::unique_ptr<unsigned char[]> data;
		WavHeader header;
		std::string Filename;
		unsigned long long size;
		void getDataFromFile();
		template<typename t>
		void convert(t& byte);
	public:
		void save(std::string filename);
		unsigned long long getSize();
		Wav() = delete;
		Wav(std::string filename);
		Wav(const Wav& obj);
		Wav(Wav&& obj);
	};
	template<typename t>
	void Wav::convert(t& byte)
	{
		byte = ntohl(byte);
		
	}
}