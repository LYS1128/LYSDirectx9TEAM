#pragma once
#include "Client_Define.h"
#include "Monster.h"
#include "Shadow.h"
#include "MonsterHpBar.h"
#include "MonsterRealHp.h"

BEGIN(Client)

class CCloneNooNoo final : public CMonster {
private:
	explicit CCloneNooNoo(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCloneNooNoo(const CCloneNooNoo& rhs);
	virtual ~CCloneNooNoo() = default;
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
	_uint m_iRand = 0;
	_bool m_bAtk = false;
public:
	static CCloneNooNoo* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END