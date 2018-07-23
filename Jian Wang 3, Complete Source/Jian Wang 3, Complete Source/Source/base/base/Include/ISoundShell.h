
#ifndef   _ISOUND_H_HEADER_INCLUDED_
#define   _ISOUND_H_HEADER_INCLUDED_
 
struct ISoundShell
{
public:
	//## 销毁接口对象
	virtual  void	Release() = 0;
	//## 初始化音效播放
	virtual  BOOL	Init(HWND pWnd) = 0;

	//---------音效播放部分---------------
	//## 音效播放接口
	virtual  void	PlayASound(
		//## 待播放音效的文件名
		LPSTR FileName,
		//## 待播放音效的声相
		INT nPan,
		//## 待播放音效的音量
		INT nVol, 
		//## 待播放音效是否循环播放
		BOOL bLoop) = 0;

	//## 停止播放音效
	virtual  void	StopASound(
		//## 需要停止播放的音效的文件名
		LPSTR FileName) = 0;

	//## 设置音效播放的音量
	virtual  void	SetSoundVolume(
		//## 音效的文件名
		LPSTR FileName,
		//## 音效的播放音量
		LONG lVolume) = 0;
	//## 判断是否正在播放音效
	virtual  BOOL    IsPlayingSound(LPSTR FileName) = 0;
	virtual void StopAllSound() = 0;

	//---------音乐播放部分---------------
	//## 音乐播放接口
	virtual  void	PlayMusic(
		//## 待播放音乐的文件名
		LPSTR FileName,
		//## 是否循环播放音乐
		BOOL bLoop) = 0;

	//## 停止播放音乐接口
	virtual  void	StopMusic() = 0;

	//## 设置音乐播放的音量大小
	virtual  void	SetMusicVolume(
		//## 音量大小
		LONG lVolume) = 0;
	//## 判断是否正在播放音乐
	virtual  BOOL   IsPlayingMusic() = 0;

	//设置Log输出文件
	virtual	void	SetLogFile(class KLogFile*	pLogFile) = 0;

	//每帧都要调用下
	virtual void	Update() = 0;
};

//------模块的接口函数的原型的定义------
typedef ISoundShell*					(*fnCreateSoundShell)();

//------接口函数的函数名字符串----------
#define	FN_CREATE_SOUND_SHELL			"CreateSoundShell"


#endif //_ISOUND_H_HEADER_INCLUDED_
