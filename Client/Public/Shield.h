#pragma once
#include "Effect.h"
#include "Client_Define.h"
#include "GameInstance.h"
#include "Player.h"

BEGIN(Client)

class CShield final : public CEffect
{
public:
	explicit CShield(LPDIRECT3DDEVICE9 pGraphic_Device);
	CShield(const CShield& rhs);
	virtual~CShield() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

private:
	HRESULT SetUp_Components();
	_float3		m_fLook;
	_float		m_fFrame = 0.f;
public:
	static CShield* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();

};

END