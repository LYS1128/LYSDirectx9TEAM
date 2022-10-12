#include "..\Public\Transform.h"

CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CComponent(pGraphic_Device)
{
}

CTransform::CTransform(const CTransform & rhs)
	: CComponent(rhs)
	, m_WorldMatrix(rhs.m_WorldMatrix)
	, m_tTransformDesc(rhs.m_tTransformDesc)
{
}

HRESULT CTransform::NativeConstruct_Prototype() {
	D3DXMatrixIdentity(&m_WorldMatrix);
	return S_OK;
}

HRESULT CTransform::NativeConstruct(void* pArg) {
	if (nullptr != pArg) {
		memcpy(&m_tTransformDesc, pArg, sizeof(TRANSFORMDESC));
	}
	return S_OK;
}

_float3 CTransform::Get_State(STATE eState) {
	return *(_float3*)&m_WorldMatrix.m[eState][0];
}

_float3 CTransform::Get_Scale() {
	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	_float3	vUp = Get_State(CTransform::STATE_UP);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);
	return _float3(D3DXVec3Length(&vRight), D3DXVec3Length(&vUp), D3DXVec3Length(&vLook));
}

_float4x4 CTransform::Get_WorldMatrix() {
	return m_WorldMatrix;;
}

CTransform::TRANSFORMDESC CTransform::Get_TransDesc() {
	return m_tTransformDesc;
}

void CTransform::Set_State(STATE eState, const _float3& vState) {
	memcpy(&m_WorldMatrix.m[eState][0], &vState, sizeof(_float3));
}

void CTransform::Set_WorldMatrix(_float4x4 WorldMatrix) {
	m_WorldMatrix = WorldMatrix;
}

void CTransform::Set_TransformState(const TRANSFORMDESC& TransformDesc) {
	m_tTransformDesc = TransformDesc;
}

HRESULT CTransform::Bind_OnGraphicDevice() const {
	if (nullptr == m_pGraphic_Device) {
		MSG_BOX(L"Failed To CTransform : Bind_OnGraphicDevice");
		return E_FAIL;
	}
	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &m_WorldMatrix);
	return S_OK;
}

HRESULT CTransform::Bind_OnShader(CShader * pShader, D3DXHANDLE hParameters) {
	_float4x4		WorldMatrix;
	D3DXMatrixTranspose(&WorldMatrix, &m_WorldMatrix);

	pShader->SetUp_RawValue(hParameters, &WorldMatrix, sizeof(_float4x4));

	return S_OK;
}

HRESULT CTransform::Go_Straight(_float fTimeDelta) {
	_float3	vPosition = Get_State(CTransform::STATE_POSITION);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);
	vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_tTransformDesc.fSpeedPerSec * fTimeDelta;
	Set_State(CTransform::STATE_POSITION, vPosition);
	return S_OK;
}

HRESULT CTransform::Go_BackWard(_float fTimeDelta) {
	_float3	vPosition = Get_State(CTransform::STATE_POSITION);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);
	vPosition -= *D3DXVec3Normalize(&vLook, &vLook) * m_tTransformDesc.fSpeedPerSec * fTimeDelta;
	Set_State(CTransform::STATE_POSITION, vPosition);
	return S_OK;
}

HRESULT CTransform::Go_Right(_float fTimeDelta) {
	_float3	vPosition = Get_State(CTransform::STATE_POSITION);
	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	vPosition += *D3DXVec3Normalize(&vRight, &vRight) * m_tTransformDesc.fSpeedPerSec * fTimeDelta;
	Set_State(CTransform::STATE_POSITION, vPosition);
	return S_OK;
}

HRESULT CTransform::Go_Left(_float fTimeDelta) {
	_float3	vPosition = Get_State(CTransform::STATE_POSITION);
	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	vPosition -= *D3DXVec3Normalize(&vRight, &vRight) * m_tTransformDesc.fSpeedPerSec * fTimeDelta;
	Set_State(CTransform::STATE_POSITION, vPosition);
	return S_OK;
}

HRESULT CTransform::Go_UpLeft(_float fTimeDelta) {
	_float3	vPosition = Get_State(CTransform::STATE_POSITION);
	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);
	vPosition -= (*D3DXVec3Normalize(&vRight, &vRight) * m_tTransformDesc.fSpeedPerSec * fTimeDelta) / sqrtf(2);
	vPosition += (*D3DXVec3Normalize(&vLook, &vLook) * m_tTransformDesc.fSpeedPerSec * fTimeDelta) / sqrtf(2);
	Set_State(CTransform::STATE_POSITION, vPosition);
	return S_OK;
}

HRESULT CTransform::Go_UpRight(_float fTimeDelta) {
	_float3	vPosition = Get_State(CTransform::STATE_POSITION);
	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);
	vPosition += (*D3DXVec3Normalize(&vRight, &vRight) * m_tTransformDesc.fSpeedPerSec * fTimeDelta) / sqrtf(2);
	vPosition += (*D3DXVec3Normalize(&vLook, &vLook) * m_tTransformDesc.fSpeedPerSec * fTimeDelta) / sqrtf(2);
	Set_State(CTransform::STATE_POSITION, vPosition);
	return S_OK;
}

