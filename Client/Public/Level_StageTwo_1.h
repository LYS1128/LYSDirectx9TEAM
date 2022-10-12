#pragma once
#include "Client_Define.h"
#include "Level.h"
#include "GameInstance.h"
#include "Monster.h"
#include "Camera.h"
#include "Player.h"
#include "Level_Loading.h"
#include "Theif.h"


BEGIN(Client)

class CLevel_StageTwo_1 final : public CLevel {
public:
	explicit CLevel_StageTwo_1(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_StageTwo_1() = default;
public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
private:
	HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Camera(const _tchar * pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Portal(const _tchar * pLayerTag);
private:
	HRESULT Load_Map(const TCHAR* pPath);
private:
	map<const _uint, _float4> m_MapCube;
	_bool bCheck = false;
public:
	static CLevel_StageTwo_1* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END