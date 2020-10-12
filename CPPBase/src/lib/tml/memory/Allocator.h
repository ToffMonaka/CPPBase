/**
 * @file
 * @brief Allocator�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief Allocator�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
