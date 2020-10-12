/**
 * @file
 * @brief Allocatorヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief Allocatorクラス
 *
 * インターフェースパターン
 */
class Allocator
{
public: Allocator(const Allocator &) = delete;
public: Allocator &operator =(const Allocator &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	Allocator();
	virtual ~Allocator();

	virtual void Init(void);
	INT Create(void);
};
}
