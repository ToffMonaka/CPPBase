/**
 * @file
 * @brief Fogヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief FogDescクラス
 */
class FogDesc : public tml::GraphicResourceDesc
{
public:

public:
	FogDesc();
	virtual ~FogDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Fogクラス
 */
class Fog : public tml::GraphicResource
{
public: Fog(const tml::Fog &) = delete;
public: tml::Fog &operator =(const tml::Fog &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	Fog();
	virtual ~Fog();

	virtual void Init(void);
	INT Create(const tml::FogDesc &);
};
}
