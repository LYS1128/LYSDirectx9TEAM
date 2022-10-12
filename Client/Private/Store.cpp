#include "stdafx.h"
#include "..\Public\Store.h"

CStore::CStore(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CStore::CStore(const CStore & rhs)
	:CUI(rhs)
{
}

HRESULT CStore::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CStore : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CStore::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CStore : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CStore : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Make_StoreObject())) {
		MSG_BOX(L"Failed To CStore : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 500.f;
	m_tUIInfo.fCY = 500.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = 270.f;

	m_iUIType = UI_STORE;

	return S_OK;
}

void CStore::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CStore::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CStore::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CStore : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CStore::SetUp_Components() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CStore : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGESEVEN, TEXT("Prototype_Component_Texture_Store"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CStore : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CStore : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CStore : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CStore::Make_StoreObject() {
	CStore_Potion::POTIONTYPE ePotionType;

	ePotionType = CStore_Potion::POTION_RED;
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Store", L"Prototype_GameObject_StoreObject", &ePotionType);

	ePotionType = CStore_Potion::POTION_BLUE;
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Store", L"Prototype_GameObject_StoreObject", &ePotionType);

	ePotionType = CStore_Potion::POTION_EXIT;
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Store", L"Prototype_GameObject_StoreObject", &ePotionType);

	CText::FONT tFont;
	ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont.rc = RECT{ 520, 290, 1280, 310 };
	lstrcpy(tFont.szText, L"가격 : 1메소");
	tFont.tFontInfo.Height = 20;
	tFont.tFontInfo.Width = 15;
	tFont.eTextId = CText::TEXT_COST;
	tFont.vARGB = _float4(255, 0, 0, 0);

	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Store", L"Prototype_GameObject_Font", &tFont);

	CText::FONT tFont1;
	ZeroMemory(&tFont1.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont1.rc = RECT{ 520, 390, 1280, 410 };
	lstrcpy(tFont1.szText, L"가격 : 1메소");
	tFont1.tFontInfo.Height = 20;
	tFont1.tFontInfo.Width = 15;
	tFont1.eTextId = CText::TEXT_COST;
	tFont1.vARGB = _float4(255, 0, 0, 0);

	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Store", L"Prototype_GameObject_Font", &tFont1);

	CText::FONT tFont2;
	ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont2.rc = RECT{ 700, 390, 1280, 410 };
	tFont2.tFontInfo.Height = 20;
	tFont2.tFontInfo.Width = 15;
	tFont2.eTextId = CText::TEXT_MESO;
	tFont2.vARGB = _float4(255, 0, 0, 0);

	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Store", L"Prototype_GameObject_Font", &tFont2);

	return S_OK;
}

CStore * CStore::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CStore* pInstance = new CStore(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CStore : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CStore::Clone(void * pArg) {
	CStore* pInstance = new CStore(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CStore : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStore::Free() {
	__super::Free();
}