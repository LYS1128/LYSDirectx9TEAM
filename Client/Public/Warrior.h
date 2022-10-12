#pragma once
#include "Client_Define.h"
#include "NPC.h"
#include "TextWindow.h"
#include "QuestWindow.h"
#include "Portal.h"

BEGIN(Client)

class CWarrior final : public CNPC
{
private:
	explicit CWarrior(LPDIRECT3DDEVICE9 pGraphic_Device);
	CWarrior(const CWarrior& rhs);
	virtual ~CWarrior() = default;
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
	static CWarrior* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();
};

END