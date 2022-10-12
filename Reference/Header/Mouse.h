#pragma once
#include "Base.h"

BEGIN(Engine)

class CMouse final : public CBase {
	DECLARE_SINGLETON(CMouse)
public:
	typedef struct tagRay {
		_float3 vRay;
		_float3 vRayPos;
	}RAY;
	typedef struct tagPick {
		_float3 vCenter;
		_float3 vPos1;
		_float3 vPos2;
		_float3 vPos3;
		_float fDis;
	}PICK;
private:
	CMouse();
	virtual ~CMouse() = default;
public:
	void Set_Graphic_Device(LPDIRECT3DDEVICE9 pGraphic_Device);
public:
	RAY Make_Ray(HWND hWnd, int iWinCX, int iWinCY);
public:
	PICK* Picking_Cube(VTXCUBETEX* pVertices, _float4x4 WorldMatrix);
private:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
	RAY m_Ray;
public:
	virtual void Free() override;
};

END