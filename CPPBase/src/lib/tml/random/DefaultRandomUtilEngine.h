/**
 * @file
 * @brief DefaultRandomUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "RandomUtilEngine.h"


namespace tml {
/**
 * @brief DefaultRandomUtilEngineDescクラス
 */
class DefaultRandomUtilEngineDesc : public tml::RandomUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	DefaultRandomUtilEngineDesc();
	virtual ~DefaultRandomUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultRandomUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief DefaultRandomUtilEngineクラス
 */
class DefaultRandomUtilEngine : public tml::RandomUtilEngine
{
public: DefaultRandomUtilEngine(const tml::DefaultRandomUtilEngine &) = delete;
public: tml::DefaultRandomUtilEngine &operator =(const tml::DefaultRandomUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	DefaultRandomUtilEngine();
	virtual ~DefaultRandomUtilEngine();

	virtual void Init(void);
	INT Create(const tml::DefaultRandomUtilEngineDesc &);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultRandomUtilEngine::Release(void)
{
	return;
}
