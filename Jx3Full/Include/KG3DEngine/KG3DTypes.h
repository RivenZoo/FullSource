#ifndef _KG3DTYPES_H_
#define _KG3DTYPES_H_

#include <functional>
#include <map>
#include <string>

using TagSFXCallBackExtraInfo = std::map<std::string, std::function<void()>>;

enum enuMotionTagBlockType
{
	MTBT_DAMAGEPERCENTAGE,
	MTBT_MISSILE,
	MTBT_FACEMOTION,
	
};
struct TagMotionCallBackExtraInfo
{
	std::vector<void> fData;
	DWORD dwData;
	enuMotionTagBlockType Type;
};

enum class enuAnimationControllerPriority
{
};

#endif
