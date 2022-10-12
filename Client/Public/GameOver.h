#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Text.h"

BEGIN(Client)

class CLevel_StageSpecial;

class CGameOver final : public CUI {
private:
	explicit CGameOver(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CGameOver(const CGameOver& rhs);
	virtual ~CGameOver() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	_bool m_bEnterForRevive = false;
	CLevel_StageSpecial* m_pLevel = nullptr;
public:
	static CGameOver* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END