#include "stdafx.h"
#include "..\Public\Ash.h"



CAsh::CAsh(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CAsh::CAsh(const CAsh & rhs)
	:CGameObject(rhs)
{
}

HRESULT CAsh::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CSnow : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CAsh::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CSnow : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CSnow : NativeConstruct");
		return E_FAIL;
	}

	m_pTransform->Scaled(_float3(0.06f, 0.06f, 0.06f));
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(rand() % 80- 20.f, -5.f, rand() % 80 - 20.f));


	m_fGO = _float3((rand() % 21 - 10) / 10.f, (rand() % 11) / 10.f, (rand() % 21 - 10) / 10.f);
	D3DXVec3Normalize(&m_fGO, &m_fGO);
	return S_OK;
}

void CAsh::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	
	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	vPos += m_fGO * m_pTransform->Get_TransDesc().fSpeedPerSec * fTimeDelta*((rand() % 11) / 10.f);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);

	if (m_pTransform->Get_State(CTransform::STATE_POSITION).y >= 15)
	{
		m_eState = STATE_DEAD;
	}
}

void CAsh::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	if (m_pGameInstance->Check_InOut(m_pTransform->Get_State(CTransform::STATE_POSITION), (m_pTransform->Get_Scale().x*0.5f)))
		m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CAsh::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iSprite))) {
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

HRESULT CAsh::SetUp_Components()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = _float(rand() % 3 + 1);
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CSnow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Ash"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Ash"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CSnow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Cube", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CSnow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CSnow : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CAsh * CAsh::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CAsh*	pInstance = new CAsh(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSlime : CSnow"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CAsh::Clone(void * pArg)
{
	CAsh*	pInstance = new CAsh(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSlime : CSnow"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CAsh::Free()
{
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}
