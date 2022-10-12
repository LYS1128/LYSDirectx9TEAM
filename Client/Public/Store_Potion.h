#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Player.h"

BEGIN(Client)

class CStore_Potion final : public CUI {
public:
	enum POTIONTYPE { POTION_RED, POTION_BLUE, POTION_EXIT, POTION_END };
public:
	typedef struct tagPotion {
		_uint iCost;
		RECT RectPicking;
		POTIONTYPE ePotionType;
	}POTION;
private:
	explicit CStore_Potion(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CStore_Potion(const CStore_Potion& rhs);
	virtual ~CStore_Potion() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	POTION m_tPotion;
public:
	static CStore_Potion* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END