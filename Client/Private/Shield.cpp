#include "stdafx.h"
#include "..\Public\Shield.h"

CShield::CShield(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CEffect(pGraphic_Device)
{
}

CShield::CShield(const CShield& rhs)
	: CEffect(rhs)
{
}

HRESULT CShield::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CShield : NativeConstruct_Prototype");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CShield::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CShadow : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CShadow : NativeConstruct");
		return E_FAIL;
	}

	m_tSkillFrame.fFrame = 0.f;
	m_tSkillFrame.iSpriteEnd = 6;

	CTransform* pTargetTransform = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));
	Safe_AddRef(pTargetTransform);

	_float3 fPlayerPos = pTargetTransform->Get_State(CTransform::STATE_POSITION);
	m_pTransform->Set_State(CTransform::STATE_POSITION, fPlayerPos);
	CPlayer::BASICSTATE ePlayerState = *(CPlayer::BASICSTATE*)pArg;

	_float3 BuffLook = _float3(1.f, 0.f, 1.f);
	D3DXVec3Normalize(&BuffLook, &BuffLook);
	m_pTransform->Set_State(CTransform::STATE_LOOK, BuffLook);

	_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffRight, &BuffRight);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, BuffRight);


	m_pTransform->Scaled(_float3(2.0f, 2.0f, 2.0f));
	Safe_Release(pTargetTransform);

	
	return S_OK;
}

void CShield::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	CGameInstance*   pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CTransform*      pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"));

	_float3 vTargetPos = pTargetTransform->Get_State(CTransform::STATE_POSITION);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vTargetPos - m_pTransform->Get_State(CTransform::STATE_LOOK));

	for(_uint i = 0; i <5;++i)
		m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_ShieldParticle", &vTargetPos);

	Safe_Release(pGameInstance);

}

void CShield::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	_float4x4		ViewMatrix;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	_float3		vScale = m_pTransform->Get_Scale();

	m_pTransform->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0] * vScale.x);
	//m_pTransform->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0] * vScale.y);
	m_pTransform->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0] * vScale.z);


	m_fFrame += 6 * fTimeDelta;		//돌릴 스프라이트수 * 타임델타

	if ((_uint)m_fFrame == m_tSkillFrame.iSpriteEnd) {
		dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_State(STATE_ALIVE);
	}

	if (m_fFrame >= 6)
		m_fFrame = 0.f;

	Compute_ZDis(m_pTransform);
	//m_fZDis += 1.0f;

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CShield::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CShield : Render");
		return E_FAIL;
	}

	if (FAILED(m_pTexture->Bind_OnGraphicDevice((_uint)m_fFrame)))
		return E_FAIL;

	if (FAILED(m_pTransform->Bind_OnGraphicDevice()))
		return E_FAIL;

	m_pVIBuffer->Render();

	return S_OK;
}

HRESULT CShield::SetUp_Components()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc)))
	{
		MSG_BOX(L"Failed To CShield : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRenderer)))
	{
		MSG_BOX(L"Failed To CShield : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBuffer)))
	{
		MSG_BOX(L"Failed To CShield : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Shield"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Shield"), (CComponent**)&m_pTexture)))
	{
		MSG_BOX(L"Failed To CShield : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CShield * CShield::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CShield*	pInstance = new CShield(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed To CShield : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CShield::Clone(void * pArg)
{
	CShield* pInstance = new CShield(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed To CShield : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CShield::Free()
{
	__super::Free();

	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);

}
