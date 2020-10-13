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
	/**
	 * @brief INFO構造体
	 */
	typedef struct INFO_
	{
		size_t size;
		size_t use_size;

		/**
		 * @brief コンストラクタ
		 */
		INFO_() :
			size(0U),
			use_size(0U)
		{
			return;
		}
	} INFO;

protected:
	void Release(void);
	INT Create(void);

public:
	Allocator();
	virtual ~Allocator();

	virtual void Init(void);
	virtual tml::Allocator::INFO GetInfo(void);
};
}
