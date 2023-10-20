#include "PreCompile.h"
#include "GameEngineSerializer.h"


GameEngineSerializer::GameEngineSerializer()
{

}

GameEngineSerializer::~GameEngineSerializer()
{

}

void GameEngineSerializer::Write(const void* _Data, unsigned int _Size)
{
	// [a][b][c]
	// [a][b][c] WriteOffset = 3

	// [d]
	// [a][b][c][d][][][][][][][][][] WriteOffset = 4

	if (WriteOffset + _Size >= Data.size())
	{
		Data.resize(Data.capacity() * 2);
	}

	memcpy_s(&Data[WriteOffset], _Size, _Data, _Size);
	WriteOffset += _Size;

	//std::ostream
	//std::istream
}

void GameEngineSerializer::operator<<(const std::string& _Value)
{
	// static_cast<unsigned int>(_Value.size())

	// string
	// [6]
	// [a][a][a][b][b][b]

	operator<<(static_cast<unsigned int>(_Value.size()));
	Write(&_Value[0], _Value.size());
}
void GameEngineSerializer::operator<<(const int& _Value)
{
	Write(&_Value, sizeof(int));
}
void GameEngineSerializer::operator<<(const unsigned int& _Value)
{
	Write(&_Value, sizeof(unsigned int));
}
void GameEngineSerializer::operator<<(const uint64_t& _Value)
{
	Write(&_Value, sizeof(uint64_t));
}

void GameEngineSerializer::operator<<(const float& _Value)
{
	Write(&_Value, sizeof(float));
}
void GameEngineSerializer::operator<<(const bool& _Value)
{
	Write(&_Value, sizeof(bool));
}
void GameEngineSerializer::operator<<(const float4& _Value)
{
	Write(&_Value, sizeof(float4));
}
void GameEngineSerializer::operator<<(const float4x4& _Value)
{
	Write(&_Value, sizeof(float4x4));
}


void GameEngineSerializer::Read(void* _Data, unsigned int _Size)
{

	// [a][b][c][d][][][][][][][][][] ReadOffset = 4

	// char ReadCh;
	// Read(&ReadCh, 1);
	// ReadCh;
	// Read(&ReadCh, 1);
	// ReadCh;

	memcpy_s(_Data, _Size, &Data[ReadOffset], _Size);
	ReadOffset += _Size;
}
