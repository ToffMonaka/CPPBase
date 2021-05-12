/**
 * @file
 * @brief ManagerCommon�R�[�h�t�@�C��
 */


#include "ManagerCommon.h"
#include "Manager.h"
#include "Scene.h"
#include "BaseScene.h"
#include "Node.h"
#include "Base2DNode.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::ManagerCommon::ManagerCommon() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::ManagerCommon::~ManagerCommon()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::ManagerCommon::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create�֐�
 * @param mgr (manager)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::scene::ManagerCommon::Create(tml::scene::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	return (0);
}
