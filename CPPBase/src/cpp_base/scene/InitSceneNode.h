/**
 * @file
 * @brief InitSceneNode�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"
#include "BaseNode.h"


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneNodeDesc�N���X
 */
class InitSceneNodeDesc : public cpp_base::scene::BaseNodeDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	InitSceneNodeDesc();
	virtual ~InitSceneNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void cpp_base::scene::InitSceneNodeDesc::Release(void)
{
	cpp_base::scene::BaseNodeDesc::Release();

	return;
}


namespace cpp_base {
namespace scene {
/**
 * @brief InitSceneNode�N���X
 */
class InitSceneNode : public cpp_base::scene::BaseNode
{
public: InitSceneNode(const cpp_base::scene::InitSceneNode &) = delete;
public: cpp_base::scene::InitSceneNode &operator =(const cpp_base::scene::InitSceneNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	UINT progress_type_;

public:
	tml::shared_ptr<tml::graphic::Canvas2D> canvas_2d;
	tml::shared_ptr<tml::graphic::Model2D> bg_model;
	tml::TIME_REAL wait_update_time;
	tml::shared_ptr<tml::graphic::Font> wait_font;
	tml::shared_ptr<tml::graphic::Model2D> wait_model;

protected:
	void Release(void);

public:
	InitSceneNode();
	virtual ~InitSceneNode();

	virtual void Init(void);
	INT Create(const cpp_base::scene::InitSceneNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
