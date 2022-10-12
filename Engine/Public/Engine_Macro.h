#pragma once

#define	MSG_BOX(_message) MessageBox(nullptr, _message, L"System Message", MB_OK)

#define NO_COPY(CLASSNAME)									\
		private:											\
		CLASSNAME(const CLASSNAME&);						\
		CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)						\
		NO_COPY(CLASSNAME)									\
		private:											\
		static CLASSNAME* m_pInstance;						\
		public:												\
		static CLASSNAME* GetInstance();					\
		static unsigned long DestroyInstance();			

#define IMPLEMENT_SINGLETON(CLASSNAME)						\
		CLASSNAME* CLASSNAME::m_pInstance = NULL;			\
		CLASSNAME* CLASSNAME::GetInstance() {				\
			if(NULL == m_pInstance) {						\
				m_pInstance = new CLASSNAME;				\
			}												\
			return m_pInstance;								\
		}													\
		unsigned long CLASSNAME::DestroyInstance() {		\
			unsigned long dwRefCnt = 0;						\
			if(nullptr != m_pInstance) {					\
				dwRefCnt = m_pInstance->Release();			\
				if(0 == dwRefCnt)							\
					m_pInstance = nullptr;					\
			}												\
			return dwRefCnt;								\
		}

#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

#define BEGIN(NAMESPACE) namespace NAMESPACE { 
#define END }