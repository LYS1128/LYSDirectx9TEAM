#pragma once
#include "Client_Define.h"
#include "Boss_Skill.h"
#include "Balrog_LH.h"

BEGIN(Client)

class CPurplePog final : public CBoss_Skill {
private:
	explicit CPurplePog(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CPurplePog(const CPurplePog& rhs);
	virtual ~CPurplePog() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	_uint m_TickCount = 0;
	////////////////////////////////////////
	_uint m_iTick = 0;
	_float3 m_vLook;
public:
	static CPurplePog* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END