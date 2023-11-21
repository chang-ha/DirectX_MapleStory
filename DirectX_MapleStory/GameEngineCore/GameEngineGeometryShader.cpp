#include "PreCompile.h"
#include "GameEngineGeometryShader.h"

GameEngineGeometryShader::GameEngineGeometryShader() 
{
}

GameEngineGeometryShader::~GameEngineGeometryShader() 
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

void GameEngineGeometryShader::ShaderLoad(
	std::string_view _Path, 
	std::string_view _EntryPoint, 
	UINT _VersionHigh, 
	UINT _VersionLow)
{
	std::wstring UniPath = GameEngineString::AnsiToUnicode(_Path);

	CreateVersion(ShaderType::Geometry, _VersionHigh, _VersionLow);

	EntryName = _EntryPoint;

	int Flag = 0;

#ifdef _DEBUG
	// 11버전이 없다.
	// 에러 
	Flag = D3D10_SHADER_DEBUG;
#endif

	//std::string Include =
	//"float4 Value; \
	// float4 Pos; ";

	// 추후 상수버퍼 공부하면서 꼭 물어보세요
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// std::string*
	ID3DBlob* Error = nullptr;

	// 쉐이더를 컴파일 하는 함수입니다.
	// 
	HRESULT Result = D3DCompileFromFile(
		UniPath.c_str(), // 경로
		nullptr, // 쉐이더에서 사용할 매크로 매크로는 안씁니다.
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // 내부에서 사용한 #include 그냥 겠다. 내가 직접 안넣어준다.
		EntryName.c_str(), // "ColorShader_VS"
		Version.c_str(), // "vs_5_0"
		Flag,
		0, // 뭔지 모름.
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
		MsgBoxAssert("버텍스 쉐이더 생성에 실패했습니다.");
	}

	ShaderResCheck();
}

void GameEngineGeometryShader::Setting()
{
	GameEngineCore::GetContext()->PSSetShader(ShaderPtr, nullptr, 0);
}