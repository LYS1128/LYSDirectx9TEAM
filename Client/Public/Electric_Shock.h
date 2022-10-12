#pragma once
#include "Client_Define.h"
#include "Boss_Skill.h"
#include "Shadow.h"
#include "Balrog_LH.h"

BEGIN(Client)

class CElectric_Shock final : public CBoss_Skill {
private:
	explicit CElectric_Shock(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CElectric_Shock(const CElectric_Shock& rhs);
	virtual ~CElectric_Shock() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
	////////////////////////////////////////
	_uint m_iTick = 0;
	_float3 m_vLook;
public:
	static CElectric_Shock* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END