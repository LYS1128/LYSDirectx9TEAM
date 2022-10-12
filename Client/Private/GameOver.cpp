#include "stdafx.h"
#include "..\Public\GameOver.h"
#include "../Public/Level_StageSpecial.h"

CGameOver::CGameOver(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CGameOver::CGameOver(const CGameOver & rhs)
	: CUI(rhs)
{
}

HRESULT CGameOver::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CGameOver : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CGameOver::NativeConstruct(void * pArg) {
	if (LEVEL_STAGESPECIAL != g_iLevel) {
		if (FAILED(__super::NativeConstruct(pArg))) {
			MSG_BOX(L"Failed To CGameOver : NativeConstruct");
			return E_FAIL;
		}
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CGameOver : NativeConstruct");
		return E_FAIL;
	}
	m_tUIInfo.fCX = 400.f;
	m_tUIInfo.fCY = 200.f;
	m_tUIInfo.fX = 640.f;
	m_tUIInfo.fY = -10.f;

	if (LEVEL_STAGESPECIAL == g_iLevel) {
		m_pGraphic_Device->GetViewport(&m_ViewPort);
		D3DXMatrixOrthoLH(&m_ProjMatrix, (_float)m_ViewPort.Width, (_float)m_ViewPort.Height, 0.f, 1.f);

		m_pLevel = (CLevel_StageSpecial*)pArg;
	}

	m_iUIType = UI_GAMEOVER;

	return S_OK;
}

void CGameOver::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	if (240 >= m_tUIInfo.fY) {
		m_tUIInfo.fY += 1.f;
	}

	if (false == m_bEnterForRevive && 240.f == m_tUIInfo.fY) {
		m_bEnterForRevive = true;

		CText::FONT tFont;
		ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont.rc = RECT{ 440, 440, 840, 520 };
		lstrcpy(tFont.szText, L"Press Enter To Revive");
		tFont.tFontInfo.Height = 40;
		tFont.tFontInfo.Width = 30;
		tFont.eTextId = CText::TEXT_DEAD;
		tFont.vARGB = _float4(255, 255, 255, 255);

		m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_GameOver", L"Prototype_GameObject_Font", &tFont);
	}
}

void CGameOver::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	if (LEVEL_STAGESPECIAL != g_iLevel) {
		if (true == m_bEnterForRevive && m_pGameInstance->Key_Down(VK_RETURN)) {
			((CPlayer*)m_pPlayer)->Set_State(CGameObject::STATE_ALIVE);
			((CPlayer*)m_pPlayer)->Set_Pos(_float3(0.f, 5.f, 0.f));
			((CPlayer*)m_pPlayer)->Set_Revive();
			list<CGameObject*> GameOverList = *(m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_GameOver"));
			for (auto& iter : GameOverList) {
				iter->Set_Dead();
			}
		}
	}
	else {
		if (true == m_bEnterForRevive && m_pGameInstance->Key_Down(VK_RETURN)) {
			m_pLevel->ReStart();
			CPlayer* pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front());
			pPlayer->Set_Bullet();
			list<CGameObject*> GameOverList = *(m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_GameOver"));
			for (auto& iter : GameOverList) {
				iter->Set_Dead();
			}
		}
	}
}


HRESULT CGameOver::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CGameOver : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CGameOver::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CGameOver : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_GameOver"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CGameOver : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CGameOver : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CGameOver : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CGameOver* CGameOver::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CGameOver*	pInstance = new CGameOver(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CGameOver : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CGameOver::Clone(void* pArg) {
	CGameOver*	pInstance = new CGameOver(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CGameOver : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CGameOver::Free() {
	__super::Free();
}