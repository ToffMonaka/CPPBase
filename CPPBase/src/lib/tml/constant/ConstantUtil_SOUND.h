/**
 * @file
 * @brief ConstantUtil_SOUNDヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"
#include "ConstantInclude_OpenALSoftBase.h"


namespace tml {
namespace ConstantUtil {
namespace SOUND {
	namespace CLASS_NAME {
	}
	namespace RESOURCE_NAME {
	}
	enum class RESOURCE_TYPE : UINT {
		NONE = 0U,
		BASE,
		SOUND,
		USER,
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SOUND::RESOURCE_TYPE::COUNT);
	enum class SOUND_TYPE : UINT {
		NONE = 0U,
		BASE,
		BGM,
		SE,
		USER,
		COUNT
	};
	const UINT SOUND_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SOUND::SOUND_TYPE::COUNT);
	enum class EVENT_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT EVENT_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SOUND::EVENT_TYPE::COUNT);
}
}
}


namespace tml {
namespace sound {
class Manager;
class Sound;
class SoundDesc;
class BGMSound;
class BGMSoundDesc;
class SESound;
class SESoundDesc;
}
}
