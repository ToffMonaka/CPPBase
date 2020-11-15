/**
 * @file
 * @brief TextFile�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "File.h"


namespace tml {
/**
 * @brief TextFile�N���X
 */
class TextFile : public tml::File
{
public: TextFile(const TextFile &) = delete;
public: TextFile &operator =(const TextFile &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	TextFile();
	virtual ~TextFile();

	virtual void Init(void);

	virtual void Read(void);
	virtual void Write(void);
};
}
