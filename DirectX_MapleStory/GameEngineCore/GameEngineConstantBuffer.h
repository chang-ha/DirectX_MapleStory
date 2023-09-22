#pragma once
#include "GameEngineDirectBuffer.h"

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

	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(int _Byte, std::string_view _Name/*, int _Slot = 0*/)
	{
		if (ConstantBuffers.end() == ConstantBuffers.find(_Byte))
		{
			// 찾아서 없으면 만들어서 [_Byte] 인덱스에 넣음
			ConstantBuffers[_Byte];
		}

		std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>& Buffers = ConstantBuffers[_Byte];
		std::string UpperName = GameEngineString::ToUpperReturn(_Name.data());

		if (Buffers.end() != Buffers.find(UpperName))
		{
			return ConstantBuffers[_Byte][UpperName];
		}

		// 찾아서 없으면 ConstantBuffers 만든다.
		std::shared_ptr<GameEngineConstantBuffer> Res = GameEngineResources::CreateRes();
		// 이름없이 만들어서 SetName하는 이유는 ConstantBuffer는 관리를 따로 ConstantBuffers로 해주기 때문
		Res->SetName(_Name);
		ConstantBuffers[_Byte][UpperName] = Res;
		Res->ResCreate(_Byte);
		return Res;
	}

	void Setting(UINT _Slot);

	template<typename DataType>
	void ChangeData(const DataType& _Data)
	{
		ChangeData(&_Data, sizeof(DataType));
	}

	// 1바이트 자료형
	void ChangeData(const void* _Data, UINT _Size);
protected:

private:

	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBuffers;

	void ResCreate(int _ByteSize);
};