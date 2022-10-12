#pragma once
#include "Client_Define.h"
#include "UI.h"

BEGIN(Client)

class CDamage final : public CUI {
public:
	enum DAMAGETYPE { DAMAGE_PLAYER, DAMAGE_MONSTER, DAMAGE_END };
public:
	typedef struct tagDamage {
		_char chDamageID;
		_float fX;
		_float fY;
		DAMAGETYPE eDamageType;
	}DAMAGE;
private:
	explicit CDamage(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CDamage(const CDamage& rhs);
	virtual ~CDamage() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	DAMAGE m_tDamage;
	_uint m_iTick = 0;
public:
	static CDamage* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END