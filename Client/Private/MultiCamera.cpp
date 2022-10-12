#include "stdafx.h"
#include "..\Public\MultiCamera.h"

CMultiCamera::CMultiCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CCamera(pGraphic_Device)
{
}

CMultiCamera::CMultiCamera(const CMultiCamera & rhs)
	: CCamera(rhs)
{
}

HRESULT CMultiCamera::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMultiCamera : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMultiCamera::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMultiCamera : NativeConstruct");
		return E_FAIL;
	}
	_float3	vLook = m_CameraDesc.vAt - m_CameraDesc.vEye;
	m_pTransform->Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook));

	_float3	vRight = *D3DXVec3Cross(&vRight, &m_CameraDesc.vAxisY, &vLook);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight));

	_float3	vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);
	m_pTransform->Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp));

	m_pTransform->Set_State(CTransform::STATE_POSITION, m_CameraDesc.vEye);
	return S_OK;
}

void CMultiCamera::Tick(_float fTimeDelta) {
	if (LEVEL_STAGESPECIAL != g_iLevel) {
		if ((GetKeyState('7') & 0x8000) && (dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Get_SkillOpen() & 2)) {
			m_Mode = 1;
		}
		else if ((GetKeyState('8') & 0x8000) && (dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Get_SkillOpen() & 1)) {
			m_Mode = 3;
		}
	}

	CTransform* pTargetTransform = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
	Safe_AddRef(pTargetTransform);

	if (nullptr == pTargetTransform) {
		Safe_Release(pTargetTransform);
		Safe_Release(m_pGameInstance);
		return;
	}
	if (m_Mode == 2)
	{
		if (m_Mode != m_PreMode)
		{
			pTargetTransform->Scaled(_float3(1.f, 1.5f, 1.f));
		}
		m_PreMode = 2;
		m_CameraDesc.vEye = pTargetTransform->Get_State(CTransform::STATE_POSITION) + _float3(0.f, 8.f, -12.f);
		m_CameraDesc.vAt = pTargetTransform->Get_State(CTransform::STATE_POSITION);

		_float3	vLook = m_CameraDesc.vAt - m_CameraDesc.vEye;
		m_pTransform->Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook));

		_float3	vRight = *D3DXVec3Cross(&vRight, &m_CameraDesc.vAxisY, &vLook);
		m_pTransform->Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight));

		_float3 vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);
		m_pTransform->Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp));

		m_pTransform->Set_State(CTransform::STATE_POSITION, m_CameraDesc.vEye);
	}
	//기본카메라
	if (m_Mode == 1) {

		if (m_Mode != m_PreMode)
		{
			_float3 vRight = _float3(1.f, 0.f, -1.f);
			_float3 vUp = _float3(0.f, 1.f, 0.f);
			_float3 vLook = _float3(1.f, 0.f, 1.f);

			D3DXVec3Normalize(&vRight, &vRight);
			D3DXVec3Normalize(&vUp, &vUp);
			D3DXVec3Normalize(&vLook, &vLook);

			pTargetTransform->Set_State(CTransform::STATE_RIGHT, vRight);
			pTargetTransform->Set_State(CTransform::STATE_UP, vUp);
			pTargetTransform->Set_State(CTransform::STATE_LOOK, vLook);
			pTargetTransform->Scaled(_float3(1.f, 1.5f, 1.f));
		}



		m_PreMode = 1;
		m_CameraDesc.vEye = pTargetTransform->Get_State(CTransform::STATE_POSITION) + _float3(-5.f, 5.f, -5.f) + m_iSlowMove;
		m_CameraDesc.vAt = pTargetTransform->Get_State(CTransform::STATE_POSITION);

		_float3	vLook = m_CameraDesc.vAt - m_CameraDesc.vEye;
		m_pTransform->Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook));

		_float3	vRight = *D3DXVec3Cross(&vRight, &m_CameraDesc.vAxisY, &vLook);
		m_pTransform->Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight));

		_float3 vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);
		m_pTransform->Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp));

		m_pTransform->Set_State(CTransform::STATE_POSITION, m_CameraDesc.vEye);

		if (m_bCritical)
		{
			if (m_bPreCri == false)
			{
				m_iPreMove = m_iSlowMove;
				m_bPreCri = true;
				m_iCriticalTick = 0;
			}
			CriticalHit();
		}
	}

	//1인칭카메라
	else if (m_Mode == 3) {
		if (m_Mode != m_PreMode)
		{
			_float3 vRight = pTargetTransform->Get_State(CTransform::STATE_RIGHT);
			_float3 vUp = pTargetTransform->Get_State(CTransform::STATE_UP);
			_float3 vLook = pTargetTransform->Get_State(CTransform::STATE_LOOK);

			D3DXVec3Normalize(&vRight, &vRight);
			D3DXVec3Normalize(&vUp, &vUp);
			D3DXVec3Normalize(&vLook, &vLook);

			m_pTransform->Set_State(CTransform::STATE_RIGHT, vRight);
			m_pTransform->Set_State(CTransform::STATE_UP, vUp);
			m_pTransform->Set_State(CTransform::STATE_LOOK, vLook);
		}
		m_PreMode = 3;

		m_pTransform->Set_State(CTransform::STATE_POSITION, pTargetTransform->Get_State(CTransform::STATE_POSITION) + _float3(0.f, 1.f, 0.f));

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

		_float3 vRight = m_pTransform->Get_State(CTransform::STATE_RIGHT);
		_float3 vUp = m_pTransform->Get_State(CTransform::STATE_UP);
		_float3 vLook = m_pTransform->Get_State(CTransform::STATE_LOOK);

		D3DXVec3Normalize(&vRight, &vRight);
		D3DXVec3Normalize(&vUp, &vUp);
		D3DXVec3Normalize(&vLook, &vLook);

		pTargetTransform->Set_State(CTransform::STATE_RIGHT, vRight);
		pTargetTransform->Set_State(CTransform::STATE_UP, vUp);
		pTargetTransform->Set_State(CTransform::STATE_LOOK, vLook);
	}
	__super::Tick(fTimeDelta);
	Safe_Release(pTargetTransform);
}

