#pragma once
#include <vector>
#include "GameEngineDebug.h"
#include "GameEngineMath.h"

class GameEngineSerializer
{
public:
	// constructer destructer
	GameEngineSerializer();
	~GameEngineSerializer();

	void Write(const void* Data, unsigned int _Size);
	void operator<<(const std::string& _Value);
	void operator<<(std::string_view _Value);
	void operator<<(const int& _Value);
	void operator<<(const unsigned int& _Value);
	void operator<<(const uint64_t& _Value);
	void operator<<(const float& _Value);
	void operator<<(const bool& _Value);
	void operator<<(const float4& _Value);
	void operator<<(const float4x4& _Value);

	void Read(void* Data, unsigned int _Size);
	void operator>>(std::string& _Value);
	// void operator>>(std::string_view _Value); 스트링뷰는 읽어오는게 불가능 (스트링뷰가 원하는 것 : 주소값, 내가 저장한 것 : 문자열의 배열)
	void operator>>(int& _Value);
	void operator>>(unsigned int& _Value);
	void operator>>(uint64_t& _Value);
	void operator>>(float& _Value);
	void operator>>(bool& _Value);
	void operator>>(float4& _Value);
	void operator>>(float4x4& _Value);

	// delete function
	// GameEngineSerializer(const GameEngineSerializer& _Ohter) = delete;
	// GameEngineSerializer(GameEngineSerializer&& _Ohter) noexcept = delete;
	// GameEngineSerializer& operator=(const GameEngineSerializer& _Other) = delete;
	// GameEngineSerializer& operator=(GameEngineSerializer&& _Other) noexcept = delete;

	std::string_view GetStringView();

	void BufferResize(size_t _BufferSize)
	{
		Data.resize(_BufferSize);
	}

	size_t GetBufferSize()
	{
		return Data.size();
	}

	size_t GetWriteOffset()
	{
		return WriteOffset;
	}

	template<typename PtrType>
	PtrType* GetDataPtr()
	{
		return reinterpret_cast<PtrType*>(&Data[0]);
	}
protected:

private:
	// 이전에 읽었거나 썻던 배열 위치를 기억해야함 << 이어서 계속 읽거나 쓰기 위해서
	unsigned int WriteOffset = 0;
	unsigned int ReadOffset = 0;


	std::vector<char> Data;
};

// 파일 입출력을 할 녀석은 해당 클래스를 상속받으면 됨(아래 함수들은 무조건 구현해야함)
class GameEngineSerializerObject
{
public:
	// 객체 => File(byte 덩어리)
	virtual void Serializer(GameEngineSerializer& _Data) = 0;

	// File(byte 덩어리) => 객체
	virtual void DeSerializer(GameEngineSerializer& _Data) = 0;
};