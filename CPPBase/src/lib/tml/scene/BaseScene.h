/**
 * @file
 * @brief BaseScene�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathPosition.h"
#include "Scene.h"


namespace tml {
namespace scene {
/**
 * @brief BaseSceneDesc�N���X
 */
class BaseSceneDesc : public tml::scene::SceneDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	BaseSceneDesc();
	virtual ~BaseSceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::BaseSceneDesc::Release(void)
{
	tml::scene::SceneDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief BaseScene�N���X
 */
class BaseScene : public tml::scene::Scene
{
public: BaseScene(const tml::scene::BaseScene &) = delete;
public: tml::scene::BaseScene &operator =(const tml::scene::BaseScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	BaseScene();
	virtual ~BaseScene();

	virtual void Init(void);
	INT Create(const tml::scene::BaseSceneDesc &);

	virtual INT Start(void);
	virtual void End(void);
	virtual void Update(void);
};
}
}
