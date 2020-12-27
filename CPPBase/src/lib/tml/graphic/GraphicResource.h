/**
 * @file
 * @brief GraphicResource�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_GRAPHIC.h"


namespace tml {
class GraphicManager;
}


namespace tml {
/**
 * @brief GraphicResourceDesc�N���X
 */
class GraphicResourceDesc
{
public:
	tml::GraphicManager *manager;

public:
	GraphicResourceDesc();
	virtual ~GraphicResourceDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief GraphicResource�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class GraphicResource
{
public: GraphicResource(const tml::GraphicResource &) = delete;
public: tml::GraphicResource &operator =(const tml::GraphicResource &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::GraphicManager *mgr_;

protected:
	void Release(void);
	INT Create(const tml::GraphicResourceDesc &);

public:
	GraphicResource();
	virtual ~GraphicResource();

	virtual void Init(void);

	tml::GraphicManager *GetManager(void) const;
};
}


/**
 * @brief GetManager�֐�
 * @return mgr (manager)
 */
inline tml::GraphicManager *tml::GraphicResource::GetManager(void) const
{
	return (this->mgr_);
}
