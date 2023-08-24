#pragma once
#include <string>
#include <filesystem>

// ���� :
class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(std::string_view _path);
	~GameEnginePath();

	//// delete Function
	//GameEnginePath(const GameEnginePath& _Other) = delete;
	//GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	//GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	//GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	std::string GetFileName();

	void SetCurrentPath();
	void MoveParent();
	void MoveParentToExistsChild(std::string_view _ChildPath);
	void MoveChild(std::string_view _ChildPath);

	std::string PlusFilePath(std::string_view _ChildPath);

	std::string GetStringPath() 
	{
		return Path.string();
	}

	bool IsDirectory();

	static std::string GetParentString(const std::string& _ChildPath);

protected:
	std::filesystem::path Path;

private:

	// std::string Path;
};

