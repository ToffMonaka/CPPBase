/**
 * @file
 * @brief Model�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief ModelDesc�N���X
 */
class ModelDesc : public tml::graphic::ResourceDesc
{
public:

public:
	ModelDesc();
	virtual ~ModelDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief Model�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Model : public tml::graphic::Resource
{
public: Model(const tml::graphic::Model &) = delete;
public: tml::graphic::Model &operator =(const tml::graphic::Model &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:

protected:
	void Release(void);
	INT Create(tml::graphic::ModelDesc &);

public:
	Model();
	virtual ~Model();

	virtual void Init(void);
};
}
}
