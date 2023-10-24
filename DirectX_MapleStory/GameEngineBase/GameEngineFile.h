#pragma once
#include <string>

#include "GameEnginePath.h"
#include "GameEngineSerializer.h"

enum class FileOpenType
{
	Write,
	Read,
};

enum class FileDataType
{
	Binary,
	Text,
};

// 설명 :
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const std::string& _path);
	~GameEngineFile();

	//// delete Function
	//GameEngineFile(const GameEngineFile& _Other) = delete;
	//GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	//GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	//GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

	void Open(FileOpenType _OpenType, FileDataType _DataType);

	// 파일에서 모든 데이터를 읽어드린다.
	void DataAllRead(class GameEngineSerializer& _Data);

	// 파일에서 데이터를 읽어드린다.
	void Read(void* _Data, size_t _Size);

	void Write(class GameEngineSerializer& _Data);

	void Write(void* _Data, size_t _Size);

	template<typename ReturnType>
	ReturnType GetFileSize()
	{
		return static_cast<ReturnType>(GetFileSize());
	}

	uintmax_t GetFileSize();

protected:

private:
	FILE* FilePtr = nullptr;
	FileOpenType OpenType;
	FileDataType DataType;
};

