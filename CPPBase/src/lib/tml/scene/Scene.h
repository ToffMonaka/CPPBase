/**
 * @file
 * @brief Scene�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace scene {
/**
 * @brief SceneDesc�N���X
 */
class SceneDesc : public tml::scene::ManagerResourceDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	SceneDesc();
	virtual ~SceneDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::SceneDesc::Release(void)
{
	tml::scene::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief Scene�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Scene : public tml::scene::ManagerResource
{
public: Scene(const tml::scene::Scene &) = delete;
public: tml::scene::Scene &operator =(const tml::scene::Scene &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::SCENE::SCENE_TYPE type_;

protected:
	void Release(void);
	INT Create(const tml::scene::SceneDesc &, const tml::ConstantUtil::SCENE::SCENE_TYPE);

public:
	Scene();
	virtual ~Scene();

	virtual void Init(void);

	virtual INT Start(void) = 0;
	virtual void End(void) = 0;
	virtual void Update(void) = 0;

	tml::ConstantUtil::SCENE::SCENE_TYPE GetType(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::Scene::Release(void)
{
	tml::scene::ManagerResource::Release();

	return;
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::SCENE::SCENE_TYPE tml::scene::Scene::GetType(void) const
{
	return (this->type_);
}
