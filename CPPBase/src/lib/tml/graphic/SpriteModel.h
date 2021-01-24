/**
 * @file
 * @brief SpriteModelヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Model.h"


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelDescクラス
 */
class SpriteModelDesc : public tml::graphic::ModelDesc
{
public:

public:
	SpriteModelDesc();
	virtual ~SpriteModelDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelクラス
 */
class SpriteModel : public tml::graphic::Model
{
public: SpriteModel(const tml::graphic::SpriteModel &) = delete;
public: tml::graphic::SpriteModel &operator =(const tml::graphic::SpriteModel &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	SpriteModel();
	virtual ~SpriteModel();

	virtual void Init(void);
	INT Create(const tml::graphic::SpriteModelDesc &, tml::shared_ptr<tml::XMPosition> *pos = nullptr);
};
}
}
