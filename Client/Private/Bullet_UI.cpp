#include "stdafx.h"
#include "..\Public\Bullet_UI.h"



CBullet_UI::CBullet_UI(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CBullet_UI::CBullet_UI(const CBullet_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CBullet_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBullet_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBullet_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBullet_UI : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBullet_UI : NativeConstruct");
		return E_FAIL;
	}

	m_iSprite = 0;
	m_tUIInfo.fCX = 200;
	m_tUIInfo.fCY = 120;
	m_tUIInfo.fX = 1280 - 120;
	m_tUIInfo.fY = 720 - 80;

	
	m_iSprite = 0;
	
	return S_OK;
}

void CBullet_UI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	_uint BulletCount = m_pPlayer->Get_Bullet();
	
	switch (BulletCount)
	{
	case 0:
		m_iSprite = 20;
		break;
	case 1:
		m_iSprite = 19;
		break;
	case 2:
		m_iSprite = 18;
		break;
	case 3:
		m_iSprite = 17;
		break;
	case 4:
		m_iSprite = 16;
		break;
	case 5:
		m_iSprite = 15;
		break;
	case 6:
		m_iSprite = 14;
		break;
	case 7:
		m_iSprite = 13;
		break;
	case 8:
		m_iSprite = 12;
		break;
	case 9:
		m_iSprite = 11;
		break;
	case 10:
		m_iSprite = 10;
		break;
	case 11:
		m_iSprite = 9;
		break;
	case 12:
		m_iSprite = 8;
		break;
	case 13:
		m_iSprite = 7;
		break;
	case 14:
		m_iSprite = 6;
		break;
	case 15:
		m_iSprite = 5;
		break;
	case 16:
		m_iSprite = 4;
		break;
	case 17:
		m_iSprite = 3;
		break;
	case 18:
		m_iSprite = 2;
		break;
	case 19:
		m_iSprite = 1;
		break;
	case 20:
		m_iSprite = 0;
		break;
	}

}

void CBullet_UI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CBullet_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBullet_UI : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBullet_UI::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CBullet_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_UI_Bullet"), LEVEL_STAGESPECIAL, TEXT("Prototype_Component_Texture_UI_Bullet"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBullet_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBullet_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBullet_UI : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CBullet_UI * CBullet_UI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBullet_UI*	pInstance = new CBullet_UI(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CBullet_UI : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBullet_UI::Clone(void * pArg)
{
	CBullet_UI*	pInstance = new CBullet_UI(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CBullet_UI : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBullet_UI::Free()
{
	__super::Free();

}
