#pragma once
#include "Client_Define.h"
#include "Level.h"
#include "Level_Loading.h"
#include "GameInstance.h"

BEGIN(Client)

class CLevel_Logo final : public CLevel {
private:
	explicit CLevel_Logo(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_Logo() = default;
public:
	virtual HRESULT NativeConstruct();
	virtual void Tick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	HRESULT Ready_Logo();
private:
	RECT rc{ 0, 0, 1280, 720 };
public:
	static CLevel_Logo* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free();
};

END