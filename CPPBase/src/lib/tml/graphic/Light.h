/**
 * @file
 * @brief Lightヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief LightDescクラス
 */
class LightDesc : public tml::GraphicResourceDesc
{
public:

public:
	LightDesc();
	virtual ~LightDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Lightクラス
 */
class Light : public tml::GraphicResource
{
public: Light(const tml::Light &) = delete;
public: tml::Light &operator =(const tml::Light &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	Light();
	virtual ~Light();

	virtual void Init(void);
	INT Create(const tml::LightDesc &);
};
}
