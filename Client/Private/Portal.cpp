#include "stdafx.h"
#include "..\Public\Portal.h"
#include "../Public/Level_Loading.h"

CPortal::CPortal(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CNPC(pGraphic_Device)
{
}

CPortal::CPortal(const CPortal & rhs)
	: CNPC(rhs)
{
}

HRESULT CPortal::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMagician : NativeConstruct_Prototype");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CPortal::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMagician : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMagician : NativeConstruct");
		return E_FAIL;
	}

	m_pTransform->Set_State(CTransform::STATE_POSITION, ((NPC*)pArg)->vPosition);

	_float3 BuffLook = _float3(1.f, 0.f, 1.f);
	D3DXVec3Normalize(&BuffLook, &BuffLook);
	m_pTransform->Set_State(CTransform::STATE_LOOK, BuffLook);

	_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffRight, &BuffRight);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, BuffRight);

	m_pTransform->Scaled(_float3(1.f, 2.0f, 1.f));

	return S_OK;
}

void CPortal::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (m_pGameInstance->Key_Down('L'))
	{
		m_bOpen = true;
	}

	if (m_bOpen != m_bPreOpen)
	{
		m_bPreOpen = m_bOpen;
		if (!m_bOpen)
		{
			Safe_Release(m_pTexture);
			m_pTexture = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Portal", L"Com_Texture_RedPortal");
			Safe_AddRef(m_pTexture);
		}
		else
		{
			Safe_Release(m_pTexture);
			m_pTexture = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Portal", L"Com_Texture_BluePortal");
			Safe_AddRef(m_pTexture);
		}
	}

	if (m_bOpen && m_pGameInstance->Key_Down(VK_RETURN) && Check_Player_InArea())
	{
		switch (g_iLevel)
		{
		case Client::LEVEL_TUTORIAL:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGEONE)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGEONE:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGETWO)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGETWO:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGETWO_1)))) {
				return;
			}
			break;
		case Client::LEVEL_STAGETWO_1:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGETHREE)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGETHREE:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGEFOUR)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGEFOUR:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGESEMIBOSS)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGESEMIBOSS:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGESEMIAFTER)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGESEMIAFTER:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGEFIVE)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGEFIVE:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGESIX)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGESIX:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGESEVEN)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGESEVEN:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGEEIGHT)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGEEIGHT:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGEBOSS)))) {
				return;
			}
			break;
		}
		case Client::LEVEL_STAGEBOSS:
		{
			if (FAILED(m_pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGESPECIAL)))) {
				return;
			}
			break;
		}
		default:
			break;
		}
		}
	}
}

void CPortal::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	++m_iTick;

	if (m_iTick == 5) {
		++m_iSprite;
		m_iTick = 0;
	}

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CPortal::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMagician : Render");
		return E_FAIL;
	}

	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iSprite % 24))) {
		MSG_BOX(L"Failed To CMagician : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CMagician : Render");
		return E_FAIL;
	}

	m_pVIBuffer->Render();
	return S_OK;
}

HRESULT CPortal::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CMagician : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_RedPortal"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RedPortal"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CMagician : SetUp_Components");
		return E_FAIL;
	}
	
	Safe_Release(m_pTexture);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_BluePortal"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_BluePortal"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CMagician : SetUp_Components");
		return E_FAIL;
	}

	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CMagician : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CMagician : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CPortal * CPortal::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPortal*	pInstance = new CPortal(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CMagician : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CPortal::Clone(void * pArg)
{
	CPortal*	pInstance = new CPortal(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CMagician : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPortal::Free()
{
	__super::Free();
}
