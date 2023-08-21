#include "PreCompile.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader()
{

}

GameEngineVertexShader::~GameEngineVertexShader()
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

void GameEngineVertexShader::ShaderLoad(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHight, UINT _VersionLow)
{
	std::wstring UniPath = GameEngineString::AnsiToUnicode(_Path);
	CreateVersion(ShaderType::Vertex, _VersionHight, _VersionLow);
	EntryName = _EntryPoint;
	int Flag = 0;
#ifdef _DEBUG
	// 디버그 버전이면 에러 띄우기
	Flag = D3D10_SHADER_DEBUG;
#endif
	// 상수 버퍼때 물어보기
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// std::string의 포인터라 생각하자
	ID3DBlob* Error = nullptr;

	// 쉐이더 컴파일 함수
	HRESULT Result = D3DCompileFromFile(
		UniPath.c_str(),  // Uni경로
		nullptr, // 매크로함수 (ifdef 등)
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // 내부에서 사용한 #include를 사용한다. (내가 설정으로 특정 헤더파일을 미리 읽은 것처럼 사용가능 -> #include안해도 사용가능한 코드가 되어버림), 내가 일일히 안넣어주겠다.
		EntryName.c_str(), // ColorShader_VS
		Version.c_str(), // vs_5_0
		Flag,
		0,
		&BinaryCode,
		&Error
		);

	if (S_OK != Result)
	{
		std::string ErrorString = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgBoxAssert(ErrorString);
		return;
	}

	Result = GameEngineCore::MainDevice.GetDevice()->CreateVertexShader(
		BinaryCode->GetBufferPointer(),
		BinaryCode->GetBufferSize(),
		nullptr,
		&ShaderPtr);

	if (S_OK != Result)
	{
		MsgBoxAssert("버텍스 쉐이더 생성에 실패했습니다.");
	}
}

void GameEngineVertexShader::Setting()
{
	GameEngineCore::MainDevice.GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}