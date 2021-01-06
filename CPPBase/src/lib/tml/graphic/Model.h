/**
 * @file
 * @brief Modelヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief ModelDescクラス
 */
class ModelDesc : public tml::GraphicResourceDesc
{
public:

public:
	ModelDesc();
	virtual ~ModelDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Modelクラス
 *
 * インターフェースパターン
 */
class Model : public tml::GraphicResource
{
public: Model(const tml::Model &) = delete;
public: tml::Model &operator =(const tml::Model &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:

protected:
	void Release(void);
	INT Create(tml::ModelDesc &);

public:
	Model();
	virtual ~Model();

	virtual void Init(void);
};
}
