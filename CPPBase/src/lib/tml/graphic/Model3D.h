/**
 * @file
 * @brief Model3Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Model.h"


namespace tml {
namespace graphic {
struct DRAW_MODEL_3D_DATA_;
typedef DRAW_MODEL_3D_DATA_ DRAW_MODEL_3D_DATA;
}
}


namespace tml {
namespace graphic {
/**
 * @brief Model3DLayerクラス
 *
 * インターフェースパターン
 */
class Model3DLayer : public tml::graphic::ModelLayer
{
public: Model3DLayer(const tml::graphic::Model3DLayer &) = delete;
public: tml::graphic::Model3DLayer &operator =(const tml::graphic::Model3DLayer &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:

private:
	void Release(void);

public:
	Model3DLayer();
	virtual ~Model3DLayer();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief Model3DStageクラス
 *
 * インターフェースパターン
 */
class Model3DStage : public tml::graphic::ModelStage
{
public: Model3DStage(const tml::graphic::Model3DStage &) = delete;
public: tml::graphic::Model3DStage &operator =(const tml::graphic::Model3DStage &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:

private:
	void Release(void);

public:
	Model3DStage();
	virtual ~Model3DStage();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);

};
}
}


namespace tml {
namespace graphic {
/**
 * @brief Model3DDescクラス
 */
class Model3DDesc : public tml::graphic::ModelDesc
{
public:
	tml::Transform3D transform;
	tml::XMFLOAT4EX color;
	tml::XMFLOAT3EX size;
	bool size_auto_flag;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Model3DDesc();
	virtual ~Model3DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Model3DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Model3Dクラス
 *
 * インターフェースパターン
 */
class Model3D : public tml::graphic::Model
{
public: Model3D(const tml::graphic::Model3D &) = delete;
public: tml::graphic::Model3D &operator =(const tml::graphic::Model3D &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	const tml::graphic::Model3DDesc *desc_;

public:
	tml::Transform3D transform;
	tml::XMFLOAT4EX color;
	tml::XMFLOAT3EX size;
	tml::graphic::DRAW_MODEL_3D_DATA *draw_data;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Model3D();
	virtual ~Model3D();

	virtual void Init(void);

	const tml::graphic::Model3DDesc *GetDesc(void) const;
};
}
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::Model3DDesc *tml::graphic::Model3D::GetDesc(void) const
{
	return (this->desc_);
}
