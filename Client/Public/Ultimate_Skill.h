#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Dark_Effect.h"
#include "Monster.h"

BEGIN(Client)

class CUltimate_Skill final : public CUI {
private:
	explicit CUltimate_Skill(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CUltimate_Skill(const CUltimate_Skill& rhs);
	virtual ~CUltimate_Skill() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CUltimate_Skill* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END