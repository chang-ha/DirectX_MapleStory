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
	// void operator>>(std::string_view _Value); ��Ʈ����� �о���°� �Ұ��� (��Ʈ���䰡 ���ϴ� �� : �ּҰ�, ���� ������ �� : ���ڿ��� �迭)
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
	// ������ �о��ų� ���� �迭 ��ġ�� ����ؾ��� << �̾ ��� �аų� ���� ���ؼ�
	unsigned int WriteOffset = 0;
	unsigned int ReadOffset = 0;


	std::vector<char> Data;
};

// ���� ������� �� �༮�� �ش� Ŭ������ ��ӹ����� ��(�Ʒ� �Լ����� ������ �����ؾ���)
class GameEngineSerializerObject
{
public:
	// ��ü => File(byte ���)
	virtual void Serializer(GameEngineSerializer& _Data) = 0;

	// File(byte ���) => ��ü
	virtual void DeSerializer(GameEngineSerializer& _Data) = 0;
};