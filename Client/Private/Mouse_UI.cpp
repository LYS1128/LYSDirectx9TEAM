#include "stdafx.h"
#include "..\Public\Mouse_UI.h"

CMouse_UI::CMouse_UI(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CMouse_UI::CMouse_UI(const CMouse_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CMouse_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMouse_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMouse_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMouse_UI : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMouse_UI : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 50.f;
	m_tUIInfo.fCY = 50.f;

	m_iUIType = UI_MOUSE;

	return S_OK;
}

void CMouse_UI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


	m_tUIInfo.fX = (_float)pt.x;
	m_tUIInfo.fY = (_float)pt.y;

	ShowCursor(FALSE);

	if (m_pGameInstance->Key_Pressing(VK_LBUTTON))
		m_iSprite = 1;
	else if (m_pGameInstance->Key_Pressing(VK_RBUTTON))
		m_iSprite = 1;
	else
		m_iSprite = 0;
}

void CMouse_UI::LateTick(_float fTimeDelta)
{
	CMultiCamera* pCamera = (CMultiCamera*)(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Camera")->front());
	Safe_AddRef(pCamera);

	if (nullptr == pCamera) {
		return;
	}

	if (3 != pCamera->Get_CameraMode()) {
		__super::LateTick(fTimeDelta);
	}
	Safe_Release(pCamera);
}

HRESULT CMouse_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMouse_UI : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMouse_UI::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CMouse_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Mouse_UI"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Mouse_UI"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CMouse_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CMouse_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CMouse_UI : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CMouse_UI * CMouse_UI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CMouse_UI*	pInstance = new CMouse_UI(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CMouse_UI : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMouse_UI::Clone(void * pArg)
{
	CMouse_UI*	pInstance = new CMouse_UI(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CMouse_UI : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMouse_UI::Free()
{
	__super::Free();
}
