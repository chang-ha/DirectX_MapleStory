#pragma once
#include "GameEngineDirectBuffer.h"
#include "GameEngineShader.h"

class GameEngineConstantBuffer : public GameEngineResources<GameEngineConstantBuffer>, public GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

	// delete Function
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _Other) noexcept = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer& operator=(GameEngineConstantBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(int _Byte, const std::string_view& _Name, ShaderType _Type = ShaderType::None, int _Slot = 0)
	{
		if (ConstantBuffers.end() == ConstantBuffers.find(_Byte))
		{
			// ã�Ƽ� ������ ���� [_Byte] �ε����� ����
			ConstantBuffers[_Byte];
		}

		std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>& Buffers = ConstantBuffers[_Byte];
		std::string UpperName = GameEngineString::ToUpperReturn(_Name.data());

		if (Buffers.end() != Buffers.find(UpperName))
		{
			return ConstantBuffers[_Byte][UpperName];
		}

		// ã�Ƽ� ������ ConstantBuffers �����.
		std::shared_ptr<GameEngineConstantBuffer> Res = GameEngineResources::CreateRes();
		// �̸����� ���� SetName�ϴ� ������ ConstantBuffer�� ������ ���� ConstantBuffers�� ���ֱ� ����
		Res->SetName(_Name);
		Res->Type = _Type;
		Res->Slot = _Slot;
		ConstantBuffers[_Byte][UpperName] = Res;
		Res->ResCreate(_Byte);
		return Res;
	}

	void Setting();
protected:

private:
	int Slot = 0;
	ShaderType Type = ShaderType::None;

	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBuffers;

	void ResCreate(int _ByteSize);
};