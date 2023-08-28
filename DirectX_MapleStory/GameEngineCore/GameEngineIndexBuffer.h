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

	// ��������
	UINT IndexSize = 4; // ������ unsigned int�� ����� ���̱� ���� << unsinged int�� ����� ��� ���� ������ ǥ�� ���� (�� 43�ﰳ) short�� ���� �Ұ���
	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
	UINT Offset = 0;
};

