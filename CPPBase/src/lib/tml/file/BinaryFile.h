/**
 * @file
 * @brief BinaryFileヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "File.h"


namespace tml {
/**
 * @brief BinaryFileクラス
 */
class BinaryFile : public tml::File
{
public: BinaryFile(const BinaryFile &) = delete;
public: BinaryFile &operator =(const BinaryFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	BinaryFile();
	virtual ~BinaryFile();

	virtual void Init(void);

	virtual void Read(void);
	virtual void Write(void);
};
}
