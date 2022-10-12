#include "stdafx.h"
#include "..\Public\Magician.h"

CMagician::CMagician(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CNPC(pGraphic_Device)
{
}

CMagician::CMagician(const CMagician & rhs)
	: CNPC(rhs)
{
}

HRESULT CMagician::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMagician : NativeConstruct_Prototype");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CMagician::NativeConstruct(void * pArg)
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

	m_pTransform->Scaled(_float3(1.5f, 2.0f, 1.5f));

	return S_OK;
}

void CMagician::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (m_pGameInstance->Key_Down('Z') && Check_Player_InArea())
	{
		if (g_iLevel == LEVEL_TUTORIAL)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"치얼업 베이베~");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"치얼업 베이베~!");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"좀 더 힘을 내~!");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"...엥? 뭐야, 이런 곳에 이방인이?");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"누구세요잇?");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"어.... 그런 일이.... 대박;;");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"그렇다면 정식으로 저를 소개하겠습니다잇.");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"안녕하세요잇! 저는 상현공주입니다잇.");

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"잠깐 저에게 손을 줘보실래요잇?");

					++m_iTextSprite;
					break; }
				case 10: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 11: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"이... 이건 도대체?!");

					++m_iTextSprite;
					break; }
				case 12: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...당신 혹시 한가하다면 이 세계의 영웅이 되어보시지 않겠어요잇?");

					++m_iTextSprite;
					break; }
				case 13: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"조작법: WSAD(상하좌우) SPACE(점프) ENTER(포탈)");

					++m_iTextSprite;
					break; }
				case 14: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L";;;");

					++m_iTextSprite;
					break; }
				case 15: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"위에 있는 포탈을 타고 다음 스테이지로 오세요잇! 기다리고 있을게요잇!");

					++m_iTextSprite;
					break; }
				case 16: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List();
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"? 빨리 가세요잇.");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List();
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
		else if (g_iLevel == LEVEL_STAGEONE)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"빨리도 오셨네요잇. (시계를 본다....)");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"...괜찮습니다잇. 원래 처음에는 다들 그렇더라구요잇.");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...?");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"잡담은 여기까지! 우리 세계에서 살아나갈 수 있는 방법을 알려드릴게요잇.");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"혹시 공격하는 방법은 알고 있으세요잇?");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"에휴잇.... 제가 알려드릴게요잇. ");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"조작법: 1(Freezing)");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"한 번 찔러보세요잇.");

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 10: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"좋아요잇. 준비가 다 된 것 같네요잇.");

					++m_iTextSprite;
					break; }
				case 11: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"지금 저 포탈이 빨간색인게 보이세요잇? 저런 상태일 때는 포탈을 이용하실 수 없어요잇.");


					++m_iTextSprite;
					break; }
				case 12: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"왠지 맵 안쪽에 있는 박 몬스터를 잡으면 포탈이 열릴 것만 같아요잇.");

					++m_iTextSprite;
					break; }
				case 13: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"아.... 그런데 누가 저 박을 처리해준담?");

					++m_iTextSprite;
					break; }
				case 14: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;");

					++m_iTextSprite;
					break; }
				case 15: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"얼른 다녀오세요잇.");

					++m_iTextSprite;
					break; }
				case 16: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"아참!");
					++m_iTextSprite;
					break; }
				case 17: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"조작법 - K(스탯창보기)");
					++m_iTextSprite;
					break; }
				case 18: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"그럼 빨리 가세요잇. (1초... 2초... 3초..........)");
					++m_iTextSprite;
					break; }
				case 19: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L";;;;;;");

					++m_iTextSprite;

					break; 
				}
				case 20: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_QuestWindow", L"Prototype_GameObject_QuestWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CQuest::QUEST tQuest;
					tQuest.tFont.eTextId = CText::TEXT_QUEST;
					tQuest.tFont.rc = { 1060, 325, g_iWinCX, 400 };
					lstrcpy(tQuest.tFont.szText, L"잡은 몬스터 수 ( %d");
					tQuest.tFont.tFontInfo.Width =15;
					tQuest.tFont.tFontInfo.Height = 10;
					tQuest.tFont.vARGB = _float4(255, 0, 0, 0);
					tQuest.iRequireMonsterCnt = 1;
					tQuest.iOption = 0;

					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Quest", L"Prototype_Quest", &tQuest);

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List();
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"34초... 35초... 36초...");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List();
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
					CQuestWindow* pQuestWindow = (CQuestWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_QuestWindow")->Get_List()->front());
					pQuestWindow->Set_Dead();
					

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"아라라... 벌써 박을 부수셨단 말이에요잇...? 제법인걸요잇....");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1:{
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"(박이 이렇게 쉽게...? 저 녀석 보기보다... 실압근?)");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 3: {
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"좋아요잇! 이제 포탈의 색깔이 파란색으로 변했을거에요잇!");
					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"어서 다음 스테이지로 이동해요잇! 가보자잇!");
					++m_iTextSprite;
					
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...?");

					++m_iTextSprite;
					break; }
				case 6: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List();
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"가보자~ 가보자~");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List();
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
		else if (g_iLevel == LEVEL_STAGETWO)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"영웅님! 어서오세요잇!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"혹시 아이템을 사용하는 방법을 아세요잇?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"이 세계의 몬스터들과 맞서기 위해선 물약은 필수에요잇! 필수~!");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"HP가 모자라면 파란물약, MP가 모자라면 빨간물약을 먹어보세요잇!");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"아.... 반대인가...? 아무튼! 여기 물약이에요잇!");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"조작법: Ctrl+1(빨간물약). Ctrl+2(파란물약)");
					dynamic_cast<CPlayer*>((m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front()))->PlusHpPo();
					dynamic_cast<CPlayer*>((m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front()))->PlusMpPo();

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"그리고, 영웅님에게 앞으로 필요할 스킬을 하나 알려드릴게요잇!");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"우선 신발이랑 양말을 벗고 신성한 의식을 준비하세요잇!");

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...?");

					++m_iTextSprite;
					break; }
				case 10: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"농담이에요잇! 손을 줘보실래요잇?");

					++m_iTextSprite;
					break; }
				case 11: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"조작법: 2(Cray)");
					dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_SkillOpen(64);

					++m_iTextSprite;
					break; }
				case 12: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"어때요잇? 몸 안이 힘으로 가득 찬 느낌이죠잇?");

					++m_iTextSprite;
					break; }
				case 13: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"그럼 슬라임을 잡아 그 증거로 몬스터의 소울을 다섯 개 가져오세요잇!");

					++m_iTextSprite;
					break; }
				case 14: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"몬스터가 떨어트린 아이템 근처로 다가가면 얻을 수 있어요잇.");

					++m_iTextSprite;
					break; }
				case 15: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"빨리요잇! 밥값하러 가세요잇!");

					++m_iTextSprite;
					break; }
				case 16: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;");

					++m_iTextSprite;
					break; }
				case 17: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_QuestWindow", L"Prototype_GameObject_QuestWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CQuest::QUEST tQuest;
					tQuest.tFont.eTextId = CText::TEXT_QUEST;
					tQuest.tFont.rc = { 1060, 325, g_iWinCX, 400 };
					lstrcpy(tQuest.tFont.szText, L"가진 소울의 수 ( %d");
					tQuest.tFont.tFontInfo.Width = 15;
					tQuest.tFont.tFontInfo.Height = 10;
					tQuest.tFont.vARGB = _float4(255, 0, 0, 0);
					tQuest.iRequireMonsterCnt = 5;
					tQuest.iOption = 1;

					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Quest", L"Prototype_Quest", &tQuest);

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List();
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"어.... 소울은 어디에 있는거죠잇? 혼나요잇!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List();
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
					CQuestWindow* pQuestWindow = (CQuestWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_QuestWindow")->Get_List()->front());
					pQuestWindow->Set_Dead();
				

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"하나... 둘... 다섯!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"잘했어요잇! 포탈의 색깔이 파란색으로 변했어요잇!");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"다음 스테이지에서 당신의 실력을 평가해 보겠어요잇!");
					++m_iTextSprite;
					break; }
				case 3: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List();
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"가보자~ 가보자~");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List();
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
					lstrcpy(tFont.szText, L"세젤귀상현공주");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"어머나~ 이게 누구야? 우리 영웅님 아니야?");
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
					pText->Set_Text(L"보아하니~ 제법 강해진 것 같네?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...!");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"제법이네? 맞아~ 전부 내가 꾸며낸 일이야.");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"요새 메이플 월드에 신참 모험가가 안 들어온다는 소문 들었지?");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"내가 다 잡아먹어버렸지롱~");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...!!!");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"세젤귀상현공주");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"열 낼 필요 없어~ 너도 그 중 하나일 뿐이니까.");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"네가 열심히 모은 소울은 내가 가져갈게~ 너는 여기서 죽도록 해.");
					dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Lost_Soul();

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"그럼, 안녕?");

					++m_iTextSprite;
					break; }
				case 10 : {
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
	}
}

void CMagician::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	++m_iTick;

	if (m_iTick == 10) {
		++m_iSprite;
		m_iTick = 0;
	}

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CMagician::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMagician : Render");
		return E_FAIL;
	}

	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iSprite%6))) {
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

HRESULT CMagician::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CMagician : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureMagician"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Magician"), (CComponent**)&m_pTexture))) {
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

CMagician * CMagician::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CMagician*	pInstance = new CMagician(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CMagician : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMagician::Clone(void * pArg)
{
	CMagician*	pInstance = new CMagician(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CMagician : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician::Free()
{
	__super::Free();
}
