#pragma once
#include "Client_Define.h"
#include "Monster.h"
#include "Shadow.h"
#include "MonsterHpBar.h"
#include "MonsterRealHp.h"

BEGIN(Client)

class CBalrog_LH final : public CMonster {
private:
	explicit CBalrog_LH(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBalrog_LH(const CBalrog_LH& rhs);
	virtual ~CBalrog_LH() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

private:
	_uint m_tickCount = 0;
	_uint m_iRand = 0, m_iMode = 0;
	_bool m_bCheck = false, m_bCheck2 = false, m_bPreCheck2 = false;
public:
	static CBalrog_LH* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END