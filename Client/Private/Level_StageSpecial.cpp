#include "stdafx.h"
#include "..\Public\Level_StageSpecial.h"

CLevel_StageSpecial::CLevel_StageSpecial(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_StageSpecial::NativeConstruct() {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(L"Layer_Ground"))) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(L"Layer_Player"))) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Camera())) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Portal(L"Layer_Portal"))) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_UI(L"Layer_UI"))) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : NativeConstruct");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CText::FONT tFont1;
	ZeroMemory(&tFont1.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont1.rc = RECT{ 500, 100, 1280, 150 };
	lstrcpy(tFont1.szText, L"");
	wsprintf(tFont1.szText, L"남은 목숨 : %d", m_iLife);
	tFont1.tFontInfo.Height = 50;
	tFont1.tFontInfo.Width = 40;
	tFont1.eTextId = CText::TEXT_NPC;
	tFont1.vARGB = _float4(255, 255, 255, 255);
	pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESPECIAL, L"Layer_LifeFont", L"Prototype_GameObject_Font", &tFont1);

	CText::FONT tFont2;
	ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont2.rc = RECT{ 500, 160, 1280, 210 };
	lstrcpy(tFont2.szText, L"");
	wsprintf(tFont2.szText, L"점수 : %d", m_iScore);
	tFont2.tFontInfo.Height = 50;
	tFont2.tFontInfo.Width = 40;
	tFont2.eTextId = CText::TEXT_NPC;
	tFont2.vARGB = _float4(255, 255, 255, 255);
	pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESPECIAL, L"Layer_ScoreFont", L"Prototype_GameObject_Font", &tFont2);

	Safe_Release(pGameInstance);

	g_iLevel = LEVEL_STAGESPECIAL;

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);

	return S_OK;
}

void CLevel_StageSpecial::Tick(_float fTimeDelta) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	
	CSound_Manager::GetInstance()->PlaySound(L"Stage_Special.wav", CSound_Manager::BGM, VOLUME);

	++m_iTick;

	if (m_iPreScore != m_iScore) {
		m_iPreScore = m_iScore;
		if (0 == m_iScore % 1000) {
			++m_iRegen;
		}
	}

	if (180 <= m_iTick) {
		m_iTick = 0;
		for (_uint i = 0; i < m_iRegen; ++i) {
			pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESPECIAL, L"Layer_SpecialMonster", L"Prototype_GameObject_Special", this);
		}
	}
	_tchar szBuff[256] = L"";
	wsprintf(szBuff, L"남은 생명 : %d", m_iLife);
	CText* pText = ((CText*)(pGameInstance->Find_Layer_List(LEVEL_STAGESPECIAL, L"Layer_LifeFont")->front()));
	pText->Set_Text(szBuff);

	_tchar szBuff2[256] = L"";
	wsprintf(szBuff2, L"점수 : %d", m_iScore);
	CText* pText2 = ((CText*)(pGameInstance->Find_Layer_List(LEVEL_STAGESPECIAL, L"Layer_ScoreFont")->front()));
	pText2->Set_Text(szBuff2);

	if (0 >= m_iLife && false == m_bGameOver) {
		m_bGameOver = true;
		pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_GameOver", L"Prototype_GameObject_GameOver_UI", this);
	}

	Safe_Release(pGameInstance);
}

HRESULT CLevel_StageSpecial::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : Render");
		return E_FAIL;
	}
	return S_OK;
}

void CLevel_StageSpecial::ReStart() {
	m_iPreScore = 0;
	m_iScore = 0;
	m_iLife = 5;
	m_iRegen = 1;
	m_bGameOver = false;

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	list<CGameObject*>* pMonsterList = pGameInstance->Find_Layer_List(LEVEL_STAGESPECIAL, L"Layer_SpecialMonster");
	if (nullptr != pMonsterList) {
		for (auto& iter : *pMonsterList) {
			Safe_Release(iter);
		}
		pMonsterList->clear();
	}
	Safe_Release(pGameInstance);
}

HRESULT CLevel_StageSpecial::Ready_Layer_Player(const _tchar * pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CShadow*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Shadow")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_RIGHT, _float3(1.f, 0.f, 0.f));
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_UP, _float3(0.f, 1.f, 0.f));
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_LOOK, _float3(0.f, 0.f, 1.f));
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(12.5f, 1.5f, 0.f));
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_HpLow(false);

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSpecial::Ready_Layer_Portal(const _tchar * pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(_float3(8.5f, 55.5f, 36.5f)));
	dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSpecial::Ready_Layer_BackGround(const _tchar * pLayerTag) {
	if (FAILED(Load_Map(L"../../Data/StageSpecial.dat"))) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : Ready_Layer_BackGround");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (auto iter : m_MapCube) {
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESPECIAL, pLayerTag, L"Prototype_GameObject_Ground", &iter))) {
			MSG_BOX(L"Failed To CLevel_StageSpecial : Ready_Layer_BackGround");
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESPECIAL, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : Ready_Layer_BackGround");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSpecial::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CPlayer* pPlayer = (CPlayer*)(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front());


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESPECIAL, pLayerTag, TEXT("Prototype_GameObject_UI_Bullet"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_UI_Bullet");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSpecial::Ready_Layer_Camera() {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (nullptr == pGameInstance) {
		Safe_Release(pGameInstance);
		return E_FAIL;
	}

	CMultiCamera* pCamera = (CMultiCamera*)(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Camera")->front());
	Safe_AddRef(pCamera);

	if (nullptr == pCamera) {
		Safe_Release(pGameInstance);
		Safe_Release(pCamera);
		return E_FAIL;
	}

	pCamera->Set_ModeFPS();

	Safe_Release(pCamera);
	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLevel_StageSpecial::Load_Map(const TCHAR * pPath) {
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : Load_Map");
		return E_FAIL;
	}
	DWORD dwByte = 0;
	_float4* pInfo = nullptr;

	while (true) {
		pInfo = new _float4;

		ReadFile(hFile, pInfo, sizeof(_float4), &dwByte, nullptr);

		if (0 == dwByte) {
			Safe_Delete(pInfo);
			break;
		}
		_uint iCubeIndex = (_uint(pInfo->x + 0.5f) * 10000 + _uint(pInfo->y + 0.5f) * 100 + _uint(pInfo->z + 0.5f));
		m_MapCube.insert(map<_uint, _float4>::value_type(iCubeIndex, *pInfo));

		Safe_Delete(pInfo);
	}
	CloseHandle(hFile);
	return S_OK;
}

CLevel_StageSpecial * CLevel_StageSpecial::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_StageSpecial* pInstance = new CLevel_StageSpecial(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageSpecial : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_StageSpecial::Free() {
	__super::Free();
}