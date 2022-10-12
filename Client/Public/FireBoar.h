#pragma once
#include "Client_Define.h"
#include "Monster.h"
#include "Shadow.h"
#include "MonsterHpBar.h"
#include "MonsterRealHp.h"

BEGIN(Client)

class CFireBoar final : public CMonster
{
private:
	explicit CFireBoar(LPDIRECT3DDEVICE9 pGraphic_Device);
	CFireBoar(const CFireBoar& rhs);
	virtual~CFireBoar() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CFireBoar* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
