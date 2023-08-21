#include "PreCompile.h"
#include "GameEngineRasterizer.h"


GameEngineRasterizer::GameEngineRasterizer()
{

}

GameEngineRasterizer::~GameEngineRasterizer()
{
	//if (nullptr != State)
	//{
	//	State->Release();
	//	State = nullptr;
	//}
}

void GameEngineRasterizer::ResCreate(const D3D11_RASTERIZER_DESC& _Desc)
{
	Desc = _Desc;
	if (S_OK != GameEngineCore::MainDevice.GetDevice()->CreateRasterizerState(&_Desc, &State))
	{
		MsgBoxAssert("레스터라이저를 만드는데 실패했습니다.");
	}
}

void GameEngineRasterizer::Setting()
{
	if (nullptr == State)
	{
		MsgBoxAssert("레스터 라이저 세팅이 존재하지 앟는데 세팅하려고 했습니다. ResCreate함수를 먼저 호출해 주세요.");
	}
	
	GameEngineCore::MainDevice.GetContext()->RSSetState(State);
}