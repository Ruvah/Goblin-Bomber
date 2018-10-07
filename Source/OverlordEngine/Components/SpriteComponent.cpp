//Precompiled Header [ALWAYS ON TOP IN CPP]
#include "stdafx.h"

#include "SpriteComponent.h"
#include "../Diagnostics/Logger.h"
#include "../Scenegraph/GameObject.h"
#include "../Graphics/TextureData.h"
#include "../Content/ContentManager.h"
#include "../Graphics/SpriteRenderer.h"
#include "../Components/TransformComponent.h"
#include "../Helpers/MathHelper.h"

SpriteComponent::SpriteComponent(const wstring& spriteAsset, XMFLOAT2 pivot, XMFLOAT4 color):
	m_SpriteAsset(spriteAsset),
	m_Pivot(pivot),
	m_Color(color),
	m_pTexture(nullptr)
{

}


SpriteComponent::~SpriteComponent(void)
{
}

void SpriteComponent::Initialize(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	m_pTexture = ContentManager::Load<TextureData>(m_SpriteAsset);
}

void SpriteComponent::SetTexture(const wstring& spriteAsset)
{
	m_SpriteAsset = spriteAsset;
	m_pTexture = ContentManager::Load<TextureData>(m_SpriteAsset);
}

void SpriteComponent::Update(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

void SpriteComponent::Draw(const GameContext& gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	if (!m_pTexture)
		return;

	// Here you need to draw the SpriteComponent using the Draw of the sprite renderer
	// The sprite renderer is a singleton
	XMFLOAT2 pos = XMFLOAT2{GetTransform()->GetPosition().x,GetTransform()->GetPosition().y};
	XMFLOAT2 scale = XMFLOAT2{ GetTransform()->GetScale().x,GetTransform()->GetScale().y };
	XMFLOAT3 rot = QuaternionToEuler(GetTransform()->GetRotation());
	SpriteRenderer::GetInstance()->Draw(m_pTexture, pos, m_Color, m_Pivot, scale, rot.z, GetTransform()->GetPosition().z);
	// you will need to get position, the rotation and the scale
	// You can use the QuaternionToEuler function to help you with the z rotation 
}
