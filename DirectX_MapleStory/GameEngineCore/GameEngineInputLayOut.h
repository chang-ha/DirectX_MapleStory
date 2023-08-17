#pragma once

class GameEngineInputLayOutInfo
{
public:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Infos;

};

// Ό³Έν :
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
	void ResCreate(const std::vector<D3D11_INPUT_ELEMENT_DESC>& _ArrLayOutInfo, std::shared_ptr<class GameEngineVertexShader> _Shader);
protected:

private:
	ID3D11InputLayout* LayOut = nullptr;


};

