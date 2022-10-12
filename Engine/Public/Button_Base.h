#pragma once
#include "GameObject.h"
#include "Transform.h"

BEGIN(Engine)

class ENGINE_DLL CButton_Base abstract : public CGameObject {
public:
	typedef struct tagButtonDesc {
		_float3 vPos;
	}BUTTONDESC;
protected:
	explicit CButton_Base(LPDIRECT3DDEVICE9 pGraphic_Device);
	CButton_Base(const CButton_Base& rhs);
	virtual ~CButton_Base() = default;
protected:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
protected:
	CTransform* m_pTransform = nullptr;
	BUTTONDESC m_tButtonDesc;
public:
	virtual CButton_Base* Clone(void* pArg) = 0;
	virtual void Free();
};

END