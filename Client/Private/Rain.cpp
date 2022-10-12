#include "stdafx.h"
#include "..\Public\Rain.h"



CRain::CRain(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CRain::CRain(const CRain & rhs)
	:CGameObject(rhs)
{
}

HRESULT CRain::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CRain : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CRain::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CRain : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CRain : NativeConstruct");
		return E_FAIL;
	}

	m_pTransform->Scaled(_float3(0.03f, 0.06f, 0.03f));
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(rand() % 80 - 20.f, 30.f, rand() % 80 - 20.f));

	return S_OK;
}

void CRain::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	
		m_pTransform->Go_Down(fTimeDelta*1.8f);
		if (m_pTransform->Get_State(CTransform::STATE_POSITION).y <= -10.f)
		{
			m_eState = STATE_DEAD;
		}
}

void CRain::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	if (m_pGameInstance->Check_InOut(m_pTransform->Get_State(CTransform::STATE_POSITION), (m_pTransform->Get_Scale().x*0.5f)))
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CRain::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTexture->Bind_OnGraphicDevice(0))) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}


	m_pVIBuffer->Render();

	return S_OK;
}

HRESULT CRain::SetUp_Components()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 7.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CRain : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Rain"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Rain"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CRain : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Cube", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CRain : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CRain : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CRain * CRain::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CRain*	pInstance = new CRain(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSlime : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CRain::Clone(void * pArg)
{
	CRain*	pInstance = new CRain(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSlime : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRain::Free()
{
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}
