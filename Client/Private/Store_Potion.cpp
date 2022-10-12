#include "stdafx.h"
#include "..\Public\Store_Potion.h"

CStore_Potion::CStore_Potion(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CStore_Potion::CStore_Potion(const CStore_Potion & rhs)
	:CUI(rhs)
{
}

HRESULT CStore_Potion::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CStore_Potion : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CStore_Potion::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CStore_Potion : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CStore_Potion : NativeConstruct");
		return E_FAIL;
	}

	ZeroMemory(&m_tPotion, sizeof(POTION));
	m_tPotion.ePotionType = *(POTIONTYPE*)pArg;

	switch (m_tPotion.ePotionType) {
	case POTION_RED: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_RedPotion"), LEVEL_STAGESEVEN, TEXT("Prototype_Component_Texture_Red"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To CStore_Potion : SetUp_Components(Texture)");
			return E_FAIL;
		}
		m_tPotion.iCost = 1;

		m_tUIInfo.fCX = 100.f;
		m_tUIInfo.fCY = 100.f;
		m_tUIInfo.fX = 460.f;
		m_tUIInfo.fY = 280.f;
		break;
	}
	case POTION_BLUE: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_BluePotion"), LEVEL_STAGESEVEN, TEXT("Prototype_Component_Texture_Blue"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To CStore_Potion : SetUp_Components(Texture)");
			return E_FAIL;
		}
		m_tPotion.iCost = 1;

		m_tUIInfo.fCX = 100.f;
		m_tUIInfo.fCY = 100.f;
		m_tUIInfo.fX = 460.f;
		m_tUIInfo.fY = 380.f;
		break;
	}
	case POTION_EXIT: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Exit"), LEVEL_STAGESEVEN, TEXT("Prototype_Component_Texture_Exit"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To CStore_Potion : SetUp_Components(Texture)");
			return E_FAIL;
		}
		m_tUIInfo.fCX = 40.f;
		m_tUIInfo.fCY = 40.f;
		m_tUIInfo.fX = 858.f;
		m_tUIInfo.fY = 53.f;
		break;
	}
	}
	m_tPotion.RectPicking.left = LONG(m_tUIInfo.fX - m_tUIInfo.fCX * 0.5f);
	m_tPotion.RectPicking.top = LONG(m_tUIInfo.fY - m_tUIInfo.fCY * 0.5f);
	m_tPotion.RectPicking.right = LONG(m_tUIInfo.fX + m_tUIInfo.fCX * 0.5f);
	m_tPotion.RectPicking.bottom = LONG(m_tUIInfo.fY + m_tUIInfo.fCY * 0.5f);

	m_iUIType = UI_STOREOBJECT;

	return S_OK;
}

void CStore_Potion::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	m_pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front());
	Safe_AddRef(m_pPlayer);

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tPotion.RectPicking, pt)) {
		if (m_pGameInstance->Key_Down(VK_LBUTTON)) {
			if (POTION_EXIT == m_tPotion.ePotionType) {
				list<CGameObject*>* pStoreList = m_pGameInstance->Find_Layer_List(LEVEL_STAGESEVEN, L"Layer_Store");
				if (nullptr != pStoreList) {
					for (auto& iter : *pStoreList) {
						iter->Set_Dead();
					}
				}
			}
			else if (m_pPlayer->Get_Meso() >= m_tPotion.iCost) {
				switch (m_tPotion.ePotionType) {
				case POTION_RED: {
					m_pPlayer->Set_RedPotion();
					m_pPlayer->Set_Meso(m_tPotion.iCost);
					break;
				}
				case POTION_BLUE: {
					m_pPlayer->Set_BluePotion();
					m_pPlayer->Set_Meso(m_tPotion.iCost);
					break;
				}
				}
			}
		}
	}

	Safe_Release(m_pPlayer);
}

void CStore_Potion::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CStore_Potion::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CStore : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CStore_Potion::SetUp_Components() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CSemi_2 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CSemi_2 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CSemi_2 : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CStore_Potion * CStore_Potion::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CStore_Potion* pInstance = new CStore_Potion(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CStore_Potion : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CStore_Potion::Clone(void * pArg) {
	CStore_Potion* pInstance = new CStore_Potion(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CStore_Potion : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStore_Potion::Free() {
	__super::Free();
}