#pragma once
#include "Base.h"

BEGIN(Engine)

class CFrustum final : public CBase {
	DECLARE_SINGLETON(CFrustum)
private:
	CFrustum();
	virtual ~CFrustum() = default;
public:
	void Tick(LPDIRECT3DDEVICE9 pGraphic_Device, _float fTimeDelta);
	_bool Check_InOut(_float3 vPos, _float fRadius);
private:
	_float3 m_vFrustumPoint[8];
public:
	virtual void Free();
};

END