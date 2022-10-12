#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "Monster.h"

BEGIN(Client)

class CMonsterHpBar final : public CGameObject {
public:
	typedef struct tagMonsterInfo {
		CMonster* pMonster;
		_float3 vPos;
	}MONSTERINFO;
private:
	explicit CMonsterHpBar(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CMonsterHpBar(const CMonsterHpBar& rhs);
	virtual ~CMonsterHpBar() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	CTransform* m_pTransform = nullptr;
	CVIBuffer_Rect* m_pVIBuffer = nullptr;
	CTexture* m_pTexture = nullptr;
	CRenderer* m_pRenderer = nullptr;
	CMonster* m_pMonster = nullptr;
public:
	static CMonsterHpBar* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END