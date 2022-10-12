#pragma once
#include "Client_Define.h"
#include "Boss_Skill.h"

BEGIN(Client)

class CMeteor final : public CBoss_Skill {
private:
	explicit CMeteor(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CMeteor(const CMeteor& rhs);
	virtual ~CMeteor() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CMeteor* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END