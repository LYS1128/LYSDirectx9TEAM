#pragma once
#include "Client_Define.h"
#include "Camera.h"
#include "GameInstance.h"
#include "Player.h"


BEGIN(Client)

class CMultiCamera final : public CCamera {
private:
	explicit CMultiCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CMultiCamera(const CMultiCamera& rhs);
	virtual ~CMultiCamera() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	_uint Get_CameraMode() { return m_Mode; }
	_float Get_CameraFovy() { return m_CameraDesc.fFovy; }
	void Set_CameraFovy(_float fAngle) { m_CameraDesc.fFovy -= D3DXToRadian(fAngle); }
	void Set_AbouluteFovy(_float fAngle) { m_CameraDesc.fFovy = fAngle; }
	void Set_ModeFPS() { m_Mode = 3; }
	void Set_ModeOX() { m_Mode = 2; }
	void Set_ModeDefault() { m_Mode = 1; }
	void Set_Critical(_bool b) { m_bCritical = b; }
private:
	_bool Key_Down(int iKey);

public:
	void BossPhase1();
	void BossPhase2();
	void BossPhase3();
	void CriticalHit();
public:
	static CMultiCamera* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
private:
	_bool m_bKeyState[0xff];
	POINT m_pPreCur, m_pCurrentCur;
	_uint m_Mode = 1;
	_uint m_PreMode = 1;
	_float3 m_iSlowMove = _float3(0.f, 0.f, 0.f);
	_float3 m_iPreMove = _float3(0.f, 0.f, 0.f);
	_uint m_iCriticalTick = 0;
	_bool m_bCritical = false, m_bPreCri = false;
};

END