void CMultiCamera::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CMultiCamera::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMultiCamera : Render");
		return E_FAIL;
	}
	return S_OK;
}

_bool CMultiCamera::Key_Down(int iKey) {
	if (!m_bKeyState[iKey] && (GetAsyncKeyState(iKey) & 0x8000)) {
		m_bKeyState[iKey] = !m_bKeyState[iKey];
		return true;
	}
	if (m_bKeyState[iKey] && !(GetAsyncKeyState(iKey) & 0x8000)) {
		m_bKeyState[iKey] = !m_bKeyState[iKey];
	}
	return false;
}

void CMultiCamera::BossPhase1()
{
	if (m_iSlowMove.y <= 1.f)
	{
		m_iSlowMove += _float3(-0.05f, 0.05f, -0.05f);
		}
}

void CMultiCamera::BossPhase2()
{
	if (m_iSlowMove.y <= 3.f)
	{
		m_iSlowMove += _float3(-0.05f, 0.05f, -0.05f);
		}
}


void CMultiCamera::BossPhase3()
{
	if (m_iSlowMove.y >=0.f)
	{
		m_iSlowMove -= _float3(-0.1f, 0.1f, -0.1f);
			}
}

void CMultiCamera::CriticalHit()
{
	++m_iCriticalTick;
	if (m_iCriticalTick <= 5)
	{
		m_iSlowMove += m_pTransform->Get_State(CTransform::STATE_RIGHT)*0.001;
		m_pTransform->Set_State(CTransform::STATE_LOOK, m_pTransform->Get_State(CTransform::STATE_LOOK) + m_pTransform->Get_State(CTransform::STATE_RIGHT)*0.001*m_iCriticalTick);
	}
	else if (m_iCriticalTick <= 15)
	{
		m_iSlowMove -= m_pTransform->Get_State(CTransform::STATE_RIGHT)*0.001;
		m_pTransform->Set_State(CTransform::STATE_LOOK, m_pTransform->Get_State(CTransform::STATE_LOOK) - m_pTransform->Get_State(CTransform::STATE_RIGHT)*0.001*(m_iCriticalTick -5));

	}
	else if (m_iCriticalTick <= 20)
	{
		m_iSlowMove += m_pTransform->Get_State(CTransform::STATE_RIGHT)*0.001;
		m_pTransform->Set_State(CTransform::STATE_LOOK, m_pTransform->Get_State(CTransform::STATE_LOOK) + m_pTransform->Get_State(CTransform::STATE_RIGHT)*0.001*(m_iCriticalTick - 15));

	}
	else
	{
		m_iSlowMove = m_iPreMove;
		m_bCritical = false;
		m_bPreCri = false;
	}

}

CMultiCamera* CMultiCamera::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CMultiCamera* pInstance = new CMultiCamera(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CMultiCamera : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMultiCamera::Clone(void* pArg) {
	CMultiCamera* pInstance = new CMultiCamera(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CMultiCamera : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMultiCamera::Free() {
	__super::Free();
}