#include "..\Public\Collision.h"

CCollision::CCollision(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CComponent(pGraphic_Device)
{
}

CCollision::CCollision(const CCollision & rhs)
	: CComponent(rhs)
{
}

HRESULT CCollision::NativeConstruct_Prototype() {
	return S_OK;
}

HRESULT CCollision::NativeConstruct(void* pArg) {
	return S_OK;
}

CCollision::COLLISION CCollision::Check_CollisionXZ(_float3 vPos1, _float3 fLength1, _float3 vPos2, _float3 fLength2) {


	//fLength1는 큐브스케일 2는 플레이어
	//fDis 
	_float fDisX = (fLength1.x / 2.f) + (fLength2.x / 4.f);
	_float fDisY = (fLength1.y / 2.f) + (fLength2.y / 2.f);
	_float fDisZ = (fLength1.z / 2.f) + (fLength2.z / 4.f);

	//중점사이의거리
	_float fPosDisX = fabs(vPos1.x - vPos2.x);
	_float fPosDisY = fabs(vPos1.y - vPos2.y);
	_float fPosDisZ = fabs(vPos1.z - vPos2.z);


	COLLISION eCol = COL_END;

	if ((fDisX > fPosDisX) && (fDisY > fPosDisY) && (fDisZ > fPosDisZ)) {

		if (vPos1.y > vPos2.y&& fPosDisY >(fLength2.y / 2.f)) {
			eCol = COL_DOWN;
		}
		if (vPos1.y < vPos2.y && fPosDisY >(fLength2.y / 2.f)) {
			eCol = COL_UP;
		}
		else
		{
			if (vPos1.x > vPos2.x && fPosDisZ <= fPosDisX) {
				eCol = COL_RIGHT;
			}
			if (vPos1.x < vPos2.x&& fPosDisZ < fPosDisX) {
				eCol = COL_LEFT;
			}
			if (vPos1.z > vPos2.z&& fPosDisZ >= fPosDisX) {
				eCol = COL_FRONT;
			}
			if (vPos1.z < vPos2.z&& fPosDisZ > fPosDisX) {
				eCol = COL_BACK;
			}
		}
	}
	return eCol;
}

void CCollision::My_Collision(_float4 Cube, CTransform* pTransform2)
{
	_float3 vPos1 = _float3(Cube.x, Cube.y, Cube.z);
	_float3 vPos2 = pTransform2->Get_State(CTransform::STATE_POSITION);

	_float3 vScale1 = _float3(1.f, 1.f, 1.f);
	_float3 vScale2 = _float3(pTransform2->Get_Scale().x, pTransform2->Get_Scale().y, pTransform2->Get_Scale().z);

	COLLISION eCollisionXZ = Check_CollisionXZ(vPos1, vScale1, vPos2, vScale2);
	if (eCollisionXZ != COL_END)
	{
		vPos2.y = vPos1.y + vScale1.y / 2 + vScale2.y / 2;
		pTransform2->Set_State(CTransform::STATE_POSITION, vPos2);
	}
}

_uint CCollision::After_Collision(_float4 Cube, CTransform* pTransform2) {
	_float3 vPos1 = _float3(Cube.x, Cube.y, Cube.z);
	_float3 vPos2 = pTransform2->Get_State(CTransform::STATE_POSITION);

	_float3 vScale1 = _float3(1.f, 1.f, 1.f);
	_float3 vScale2 = _float3(pTransform2->Get_Scale().x, pTransform2->Get_Scale().y, pTransform2->Get_Scale().z);

	COLLISION eCollisionXZ = Check_CollisionXZ(vPos1, vScale1, vPos2, vScale2);

	if (COL_LEFT == eCollisionXZ) {
		vPos2.x = vPos1.x + vScale1.x / 2 + vScale2.x / 4;
		pTransform2->Set_State(CTransform::STATE_POSITION, vPos2);
		return 1;
	}
	else if (COL_RIGHT == eCollisionXZ) {
		vPos2.x = vPos1.x - vScale1.x / 2 - vScale2.x / 4;
		pTransform2->Set_State(CTransform::STATE_POSITION, vPos2);
		return 1;
	}
	if (COL_UP == eCollisionXZ) {
		vPos2.y = vPos1.y + vScale1.y / 2 + vScale2.y / 2;
		pTransform2->Set_State(CTransform::STATE_POSITION, vPos2);
		return 2;
	}
	else if (COL_DOWN == eCollisionXZ) {
		vPos2.y = vPos1.y - vScale1.y / 2 - vScale2.y / 2;
		pTransform2->Set_State(CTransform::STATE_POSITION, vPos2);
		return 1;
	}
	if (COL_BACK == eCollisionXZ) {
		vPos2.z = vPos1.z + vScale1.z / 2 + vScale2.z / 4;
		pTransform2->Set_State(CTransform::STATE_POSITION, vPos2);
		return 1;
	}
	else if (COL_FRONT == eCollisionXZ) {
		vPos2.z = vPos1.z - vScale1.z / 2 - vScale2.z / 4;
		pTransform2->Set_State(CTransform::STATE_POSITION, vPos2);
		return 1;
	}
	return 0;
}


_bool CCollision::Collision_Cylinder(CTransform* pTransform1, CTransform* pTransform2) {
	_float3 vPostion1 = pTransform1->Get_State(CTransform::STATE_POSITION);
	_float3 vScale1 = pTransform1->Get_Scale();

	_float3 vPostion2 = pTransform2->Get_State(CTransform::STATE_POSITION);
	_float3 vScale2 = pTransform2->Get_Scale();

	_float fDis = sqrtf(pow((vPostion1.x - vPostion2.x), 2) + pow((vPostion1.z - vPostion2.z), 2));
	if (fDis <= vScale1.x * 0.3f + vScale2.x * 0.3f && vPostion1.y + vScale1.y * 0.5f >= vPostion2.y && vPostion1.y - vScale1.y * 0.5f <= vPostion2.y) {
		return true;
	}

	return false;
}

_bool CCollision::Collision_Sphere(CTransform * pTransform1, CTransform * pTransform2) {
	_float fDis = sqrtf(pow(pTransform1->Get_State(CTransform::STATE_POSITION).x - pTransform2->Get_State(CTransform::STATE_POSITION).x, 2) +
						pow((pTransform2->Get_State(CTransform::STATE_POSITION).y- pTransform1->Get_Scale().y+0.5f) - pTransform1->Get_State(CTransform::STATE_POSITION).y, 2) +
						pow(pTransform1->Get_State(CTransform::STATE_POSITION).z - pTransform2->Get_State(CTransform::STATE_POSITION).z, 2));

	_float fRadius1 = pTransform1->Get_Scale().x * 0.45f;
	_float fRadius2 = pTransform2->Get_Scale().x * 0.45f;

	if (fDis < fRadius1 + fRadius2) {
		return true;
	}
	return false;
}

CCollision* CCollision::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CCollision*	pInstance = new CCollision(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CCollision : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CCollision::Clone(void * pArg) {
	CCollision*	pInstance = new CCollision(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CCollision : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCollision::Free() {
}