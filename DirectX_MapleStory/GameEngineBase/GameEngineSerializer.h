#pragma once
#include <vector>

class GameEngineSerializer
{
public:
	// constructer destructer
	GameEngineSerializer();
	~GameEngineSerializer();

	// delete function
	// GameEngineSerializer(const GameEngineSerializer& _Ohter) = delete;
	// GameEngineSerializer(GameEngineSerializer&& _Ohter) noexcept = delete;
	// GameEngineSerializer& operator=(const GameEngineSerializer& _Other) = delete;
	// GameEngineSerializer& operator=(GameEngineSerializer&& _Other) noexcept = delete;

	void BufferResize(size_t _BufferSize)
	{
		Data.resize(_BufferSize);
	}

	size_t GetBufferSize()
	{
		return Data.size();
	}

	template<typename PtrType>
	PtrType* GetDataPtr()
	{
		return reinterpret_cast<PtrType*>(&Data[0]);
	}
protected:

private:
	std::vector<char> Data;
};

