#pragma once

class GameEngineInputLayOutInfo
{
public:
	void AddInputLayOutDesc(
		LPCSTR _SemanticName, // ���� �������̴� ���� �÷���. = "POSITION"
		DXGI_FORMAT _Format, // ���� n����Ʈ ¥�� ������ �ڷ��� = DXGI_FORMAT::R32G32 32
		UINT _SemanticIndex = 0, // POSTION0
		UINT _AlignedByteOffset = -1, // 0��° ����Ʈ���� 
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, // ���ؽ� �����Ͱ� �ν��Ͻ� �����ʹ� ��°� ǥ��
		UINT _InputSlot = 0, // n���� ���ؽ� ���۸� �����Ҷ� n��° ���ؽ� ������ ��ǲ ���̾ƿ��̴� ��°� ǥ���ϴ°�
		UINT _InstanceDataStepRate = 0 // ���߿� ���߿� �ν��Ͻ��̶�� ������ ��ﶧ ������ �������̴�.
	);

	static UINT FormatSize(DXGI_FORMAT _Format);
	int Offset = 0;
	std::vector<D3D11_INPUT_ELEMENT_DESC> Infos;
};

// ���� :
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

