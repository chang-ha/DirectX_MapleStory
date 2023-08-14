#pragma once

// ���̷�Ʈx�� ������ ����.
// �׷���ī�带 �̿��ؼ� 3D ������ ��� �ñ�°�.
// �׷���ī��� 3D������ ���� ������ ����ȭ�� ������ġ�̴�.
// �ȼ�������ŭ�� ���ÿ����� �����ϴ�. 1+1  ���ÿ� 1280 x 720
// �츮�� �̰� C++��¥��
// for(int i = 0; i < 1280 x 720 ; ++i)
// {
// }

// ���� :
class GameEngineDevice
{
	friend class GameEngineCore;

public:
	// constrcuter destructer
	GameEngineDevice();
	~GameEngineDevice();

	// delete Function
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator=(GameEngineDevice&& _Other) noexcept = delete;

	// �����쿡�� ������� ������
	// �ٰ��� HWND�� ���� �䱸�մϴ�.
	// �׷��� �����Ա����� �� window�� �� ���Ѵ�.

	// 
	void Initiallize(const class GameEngineWindow& _Window);

	ID3D11Device* GetDevice()
	{
		return Device;
	}

	ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

protected:

private:
	const GameEngineWindow* Window;

	IDXGIAdapter* GetHighPerformanceAdapter();

	// �׷���ī���� �޸𸮰��� ���ٱ��� �������̽�
	// Ex) �̹��� ������ ����� ����� �ִ� ���Ѵ�.
	// ������ ������� ����̽�
	ID3D11Device* Device = nullptr;

	// �׷���ī���� ����(�׸���)���� ���ٱ��� �������̽�
	// �ε�� �̹����� ������� ������ ȭ�鿡 �׷���
	// ������ �׸����� ���ؽ�Ʈ
	ID3D11DeviceContext* Context = nullptr;

	// ȭ�� ��� ó���� �������̽�

	IDXGISwapChain* SwapChain = nullptr;

	std::shared_ptr<class GameEngineTexture> BackBufferTexture;
	std::shared_ptr<class GameEngineRenderTarget> BackBufferRenderTarget;

	void RenderStart();
	void RenderEnd();
	void CreateSwapChain();
	void ResourcesInit();
};

