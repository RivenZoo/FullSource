#ifndef _KG3DTYPES_H_
#define _KG3DTYPES_H_

#include <functional>
#include <map>
#include <string>

using TagSFXCallBackExtraInfo = std::map<std::string, std::function<void()>>;
enum 
{
	MTBT_DAMAGEPERCENTAGE,
	MTBT_MISSILE,
};
struct TagMotionCallBackExtraInfo
{
	void fData;
	DWORD dwData;
};

enum class enuAnimationControllerPriority
{
};

#endif
