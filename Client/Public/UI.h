#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "Player.h"

BEGIN(Client)

class CUI abstract : public CGameObject {
public:
	typedef struct tagUIInfo {
		_float fX;
		_float fY;
		_float fCX;
		_float fCY;
}UIINFO;
protected:
	explicit CUI(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CUI(const CUI& rhs);
	virtual ~CUI() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
protected:
	CTransform* m_pTransform = nullptr;
	CVIBuffer* m_pVIBuffer = nullptr;
	CTexture* m_pTexture = nullptr;
	CRenderer* m_pRenderer = nullptr;
protected:
	D3DVIEWPORT9 m_ViewPort;
	_float4x4 m_ProjMatrix;
	UIINFO m_tUIInfo;
	_uint m_iSprite = 0;
	_uint m_iTickCount = 0;
	_bool m_bCheck = false;
	CPlayer* m_pPlayer = nullptr;

public:
	void Set_Sprite(_uint Num) { m_iSprite = Num; }
public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END