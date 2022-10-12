#include "stdafx.h"
#include "..\Public\StatWindow.h"



CStatWindow::CStatWindow(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CStatWindow::CStatWindow(const CStatWindow & rhs)
	: CUI(rhs)
{
}

HRESULT CStatWindow::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CStatWindow : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CStatWindow::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CStatWindow : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CStatWindow : NativeConstruct");
		return E_FAIL;
	}

	m_iSprite = 0;
	m_tUIInfo.fCX = 150;
	m_tUIInfo.fCY = 200;
	m_tUIInfo.fX = 240;
	m_tUIInfo.fY = 200;

	_tchar Buff[32] = TEXT("");
	wsprintf(Buff, L"Level: %d", dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Get_Player_Info().iLevel);

	CText::FONT tFont;
	ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont.rc = RECT{ 190, 160, 1280,190 };
	lstrcpy(tFont.szText, Buff);
	tFont.tFontInfo.Height = 20;
	tFont.tFontInfo.Width = 15;
	tFont.eTextId = CText::TEXT_STAT;
	tFont.vARGB = _float4(255, 50, 35, 20);

	_tchar Buff2[32] = TEXT("");
	wsprintf(Buff2, L"ATK: %d", dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Get_Player_Info().iAtt);


	CText::FONT tFont2;
	ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont2.rc = RECT{ 190, 200, 1280,230 };
	lstrcpy(tFont2.szText, Buff2);
	tFont2.tFontInfo.Height = 20;
	tFont2.tFontInfo.Width = 15;
	tFont2.eTextId = CText::TEXT_STAT;
	tFont2.vARGB = _float4(255, 50, 35, 20);

	_tchar Buff3[32] = TEXT("");
	wsprintf(Buff3, L"DEF: %d", dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Get_Player_Info().iDef);


	CText::FONT tFont3;
	ZeroMemory(&tFont3.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont3.rc = RECT{ 190, 240, 1280,270 };
	lstrcpy(tFont3.szText, Buff3);
	tFont3.tFontInfo.Height = 20;
	tFont3.tFontInfo.Width = 15;
	tFont3.eTextId = CText::TEXT_STAT;
	tFont3.vARGB = _float4(255, 50, 35, 20);

	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_FontS", L"Prototype_GameObject_Font", &tFont);
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_FontS", L"Prototype_GameObject_Font", &tFont2);
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_FontS", L"Prototype_GameObject_Font", &tFont3);

	
	return S_OK;
}

void CStatWindow::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	auto iter = m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_FontS")->Get_List()->begin();

	CText* pText = (CText*)(*iter);
	_tchar sz[32] = L"";
	wsprintf(sz, L"Level: %d", dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Get_Player_Info().iLevel);
	pText->Set_Text(sz);

	++iter;

	CText* pText1 = (CText*)(*iter);
	_tchar sz1[32] = L"";
	wsprintf(sz1, L"ATK: %d", dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Get_Player_Info().iAtt);
	pText1->Set_Text(sz1);

	++iter;

	CText* pText2 = (CText*)(*iter);
	_tchar sz2[32] = L"";
	wsprintf(sz2, L"DEF: %d", dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Get_Player_Info().iDef);
	pText2->Set_Text(sz2);

}

void CStatWindow::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CStatWindow::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CStatWindow : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CStatWindow::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CStatWindow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_StatWindow"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_StatWindow"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CStatWindow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CStatWindow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CStatWindow : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CStatWindow * CStatWindow::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CStatWindow*	pInstance = new CStatWindow(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CStatWindow : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CStatWindow::Clone(void * pArg)
{
	CStatWindow*	pInstance = new CStatWindow(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CStatWindow : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStatWindow::Free()
{
	__super::Free();

}
