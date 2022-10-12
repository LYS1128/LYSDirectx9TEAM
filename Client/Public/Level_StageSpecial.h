#pragma once
#include "Client_Define.h"
#include "Level.h"
#include "GameInstance.h"
#include "Camera.h"
#include "MultiCamera.h"
#include "Player.h"
#include "Level_Loading.h"
#include "Text.h"

BEGIN(Client)

class CLevel_StageSpecial final : public CLevel {
private:
	explicit CLevel_StageSpecial(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_StageSpecial() = default;
public:
	virtual HRESULT NativeConstruct() override;
	virtual void Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
public:
	void Score() { m_iScore += 100; }
	void Life() { --m_iLife; }
	void ReStart();
private:
	HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Portal(const _tchar * pLayerTag);
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);
	HRESULT Ready_Layer_UI(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Camera();
private:
	HRESULT Load_Map(const TCHAR* pPath);
private:
	map<const _uint, _float4> m_MapCube;
private:
	_uint m_iScore = 0, m_iPreScore = 0;
	_uint m_iLife = 5;
	_uint m_iTick = 0, m_iRegen = 1;
	_bool m_bGameOver = false;
public:
	static CLevel_StageSpecial* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;
};

END