#pragma once
#include "Client_Define.h"
#include "NPC.h"
#include "TextWindow.h"


BEGIN(Client)
class CLevel_Loading;

class CPortal final : public CNPC
{
private:
	explicit CPortal(LPDIRECT3DDEVICE9 pGraphic_Device);
	CPortal(const CPortal& rhs);
	virtual ~CPortal() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	HRESULT SetUp_Components();
	void Set_Open(_bool Open) { m_bOpen = Open; }
private:
	_uint m_iTick = 0, m_iSprite = 0;
	LEVEL m_Level = LEVEL_TUTORIAL;
	_bool m_bPreOpen = true;
	_bool m_bOpen = true;

public:
	static CPortal* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();
};

END