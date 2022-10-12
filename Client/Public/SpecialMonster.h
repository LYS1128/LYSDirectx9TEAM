#pragma once
#include "Client_Define.h"
#include "Monster.h"
#include "GameInstance.h"

BEGIN(Client)

class CLevel_StageSpecial;

class CSpecialMonster final : public CMonster {
private:
	explicit CSpecialMonster(LPDIRECT3DDEVICE9 pGraphic_Device);
	CSpecialMonster(const CSpecialMonster& rhs);
	virtual ~CSpecialMonster() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	void Collision_Bullet();
	void Move_Frame();
private:
	HRESULT SetUp_Components();
private:
	CLevel_StageSpecial* m_pLevel = nullptr;
public:
	static CSpecialMonster* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END