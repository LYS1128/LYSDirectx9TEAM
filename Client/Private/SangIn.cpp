#include "stdafx.h"
#include "..\Public\SangIn.h"

CSangIn::CSangIn(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CNPC(pGraphic_Device)
{
}

CSangIn::CSangIn(const CSangIn & rhs)
	: CNPC(rhs)
{
}

HRESULT CSangIn::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CSangIn : NativeConstruct_Prototype");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CSangIn::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CSangIn : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CSangIn : NativeConstruct");
		return E_FAIL;
	}

	m_pTransform->Set_State(CTransform::STATE_POSITION, ((NPC*)pArg)->vPosition);

	_float3 BuffLook = _float3(1.f, 0.f, 1.f);
	D3DXVec3Normalize(&BuffLook, &BuffLook);
	m_pTransform->Set_State(CTransform::STATE_LOOK, BuffLook);

	_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffRight, &BuffRight);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, BuffRight);

	m_pTransform->Scaled(_float3(1.5f, 2.0f, 1.5f));

	return S_OK;
}

void CSangIn::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (m_pGameInstance->Key_Down('X') && Check_Player_InArea())
	{
		if (g_iLevel == LEVEL_STAGESEVEN)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"송☆채★바☆리");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"헐~!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"송☆채★바☆리");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"밑에 층 레이스 바글바글한거 진짜 선넘네;;");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"나 좀 도와주라;;");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"레이스 20마리만 잡아다 줘. 그러면 내가 좋은 물건을 팔아줄게. 오키?");

					++m_iTextSprite;
					break; }

				case 5: {
					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_QuestWindow", L"Prototype_GameObject_QuestWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CQuest::QUEST tQuest;
					tQuest.tFont.eTextId = CText::TEXT_QUEST;
					tQuest.tFont.rc = { 1060, 325, g_iWinCX, 400 };
					lstrcpy(tQuest.tFont.szText, L"잡은 몬스터 수 ( %d");
					tQuest.tFont.tFontInfo.Width = 15;
					tQuest.tFont.tFontInfo.Height = 10;
					tQuest.tFont.vARGB = _float4(255, 0, 0, 0);
					tQuest.iRequireMonsterCnt = 20;
					tQuest.iOption = 0;

					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Quest", L"Prototype_Quest", &tQuest);

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}

					m_iTextSprite = 0;
					m_iTalkState = 1;
					break;
				}
				}
			}
			else if (m_iTalkState == 1)
			{
				if (Complete_Quest() == true)
				{
					m_iTalkState = 2;
					return;
				}

				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"송☆채★바☆리");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(아래층의 레이스들을 향해 주먹을 휘두르며 위협하고 있다.)");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					break;
				}
				}
			}
			else if (m_iTalkState == 2)
			{
				switch (m_iTextSprite)
				{
				case 0: {
					list<CGameObject*>* listQuest = m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Quest");
					((CQuest*)(listQuest->front()))->Set_Dead();
					CQuestWindow* pQuestWindow = (CQuestWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_QuestWindow")->Get_List()->front());
					pQuestWindow->Set_Dead();

					dynamic_cast<CTheif*>(m_pGameInstance->Find_Layer_List(LEVEL_STAGESEVEN, L"Layer_NPC")->front())->Set_TalkState(2);

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"송☆채★바☆리");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"오! 땡큐땡큐!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"약속대로 내 물건들을 보여줄게. 특별히 싸게 넘기는 거야. 엣헴!");

					++m_iTextSprite;

					break; }
				case 2: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Store", L"Prototype_GameObject_Store");

					m_iTextSprite = 0;
					m_iTalkState = 3;
					break;
				}
				}
			}
			else if (m_iTalkState == 3)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"송☆채★바☆리");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"물약 사가실?");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Store", L"Prototype_GameObject_Store");

					m_iTextSprite = 0;
					break;
				}
				}
			}
		}
	}
}


void CSangIn::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	++m_iTick;

	if (m_iTick == 5) {
		++m_iSprite;
		m_iTick = 0;
	}

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CSangIn::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSangIn : Render");
		return E_FAIL;
	}


	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iSprite%6))) {
		MSG_BOX(L"Failed To CSangIn : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CSangIn : Render");
		return E_FAIL;
	}

	m_pVIBuffer->Render();
	return S_OK;
}

HRESULT CSangIn::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CSangIn : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureTheif"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_SangIn"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CSangIn : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CSangIn : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CSangIn : SetUp_Components");
		return E_FAIL;
 	}

	return S_OK;
}

CSangIn * CSangIn::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSangIn*	pInstance = new CSangIn(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSangIn : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CSangIn::Clone(void * pArg)
{
	CSangIn*	pInstance = new CSangIn(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSangIn : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSangIn::Free()
{
	__super::Free();
}
