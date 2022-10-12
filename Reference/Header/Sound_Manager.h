#pragma once
#include "Base.h"

BEGIN(Engine)

class CSound_Manager final : public CBase {
	DECLARE_SINGLETON(CSound_Manager)
public: 
	enum CHANNELID {BGM, PLAYER, MONSTER, EFFECT, UI, MAXCHANNEL};
private:
	CSound_Manager();
	virtual ~CSound_Manager() = default;
public:
	HRESULT NativeConstruct(); 
public:
	void PlaySound(TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void PlayBGM(TCHAR* pSoundKey, float fVolume);
	void StopSound(CHANNELID eID);
	void StopAll();
	void SetChannelVolume(CHANNELID eID, float fVolume);
private:
	void LoadSoundFile(); 
private:
	map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL]; 
	FMOD_SYSTEM* m_pSystem; 
public:
	virtual void Free() override;
};

END