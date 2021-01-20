/**
 * @file
 * @brief Model�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief ModelDesc�N���X
 */
class ModelDesc : public tml::graphic::ResourceDesc
{
public:
	tml::shared_ptr<tml::XMPosition> position;

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
	tml::ConstantUtil::GRAPHIC::MODEL_TYPE type_;

public:
	tml::shared_ptr<tml::XMPosition> position;

protected:
	void Release(void);
	INT Create(const tml::ConstantUtil::GRAPHIC::MODEL_TYPE, tml::graphic::ModelDesc &);

public:
	Model();
	virtual ~Model();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::MODEL_TYPE GetType(void) const;
};
}
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::MODEL_TYPE tml::graphic::Model::GetType(void) const
{
	return (this->type_);
}
