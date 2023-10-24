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
		Data.resize(Data.capacity() * 2 + _Size);
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
	Write(&_Value[0], static_cast<unsigned int>(_Value.size()));
}

void GameEngineSerializer::operator<<(std::string_view _Value)
{
	//	Write(&_Value[0], static_cast<unsigned int>(_Value.size())); == 아래와 같음 (기억해두기 용으로 다른 방법으로 작성)
	unsigned int Value = static_cast<unsigned int>(_Value.size());
	Write(&Value, 4);
	Write(_Value.data(), static_cast<unsigned int>(_Value.size()));
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


void GameEngineSerializer::operator>>(std::string& _Value)
{
	int Size = 0;
	Read(&Size, sizeof(int));
	_Value.resize(Size);
	Read(&_Value[0], Size);
}

void GameEngineSerializer::operator>>(int& _Value)
{
	Read(&_Value, sizeof(int));
}

void GameEngineSerializer::operator>>(unsigned int& _Value)
{
	Read(&_Value, sizeof(unsigned int));
}

void GameEngineSerializer::operator>>(uint64_t& _Value)
{
	Read(&_Value, sizeof(uint64_t));
}

void GameEngineSerializer::operator>>(float& _Value)
{
	Read(&_Value, sizeof(float));
}

void GameEngineSerializer::operator>>(bool& _Value)
{
	Read(&_Value, sizeof(bool));
}

void GameEngineSerializer::operator>>(float4& _Value)
{
	Read(&_Value, sizeof(float4));
}

void GameEngineSerializer::operator>>(float4x4& _Value)
{
	Read(&_Value, sizeof(float4x4));
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

std::string_view GameEngineSerializer::GetStringView()
{
	return GetDataPtr<const char>();
}