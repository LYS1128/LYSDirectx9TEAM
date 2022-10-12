#include "stdafx.h"
#include "..\Public\Level_StageEight.h"

CLevel_StageEight::CLevel_StageEight(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_StageEight::NativeConstruct() {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageEight : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(L"Layer_Ground"))) {
		MSG_BOX(L"Failed To CLevel_StageEight : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(L"Layer_Player"))) {
		MSG_BOX(L"Failed To CLevel_StageEight : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_NPC(L"Layer_NPC"))) {
		MSG_BOX(L"Failed To CLevel_StageThree : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Portal(L"Layer_Portal"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}

	g_iLevel = LEVEL_STAGEEIGHT;

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);

	return S_OK;
}

void CLevel_StageEight::Tick(_float fTimeDelta) {

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CSound_Manager::GetInstance()->PlaySound(L"Stage_8.wav", CSound_Manager::BGM, VOLUME);

	if (m_iPhase == 0)
	{
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
		{
			MSG_BOX(L"Failed To CMagician : Tick");
			return;
		}

		CText::FONT tFont;
		ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont.rc = RECT{ 150, 440, 1280,520 };
		lstrcpy(tFont.szText, L"ㅈi존전ㅅr영웅");
		tFont.tFontInfo.Height = 40;
		tFont.tFontInfo.Width = 30;
		tFont.eTextId = CText::TEXT_NPC;
		tFont.vARGB = _float4(255, 255, 255, 255);

		CText::FONT tFont2;
		ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont2.rc = RECT{ 300, 500, 1280, 550 };
		lstrcpy(tFont2.szText, L"(이 길을 걸으면 드디어 내가 영웅이 될 수 있는 건가?)");
		tFont2.tFontInfo.Height = 30;
		tFont2.tFontInfo.Width = 20;
		tFont2.eTextId = CText::TEXT_NPC;
		tFont2.vARGB = _float4(255, 255, 255, 255);

		pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
		pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

		m_iPhase = 1;
	}
	else if (m_iPhase == 1 && pGameInstance->Key_Down('X'))
	{
		CText* pText = (CText*)(pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
		pText->Set_Text(L"가보자~ 가보자~");
		m_iPhase = 2;
	}
	else if (m_iPhase == 2 && pGameInstance->Key_Down('X'))
	{
		CTextWindow* pTextWindow = (CTextWindow*)(pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_TextWindow")->Get_List()->front());
		pTextWindow->Set_Dead();

		list<CGameObject*>* pText = pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List();
		for (auto iter : *pText)
		{
			if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
				iter->Set_Dead();
		}

		m_iPhase = 3;
	}

	if (pGameInstance->Key_Down('0')) {
		if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGEBOSS)))) {
			return;
		}
	}
	else
	{
		if (pGameInstance->Find_Layer_List(LEVEL_STAGEEIGHT, L"Layer_NPC")->size() == 0 && m_bTyphon == false)
		{
			m_bTyphon = true;

			for (_uint i = 0; i < 8; ++i)
			{
				CMonster::MONSTER tMonster;
				tMonster.mapCube = m_MapCube;
				tMonster.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
				tMonster.vPosition = _float3(rand() % 8 + 3.f, 35.f, rand() % 8 + 30.f);

				if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_Monster", TEXT("Prototype_GameObject_Typhon"), &tMonster))) {
					MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Typhon");
					return;
				}
			}

		}

		if (m_bTyphon == true && pGameInstance->Find_Layer_List(LEVEL_STAGEEIGHT, L"Layer_Monster")->size() == 0)
		{
			dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);
		}
	}

	if (rand()%5 == 0) {
		for (int i = 0; i < 20; ++i) {
			if (FAILED(Ready_Layer_Rain(L"Layer_Rain"))) {
				MSG_BOX(L"Failed To CLevel_EIght : Tick");
				return;
			}
		}
	}

	Safe_Release(pGameInstance);
}

HRESULT CLevel_StageEight::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_StageEight : Render");
		return E_FAIL;
	}
	//SetWindowText(g_hWnd, TEXT("8스테이지입니다."));
	return S_OK;
}

HRESULT CLevel_StageEight::Ready_Layer_Rain(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, pLayerTag, TEXT("Prototype_GameObject_Rain")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Rain");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageEight::Ready_Layer_Player(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	//list<CGameObject*>* p = (pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List());
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CShadow*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Shadow")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION,_float3(0.f,8.f,0.f));
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_HpLow(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageEight::Ready_Layer_NPC(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CNPC::NPC tNPC;
	tNPC.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tNPC.vPosition = _float3(-2.5f, 6.5f,0.f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, pLayerTag, TEXT("Prototype_GameObject_Theif"), &tNPC))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_NPC");
		return E_FAIL;
	}

	tNPC.vPosition = _float3(6.5f, 25.5f, 34.5f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, pLayerTag, TEXT("Prototype_GameObject_Magician"), &tNPC))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_NPC");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageEight::Ready_Layer_Portal(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(_float3(8.5f, 25.5f, 36.5f)));
	dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageEight::Ready_Layer_BackGround(const _tchar* pLayerTag) {
	if (FAILED(Load_Map(L"../../Data/StageEightMap.dat"))) {
		MSG_BOX(L"Failed To CLevel_StageEight : Ready_Layer_BackGround");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (auto iter : m_MapCube) {
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, pLayerTag, L"Prototype_GameObject_Ground",&iter))) {
			MSG_BOX(L"Failed To CLevel_StageEight : Ready_Layer_BackGround");
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_StageEight : Ready_Layer_BackGround");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}


CLevel_StageEight* CLevel_StageEight::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_StageEight* pInstance = new CLevel_StageEight(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageEight : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_StageEight::Free() {
	__super::Free();
}

HRESULT CLevel_StageEight::Load_Map(const TCHAR* pPath) {
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MSG_BOX(L"Failed To CLevel_StageEight : Load_Map");
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