#include "stdafx.h"
#include "..\Public\Boss_Skill.h"

CBoss_Skill::CBoss_Skill(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CBoss_Skill::CBoss_Skill(const CBoss_Skill & rhs)
	:CGameObject(rhs)
{
	m_iDamagePercent = rhs.m_iDamagePercent;
}

HRESULT CBoss_Skill::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBoss_Skill : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBoss_Skill::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBoss_Skill : NativeConstruct");
		return E_FAIL;
	}
	CMonster* pMonster = (CMonster*)(m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->front());
	m_iDamage = pMonster->Get_Monster_Info().iAtt * m_iDamagePercent;
	return S_OK;
}

void CBoss_Skill::Tick(_float fTimeDelta) {
	MoveFrame(fTimeDelta);
	BillBoard(m_pTransform);
}

void CBoss_Skill::LateTick(_float fTimeDelta) {
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CBoss_Skill::Render() {
	if (FAILED(m_pTexture->Bind_OnGraphicDevice((_uint)m_tBossSkillFrame.fFrame))) {
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

void CBoss_Skill::MoveFrame(_float fTimeDelta) {
	m_tBossSkillFrame.fFrame += m_tBossSkillFrame.iSpriteEnd * fTimeDelta;
	if ((_uint)m_tBossSkillFrame.fFrame >= m_tBossSkillFrame.iSpriteEnd) {
		m_tBossSkillFrame.fFrame = 0.f;
		m_eState = STATE_DEAD;
	}
}

void CBoss_Skill::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
}