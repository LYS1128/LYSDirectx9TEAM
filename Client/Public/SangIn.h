#pragma once
#include "Client_Define.h"
#include "NPC.h"
#include "TextWindow.h"
#include "QuestWindow.h"
#include "Portal.h"
#include "Theif.h"

BEGIN(Client)

class CSangIn final : public CNPC
{
private:
	explicit CSangIn(LPDIRECT3DDEVICE9 pGraphic_Device);
	CSangIn(const CSangIn& rhs);
	virtual ~CSangIn() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	HRESULT SetUp_Components();
	_uint m_iTick = 0, m_iSprite = 0;
	_uint m_iTextSprite = 0;
	_uint m_iTalkState = 0;

public:
	static CSangIn* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();
};

END