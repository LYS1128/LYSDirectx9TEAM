#include "..\Public\Frustum.h"

IMPLEMENT_SINGLETON(CFrustum)

CFrustum::CFrustum() {
}

void CFrustum::Tick(LPDIRECT3DDEVICE9 pGraphic_Device, _float fTimeDelta) {
	m_vFrustumPoint[0] = { -1.f, 1.f, 0.f };
	m_vFrustumPoint[1] = { 1.f, 1.f, 0.f };
	m_vFrustumPoint[2] = { 1.f, -1.f, 0.f };
	m_vFrustumPoint[3] = { -1.f, -1.f, 0.f };
	m_vFrustumPoint[4] = { -1.f, 1.f, 1.f };
	m_vFrustumPoint[5] = { 1.f, 1.f, 1.f };
	m_vFrustumPoint[6] = { 1.f, -1.f, 1.f };
	m_vFrustumPoint[7] = { -1.f, -1.f, 1.f };

	_float4x4 ProjMatrix;
	pGraphic_Device->GetTransform(D3DTS_PROJECTION, &ProjMatrix);
	D3DXMatrixInverse(&ProjMatrix, nullptr, &ProjMatrix);

	_float4x4 ViewMatrix;
	pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	_float3 v = { -1.f, 1.f, 0.f };
	_float3 v2 = { 1.f, 1.f, 0.f };

	D3DXVec3TransformCoord(&v, &v, &ProjMatrix);
	D3DXVec3TransformCoord(&v, &v, &ViewMatrix);

	D3DXVec3TransformCoord(&v2, &v2, &ProjMatrix);
	D3DXVec3TransformCoord(&v2, &v2, &ViewMatrix);



	for (int i = 0; i < 8; ++i) {
		D3DXVec3TransformCoord(&m_vFrustumPoint[i], &m_vFrustumPoint[i], &ProjMatrix);
		D3DXVec3TransformCoord(&m_vFrustumPoint[i], &m_vFrustumPoint[i], &ViewMatrix);
	}
}

_bool CFrustum::Check_InOut(_float3 vPos, _float fRadius) {
	_bool bCheck[6];
	for (int i = 0; i < 6; ++i) {
		bCheck[i] = false;
	}

	D3DXPLANE PlaneInfo;

	//오
	D3DXPlaneFromPoints(&PlaneInfo, &m_vFrustumPoint[4], &m_vFrustumPoint[0], &m_vFrustumPoint[3]);
	if (fRadius > PlaneInfo.a * vPos.x + PlaneInfo.b * vPos.y + PlaneInfo.c * vPos.z + PlaneInfo.d) {
		bCheck[0] = true;
	}
	//왼
	D3DXPlaneFromPoints(&PlaneInfo, &m_vFrustumPoint[1], &m_vFrustumPoint[5], &m_vFrustumPoint[6]);
	if (fRadius > PlaneInfo.a * vPos.x + PlaneInfo.b * vPos.y + PlaneInfo.c * vPos.z + PlaneInfo.d) {
		bCheck[1] = true;
	}
	//위
	D3DXPlaneFromPoints(&PlaneInfo, &m_vFrustumPoint[4], &m_vFrustumPoint[5], &m_vFrustumPoint[1]);
	if (fRadius > PlaneInfo.a * vPos.x + PlaneInfo.b * vPos.y + PlaneInfo.c * vPos.z + PlaneInfo.d) {
		bCheck[2] = true;
	}
	//아래
	D3DXPlaneFromPoints(&PlaneInfo, &m_vFrustumPoint[3], &m_vFrustumPoint[2], &m_vFrustumPoint[6]);
	if (fRadius > PlaneInfo.a * vPos.x + PlaneInfo.b * vPos.y + PlaneInfo.c * vPos.z + PlaneInfo.d) {
		bCheck[3] = true;
	}
	//앞
	D3DXPlaneFromPoints(&PlaneInfo, &m_vFrustumPoint[0], &m_vFrustumPoint[1], &m_vFrustumPoint[2]);
	if (fRadius > PlaneInfo.a * vPos.x + PlaneInfo.b * vPos.y + PlaneInfo.c * vPos.z + PlaneInfo.d) {
		bCheck[4] = true;
	}
	//뒤
	D3DXPlaneFromPoints(&PlaneInfo, &m_vFrustumPoint[5], &m_vFrustumPoint[4], &m_vFrustumPoint[7]);
	if (fRadius > PlaneInfo.a * vPos.x + PlaneInfo.b * vPos.y + PlaneInfo.c * vPos.z + PlaneInfo.d) {
		bCheck[5] = true;
	}

	return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3] && bCheck[4] && bCheck[5];
}

void CFrustum::Free()
{
}