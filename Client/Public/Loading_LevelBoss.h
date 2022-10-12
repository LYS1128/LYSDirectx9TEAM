#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CLoading_LevelBoss final : public CUI
{
public:
	explicit CLoading_LevelBoss(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CLoading_LevelBoss(const CLoading_LevelBoss& rhs);
	virtual ~CLoading_LevelBoss() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

public:
	static CLoading_LevelBoss* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END