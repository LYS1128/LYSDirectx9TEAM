#pragma once
#include "Client_Define.h"
#include "Monster.h"
#include "Shadow.h"
#include "MonsterHpBar.h"
#include "MonsterRealHp.h"

BEGIN(Client)

class CBoss_Ice final : public CMonster {
private:
	explicit CBoss_Ice(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBoss_Ice(const CBoss_Ice& rhs);
	virtual ~CBoss_Ice() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CBoss_Ice* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END