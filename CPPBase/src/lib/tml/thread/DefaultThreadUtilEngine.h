/**
 * @file
 * @brief DefaultThreadUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ThreadUtilEngine.h"


namespace tml {
/**
 * @brief DefaultThreadUtilEngineDescクラス
 */
class DefaultThreadUtilEngineDesc : public tml::ThreadUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	DefaultThreadUtilEngineDesc();
	virtual ~DefaultThreadUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultThreadUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief DefaultThreadUtilEngineクラス
 */
class DefaultThreadUtilEngine : public tml::ThreadUtilEngine
{
public: DefaultThreadUtilEngine(const tml::DefaultThreadUtilEngine &) = delete;
public: tml::DefaultThreadUtilEngine &operator =(const tml::DefaultThreadUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	DefaultThreadUtilEngine();
	virtual ~DefaultThreadUtilEngine();

	virtual void Init(void);
	INT Create(const tml::DefaultThreadUtilEngineDesc &);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultThreadUtilEngine::Release(void)
{
	return;
}
