/**
 * @file
 * @brief TitleScene�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "BaseScene.h"


namespace cpp_base {
namespace scene {
/**
 * @brief TitleSceneDesc�N���X
 */
class TitleSceneDesc : public cpp_base::scene::BaseSceneDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	TitleSceneDesc();
	virtual ~TitleSceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::scene::TitleSceneDesc::Release(void)
{
	cpp_base::scene::BaseSceneDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief TitleScene�N���X
 */
class TitleScene : public cpp_base::scene::BaseScene
{
public: TitleScene(const cpp_base::scene::TitleScene &) = delete;
public: cpp_base::scene::TitleScene &operator =(const cpp_base::scene::TitleScene &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init(void);
	INT Create(const cpp_base::scene::TitleSceneDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
