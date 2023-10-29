#pragma once
#include "GameEngineResources.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

// 레스터라이저 전에 범위를 잡을때 사용하는 VertexBuffer, IndexBuffer를 관리하는 클래스입니다.
class GameEngineMesh : public GameEngineResources<GameEngineMesh>
{
public:
	// constructer destructer
	GameEngineMesh();
	~GameEngineMesh();

	// delete function
	GameEngineMesh(const GameEngineMesh& _Ohter) = delete;
	GameEngineMesh(GameEngineMesh&& _Ohter) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(GameEngineMesh&& _Other) noexcept = delete;

	// Rendering PipeLine에서 InuptAssembler1, 2를 담당
	void InputAssembler1();
	void InputAssembler2();

	static std::shared_ptr<GameEngineMesh> Create(std::string_view _Name)
	{
		return Create(_Name, _Name, _Name);
	}

	static std::shared_ptr<GameEngineMesh> Create(std::string_view _Name, std::string_view _VtxName, std::string_view _IdxName)
	{
		std::shared_ptr<GameEngineMesh> Res = GameEngineResources::CreateRes(_Name);
		Res->VertexBufferPtr = GameEngineVertexBuffer::Find(_VtxName);
		Res->IndexBufferPtr = GameEngineIndexBuffer::Find(_IdxName);

		if (nullptr == Res->VertexBufferPtr
			|| nullptr == Res->IndexBufferPtr)
		{
			MsgBoxAssert("매쉬를 만드는데 실패했습니다.");
		}

		return Res;
	}

	std::shared_ptr<class GameEngineVertexBuffer> GetVertexBuffer()
	{
		return VertexBufferPtr;
	}

	void SetTOPOLOGY(D3D11_PRIMITIVE_TOPOLOGY _TOPOLOGY)
	{
		TOPOLOGY = _TOPOLOGY;
	}

	void Draw();

protected:

private:
	// IndexBuffer가 들고있던 토폴로지를 관리
	D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	std::shared_ptr<class GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<class GameEngineIndexBuffer> IndexBufferPtr;
};

