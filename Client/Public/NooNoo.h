#pragma once
#include "Client_Define.h"
#include "Monster.h"
#include "Shadow.h"
#include "MonsterHpBar.h"
#include "MonsterRealHp.h"


BEGIN(Client)
class CLevel_Loading;

class CNooNoo final : public CMonster {
private:
	explicit CNooNoo(LPDIRECT3DDEVICE9 pGraphic_Device);
	CNooNoo(const CNooNoo& rhs);
	virtual ~CNooNoo() = default;
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
	_uint m_iPresprite=0;
	_bool m_bAtk = false, m_bLowHp = false;
public:
	static CNooNoo* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END