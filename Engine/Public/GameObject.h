#pragma once
#include "Base.h"
#include "Component.h"
#include "Transform.h"
#include "VIBuffer_Rect.h"
#include "VIBuffer_Cube.h"
#include "Texture.h"
#include "Renderer.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CBase{
public:
	enum UITYPE { UI_NONE, UI_DARK, UI_PLAYERINFO, UI_COOLDOWN, UI_INVENFONT, UI_DIALOG, UI_FONT, UI_DAMAGE, UI_GAMEOVER, UI_STORE, UI_STOREOBJECT, UI_LOGO, UI_MOUSE, UI_END };
	enum OBJECTSTATE { STATE_ALIVE, STATE_DEAD, STATE_SUPERARMOR, PLAYER_DEAD, STATE_END };
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGameObject(const CGameObject& rhs);
	virtual ~CGameObject() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	CComponent* Get_Component(const _tchar* pComponentTag);
	OBJECTSTATE Get_State();
	_float Get_ZDis();
	_uint Get_UIType() { return m_iUIType; }
protected:
	HRESULT SetUp_Components(const _tchar* pComponentTag, _uint iLevelIndex, const _tchar* pPrototypeTag, CComponent** ppOut, void* pArg = nullptr);
public:
	CComponent* Find_Component(const _tchar* pComponentTag);
protected:
	void Compute_ZDis(CTransform* pTransform);
	void BillBoard(CTransform* pTransform);
protected:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
	class CGameInstance* m_pGameInstance = nullptr;
protected:
	map<const _tchar*, CComponent*> m_Components;
	typedef map<const _tchar*, CComponent*> COMPONENTS;
protected:
	_float m_fZDis = 0.f;
	_uint m_iUIType = UI_NONE;
	OBJECTSTATE m_eState = STATE_END;

public:
	void Set_Dead() { m_eState = STATE_DEAD; }
public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END