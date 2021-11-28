/**
 * @file
 * @brief Model2D�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Model.h"


namespace tml {
namespace graphic {
struct DRAW_MODEL_2D_DATA_;
typedef DRAW_MODEL_2D_DATA_ DRAW_MODEL_2D_DATA;
}
}


namespace tml {
namespace graphic {
/**
 * @brief Model2DLayer�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Model2DLayer : public tml::graphic::ModelLayer
{
public: Model2DLayer(const tml::graphic::Model2DLayer &) = delete;
public: tml::graphic::Model2DLayer &operator =(const tml::graphic::Model2DLayer &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:

private:
	void Release(void);

public:
	Model2DLayer();
	virtual ~Model2DLayer();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief Model2DStage�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Model2DStage : public tml::graphic::ModelStage
{
public: Model2DStage(const tml::graphic::Model2DStage &) = delete;
public: tml::graphic::Model2DStage &operator =(const tml::graphic::Model2DStage &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:

private:
	void Release(void);

public:
	Model2DStage();
	virtual ~Model2DStage();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);

};
}
}


namespace tml {
namespace graphic {
/**
 * @brief Model2DDesc�N���X
 */
class Model2DDesc : public tml::graphic::ModelDesc
{
public:
	tml::Transform2D transform;
	tml::XMFLOAT4EX color;
	tml::XMFLOAT2EX size;
	bool size_auto_flag;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Model2DDesc();
	virtual ~Model2DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Model2DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Model2D�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Model2D : public tml::graphic::Model
{
public: Model2D(const tml::graphic::Model2D &) = delete;
public: tml::graphic::Model2D &operator =(const tml::graphic::Model2D &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	tml::Transform2D transform;
	tml::XMFLOAT4EX color;
	tml::XMFLOAT2EX size;
	tml::graphic::DRAW_MODEL_2D_DATA *draw_data;

private:
	void Release(void);

public:
	Model2D();
	virtual ~Model2D();

	virtual void Init(void);
	INT Create(const tml::graphic::Model2DDesc &);
};
}
}
