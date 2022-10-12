#pragma once
#include "Client_Define.h"
#include "Level.h"
#include "GameInstance.h"
#include "Monster.h"
#include "Camera.h"
#include "Player.h"
#include "Level_Loading.h"


BEGIN(Client)

class CLevel_StageSemiBoss final : public CLevel {
public:
	explicit CLevel_StageSemiBoss(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_StageSemiBoss() = default;
public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
private:
	HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Portal(const _tchar * pLayerTag);
	HRESULT Ready_Layer_Snow(const _tchar * pLayerTag);
	HRESULT Ready_Layer_White(const _tchar * pLayerTag);
	HRESULT Ready_Layer_Monster(const _tchar * pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
private:
	HRESULT Load_Map(const TCHAR* pPath);
private:
	map<const _uint, _float4> m_MapCube;
public:
	static CLevel_StageSemiBoss* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END