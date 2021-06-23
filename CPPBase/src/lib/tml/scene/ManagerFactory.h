/**
 * @file
 * @brief ManagerFactory�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_SCENE.h"
#include "../manager/ManagerResourceFactory.h"


namespace tml {
namespace scene {
/**
 * @brief ManagerFactory�N���X
 */
class ManagerFactory
{
public: ManagerFactory(const tml::scene::ManagerFactory &) = delete;
public: tml::scene::ManagerFactory &operator =(const tml::scene::ManagerFactory &) = delete;

private:
	tml::scene::Manager *mgr_;

public:
	tml::ManagerResourceFactory<tml::scene::Scene, tml::INIFileReadDesc> scene_by_ini_file;
	tml::ManagerResourceFactory<tml::scene::Scene, tml::XMLFileReadDesc> scene_by_xml_file;
	tml::ManagerResourceFactory<tml::scene::Node, tml::INIFileReadDesc> node_by_ini_file;
	tml::ManagerResourceFactory<tml::scene::Node, tml::XMLFileReadDesc> node_by_xml_file;

private:
	void SetNodeRecursivePart(const tml::shared_ptr<tml::scene::Node> &, const tml::shared_ptr<tml::XMLFileDataNode> &);

protected:
	void Release(void);

public:
	ManagerFactory();
	virtual ~ManagerFactory();

	virtual void Init(void);
	INT Create(tml::scene::Manager *);

	tml::scene::Manager *GetManager(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::scene::ManagerFactory::Release(void)
{
	return;
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::scene::Manager *tml::scene::ManagerFactory::GetManager(void)
{
	return (this->mgr_);
}
