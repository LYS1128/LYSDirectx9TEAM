#include "stdafx.h"
#include "..\Public\HP_UI.h"

CHP_UI::CHP_UI(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CHP_UI::CHP_UI(const CHP_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CHP_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CHP_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CHP_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CHP_UI : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CHP_UI : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 56.f;
	m_tUIInfo.fCY = 110.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f - 26.7f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 243.f;

	m_pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front());

	return S_OK;
}

void CHP_UI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	m_fPercent = (_float)(m_pPlayer->Get_Player_Info().iHp) / (_float)(m_pPlayer->Get_Player_Info().iMaxHp);
	if (0.f >= m_fPercent) {
		m_fPercent = 0.f;
	}
}

void CHP_UI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CHP_UI::Render() {
	if (FAILED(m_pTexture->Bind_OnShader(m_pShader, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pTransform->Bind_OnShader(m_pShader, "g_WorldMatrix")))
		return E_FAIL;

	_float4x4 ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	if (FAILED(m_pShader->SetUp_RawValue("g_fPercent", &m_fPercent, sizeof(_float))))
		return E_FAIL;
	if (FAILED(m_pShader->SetUp_RawValue("g_ViewMatrix", &ViewMatrix, sizeof(_float4x4))))
		return E_FAIL;
	if (FAILED(m_pShader->SetUp_RawValue("g_ProjMatrix", &m_ProjMatrix, sizeof(_float4x4))))
		return E_FAIL;

	m_pShader->Begin();
	m_pShader->Begin_Pass(0);

	m_pVIBuffer->Render();

	m_pShader->End_Pass();
	m_pShader->End();

	return S_OK;
}

HRESULT CHP_UI::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CHP_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_HP_UI"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_HP_UI"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CHP_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CHP_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CHP_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Shader"), LEVEL_STATIC, TEXT("Prototype_Component_Shader"), (CComponent**)&m_pShader)))
		return E_FAIL;

	return S_OK;
}

CHP_UI * CHP_UI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CHP_UI*	pInstance = new CHP_UI(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CHP_UI : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CHP_UI::Clone(void * pArg)
{
	CHP_UI*	pInstance = new CHP_UI(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CHP_UI : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHP_UI::Free()
{
	__super::Free();
	Safe_Release(m_pShader);
}
