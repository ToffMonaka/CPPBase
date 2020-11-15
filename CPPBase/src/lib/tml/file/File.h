/**
 * @file
 * @brief Fileヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief Fileクラス
 *
 * インターフェースパターン
 */
class File
{
public: File(const File &) = delete;
public: File &operator =(const File &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);

public:
	File();
	virtual ~File();

	virtual void Init(void);

	virtual void Read(void) = 0;
	virtual void Write(void) = 0;
};
}
