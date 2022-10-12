#include "..\Public\GameObject.h"
#include "GameInstance.h"

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device)
	:m_pGraphic_Device(pGraphic_Device)
	, m_pGameInstance(CGameInstance::GetInstance())
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pGraphic_Device);
}

CGameObject::CGameObject(const CGameObject & rhs)
	:m_pGraphic_Device(rhs.m_pGraphic_Device)
	, m_pGameInstance(rhs.m_pGameInstance)
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CGameObject::NativeConstruct_Prototype() {
	return S_OK;
}

HRESULT CGameObject::NativeConstruct(void* pArg) {
	m_eState = STATE_ALIVE;
	return S_OK;
}

void CGameObject::Tick(_float fTimeDelta) {
}

void CGameObject::LateTick(_float fTimeDelta) {
}

HRESULT CGameObject::Render() {
	return S_OK;
}

CComponent* CGameObject::Get_Component(const _tchar* pComponentTag) {
	return Find_Component(pComponentTag);
}

CGameObject::OBJECTSTATE CGameObject::Get_State() {
	return m_eState;
}

_float CGameObject::Get_ZDis() {
	return m_fZDis;
}

HRESULT CGameObject::SetUp_Components(const _tchar* pComponentTag, _uint iLevelIndex, const _tchar* pPrototypeTag, CComponent** ppOut, void* pArg) {
	if (nullptr != Find_Component(pComponentTag)) {
		MSG_BOX(L"Failed To CGameObject : SetUp_Components");
		return E_FAIL;
	}

	CComponent*	pComponent = m_pGameInstance->Clone_Component(iLevelIndex, pPrototypeTag, pArg);
	if (nullptr == pComponent) {
		MSG_BOX(L"Failed To CGameObject : SetUp_Components");
		return E_FAIL;
	}
	m_Components.insert(COMPONENTS::value_type(pComponentTag, pComponent));

	*ppOut = pComponent;
	Safe_AddRef(pComponent);

	return S_OK;
}

CComponent* CGameObject::Find_Component(const _tchar* pComponentTag) {
	auto Pair = find_if(m_Components.begin(), m_Components.end(), CTagFinder(pComponentTag));

	if (Pair == m_Components.end()) {
		return nullptr;
	}
	return Pair->second;
}

void CGameObject::Compute_ZDis(CTransform* pTransform) {
	_float4x4 ViewMatrix;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	if (nullptr == pTransform) {
		return;
	}

	_float3 vDis = pTransform->Get_State(CTransform::STATE_POSITION) - *((_float3*)(&ViewMatrix.m[3][0]));
	m_fZDis = D3DXVec3Length(&vDis);
}

void CGameObject::BillBoard(CTransform* pTransform) {
	_float4x4 ViewMatrix;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	_float3	vScale = pTransform->Get_Scale();

	pTransform->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0] * vScale.x);
	pTransform->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0] * vScale.y);
	pTransform->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0] * vScale.z);
}

void CGameObject::Free() {
	for (auto& Pair : m_Components) {
		Safe_Release(Pair.second);
	}
	m_Components.clear();

	Safe_Release(m_pGameInstance);
	Safe_Release(m_pGraphic_Device);
}