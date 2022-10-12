#pragma once
#include "Client_Define.h"
#include "Base.h"
#include "GameInstance.h"
//게임오브젝트
#include "Ground.h"
#include "MultiCamera.h"
#include "Player.h"
#include "Slime.h"
#include "Sky.h"
#include "Shadow.h"
#include "EffectCray.h"
#include "Shield.h"
#include "Magician.h"
#include "Hexagon_UI.h"
#include "LSkillBox.h"
#include "RSkillBox.h"
#include "HP_UI.h"
#include "MP_UI.h"
#include "AlphaHP_UI.h"
#include "AlphaMP_UI.h"
#include "EarthQuake.h"
#include "TextWindow.h"
#include "Exp_UI.h"
#include "ExpIng_UI.h"
#include "Exp_Invisible_UI.h"
#include "Exp_Text.h"
#include "Exp_Text2.h"
#include "Exp_Text3.h"
#include "Warrior.h"
#include "Theif.h"
#include "PlayerName_UI.h"
#include "StatWindow.h"
#include "Portal.h"
#include "Damage.h"
#include "Ice.h"
#include "Gourd.h"
#include "Snow.h"
#include "Rain.h"
#include "Quest.h"
#include "QuestWindow.h"
#include "Freeze.h"
#include "MonsterHpBar.h"
#include "MonsterRealHp.h"
#include "Item.h"
#include "CuteBear.h"
#include "CokeMushroom.h"
#include "IceGolem.h"
#include "GameOver.h"
#include "Pumpkin.h"
#include "NooNoo.h"
#include "MiniNooNoo.h"
#include "CloneNooNoo.h"
#include "CoolDown.h"
#include "Ultimate_Skill.h"
#include "MoonLight_Effect.h"
#include "Dark_Effect.h"
#include "Semi_1.h"
#include "Semi_2.h"
#include "Hit_Effect.h"
#include "GhostStump.h"
#include "IronBoar.h"
#include "CokeGolem.h"
#include "FireBoar.h"
#include "BossHpBar.h"
#include "BossRealHp.h"
#include "CoolDown3.h"
#include "CoolDown4.h"
#include "CoolDown5.h"
#include "CoolDown6.h"
#include "CoolDown7.h"
#include "CoolDown8.h"
#include "Wraith.h"
#include "SangIn.h"
#include "Store.h"
#include "Store_Potion.h"
#include "Typhon.h"
#include "HpLow.h"

#include "Boss_Phase1.h"
#include "BossHit_Effect.h"
#include "Claw_Attack.h"
#include "FireBall_Attack.h"
#include "Mabubjin.h"
#include "Mabubjin_Attack.h"
#include "Meteor.h"

#include "Load_Semi0.h"
#include "Loading_Level1.h"
#include "Loading_Level2.h"
#include "Loading_Level3.h"
#include "Loading_Level4.h"
#include "Loading_Level4_1.h"
#include "Loading_Level5.h"
#include "Loading_Level6.h"
#include "Loading_Level7.h"
#include "Loading_Level8.h"
#include "Loading_LevelBoss.h"
#include "Balrog.h"
#include "Blast.h"
#include "Wyvern.h"
#include "Balrog_LH.h"
#include "Balrog_RH.h"
#include "Electric_Shock.h"
#include "Boss_Ice.h"
#include "PurplePog.h"
#include "Boss_Phase2_LH.h"
#include "Boss_Phase2_RH.h"
#include "Crash.h"
#include "FPS.h"
#include "Bullet.h"
#include "SpecialMonster.h"
#include "Bullet_UI.h"
#include "LevelUp.h"
#include "Circle.h"
#include "Particle.h"
#include "Sakura.h"
#include "Ash.h"
#include "EQParticle.h"
#include "IcePart.h"
#include "Siren.h"
#include "Cray_ParticleEffect.h"
#include "ShieldParticle.h"
#include "Blood.h"
#include "BossMeteor.h"
#include "FireParticle.h"
#include "BlastParticle.h"
#include "Quiz_UI.h"

BEGIN(Client)

class CLoader final : public CBase {
private:
	explicit CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLoader() = default;
public:
	CRITICAL_SECTION Get_CriticalSection();
	LEVEL Get_LevelIndex();
	const _tchar* Get_LoadingText() const;
	_bool Get_Finished() const;
public:
	HRESULT NativeConstruct(LEVEL eLevel);
	//레벨 로딩
public:
	HRESULT Loading_LevelTurotial();
	HRESULT Loading_LevelStageOne();
	HRESULT Loading_LevelStageTwo();
	HRESULT Loading_LevelStageTwo_1();
	HRESULT Loading_LevelStageThree();
	HRESULT Loading_LevelStageFour();
	HRESULT Loading_LevelStageSemiBoss();
	HRESULT Loading_LevelStageSemiAfter();
	HRESULT Loading_LevelStageFive();
	HRESULT Loading_LevelStageSix();
	HRESULT Loading_LevelStageSeven();
	HRESULT Loading_LevelStageEight();
	HRESULT Loading_LevelStageBoss();
	HRESULT Loading_LevelStageSpecial();
private:
	LEVEL m_eLevel = LEVEL_END;
	_bool m_bFinished = false;
	_tchar			m_szLoading[MAX_PATH] = TEXT("");
private:
	LPDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
	HANDLE m_hThread = 0;
	CRITICAL_SECTION m_CriticalSection;
public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eLevel);
	virtual void Free() override;
};

END