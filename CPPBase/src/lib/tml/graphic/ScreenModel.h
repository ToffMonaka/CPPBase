/**
 * @file
 * @brief ScreenModelヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Model.h"


namespace tml {
namespace graphic {
/**
 * @brief ScreenModelDescクラス
 */
class ScreenModelDesc : public tml::graphic::ModelDesc
{
public:

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	ScreenModelDesc();
	virtual ~ScreenModelDesc();

	virtual void Init(void);
};
}
}


namespace tml {
namespace graphic {
/**
 * @brief ScreenModelクラス
 */
class ScreenModel : public tml::graphic::Model
{
public: ScreenModel(const tml::graphic::ScreenModel &) = delete;
public: tml::graphic::ScreenModel &operator =(const tml::graphic::ScreenModel &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	ScreenModel();
	virtual ~ScreenModel();

	virtual void Init(void);
	INT Create(const tml::graphic::ScreenModelDesc &, tml::shared_ptr<tml::XMPosition> *pos = nullptr);
};
}
}
