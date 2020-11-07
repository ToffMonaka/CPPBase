/**
 * @file
 * @brief FileUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief FileUtilEngineクラス
 *
 * インターフェースパターン
 */
class FileUtilEngine
{
public: FileUtilEngine(const FileUtilEngine &) = delete;
public: FileUtilEngine &operator =(const FileUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	FileUtilEngine();
	virtual ~FileUtilEngine();

	virtual void Init(void);
};
}
