#include "stdafx.h"
#include "..\Public\NPC.h"

CNPC::CNPC(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CNPC::CNPC(const CNPC& rhs)
	:CGameObject(rhs)
{
}

HRESULT CNPC::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CNPC : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CNPC::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CNPC : NativeConstruct");
		return E_FAIL;
	}
	if (nullptr == pArg) {
		MSG_BOX(L"Failed To CNPC : NativeConstruct");
		return E_FAIL;
	}
	m_pTarget = ((NPC*)pArg)->pTargetTransform;
	return S_OK;
}

void CNPC::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	Compute_ZDis(m_pTransform);


}

void CNPC::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CNPC::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CNPC : Render");
		return E_FAIL;
	}
	return S_OK;
}

_bool CNPC::Check_Player_InArea() {
	_float3 vTargetPosition = m_pTarget->Get_State(CTransform::STATE_POSITION);
	_float3 vPosition = m_pTransform->Get_State(CTransform::STATE_POSITION);
	_float3 vScale = m_pTransform->Get_Scale();

	if (vPosition.y - vScale.y <= vTargetPosition.y && vPosition.y + vScale.y >= vTargetPosition.y) {
		_float fDis = sqrtf(pow((vPosition.x - vTargetPosition.x), 2) + pow((vPosition.z - vTargetPosition.z), 2));
		if (vScale.x * 0.5f >= fDis) {
			return true;
		}
	}
	return false;
}

_bool CNPC::Complete_Quest() {
	list<CGameObject*>* listQuest = m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Quest");
	if (nullptr != listQuest) {
		if (((CQuest*)(listQuest->front()))->Get_Complete()) {
			return true;
		}
	}
	return false;
}

void CNPC::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}