#include "stdafx.h"
#include "..\Public\Effect.h"

CEffect::CEffect(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CEffect::CEffect(const CEffect & rhs)
	:CGameObject(rhs)
{
	m_fDamagePercent = rhs.m_fDamagePercent;
}

HRESULT CEffect::NativeConstruct_Prototype() {
	ZeroMemory(&m_tSkillFrame, sizeof(SKILLFRAME));
	return S_OK;
}

HRESULT CEffect::NativeConstruct(void* pArg) {
	m_pPlayer = (CPlayer*)m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front();
	Safe_AddRef(m_pPlayer);

	m_iDamage = _uint(m_pPlayer->Get_Player_Info().iAtt * m_fDamagePercent);
	return S_OK;
}

void CEffect::Tick(_float fTimeDelta) {
	MoveFrame(fTimeDelta);
	Compute_ZDis(m_pTransform);
}

void CEffect::LateTick(_float fTimeDelta) {
	m_iDamage = _uint(m_pPlayer->Get_Player_Info().iAtt * m_fDamagePercent);
}

HRESULT CEffect::Render() {
	if (FAILED(m_pTexture->Bind_OnGraphicDevice((_uint)m_tSkillFrame.fFrame))) {
		MSG_BOX(L"Failed To CEffect : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CEffect : Render");
		return E_FAIL;
	}
	m_pVIBuffer->Render();
	return S_OK;
}

void CEffect::MoveFrame(_float fTimeDelta) {
	m_tSkillFrame.fFrame += m_tSkillFrame.iSpriteEnd * fTimeDelta;
	if ((_uint)m_tSkillFrame.fFrame >= m_tSkillFrame.iSpriteEnd) {
		m_tSkillFrame.fFrame = 0.f;
		m_eState = STATE_DEAD;
	}
}

void CEffect::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTexture);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pPlayer);
}