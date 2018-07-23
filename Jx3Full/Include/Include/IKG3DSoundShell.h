
#ifndef   _I_3D_SOUND_H_HEADER_INCLUDED_
#define   _I_3D_SOUND_H_HEADER_INCLUDED_

#ifndef D3DVECTOR_DEFINED
typedef struct _D3DVECTOR {
	float x;
	float y;
	float z;
} D3DVECTOR;
#define D3DVECTOR_DEFINED
#endif

//------录制声音操作相关定义------------
struct SoundParameters
{
	static const int sMaxNum = 10;
	int nNum;
	int nFrom[sMaxNum];
	size_t size_tDataSize;
	char* pData; 
	SoundParameters():nNum(0),size_tDataSize(0),pData(0){};
};

enum SoundFunctionType
{
	SOUNDFT_PLAYBGMUSIC,
    SOUNDFT_STOPBGMUSIC,
    SOUNDFT_SETBGMUSICVOLUME,
    SOUNDFT_SETBGMUSICLOOP
};

typedef HRESULT (*RecordSoundEventFuc)(SoundFunctionType EventFunction, SoundParameters& AParameters);


struct IKG3DSoundShell
{
public:
	virtual ULONG AddRef() = 0;
	//销毁接口对象
	virtual ULONG Release() = 0;
	//初始化音效播放
	virtual HRESULT	Init(HWND hWnd) = 0;

	virtual HRESULT Active() = 0;

	//收听者接口
	virtual HRESULT	SetListenerPosition(D3DVECTOR* pvPosition, D3DVECTOR* pvVelocity) = 0;
	virtual HRESULT	GetListenerPosition(D3DVECTOR* pvPosition, D3DVECTOR* pvVelocity) = 0;
	virtual HRESULT	SetOrientation(D3DVECTOR* pvFront, D3DVECTOR* pvTop) = 0;
	virtual HRESULT	SetListenerParameters(FLOAT fDopplerFactor, FLOAT fRolloffFactor) = 0;

	virtual HRESULT	SetVolume(float fVolume) = 0; //设置整体音量 0 - 1
	virtual float	GetVolume() = 0; //取得整体音量
	virtual HRESULT	SetVolume(int nType, float fVolume) = 0; //设置这一类型的音乐的音量 0 - 1
	virtual float	GetVolume(int nType) = 0; //取得这一类型的音量

	virtual HRESULT	Lock() = 0; //锁定，这个时候停止播放声音
	virtual HRESULT	Unlock() = 0; //解除锁定，这个时候看Enable的情况是否播放
	virtual BOOL	IsLocked() = 0; //是否被锁定

	virtual HRESULT	Enable(BOOL bEnable) = 0; //允许播放音乐
	virtual BOOL	IsEnable() = 0;
	virtual HRESULT	Enable(int nType, BOOL bEnable) = 0; //允许播放这一类型音乐
	virtual BOOL	IsEnable(int nType) = 0;

	virtual HRESULT	Enable3DSound(BOOL bEnable) = 0; //允许3D方式播放音效
	virtual BOOL	IsEnable3DSound() = 0;

	//----------2D音乐接口-----------------
	//播放背景音乐，同时只能播放一个背景音乐，mp3，双通道
	virtual HRESULT PlayBgMusic(int nType, LPCSTR FileName, INT nPan, float fVolume) = 0;
	virtual HRESULT StopBgMusic(BOOL bImmediately) = 0;
	virtual HRESULT SetBgMusicVolume(float fVolume) = 0;
	virtual BOOL	IsPlayingBgMusic() = 0; 
	virtual BOOL	IsPlayingBgMusic(LPCSTR FileName) = 0;
	virtual BOOL	IsBgMusicLoop() = 0;
	virtual HRESULT	SetBgMusicLoop(BOOL bLoop) = 0;

	//播放其他音乐，比如人物内心对白等，可以同时存在多个。mp3，双通道
	virtual HRESULT PlayMusic(int nType, LPCSTR FileName, INT nPan, float fVolume, BOOL bLoop, DWORD *pdwID) = 0;
	virtual HRESULT StopMusic(DWORD dwID) = 0;
	virtual HRESULT SetMusicVolume(DWORD dwID, float fVolume) = 0;
	virtual BOOL	IsPlayingMusic(DWORD dwID) = 0;
	virtual BOOL	IsPlayingMusic(LPCSTR FileName) = 0;
	virtual HRESULT StopAllMusic() = 0;

