#pragma once

class GameEngineInputLayOutInfo
{
public:
	void AddInputLayOutDesc(
		LPCSTR _SemanticName, // 내가 포지션이다 내가 컬러다. = "POSITION"
		DXGI_FORMAT _Format, // 내가 n바이트 짜리 정보다 자료형 = DXGI_FORMAT::R32G32 32
		UINT _SemanticIndex = 0, // POSTION0
		UINT _AlignedByteOffset = -1, // 0번째 바이트부터 
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, // 버텍스 데이터가 인스턴싱 데이터다 라는걸 표현
		UINT _InputSlot = 0, // n개의 버텍스 버퍼를 세팅할때 n번째 버텍스 버퍼의 인풋 레이아웃이다 라는걸 표현하는것
		UINT _InstanceDataStepRate = 0 // 나중에 나중에 인스턴싱이라는 구조를 배울때 쓸때가 있을것이다.
	);

	static UINT FormatSize(DXGI_FORMAT _Format);
	int Offset = 0;
	std::vector<D3D11_INPUT_ELEMENT_DESC> Infos;
};

// 설명 :
class GameEngineInputLayOut
{
public:
	// constrcuter destructer
	GameEngineInputLayOut();
	~GameEngineInputLayOut();

	// delete Function
	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(GameEngineInputLayOut&& _Other) noexcept = delete;

	void Setting();
	void ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Buffer, std::shared_ptr<class GameEngineVertexShader> _Shader);
protected:

private:
	ID3D11InputLayout* LayOut = nullptr;


};

