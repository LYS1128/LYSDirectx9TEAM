#include "stdafx.h"
#include "..\Public\Theif.h"

CTheif::CTheif(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CNPC(pGraphic_Device)
{
}

CTheif::CTheif(const CTheif & rhs)
	: CNPC(rhs)
{
}

HRESULT CTheif::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CTheif : NativeConstruct_Prototype");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CTheif::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CTheif : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CTheif : NativeConstruct");
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

void CTheif::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (m_pGameInstance->Key_Down('Z') && Check_Player_InArea())
	{
		if (g_iLevel == LEVEL_STAGESIX)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(...게슴츠레한 눈으로 쳐다보고 있다.)");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;;;");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zX문어왕한승Xz");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"당신! 그래, 당신 말이야.");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"당신이 그 소문의 영웅이로군!");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"나 말이야? 나로 말할 것 같으면....");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"이 세계의 현자 문어왕이다.");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zX문어왕한승Xz");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"흠.... 그래. 하지만 아직 부족해.");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"조금 더 강해진 후에 꼭대기로 올라오도록!");

					++m_iTextSprite;
					break; }
				case 9: {
					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_QuestWindow", L"Prototype_GameObject_QuestWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CQuest::QUEST tQuest;
					tQuest.tFont.eTextId = CText::TEXT_QUEST;
					tQuest.tFont.rc = { 1060, 325, g_iWinCX, 400 };
					lstrcpy(tQuest.tFont.szText, L"20레벨 달성 ( %d");
					tQuest.tFont.tFontInfo.Width = 15;
					tQuest.tFont.tFontInfo.Height = 10;
					tQuest.tFont.vARGB = _float4(255, 0, 0, 0);
					tQuest.iRequireMonsterCnt = 20;
					tQuest.iOption = 2;

					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Quest", L"Prototype_Quest", &tQuest);

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}

					m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(79.51f, 20.5f, 55.51f));

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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"레벨 20을 달성하고 오도록!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List();
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
					CQuestWindow* pQuestWindow = (CQuestWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_QuestWindow")->Get_List()->front());
					pQuestWindow->Set_Dead();
					

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"이야~ 벌써 레벨 20을 달성했군!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"(과연 영웅.... ???를 무찌를 재목이군...!)");

					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"이제 이 기술을 전수해줄 때가 되었다. 세상을 뒤흔들 기술을 가르쳐주지!");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"조작법: 5(Earthquake)");
					dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_SkillOpen(8);
					++m_iTextSprite;
					break; }
				case 4: {
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"포탈을 열어두었으니 다음 스테이지에서 보세.");
					++m_iTextSprite;

					break; }
				case 5: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(무언가를 생각하고 있다.)");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Font")->Get_List();
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
		}
		else if (g_iLevel == LEVEL_STAGESEVEN)
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
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"음? 자네는....");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"아, 그래. 내가 여기로 오라고 했었지?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;;;");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zX문어왕한승Xz");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"저기 유적 윗층에 곤란에 처한 상인이 있는 것 같군.");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"가서 저 자를 도와주게.");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;;;;;;");

					++m_iTextSprite;
					break; }
				case 6: {

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
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"어서 가서 도와주게나. 좋은 물건을 얻을 수 있을걸세.");
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
					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"좋아, 훌륭한 인성 또한 영웅의 미덕이라네.");
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
					pText2->Set_Text(L"일취월장 하는군, 영웅!");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"자네에게라면 궁극의 비기를 알려주어도 될 것 같네. 위험한 힘이니 조심히 사용하게.");
					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"조작법: 6(MoonLight)");
					dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_SkillOpen(4);
					++m_iTextSprite;
					break; }
				case 4: {
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"그럼 다음 스테이지에서 보세. 만만치 않은 곳이니 필요한 물건이 있다면 지금 구입하는 것이 좋을게야.");
					++m_iTextSprite;
					break; }
				case 5: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
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
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(심각한 얼굴로 고민하고 있다.)");
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
		}
		else if (g_iLevel == LEVEL_STAGEEIGHT)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"드디어 이곳으로 왔군, 영웅!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"그렇군.... 결국 이렇게 될 운명인가....");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zX문어왕한승Xz");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"이제 앞으로 나아가도록 하게. 이 길의 끝에 그대의 운명이 기다리고 있네!");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zX문어왕한승Xz");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"마지막으로 물어볼 게 있다니.... 이제까지 무슨 생각을 그렇게 했냐고?");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"그건 당연하지 않은가.");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"오늘 점심 뭐 먹지?");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"난 이제 점심을 먹으러 가봐야겠군. 행운을 비네, 영웅....");

					++m_iTextSprite;
					break; }
				case 9: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}

					m_eState = STATE_DEAD;
					m_iTextSprite = 0;
					m_iTalkState = 1;
					break;
				}
				}
			}
		}
		else if (g_iLevel == LEVEL_STAGEBOSS)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"상현공주의 마왕 발록을 무찔렀군, 모험가여!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"나는 점심으로 햄버거를 먹고 왔다네.");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;;;");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zX문어왕한승Xz");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"이 세계를 지켜주어서 고맙네! 자네는 영웅이야!");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zX문어왕한승Xz");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"보답으로 즐길 거리를 준비했다네. 미니게임을 즐겨보게나!");

					++m_iTextSprite;
					break; }
				case 6: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List();
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
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"zX문어왕한승Xz");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"Team: 고영웅 강한승 김상현 이윤서");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List();
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
		}
	}
}

void CTheif::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	++m_iTick;

	if (m_iTick == 10) {
		++m_iSprite;
		m_iTick = 0;
	}

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CTheif::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CTheif : Render");
		return E_FAIL;
	}


	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iSprite % 8))) {
		MSG_BOX(L"Failed To CTheif : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CTheif : Render");
		return E_FAIL;
	}

	m_pVIBuffer->Render();
	return S_OK;
}

HRESULT CTheif::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CTheif : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureTheif"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Theif"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CTheif : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CTheif : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CTheif : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CTheif * CTheif::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTheif*	pInstance = new CTheif(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CTheif : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CTheif::Clone(void * pArg)
{
	CTheif*	pInstance = new CTheif(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CTheif : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTheif::Free()
{
	__super::Free();
}
