#include "stdafx.h"
#include "..\Public\Quest.h"

CQuest::CQuest(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CText(pGraphic_Device)
{
}

CQuest::CQuest(const CQuest & rhs)
	: CText(rhs)
{
}

HRESULT CQuest::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CQuest : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CQuest::NativeConstruct(void* pArg) {
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CQuest : NativeConstruct");
		return E_FAIL;
	}

	memcpy(&m_tFont, &((QUEST*)pArg)->tFont, sizeof(FONT));
	lstrcpy(m_szQuest, m_tFont.szText);
	m_tQuest.iRequireMonsterCnt = ((QUEST*)pArg)->iRequireMonsterCnt;
	m_tQuest.iOption = ((QUEST*)pArg)->iOption;

	m_tFont.tFontInfo.Weight = FW_HEAVY;
	m_tFont.tFontInfo.CharSet = HANGEUL_CHARSET;
	m_tFont.tFontInfo.Italic = false;
	lstrcpy(m_tFont.tFontInfo.FaceName, L"메이플스토리 Light");

	if (FAILED(D3DXCreateFontIndirect(m_pGraphic_Device, &m_tFont.tFontInfo, &m_pFont))) {
		MSG_BOX(L"Failed To CQuest : NativeConstruct");
		return E_FAIL;
	}

	return S_OK;
}

void CQuest::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	_tchar szBuff[256] = L"";
	if (m_tQuest.iOption == 0)
	{
		wsprintf(szBuff, m_szQuest, m_iMonsterCnt);
		_tchar szBuff2[256] = L"";
		wsprintf(szBuff2, L" / %d", m_tQuest.iRequireMonsterCnt);
		lstrcat(szBuff, szBuff2);
		lstrcat(szBuff, L" )");
		wsprintf(m_tFont.szText, szBuff, m_iMonsterCnt);
	}
	else if (m_tQuest.iOption == 1)
	{
		wsprintf(szBuff, m_szQuest, dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Get_SoulNum());
		_tchar szBuff2[256] = L"";
		wsprintf(szBuff2, L" / %d", m_tQuest.iRequireMonsterCnt);
		lstrcat(szBuff, szBuff2);
		lstrcat(szBuff, L" )");
		wsprintf(m_tFont.szText, szBuff, m_iMonsterCnt);
	}
	else if (m_tQuest.iOption == 2)
	{
		wsprintf(szBuff, m_szQuest, dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Get_Player_Info().iLevel);
		_tchar szBuff2[256] = L"";
		wsprintf(szBuff2, L" / %d", m_tQuest.iRequireMonsterCnt);
		lstrcat(szBuff, szBuff2);
		lstrcat(szBuff, L" )");
		wsprintf(m_tFont.szText, szBuff, m_iMonsterCnt);
	}
}

void CQuest::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	if (m_tQuest.iOption == 0)
	{
		if (m_iMonsterCnt >= m_tQuest.iRequireMonsterCnt) {
			m_bComplete = true;
		}
	}
	else if (m_tQuest.iOption == 1)
	{
		if (dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Get_SoulNum() >= m_tQuest.iRequireMonsterCnt) {
			m_bComplete = true;
		}
	}
	else if (m_tQuest.iOption == 2)
	{
		if (dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Get_Player_Info().iLevel >= m_tQuest.iRequireMonsterCnt) {
			m_bComplete = true;
		}
	}
}

HRESULT CQuest::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CQuest : Render");
		return E_FAIL;
	}
	return S_OK;
}

void CQuest::Set_MonsterCnt() {
	++m_iMonsterCnt;
}

CQuest* CQuest::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CQuest* pInstance = new CQuest(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CQuest : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CQuest::Clone(void * pArg) {
	CQuest* pInstance = new CQuest(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CQuest : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CQuest::Free() {
	__super::Free();
}