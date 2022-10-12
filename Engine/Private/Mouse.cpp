#include "..\Public\Mouse.h"

IMPLEMENT_SINGLETON(CMouse)

CMouse::CMouse()
{
}

void CMouse::Set_Graphic_Device(LPDIRECT3DDEVICE9 pGraphic_Device) {
	m_pGraphic_Device = pGraphic_Device;
	Safe_AddRef(m_pGraphic_Device);
}

CMouse::RAY CMouse::Make_Ray(HWND hWnd, int iWinCX, int iWinCY) {
	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	_float3 vProjPos{};
	vProjPos.x = pt.x / (iWinCX / 2.f) - 1;
	vProjPos.y = pt.y / (iWinCY / -2.f) + 1;
	vProjPos.z = 1.f;

	_float4x4 ProjMatrix{};
	m_pGraphic_Device->GetTransform(D3DTS_PROJECTION, &ProjMatrix);
	D3DXMatrixInverse(&ProjMatrix, nullptr, &ProjMatrix);

	_float3 vViewPos{};
	D3DXVec3TransformCoord(&vViewPos, &vProjPos, &ProjMatrix);

	m_Ray.vRay = vViewPos;
	m_Ray.vRayPos = { 0.f, 0.f, 0.f };

	_float4x4 CameraWoeldMatrix{};
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &CameraWoeldMatrix);
	D3DXMatrixInverse(&CameraWoeldMatrix, nullptr, &CameraWoeldMatrix);

	D3DXVec3TransformCoord(&m_Ray.vRayPos, &m_Ray.vRayPos, &CameraWoeldMatrix);
	D3DXVec3TransformNormal(&m_Ray.vRay, &m_Ray.vRay, &CameraWoeldMatrix);
	D3DXVec3Normalize(&m_Ray.vRay, &m_Ray.vRay);
	return m_Ray;
}

void CMouse::Free() {
	Safe_Release(m_pGraphic_Device);
}

CMouse::PICK* CMouse::Picking_Cube(VTXCUBETEX* pVertices, _float4x4 WorldMatrix) {
	_float fDistance;
	_float4x4 InverseWorld = *D3DXMatrixInverse(&InverseWorld, nullptr, &WorldMatrix);

	CMouse::RAY InstanceRay = m_Ray;

	D3DXVec3TransformCoord(&InstanceRay.vRayPos, &InstanceRay.vRayPos, &InverseWorld);
	D3DXVec3TransformNormal(&InstanceRay.vRay, &InstanceRay.vRay, &InverseWorld);

	vector<PICK*> vecPick;

	if (D3DXIntersectTri(&pVertices[1].vPosition, &pVertices[5].vPosition, &pVertices[6].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));

		tPick.vPos1 = pVertices[1].vPosition;
		tPick.vPos2 = pVertices[5].vPosition;
		tPick.vPos3 = pVertices[6].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[1].vPosition, &pVertices[6].vPosition, &pVertices[2].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));

		tPick.vPos1 = pVertices[1].vPosition;
		tPick.vPos2 = pVertices[6].vPosition;
		tPick.vPos3 = pVertices[2].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[4].vPosition, &pVertices[0].vPosition, &pVertices[3].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));
		
		tPick.vPos1 = pVertices[4].vPosition;
		tPick.vPos2 = pVertices[0].vPosition;
		tPick.vPos3 = pVertices[3].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[4].vPosition, &pVertices[3].vPosition, &pVertices[7].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));
		
		tPick.vPos1 = pVertices[4].vPosition;
		tPick.vPos2 = pVertices[3].vPosition;
		tPick.vPos3 = pVertices[7].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[4].vPosition, &pVertices[5].vPosition, &pVertices[1].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));
		
		tPick.vPos1 = pVertices[4].vPosition;
		tPick.vPos2 = pVertices[5].vPosition;
		tPick.vPos3 = pVertices[1].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[4].vPosition, &pVertices[1].vPosition, &pVertices[0].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));
		
		tPick.vPos1 = pVertices[4].vPosition;
		tPick.vPos2 = pVertices[1].vPosition;
		tPick.vPos3 = pVertices[0].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[3].vPosition, &pVertices[2].vPosition, &pVertices[6].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));
		
		tPick.vPos1 = pVertices[3].vPosition;
		tPick.vPos2 = pVertices[2].vPosition;
		tPick.vPos3 = pVertices[6].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[3].vPosition, &pVertices[6].vPosition, &pVertices[7].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));
		
		tPick.vPos1 = pVertices[3].vPosition;
		tPick.vPos2 = pVertices[6].vPosition;
		tPick.vPos3 = pVertices[7].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[5].vPosition, &pVertices[4].vPosition, &pVertices[7].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));
		
		tPick.vPos1 = pVertices[5].vPosition;
		tPick.vPos2 = pVertices[4].vPosition;
		tPick.vPos3 = pVertices[7].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[5].vPosition, &pVertices[7].vPosition, &pVertices[6].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));
		
		tPick.vPos1 = pVertices[5].vPosition;
		tPick.vPos2 = pVertices[7].vPosition;
		tPick.vPos3 = pVertices[6].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[0].vPosition, &pVertices[1].vPosition, &pVertices[2].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));
		
		tPick.vPos1 = pVertices[0].vPosition;
		tPick.vPos2 = pVertices[1].vPosition;
		tPick.vPos3 = pVertices[2].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (D3DXIntersectTri(&pVertices[0].vPosition, &pVertices[2].vPosition, &pVertices[3].vPosition, &InstanceRay.vRayPos, &InstanceRay.vRay, nullptr, nullptr, &fDistance)) {
		PICK tPick;
		tPick.vCenter = *(_float3*)(&(WorldMatrix.m[3][0]));
		
		tPick.vPos1 = pVertices[0].vPosition;
		tPick.vPos2 = pVertices[2].vPosition;
		tPick.vPos3 = pVertices[3].vPosition;

		D3DXVec3TransformCoord(&tPick.vPos1, &tPick.vPos1, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos2, &tPick.vPos2, &WorldMatrix);
		D3DXVec3TransformCoord(&tPick.vPos3, &tPick.vPos3, &WorldMatrix);

		tPick.fDis = fDistance;
		vecPick.push_back(&tPick);
	}
	if (0 != vecPick.size()) {
		sort(vecPick.begin(), vecPick.end(), [](PICK* first, PICK* second) -> bool
		{
			return first->fDis < second->fDis;
		});
		return vecPick.front();
	}
	return nullptr;
}