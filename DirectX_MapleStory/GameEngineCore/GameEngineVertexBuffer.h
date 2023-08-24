#pragma once
#include "GameEngineDirectBuffer.h"

// Ό³Έν :
class GameEngineVertexBuffer :
	public GameEngineResources<GameEngineVertexBuffer>, public GameEngineDirectBuffer
{
	friend class GameEngineInputLayOut;

public:
	// constrcuter destructer
	GameEngineVertexBuffer();
	~GameEngineVertexBuffer();

	// delete Function
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _Other) noexcept = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer& operator=(GameEngineVertexBuffer&& _Other) noexcept = delete;

	template<typename VertexType>
	static std::shared_ptr<GameEngineVertexBuffer> Create(std::string_view _Name, const std::vector<VertexType>& _Data)
	{
		std::shared_ptr<GameEngineVertexBuffer> Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(&_Data[0], sizeof(VertexType), _Data.size());
		Res->VertexInfoPtr = &VertexType::VertexInfo;
		return Res;
	}

	void Setting();

protected:

private:
	void ResCreate(const void* _Data, size_t _VertexSize, size_t _VertexCount);

	UINT VertexSize = 0;
	UINT VertexCount = 0;
	UINT Offset = 0;

	const class GameEngineInputLayOutInfo* VertexInfoPtr;
};
