#include "stdafx.h"
#include "..\Public\Text.h"


CText::CText(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CText::CText(const CText& rhs)
	:CGameObject(rhs)
{
}

HRESULT CText::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMyFont : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CText::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CText : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CText : NativeConstruct");
		return E_FAIL;
	}

	memcpy(&m_tFont, (FONT*)pArg, sizeof(FONT));

	m_tFont.tFontInfo.Weight = FW_HEAVY;
	m_tFont.tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(m_tFont.tFontInfo.FaceName, L"메이플스토리 Light");

	if (FAILED(D3DXCreateFontIndirect(m_pGraphic_Device, &m_tFont.tFontInfo, &m_pFont))) {
		MSG_BOX(L"Failed To CText : NativeConstruct");
		return E_FAIL;
	}
	if (TEXT_COST == m_tFont.eTextId || TEXT_MESO == m_tFont.eTextId) {
		m_iUIType = UI_STOREOBJECT;
	}

	if (TEXT_STAT == m_tFont.eTextId) {
		m_iUIType = UI_PLAYERINFO;
		}

	if (TEXT_NPC == m_tFont.eTextId) {
		m_iUIType = UI_FONT;
	}

	return S_OK;
}

void CText::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	if (TEXT_WARNING == m_tFont.eTextId) {
		++m_iWarningTick;
		if (120 <= m_iWarningTick) {
			m_eState = STATE_DEAD;
		}
	}
	else if (TEXT_MESO == m_tFont.eTextId) {
		CPlayer* pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front());
		_tchar szBuff[32] = L"";
		wsprintf(szBuff, L"보유 메소 : %d", pPlayer->Get_Meso());
		lstrcpy(m_tFont.szText, szBuff);
	}
}

void CText::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_UI, this);
}

HRESULT CText::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMyFont : Render");
		return E_FAIL;
	}
	m_pFont->DrawTextW(nullptr, m_tFont.szText, lstrlen(m_tFont.szText), &m_tFont.rc, 0, D3DCOLOR_ARGB((_uint)m_tFont.vARGB.x, (_uint)m_tFont.vARGB.y, (_uint)m_tFont.vARGB.z, (_uint)m_tFont.vARGB.w));
	return S_OK;
}

void CText::Set_Text(_tchar * szText) {
	lstrcpy(m_tFont.szText, szText);
}

void CText::Set_Rect(RECT _Rect)
{
	memcpy(&m_tFont.rc, &_Rect, sizeof(RECT));
}

CText* CText::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CText* pInstance = new CText(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CText : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CText::Clone(void* pArg) {
	CText* pInstance = new CText(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CText : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CText::Free() {
	__super::Free();
	Safe_Release(m_pRenderer);
}