	//播放音效，比如界面提示音。可以同时存在多个。wav,双通道
	virtual HRESULT PlaySound(int nType, LPCSTR FileName, INT nPan, float fVolume, BOOL bLoop, DWORD *pdwID) = 0;
	virtual HRESULT StopSound(DWORD dwID) = 0;
	virtual HRESULT StopSoundAfterThisTime(DWORD dwID) = 0;
	virtual HRESULT SetSoundVolume(DWORD dwID, float fVolume) = 0;
	virtual BOOL	IsPlayingSound(DWORD dwID) = 0;
	virtual BOOL	IsPlayingSound(LPCSTR FileName) = 0;
	virtual HRESULT StopAllSound() = 0;


	//----------3D音乐接口-----------------
	//播放其他音乐，比如人物对话，可以同时存在多个。mp3，单通道
	virtual HRESULT Play3DMusic(int nType, LPCSTR FileName, float fVolume, BOOL bLoop, D3DVECTOR* pvPosition, D3DVECTOR* pvVelocity, FLOAT fMinDistance, FLOAT fMaxDistance, DWORD *pdwID) = 0;
	virtual HRESULT Stop3DMusic(DWORD dwID) = 0;
	virtual HRESULT Set3DMusicVolume(DWORD dwID, float fVolume) = 0;
	virtual BOOL	IsPlaying3DMusic(DWORD dwID) = 0;
	virtual BOOL	IsPlaying3DMusic(LPCSTR FileName) = 0;
	virtual HRESULT	Set3DMusicPosition(DWORD dwID, D3DVECTOR* pvPosition, D3DVECTOR* pvVelocity) = 0;
	virtual HRESULT	Set3DMusicParameters(DWORD dwID, FLOAT fMinDistance, FLOAT fMaxDistance) = 0;
	virtual HRESULT StopAll3DMusic() = 0;

	//播放音效，比如打击声音，或者特效声音。可以同时存在多个。wav，单通道
	virtual HRESULT Play3DSound(int nType, LPCSTR FileName, float fVolume, BOOL bLoop, D3DVECTOR* pvPosition, D3DVECTOR* pvVelocity, FLOAT fMinDistance, FLOAT fMaxDistance, DWORD *pdwID) = 0;
	virtual HRESULT Stop3DSound(DWORD dwID) = 0;
	virtual HRESULT Stop3DSoundAfterThisTime(DWORD dwID) = 0;
	virtual HRESULT Set3DSoundVolume(DWORD dwID, float fVolume) = 0;
	virtual BOOL	IsPlaying3DSound(DWORD dwID) = 0;
	virtual BOOL	IsPlaying3DSound(LPCSTR FileName) = 0;
	virtual HRESULT	Set3DSoundPosition(DWORD dwID, D3DVECTOR* pvPosition, D3DVECTOR* pvVelocity) = 0;
	virtual HRESULT	Set3DSoundParameters(DWORD dwID, FLOAT fMinDistance, FLOAT fMaxDistance) = 0;
	virtual HRESULT StopAll3DSound() = 0;

	//录音接口
	virtual HRESULT StartRecordSound() = 0;
	virtual HRESULT StopRecordSound() = 0;
	virtual HRESULT LockRecordSoundBuffer(void **ppBuffer, DWORD *pdwSize) = 0;
	virtual HRESULT ClearRecordSoundBuffer() = 0;
	virtual HRESULT UnlockRecordSoundBuffer() = 0;
	virtual void * GetRecordSoundWaveFormatEx() = 0;

    //录操作接口相关
	virtual HRESULT SetEventRecordFuc(RecordSoundEventFuc pFunc) = 0;
};

struct IKG3DSoundShellHolder
{
	virtual BOOL InitSoundShell() = 0;
	virtual void UnInitSoundShell() = 0;
	virtual void UpdateSoundShell() = 0;
	virtual IKG3DSoundShell *GetSoundShell() = 0;
};

//------模块的接口函数的原型的定义------
typedef IKG3DSoundShell*					(*fnCreate3DSoundShell)();

//------接口函数的函数名字符串----------
#define	FN_CREATE_3DSOUND_SHELL			"Create3DSoundShell"

#ifdef K3DSOUND_EXPORTS
	extern "C" __declspec(dllexport) IKG3DSoundShell*  Create3DSoundShell();
#else
	extern "C" __declspec(dllimport) IKG3DSoundShell*  Create3DSoundShell();
#endif

#define WM_KG3DSOUND_MSG (WM_USER + 1020)
#define KG3DSOUND_MUSIC_FINISHED 1

#endif //_ISOUND_H_HEADER_INCLUDED_
