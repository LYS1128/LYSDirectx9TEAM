#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Player.h"

BEGIN(Client)

class CText : public CGameObject {
public:
	enum TEXTID {TEXT_INVEN,TEXT_QUEST, TEXT_STAT, TEXT_NPC, TEXT_WARNING, TEXT_DEAD, TEXT_COST, TEXT_MESO, TEXT_END};
public:
	typedef struct tagFontInfo {
		D3DXFONT_DESCW tFontInfo;
		RECT rc;
		_tchar szText[256];
		TEXTID eTextId;
		_float4 vARGB;
	}FONT;
protected:
	explicit CText(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CText(const CText& rhs);
	virtual ~CText() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	void Set_Text(_tchar* szText);
	void Set_Rect(RECT _Rect);
	TEXTID Get_TextID() { return m_tFont.eTextId; }
protected:
	CRenderer* m_pRenderer = nullptr;
protected:
	FONT m_tFont;
	LPD3DXFONT m_pFont = nullptr;
	_uint m_iWarningTick = 0;
public:
	static CText* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END
