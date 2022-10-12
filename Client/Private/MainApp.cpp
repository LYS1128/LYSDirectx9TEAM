#include "stdafx.h"
#include "..\Public\MainApp.h"

CMainApp::CMainApp()
	:m_pGameInstance(CGameInstance::GetInstance()),
	m_dwTime(GetTickCount())
{
	Safe_AddRef(m_pGameInstance);
}

HRESULT CMainApp::NativeConstruct() {
	CGraphic_Device::INITENGINE InitDevice;
	ZeroMemory(&InitDevice, sizeof(CGraphic_Device::INITENGINE));

	InitDevice.hWnd = g_hWnd;
	InitDevice.iWinCX = g_iWinCX;
	InitDevice.iWinCY = g_iWinCY;	

	if (FAILED(m_pGameInstance->Initialize_Engine(g_hInst, LEVEL_END, InitDevice, &m_pGraphic_Device))) {
		MSG_BOX(L"Failed To CMainApp : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Prototype_Component())) {
		MSG_BOX(L"Failed To CMainApp : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_RenderState())) {
		MSG_BOX(L"Failed To CMainApp : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Font())) {
		MSG_BOX(L"Failed To CMainApp : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(OpenLevel(LEVEL_LOGO))) {
		MSG_BOX(L"Failed To CMainApp : NativeConstruct");
		return E_FAIL;
	}
	CSound_Manager::GetInstance()->NativeConsruct();
	return S_OK;
}

void CMainApp::Tick(_float fTimeDelta) {
	if (nullptr == m_pGameInstance) {
		return;
	}
 	m_pGameInstance->Tick_Engine(fTimeDelta);
}

HRESULT CMainApp::Render() {
	if (FAILED(m_pGameInstance->Render_Begin())) {
		MSG_BOX(L"Failed To CMainApp : Render");
		return E_FAIL;
	}
	if (FAILED(m_pRenderer->Render_GameObjects())) {
		MSG_BOX(L"Failed To CMainApp : Render");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Render_Engine())) {
		MSG_BOX(L"Failed To CMainApp : Render");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Render_End())) {
		MSG_BOX(L"Failed To CMainApp : Render");
		return E_FAIL;
	}

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

	return S_OK;
}

HRESULT CMainApp::OpenLevel(LEVEL eLevelIndex) {
	if (nullptr == m_pGameInstance) {
		MSG_BOX(L"Failed To CMainApp : OpenLevel");
		return E_FAIL;
	}
	CLevel* pLevel = nullptr;
	if (LEVEL_LOGO == eLevelIndex) {
		pLevel = CLevel_Logo::Create(m_pGraphic_Device);
	}
	else {

	}
	if (m_pGameInstance->OpenLevel(eLevelIndex, pLevel)) {
		MSG_BOX(L"Failed To CMainApp : OpenLevel");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMainApp::SetUp_Prototype_Component() {
	//트랜스폼
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), CTransform::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CMainApp : SetUp_Prototype_Component");
		return E_FAIL;
	}
	//버퍼
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), CVIBuffer_Rect::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CMainApp : SetUp_Prototype_Component");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Cube"), CVIBuffer_Cube::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CMainApp : SetUp_Prototype_Component");
		return E_FAIL;
	}
	//렌더러
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), m_pRenderer = CRenderer::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CMainApp : SetUp_Prototype_Component");
		return E_FAIL;
	}
	Safe_AddRef(m_pRenderer);
	//충돌
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, L"Prototype_Component_Collision", CCollision::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CMainApp : SetUp_Prototype_Component");
		return E_FAIL;
	}
	//쉐이더
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, L"Prototype_Component_Shader", CShader::Create(m_pGraphic_Device, TEXT("../Shader/Shader_Rect.hlsl"))))) {
		MSG_BOX(L"Failed To CMainApp : SetUp_Prototype_Component");
		return E_FAIL;
	}

	// UI
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOGO, TEXT("Prototype_Component_Texture_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Logo/Logo%d.png"), 151)))) {
		MSG_BOX(L"Failed To CMainApp : SetUp_Prototype_Component");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI"), CObject_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CMainApp : SetUp_Prototype_Component");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Mouse_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Mouse/Mouse%d.png"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(마우스)");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Mouse_UI"), CMouse_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(마우스)");
		return E_FAIL;
	}

#pragma region Loading
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_UI_LDSPR0"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Spring0/Loading_Spring0_%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(로딩이미지)");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDSPR0"), CLoad_Spring::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(봄로딩화면)");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STAGESEMIBOSS, TEXT("Prototype_Component_Texture_NNA"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Spring0/Loading_Spring0_0.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(로딩이미지)");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_NNA"), CNooNooAttack::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(봄로딩화면)");
		return E_FAIL;
	}



#pragma endregion


	return S_OK;
}

HRESULT CMainApp::SetUp_RenderState() {
	if (nullptr == m_pGraphic_Device) {
		MSG_BOX(L"Failed To CMainApp : SetUp_RenderState");
		return E_FAIL;
	}
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	return S_OK;
}

HRESULT CMainApp::Ready_Font() {
	if (FAILED(m_pGameInstance->Add_Prototype(L"Prototype_GameObject_Font", CText::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CMainApp : Ready_Font");
		return E_FAIL;
	}
	return S_OK;
}

CMainApp* CMainApp::Create() {
	CMainApp* pInstance = new CMainApp;
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CMainApp : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainApp::Free() {
	m_pGameInstance->Release_Engine();
	m_pGameInstance->Free();
	CSound_Manager::GetInstance()->DestroyInstance();
	Safe_Release(m_pGameInstance);
	Safe_Release(m_pRenderer);
}