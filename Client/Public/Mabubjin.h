#pragma once
#include "Client_Define.h"
#include "Boss_Skill.h"

BEGIN(Client)

class CMabubjin final : public CBoss_Skill {
private:
	explicit CMabubjin(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CMabubjin(const CMabubjin& rhs);
	virtual ~CMabubjin() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	_uint m_iTick = 0;
public:
	static CMabubjin* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END