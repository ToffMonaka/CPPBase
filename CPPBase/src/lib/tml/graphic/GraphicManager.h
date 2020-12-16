/**
 * @file
 * @brief GraphicManager�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief GraphicManager�N���X
 */
class GraphicManager
{
public: GraphicManager(const tml::GraphicManager &) = delete;
public: tml::GraphicManager &operator =(const tml::GraphicManager &) = delete;

private:
	void Release(void);

public:
	GraphicManager();
	virtual ~GraphicManager();

	virtual void Init(void);
	INT Create(void);
};
}
