#pragma once
#include "Client_Define.h"
#include "Monster.h"
#include "Shadow.h"
#include "MonsterHpBar.h"
#include "MonsterRealHp.h"

BEGIN(Client)

class CTyphon final : public CMonster {
private:
	explicit CTyphon(LPDIRECT3DDEVICE9 pGraphic_Device);
	CTyphon(const CTyphon& rhs);
	virtual ~CTyphon() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CTyphon* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END