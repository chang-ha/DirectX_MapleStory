#pragma once
#include "GameEngineDirectBuffer.h"

class GameEngineIndexBuffer : public GameEngineResources<GameEngineIndexBuffer>, public GameEngineDirectBuffer
{
	// friend class GameEngineInputLayOut;

public:
	// constructer destructer
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer();

	// delete function
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _Ohter) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _Ohter) noexcept = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer& operator=(GameEngineIndexBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineIndexBuffer> Create(std::string_view _Name, const std::vector<unsigned int>& _Data)
	{
		std::shared_ptr<GameEngineIndexBuffer> Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(&_Data[0], _Data.size());
		return Res;
	}

	inline int GetIndexCount()
	{
		return IndexCount;
	}

	void Setting();
protected:

private:
	void ResCreate(const void* _Data, size_t _IndexCount);

	UINT IndexCount = 0;

	// 고정값들
	UINT IndexSize = 4; // 무조건 unsigned int만 사용할 것이기 때문 << unsinged int로 충분히 모든 점의 갯수를 표현 가능 (약 43억개) short는 요즘 불가능
	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
	UINT Offset = 0;
};

