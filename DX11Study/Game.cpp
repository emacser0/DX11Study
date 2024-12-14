#include "pch.h"
#include "Game.h"
#include "Graphics.h"
#include "Pipeline.h"
#include "ConstantBuffer.h"
#include "GameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"
#include "GeometryHelper.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "Texture.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "BlendState.h"

using namespace SimpleMath;

FGame::FGame()
	: Graphics(nullptr)
	, Pipeline(nullptr)
	, GameObject(nullptr)
{
}

FGame::~FGame()
{

}

void FGame::Init(HWND InWindowHandle)
{
	Graphics = std::make_shared<FGraphics>(InWindowHandle);

	ComPtr<ID3D11Device> Device = Graphics->GetDevice();
	ComPtr<ID3D11DeviceContext> DeviceContext = Graphics->GetDeviceContext();

	Pipeline = std::make_shared<FPipeline>(DeviceContext);

	GameObject = std::make_shared<UGameObject>(Device, DeviceContext);
}

void FGame::Update()
{
	GameObject->Update();
}

void FGame::Render()
{
	Graphics->RenderBegin();

	GameObject->Render(Pipeline);

	Graphics->RenderEnd();
}
