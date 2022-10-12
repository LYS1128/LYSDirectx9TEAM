#include "stdafx.h"
#include "..\Public\Quiz_UI.h"



CQuiz_UI::CQuiz_UI(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CQuiz_UI::CQuiz_UI(const CQuiz_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CQuiz_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CQuiz_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CQuiz_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CQuiz_UI : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CQuiz_UI : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 1000.f;
	m_tUIInfo.fCY = 180.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f - 200.f;

	m_iUIType = UI_LOGO;
	m_iSprite = 0;
	return S_OK;
}

void CQuiz_UI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
		
}

void CQuiz_UI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	++m_iTickCount;
	++m_iQuizCount;

	_float3 PlayerPos = dynamic_cast<CTransform*>(m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"))->Get_State(CTransform::STATE_POSITION);

	if (m_iTickCount == 7)
	{
		m_iTickCount = 0;

		++m_iSprite;
		
		if (m_iSprite == 10 && m_iQuizCount <= 252)
		{
			m_iSprite = 9;
		}
		else if (m_iSprite == 21 && m_iQuizCount <= 504)
		{
			m_iSprite = 20;
		}
		else if (m_iSprite == 32 && m_iQuizCount <= 1008)
		{
			m_iSprite = 31;
			CSound_Manager::GetInstance()->PlaySound(L"TickTock.wav", CSound_Manager::SYSTEM_EFFECT2, VOLUME);
		}
		else if (m_iSprite == 44 && m_iQuizCount <= 1260)
		{
			if (PlayerPos.x >= 12.f && m_bCheck == false)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT2);
				CSound_Manager::GetInstance()->PlaySound(L"Success.wav", CSound_Manager::SYSTEM_EFFECT3, VOLUME);
				m_bCheck = true;
				m_pPlayer->Exp_Plus(m_pPlayer->Get_Player_Info().iMaxExp * 0.3f);
				
			}
			else if (PlayerPos.x <= 12.f && m_bCheck == false)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT2);
				CSound_Manager::GetInstance()->PlaySound(L"Warning.wav", CSound_Manager::SYSTEM_EFFECT3, VOLUME);
				m_bCheck = true;
				m_pPlayer->Hp_Minus(m_pPlayer->Get_Player_Info().iMaxHp * 0.3f);			
			}
			m_iSprite = 43;
		}
		else if (m_iSprite == 55 && m_iQuizCount <= 1764)
		{
			CSound_Manager::GetInstance()->PlaySound(L"TickTock.wav", CSound_Manager::SYSTEM_EFFECT2, VOLUME);
			m_bCheck = false;
			m_iSprite = 54;
		}
		else if (m_iSprite == 66 && m_iQuizCount <= 2016)
		{
			if (PlayerPos.x <= 12.f && m_bCheck == false)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT2);
				CSound_Manager::GetInstance()->PlaySound(L"Success.wav", CSound_Manager::SYSTEM_EFFECT3, VOLUME);
				m_bCheck = true;
				m_pPlayer->Exp_Plus(m_pPlayer->Get_Player_Info().iMaxExp * 0.3f);
			}
			else if (PlayerPos.x >= 12.f && m_bCheck == false)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT2);
				CSound_Manager::GetInstance()->PlaySound(L"Warning.wav", CSound_Manager::SYSTEM_EFFECT3, VOLUME);
				m_bCheck = true;
				m_pPlayer->Hp_Minus(m_pPlayer->Get_Player_Info().iMaxHp * 0.3f);
			}
			m_iSprite = 65;
		}
		else if (m_iSprite == 77 && m_iQuizCount <= 2520)
		{
			CSound_Manager::GetInstance()->PlaySound(L"TickTock.wav", CSound_Manager::SYSTEM_EFFECT2, VOLUME);
			m_bCheck = false;
			m_iSprite = 76;
		}
		else if (m_iSprite == 88 && m_iQuizCount <= 2772)
		{
			m_iSprite = 87;
			if (PlayerPos.x <= 12.f&& m_bCheck == false)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT2);
				CSound_Manager::GetInstance()->PlaySound(L"Success.wav", CSound_Manager::SYSTEM_EFFECT3, VOLUME);
				m_bCheck = true;
				m_pPlayer->Exp_Plus(m_pPlayer->Get_Player_Info().iMaxExp * 0.3f);
			}
			else if (PlayerPos.x >= 12.f && m_bCheck == false)
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT2);
				CSound_Manager::GetInstance()->PlaySound(L"Warning.wav", CSound_Manager::SYSTEM_EFFECT3, VOLUME);
				m_bCheck = true;
				m_pPlayer->Hp_Minus(m_pPlayer->Get_Player_Info().iMaxHp * 0.3f);
			}
		}
		else if (m_iSprite == 99 && m_iQuizCount <= 3024)
		{
			m_iSprite = 98;
		}
		else if (m_iSprite == 101 && m_iQuizCount <= 3087)
		{
			m_iSprite = 100;
		}
		else if (m_iSprite == 103 && m_iQuizCount <= 3150)
		{
			m_iSprite = 102;
		}
		else if (m_iSprite == 104)
			m_eState = STATE_DEAD;
	}
	


}

HRESULT CQuiz_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CQuiz_UI : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CQuiz_UI::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CQuiz_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_QuizUI"), LEVEL_STAGETWO_1, TEXT("Prototype_Component_Texture_QuizUI"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CQuiz_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CQuiz_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CQuiz_UI : SetUp_Components");
		return E_FAIL;
	}
	
	return S_OK;
}

CQuiz_UI * CQuiz_UI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CQuiz_UI*	pInstance = new CQuiz_UI(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CQuiz_UI : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CQuiz_UI::Clone(void * pArg)
{
	CQuiz_UI*	pInstance = new CQuiz_UI(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CQuiz_UI : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CQuiz_UI::Free()
{
	__super::Free();
}
