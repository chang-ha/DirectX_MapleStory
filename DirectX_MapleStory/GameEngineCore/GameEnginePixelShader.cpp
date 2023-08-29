#include "PreCompile.h"
#include "GameEnginePixelShader.h"

GameEnginePixelShader::GameEnginePixelShader()
{

}

GameEnginePixelShader::~GameEnginePixelShader()
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

void GameEnginePixelShader::ShaderLoad(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	std::wstring UniPath = GameEngineString::AnsiToUnicode(_Path);
	CreateVersion(ShaderType::Pixel, _VersionHigh, _VersionLow);
	EntryName = _EntryPoint;
	int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif 
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* Error = nullptr;

	HRESULT Result = D3DCompileFromFile(
		UniPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryName.c_str(),
		Version.c_str(),
		Flag,
		0,
		&BinaryCode,
		&Error);

	if (S_OK != Result)
	{
		std::string ErrorString = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgBoxAssert(ErrorString);
		return;
	}

	Result = GameEngineCore::GetDevice()->CreatePixelShader(
		BinaryCode->GetBufferPointer(),
		BinaryCode->GetBufferSize(),
		nullptr,
		&ShaderPtr);

	if (S_OK != Result)
	{
		MsgBoxAssert("픽셀 쉐이더 생성에 실패했습니다.");
	}
}

void GameEnginePixelShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgBoxAssert("쉐이더를 생성하지 않았습니다. 먼저 ShaderLoad함수를 호출해 주세요");
	}

	GameEngineCore::GetContext()->PSSetShader(ShaderPtr, nullptr, 0);
}