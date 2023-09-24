#pragma once
#include <GameEngineBase/GameEnginePath.h>


// ���� :
template<typename ResourcesType>
class GameEngineResources
{
public:
	// constrcuter destructer
	GameEngineResources() {}
	~GameEngineResources() {}

	// delete Function
	//GameEngineResources(const GameEngineResources& _Other) = delete;
	//GameEngineResources(GameEngineResources&& _Other) noexcept = delete;
	//GameEngineResources& operator=(const GameEngineResources& _Other) = delete;
	//GameEngineResources& operator=(GameEngineResources&& _Other) noexcept = delete;

	static std::shared_ptr<ResourcesType> Find(std::string_view _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);

		// ���ø����� �ٸ� ���ø��� ����Ҷ��� ���϶��� �ִ�.
		// ���ΰ� Ǯ���� ���ø� �ȿ��� �ٸ� ���ø� ����Ҷ� typename�� �տ� �ٿ��ָ� �ȴ�.
		typename std::map<std::string, std::shared_ptr<ResourcesType>>::iterator FindIter = NameRes.find(UpperName);

		if (FindIter == NameRes.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

	// �̸����� �ε��� �ִ� ����� �ֽ��ϴ�.
	static void Release(std::string_view _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);

		// ���ø����� �ٸ� ���ø��� ����Ҷ��� ���϶��� �ִ�.
		// ���ΰ� Ǯ���� ���ø� �ȿ��� �ٸ� ���ø� ����Ҷ� typename�� �տ� �ٿ��ָ� �ȴ�.
		typename std::map<std::string, std::shared_ptr<ResourcesType>>::iterator FindIter = NameRes.find(UpperName);

		if (FindIter == NameRes.end())
		{
			MsgBoxAssert("���������� �ʴ� ���ҽ��� ������� �߽��ϴ�.");
			return;
		}

		NameRes.erase(FindIter);
	}

	void SetName(std::string_view _Name)
	{
		Name = _Name;
	}

	std::string_view GetName()
	{
		return Name;
	}

protected:

	static std::shared_ptr<ResourcesType> CreateRes()
	{
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>();
		UnNameRes.push_back(NewRes);
		return NewRes;
	}

	static std::shared_ptr<ResourcesType> CreateRes(std::string_view _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>();
		NewRes->Name = UpperName;
		NameRes.insert(std::pair<std::string, std::shared_ptr<ResourcesType>>(UpperName, NewRes));
		return NewRes;
	}

	static std::shared_ptr<ResourcesType> CreateRes(std::string_view _Name, std::string_view _Path)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>(ResourcesType);
		NewRes->Name = UpperName;
		NewRes->Path = _Path.data();
		NameRes.insert(UpperName, NewRes);
	}

private:
	static std::map<std::string, std::shared_ptr<ResourcesType>> NameRes;
	static std::list<std::shared_ptr<ResourcesType>> UnNameRes;

	std::string Name;
	GameEnginePath Path;
};

// ���ø� Ŭ���� ������ static���� �ʱ�ȭ �ϴ¹�
template<typename ResourcesType>
std::map<std::string, std::shared_ptr<ResourcesType>> GameEngineResources<ResourcesType>::NameRes;

template<typename ResourcesType>
std::list<std::shared_ptr<ResourcesType>> GameEngineResources<ResourcesType>::UnNameRes;

