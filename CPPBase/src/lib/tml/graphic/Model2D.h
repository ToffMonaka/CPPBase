/**
 * @file
 * @brief Model2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Model.h"


namespace tml {
namespace graphic {
/**
 * @brief Model2DLayerクラス
 *
 * インターフェースパターン
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
 * @brief Model2DStageクラス
 *
 * インターフェースパターン
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
 * @brief Model2DDescクラス
 */
class Model2DDesc : public tml::graphic::ModelDesc
{
public:
	tml::XMPosition2D position;
	tml::XMFLOAT2EX size;
	bool size_auto_flag;
	tml::XMFLOAT2EX scale;
	tml::XMFLOAT4EX color;

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
 * @brief Release関数
 */
inline void tml::graphic::Model2DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Model2Dクラス
 *
 * インターフェースパターン
 */
class Model2D : public tml::graphic::Model
{
public: Model2D(const tml::graphic::Model2D &) = delete;
public: tml::graphic::Model2D &operator =(const tml::graphic::Model2D &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::MODEL_TYPE::_2D);

public:
	tml::XMPosition2D position;
	tml::XMFLOAT2EX size;
	tml::XMFLOAT2EX scale;
	tml::XMFLOAT4EX color;

private:
	void Release(void);

public:
	Model2D();
	virtual ~Model2D();

	virtual void Init(void);
	INT Create(const tml::graphic::Model2DDesc &);

	virtual DirectX::XMMATRIX &GetWorldMatrix(DirectX::XMMATRIX &) = 0;
};
}
}
