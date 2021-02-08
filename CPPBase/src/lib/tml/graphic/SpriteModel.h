/**
 * @file
 * @brief SpriteModel�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Model.h"


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelLayer�N���X
 */
class SpriteModelLayer : public tml::graphic::ModelLayer
{
public: SpriteModelLayer(const tml::graphic::SpriteModelLayer &) = delete;
public: tml::graphic::SpriteModelLayer &operator =(const tml::graphic::SpriteModelLayer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	SpriteModelLayer();
	virtual ~SpriteModelLayer();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::SpriteModelLayer::Release(void)
{
	tml::graphic::ModelLayer::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelStage�N���X
 */
class SpriteModelStage : public tml::graphic::ModelStage
{
public: SpriteModelStage(const tml::graphic::SpriteModelStage &) = delete;
public: tml::graphic::SpriteModelStage &operator =(const tml::graphic::SpriteModelStage &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	SpriteModelStage();
	virtual ~SpriteModelStage();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);

	tml::graphic::SpriteModelLayer *GetLayer(const UINT);
	void SetLayer(const UINT, tml::unique_ptr<tml::graphic::SpriteModelLayer> &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::SpriteModelStage::Release(void)
{
	tml::graphic::ModelStage::Release();

	return;
}


/**
 * @brief GetLayer�֐�
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=���s
 */
inline tml::graphic::SpriteModelLayer *tml::graphic::SpriteModelStage::GetLayer(const UINT index)
{
	return (static_cast<tml::graphic::SpriteModelLayer *>(tml::graphic::ModelStage::GetLayer(index)));
}


/**
 * @brief SetLayer�֐�
 * @param index (index)
 * @param layer (layer)
 */
inline void tml::graphic::SpriteModelStage::SetLayer(const UINT index, tml::unique_ptr<tml::graphic::SpriteModelLayer> &layer)
{
	tml::unique_ptr<tml::graphic::ModelLayer> tmp_layer = std::move(layer);

	tml::graphic::ModelStage::SetLayer(index, tmp_layer);

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelDesc�N���X
 */
class SpriteModelDesc : public tml::graphic::ModelDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	SpriteModelDesc();
	virtual ~SpriteModelDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::SpriteModelDesc::Release(void)
{
	tml::graphic::ModelDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief SpriteModel�N���X
 */
class SpriteModel : public tml::graphic::Model
{
public: SpriteModel(const tml::graphic::SpriteModel &) = delete;
public: tml::graphic::SpriteModel &operator =(const tml::graphic::SpriteModel &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	SpriteModel();
	virtual ~SpriteModel();

	virtual void Init(void);
	INT Create(const tml::graphic::SpriteModelDesc &, tml::shared_ptr<tml::XMPosition> *pos = nullptr);

	tml::graphic::SpriteModelStage *GetStage(const UINT);
	void SetStage(const UINT, tml::unique_ptr<tml::graphic::SpriteModelStage> &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::SpriteModel::Release(void)
{
	tml::graphic::Model::Release();

	return;
}


/**
 * @brief GetStage�֐�
 * @param index (index)
 * @return stage (stage)<br>
 * nullptr=���s
 */
inline tml::graphic::SpriteModelStage *tml::graphic::SpriteModel::GetStage(const UINT index)
{
	return (static_cast<tml::graphic::SpriteModelStage *>(tml::graphic::Model::GetStage(index)));
}


/**
 * @brief SetStage�֐�
 * @param index (index)
 * @param stage (stage)
 */
inline void tml::graphic::SpriteModel::SetStage(const UINT index, tml::unique_ptr<tml::graphic::SpriteModelStage> &stage)
{
	tml::unique_ptr<tml::graphic::ModelStage> tmp_stage = std::move(stage);

	tml::graphic::Model::SetStage(index, tmp_stage);

	return;
}
