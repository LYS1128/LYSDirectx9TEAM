#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "GameInstance.h"
#include "Collision.h"
#include "Player.h"

BEGIN(Client)

class CItem final : public CGameObject {
public:
	typedef struct tagItem {
		map<const _uint, _float4> mapCube;
		CTransform* pTargetTransform;
		_float3 vPosition;
		_uint iOption;
	}ITEM;
private:
	explicit CItem(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CItem(const CItem& rhs);
	virtual ~CItem() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

public:
	HRESULT SetUp_Components();
	_bool Check_Player_InArea();
private:
	CTransform* m_pTransform = nullptr;
	CVIBuffer_Rect* m_pVIBuffer = nullptr;
	CTexture* m_pTexture = nullptr;
	CRenderer* m_pRenderer = nullptr;
	CCollision* m_pCollision = nullptr;
public:
	static CItem * Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;

private:
	ITEM m_tItem;
	//CTransform* m_pTarget = nullptr;
	CPlayer* m_pPlayer = nullptr;
};

END