HRESULT CTransform::Go_DownLeft(_float fTimeDelta) {
	_float3	vPosition = Get_State(CTransform::STATE_POSITION);
	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);
	vPosition -= (*D3DXVec3Normalize(&vRight, &vRight) * m_tTransformDesc.fSpeedPerSec * fTimeDelta) / sqrtf(2);
	vPosition -= (*D3DXVec3Normalize(&vLook, &vLook) * m_tTransformDesc.fSpeedPerSec * fTimeDelta) / sqrtf(2);
	Set_State(CTransform::STATE_POSITION, vPosition);
	return S_OK;
}

HRESULT CTransform::Go_DownRight(_float fTimeDelta) {
	_float3	vPosition = Get_State(CTransform::STATE_POSITION);
	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);
	vPosition += (*D3DXVec3Normalize(&vRight, &vRight) * m_tTransformDesc.fSpeedPerSec * fTimeDelta) / sqrtf(2);
	vPosition -= (*D3DXVec3Normalize(&vLook, &vLook) * m_tTransformDesc.fSpeedPerSec * fTimeDelta) / sqrtf(2);
	Set_State(CTransform::STATE_POSITION, vPosition);
	return S_OK;
}

HRESULT CTransform::Go_Up(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vUp = Get_State(CTransform::STATE_UP);

	vPosition += *D3DXVec3Normalize(&vUp, &vUp) * m_tTransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_Down(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vUp = Get_State(CTransform::STATE_UP);

	vPosition -= *D3DXVec3Normalize(&vUp, &vUp) * m_tTransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Scaled(_float3 vScale) {
	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	_float3	vUp = Get_State(CTransform::STATE_UP);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);

	Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * vScale.x);
	Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * vScale.y);
	Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * vScale.z);

	return S_OK;
}

HRESULT CTransform::Scaling(_float fTimeDelta) {
	_float fScale = 0.f;

	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	fScale = D3DXVec3Length(&vRight) + m_tTransformDesc.fScalePerSec * fTimeDelta;

	Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * fScale);

	_float3 vUp = Get_State(CTransform::STATE_UP);
	fScale = D3DXVec3Length(&vUp) + m_tTransformDesc.fScalePerSec * fTimeDelta;

	Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * fScale);

	_float3 vLook = Get_State(CTransform::STATE_LOOK);
	fScale = D3DXVec3Length(&vLook) + m_tTransformDesc.fScalePerSec * fTimeDelta;

	Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * fScale);

	return S_OK;
}

HRESULT CTransform::TextureTurn() {
	_float4x4 RotationMatrix;

	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	_float3	vUp = Get_State(CTransform::STATE_UP);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);

	D3DXMatrixRotationAxis(&RotationMatrix, &vUp, D3DXToRadian(180.f));

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::Turn(const _float3& vAxis, _float fTimeDelta) {
	_float4x4 RotationMatrix;

	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, fTimeDelta);

	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	_float3	vUp = Get_State(CTransform::STATE_UP);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::Chase(const _float3 & vTargetPos, _float fTimeDelta, _float fLimitDistance) {
	_float3	vPosition = Get_State(CTransform::STATE_POSITION);
	_float3	vLook = _float3(vTargetPos.x - vPosition.x, 0.f, vTargetPos.z - vPosition.z);
	_float	fDistance = D3DXVec3Length(&vLook);

	if (fDistance > fLimitDistance) {
		vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_tTransformDesc.fSpeedPerSec * fTimeDelta;
	}
	Set_State(CTransform::STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::LookAt(const _float3 & vTargetPos) {
	_float3	vPosition = Get_State(CTransform::STATE_POSITION);
	_float3	vScale = Get_Scale();

	_float3	vLook = vTargetPos - vPosition;
	_float3	vAxisY = _float3(0.f, 1.f, 0.f);
	_float3	vRight = *D3DXVec3Cross(&vRight, &vAxisY, &vLook);
	_float3	vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::MoveOnTerrain(_float3* pVertex, _float fTimeDelta) {
	_float3 vPosition = Get_State(CTransform::STATE_POSITION);

	_float3 vVec[2] = {
		{ pVertex[0].x - pVertex[1].x, pVertex[0].y - pVertex[1].y, pVertex[0].z - pVertex[1].z },
		{ pVertex[0].x - pVertex[2].x, pVertex[0].y - pVertex[2].y, pVertex[0].z - pVertex[2].z }
	};

	_float3 vNormal = *D3DXVec3Cross(&vNormal, &vVec[0], &vVec[1]);

	vPosition.y = -((vNormal.x * (vPosition.x - pVertex[0].x) + vNormal.z * (vPosition.z - pVertex[0].z)) / vNormal.y) + pVertex[0].y + 0.5f;

	Set_State(CTransform::STATE_POSITION, vPosition);
	return S_OK;
}

CTransform* CTransform::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CTransform*	pInstance = new CTransform(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CTransform : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CTransform::Clone(void* pArg) {
	CTransform*	pInstance = new CTransform(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CTransform : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTransform::Free() {
	__super::Free();
}