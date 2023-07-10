#pragma once
#include <string>
#include <filesystem>

// Ό³Έν :
class GameEnginePath
{
public:
	// constrcuter destructer
	GameEnginePath();
	GameEnginePath(const std::string& _path);
	~GameEnginePath();

	//// delete Function
	//GameEnginePath(const GameEnginePath& _Other) = delete;
	//GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	//GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	//GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	std::string GetFileName();

	void SetCurrentPath();
	void MoveParent();
	void MoveParentToExistsChild(const std::string& _ChildPath);
	void MoveChild(const std::string& _ChildPath);

	std::string PlusFilePath(const std::string& _ChildPath);

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

