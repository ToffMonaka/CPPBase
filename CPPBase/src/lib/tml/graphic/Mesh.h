/**
 * @file
 * @brief Mesh�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "GraphicResource.h"


namespace tml {
/**
 * @brief MeshDesc�N���X
 */
class MeshDesc : public tml::GraphicResourceDesc
{
public:

public:
	MeshDesc();
	virtual ~MeshDesc();

	virtual void Init(void);
};
}


namespace tml {
/**
 * @brief Mesh�N���X
 */
class Mesh : public tml::GraphicResource
{
public: Mesh(const tml::Mesh &) = delete;
public: tml::Mesh &operator =(const tml::Mesh &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	Mesh();
	virtual ~Mesh();

	virtual void Init(void);
	INT Create(const tml::MeshDesc &);
};
}
