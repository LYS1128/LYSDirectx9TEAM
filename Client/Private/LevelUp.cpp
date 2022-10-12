#include "stdafx.h"
#include "..\Public\LevelUp.h"

CLevelUp::CLevelUp(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CLevelUp::CLevelUp(const CLevelUp & rhs)
	: CUI(rhs)
{
}

HRESULT CLevelUp::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CLevelUp : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLevelUp::NativeConstruct(void * pArg) {
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CLevelUp : NativeConstruct");
		return E_FAIL;
	}
	m_pGraphic_Device->GetViewport(&m_ViewPort);
	D3DXMatrixOrthoLH(&m_ProjMatrix, (_float)m_ViewPort.Width, (_float)m_ViewPort.Height, 0.f, 1.f);

	m_tUIInfo.fCX = 200.f;
	m_tUIInfo.fCY = 300.f;
	m_tUIInfo.fX = 640.f;
	m_tUIInfo.fY = 280.f;

	m_iUIType = UI_END;
	CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
	CSound_Manager::GetInstance()->PlaySound(L"Levelup.wav", CSound_Manager::EFFECT, VOLUME);

	return S_OK;
}

void CLevelUp::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CLevelUp::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	++m_iTickCount;
	if (5 <= m_iTickCount) {
		m_iTickCount = 0;
		++m_iSprite;
		if (21 <= m_iSprite) {
			m_iSprite = 0;
			m_eState = STATE_DEAD;
		}
	}
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_UI, this);
}

HRESULT CLevelUp::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevelUp : Render");
		return E_FAIL;
	}
	
	return S_OK;
}

HRESULT CLevelUp::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_LevelUp"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CLevelUp * CLevelUp::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevelUp* pInstance = new CLevelUp(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CLevelUp : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CLevelUp::Clone(void * pArg) {
	CLevelUp*	pInstance = new CLevelUp(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CLevelUp : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevelUp::Free() {
__super::Free();
Safe_Release(m_pTransform);
Safe_Release(m_pTexture);
Safe_Release(m_pVIBuffer);
Safe_Release(m_pRenderer);
}