#include "stdafx.h"
#include "..\Public\Cube.h"

CCube::CCube(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CCube::CCube(const CCube & rhs)
	:CGameObject(rhs)
{
}

HRESULT CCube::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	m_fInfo = _float4(0, 0, 0, 0);

	return S_OK;
}

HRESULT CCube::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	m_fInfo = _float4(0, 0, 0, 0);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_fInfo = *(_float4*)pArg;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fInfo.x, m_fInfo.y, m_fInfo.z));
	return S_OK;
}

void CCube::Tick(_float fTimeDelta)
{

	__super::Tick(fTimeDelta);
}

void CCube::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CCube::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pTextureCom->Bind_OnGraphicDevice((_uint)m_fInfo.w)))
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_OnGraphicDevice()))
		return E_FAIL;

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CCube::SetUp_Components()
{
	CTransform::TRANSFORMDESC		TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 10.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), 0, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), 0, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), 0, TEXT("Prototype_Component_VIBuffer_Cube"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), 0, TEXT("Prototype_Component_Texture_Default"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

CCube* CCube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCube*	pInstance = new CCube(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCube"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCube::Clone(void * pArg)
{
	CCube*	pInstance = new CCube(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCube"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCube::Free()
{
	__super::Free();

	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
}
