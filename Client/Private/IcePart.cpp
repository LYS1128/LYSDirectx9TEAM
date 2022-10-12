#include "stdafx.h"
#include "..\Public\IcePart.h"

CIcePart::CIcePart(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CIcePart::CIcePart(const CIcePart & rhs)
	: CGameObject(rhs)
{
}

HRESULT CIcePart::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CIcePart : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CIcePart::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CIcePart : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CIcePart : NativeConstruct");
		return E_FAIL;
	}

	_float3 Pos = *((_float3*)pArg);


	_uint Rand = rand();
	m_pTransform->Scaled(_float3(0.1f + (Rand % 2)*0.05f, 0.1f + (Rand % 2)*0.05f, 0.1f + (Rand % 2)*0.05f));
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(Pos.x + cos(Rand), Pos.y - 0.3f, Pos.z + sin(Rand)));
	m_fOriginPosY = Pos.y - 0.3f;
	m_fGO = _float3(cos(Rand), (rand() % 11) / 10.f, sin(Rand));
	D3DXVec3Normalize(&m_fGO, &m_fGO);

	m_fG = rand() % 3 + 3.f;
	return S_OK;
}

void CIcePart::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	++m_TickCount;
	if (m_TickCount >= 50)
		m_eState = STATE_DEAD;

	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	vPos += m_fGO*0.05f;
	vPos.y = m_fOriginPosY + 2.4f * m_TickCount*0.1 - ((m_fG * pow(m_TickCount*0.1, 2)) * 0.5f);

	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);
	m_pTransform->Scaling(-fTimeDelta / 3);
}

void CIcePart::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CIcePart::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTexture->Bind_OnGraphicDevice(rand() % 3 + 13))) {
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

HRESULT CIcePart::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 7.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CRain : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Particle"), (CComponent**)&m_pTexture))) {
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

CIcePart * CIcePart::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CIcePart*	pInstance = new CIcePart(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CIcePart : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CIcePart::Clone(void * pArg) {
	CIcePart*	pInstance = new CIcePart(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CIcePart : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CIcePart::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}