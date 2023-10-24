#include "PreCompile.h"
#include "GameEngineDebug.h"
#include "GameEngineFile.h"
// #include <filesystem>

GameEngineFile::GameEngineFile() 
{
}

GameEngineFile::~GameEngineFile() 
{
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}


GameEngineFile::GameEngineFile(const std::string& _path)
	: GameEnginePath(_path)
{

}

void GameEngineFile::Open(FileOpenType _OpenType, FileDataType _DateType)
{
	std::string Path = /*GameEngineFile::*/GetStringPath();
	std::string Mode = "";
	switch (_OpenType)
	{
	case FileOpenType::Write:
		Mode += "w";
		break;
	case FileOpenType::Read:
		Mode += "r";
		break;
	default:
		break;
	}
	
	switch (_DateType)
	{
	case FileDataType::Binary:
		Mode += "b";
		break;
	case FileDataType::Text:
		Mode += "t";
		break;
	default:
		break;
	}

	fopen_s(&FilePtr, Path.c_str(), Mode.c_str());
	OpenType = _OpenType;
	DataType = _DateType;

	if (false == IsExits() && OpenType == FileOpenType::Read)
	{
		MsgBoxAssert("�������� �ʴ� ������ ��� �������� �ؽ��ϴ�.");
	}
}

void GameEngineFile::DataAllRead(class GameEngineSerializer& _Data)
{
	_Data.BufferResize(GetFileSize<size_t>());
	Read(_Data.GetDataPtr<void>(), _Data.GetBufferSize());
}

void GameEngineFile::Read(void* _Data, size_t _Size)
{
	if (nullptr == FilePtr)
	{
		MsgBoxAssert("������ ���� ������ �������� �߽��ϴ�. Open�� ���� ������� �ּ���.");
	}

	if (FileOpenType::Read != OpenType)
	{
		MsgBoxAssert("�б� ���� ������ ���� �����Դϴ�.");
	}
	
	fread_s(_Data, _Size, _Size, 1, FilePtr);
}

uintmax_t GameEngineFile::GetFileSize()
{
	return std::filesystem::file_size(Path);
}

void GameEngineFile::Write(class GameEngineSerializer& _Data)
{
	Write(_Data.GetDataPtr<void>(), _Data.GetBufferSize());
}

// ���Ͽ��� �����͸� ����.
void GameEngineFile::Write(void* _Data, size_t _Size)
{
	if (nullptr == FilePtr)
	{
		MsgBoxAssert("������ ���� ������ �������� �߽��ϴ�. Open�� ���� �������ּ���.");
	}

	if (OpenType != FileOpenType::Write)
	{
		MsgBoxAssert("���� ���� ������ ���� �����Դϴ�.");
	}

	fwrite(_Data, _Size, 1, FilePtr);

}