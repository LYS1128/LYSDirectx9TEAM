#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "GameInstance.h"
#include "Text.h"
#include "Quest.h"

class CNPC abstract : public CGameObject {
public:
	typedef struct tagNPC {
		CTransform* pTargetTransform;
		_float3 vPosition;
	}NPC;
protected:
	explicit CNPC(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CNPC(const CNPC& rhs);
	virtual ~CNPC() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	_bool Check_Player_InArea();
	_bool Complete_Quest();
protected:
	CTransform*	m_pTransform = nullptr;
	CVIBuffer_Rect* m_pVIBuffer = nullptr;
	CTexture* m_pTexture = nullptr;
	CRenderer* m_pRenderer = nullptr;
protected:
	CTransform* m_pTarget = nullptr;
public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

