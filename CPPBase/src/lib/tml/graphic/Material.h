/**
 * @file
 * @brief Materialヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief MaterialDescクラス
 */
class MaterialDesc : public tml::GraphicResourceDesc
{
public:

public:
	MaterialDesc();
	virtual ~MaterialDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Materialクラス
 */
class Material : public tml::GraphicResource
{
public: Material(const tml::Material &) = delete;
public: tml::Material &operator =(const tml::Material &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	Material();
	virtual ~Material();

	virtual void Init(void);
	INT Create(const tml::MaterialDesc &);
};
}
