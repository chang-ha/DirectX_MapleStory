#include "PreCompile.h"
#include "GameEngineShader.h"

GameEngineShader::GameEngineShader()
{

}

GameEngineShader::~GameEngineShader()
{

}

void GameEngineShader::CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow)
{
	ShaderTypeValue = _Type;
	switch (_Type)
	{
	case ShaderType::None:
	{
		MsgBoxAssert("쒜이더 타입이 잘못들어왔습니다.");
		break;
	}
	case ShaderType::Vertex:
	{
		Version = "vs";
		break;
	}
	case ShaderType::Pixel:
	{
		Version = "ps";
		break;
	}
	case ShaderType::Compute:
		Version = "cs";
		break;
	case ShaderType::Max:
	default:
	{
		MsgBoxAssert("쒜이더 타입이 잘못들어왔습니다.");
		break;
	}
	}
	Version += "_";
	Version += std::to_string(_VersionHigh); // 5
	Version += "_";
	Version += std::to_string(_VersionLow); // 5
}

#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineGeometryShader.h"
#include "GameEngineComputeShader.h"

bool GameEngineShader::AutoCompile(GameEngineFile& _File)
{
	_File.Open(FileOpenType::Read, FileDataType::Text);

	uintmax_t size = _File.GetFileSize();
	if (0 == size)
	{
		return false;
	}

	GameEngineSerializer Ser;
	_File.DataAllRead(Ser);

	std::string_view ShaderCode = Ser.GetStringView();

	{
		size_t EntryIndex = ShaderCode.find("_VS(");
		if (EntryIndex != std::string::npos)
		{
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);
			GameEngineVertexShader::Load(_File.GetStringPath(), EntryName);
		}
	}

	{
		size_t EntryIndex = ShaderCode.find("_PS(");
		if (EntryIndex != std::string::npos)
		{
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);
			GameEnginePixelShader::Load(_File.GetStringPath(), EntryName);
		}
	}

	{
		// find 앞에서 부터 뒤져서 바이트 위치를 알려줍니다.
		size_t EntryIndex = ShaderCode.find("_GS(");
		// 못찾았을때 나옵니다.
		if (EntryIndex != std::string::npos)
		{
			// 내가 지정한 위치에서부터 앞으로 찾기 아서 
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEngineGeometryShader::Load(_File.GetStringPath(), EntryName);

		}
	}

	{
		// find 앞에서 부터 뒤져서 바이트 위치를 알려줍니다.
		size_t EntryIndex = ShaderCode.find("_CS(");
		// 못찾았을때 나옵니다.
		if (EntryIndex != std::string::npos)
		{
			// 내가 지정한 위치에서부터 앞으로 찾기 아서 
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEngineComputeShader::Load(_File.GetStringPath(), EntryName);

		}
	}

	return true;
}

void GameEngineShader::ShaderResCheck()
{
	ResHelper.ShaderResCheck(EntryName, this, BinaryCode);
}