#include "stdafx.h"
#include "../Default/stdafx.h"
#include "Camera_Default.h"
#include "GameInstance.h"

CCamera_Default::CCamera_Default(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCamera(pGraphic_Device)
{
}

CCamera_Default::CCamera_Default(const CCamera_Default & rhs)
	: CCamera(rhs)
{
}

HRESULT CCamera_Default::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCamera_Default::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

void CCamera_Default::Tick(_float fTimeDelta)
{
	if (Key_Down(VK_RBUTTON))
	{
		GetCursorPos(&m_pPreCur);
	}

	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		GetCursorPos(&m_pCurrentCur);

		if (fabs(m_pPreCur.x - m_pCurrentCur.x) > fabs(m_pPreCur.y - m_pCurrentCur.y))
		{
			if (m_pPreCur.x - m_pCurrentCur.x < 0)
			{
				m_pTransform->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta*(m_pCurrentCur.x - m_pPreCur.x) / 5.f);
			}

			if (m_pPreCur.x - m_pCurrentCur.x > 0)
			{
				m_pTransform->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta*(m_pCurrentCur.x - m_pPreCur.x) / 5.f);
			}
		}
		if (fabs(m_pPreCur.x - m_pCurrentCur.x) < fabs(m_pPreCur.y - m_pCurrentCur.y))
		{
			if (m_pPreCur.y - m_pCurrentCur.y < 0)
			{
				m_pTransform->Turn(m_pTransform->Get_State(CTransform::STATE_RIGHT), fTimeDelta*(m_pCurrentCur.y - m_pPreCur.y) / 5.f);
			}

			if (m_pPreCur.y - m_pCurrentCur.y > 0)
			{
				m_pTransform->Turn(m_pTransform->Get_State(CTransform::STATE_RIGHT), fTimeDelta*(m_pCurrentCur.y - m_pPreCur.y) / 5.f);
			}
		}

		GetCursorPos(&m_pPreCur);
	}

	if (GetKeyState('W') & 0x8000)
	{
		m_pTransform->Go_Straight(fTimeDelta);
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_pTransform->Go_BackWard(fTimeDelta);
	}
	if (GetKeyState('A') & 0x8000)
	{
		m_pTransform->Go_Left(fTimeDelta);
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_pTransform->Go_Right(fTimeDelta);
	}
	if (GetKeyState('Q') & 0x8000)
	{
		m_pTransform->Go_Up(fTimeDelta);
	}
	if (GetKeyState('E') & 0x8000)
	{
		m_pTransform->Go_Down(fTimeDelta);
	}

	__super::Tick(fTimeDelta);
}

void CCamera_Default::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CCamera_Default::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

CCamera_Default * CCamera_Default::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCamera_Default*	pInstance = new CCamera_Default(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created CCamera_Default"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCamera_Default::Clone(void * pArg)
{
	CCamera_Default*	pInstance = new CCamera_Default(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSG_BOX(TEXT("Failed to Created CCamera_Default"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera_Default::Free()
{
	__super::Free();

}

bool CCamera_Default::Key_Down(int iKey)
{
	if (!m_bKeyState[iKey] && (GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}

	if (m_bKeyState[iKey] && !(GetAsyncKeyState(iKey) & 0x8000))
		m_bKeyState[iKey] = !m_bKeyState[iKey];

	return false;
}