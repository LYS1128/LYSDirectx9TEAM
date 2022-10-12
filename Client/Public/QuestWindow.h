#pragma once
#include "Client_Define.h"
#include "UI.h"

BEGIN(Client)

class CQuestWindow final : public CUI
{
private:
	explicit CQuestWindow(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CQuestWindow(const CQuestWindow& rhs);
	virtual ~CQuestWindow() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

public:
	static CQuestWindow* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END