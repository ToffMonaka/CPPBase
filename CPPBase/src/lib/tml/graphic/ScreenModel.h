/**
 * @file
 * @brief ScreenModel�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathPosition.h"
#include "Model.h"


namespace tml {
namespace graphic {
/**
 * @brief ScreenModelLayer�N���X
 */
class ScreenModelLayer : public tml::graphic::ModelLayer
{
public: ScreenModelLayer(const tml::graphic::ScreenModelLayer &) = delete;
public: tml::graphic::ScreenModelLayer &operator =(const tml::graphic::ScreenModelLayer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	ScreenModelLayer();
	virtual ~ScreenModelLayer();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ScreenModelLayer::Release(void)
{
	tml::graphic::ModelLayer::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ScreenModelStage�N���X
 */
class ScreenModelStage : public tml::graphic::ModelStage
{
public: ScreenModelStage(const tml::graphic::ScreenModelStage &) = delete;
public: tml::graphic::ScreenModelStage &operator =(const tml::graphic::ScreenModelStage &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	ScreenModelStage();
	virtual ~ScreenModelStage();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);

	tml::graphic::ScreenModelLayer *GetLayer(const UINT);
	tml::graphic::ScreenModelLayer *GetLayerFast(const UINT);
	void SetLayer(const UINT, tml::unique_ptr<tml::graphic::ScreenModelLayer> &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ScreenModelStage::Release(void)
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
inline tml::graphic::ScreenModelLayer *tml::graphic::ScreenModelStage::GetLayer(const UINT index)
{
	return (static_cast<tml::graphic::ScreenModelLayer *>(tml::graphic::ModelStage::GetLayer(index)));
}


/**
 * @brief GetLayerFast�֐�
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=���s
 */
inline tml::graphic::ScreenModelLayer *tml::graphic::ScreenModelStage::GetLayerFast(const UINT index)
{
	return (static_cast<tml::graphic::ScreenModelLayer *>(tml::graphic::ModelStage::GetLayerFast(index)));
}


/**
 * @brief SetLayer�֐�
 * @param index (index)
 * @param layer (layer)
 */
inline void tml::graphic::ScreenModelStage::SetLayer(const UINT index, tml::unique_ptr<tml::graphic::ScreenModelLayer> &layer)
{
	tml::unique_ptr<tml::graphic::ModelLayer> tmp_layer = std::move(layer);

	tml::graphic::ModelStage::SetLayer(index, tmp_layer);

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ScreenModelDesc�N���X
 */
class ScreenModelDesc : public tml::graphic::ModelDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	ScreenModelDesc();
	virtual ~ScreenModelDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::ScreenModelDesc::Release(void)
{
	tml::graphic::ModelDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ScreenModel�N���X
 */
class ScreenModel : public tml::graphic::Model
{
public: ScreenModel(const tml::graphic::ScreenModel &) = delete;
public: tml::graphic::ScreenModel &operator =(const tml::graphic::ScreenModel &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief VERTEX_BUFFER_ELEMENT�\����
	 */
	typedef struct VERTEX_BUFFER_ELEMENT_
	{
		tml::XMFLOAT4EX position;
		tml::XMFLOAT2EX texture_position;
		UINT layer_index;

		/**
		 * @brief �R���X�g���N�^
		 */
		VERTEX_BUFFER_ELEMENT_() :
			layer_index(0U)
		{
			return;
		};

		/**
		 * @brief �R���X�g���N�^
		 * @param pos (position)
		 * @param tex_pos (texture_position)
		 * @param layer_index (layer_index)
		 */
		VERTEX_BUFFER_ELEMENT_(const tml::XMFLOAT4EX &pos, const tml::XMFLOAT2EX &tex_pos, const UINT layer_index) :
			position(pos),
			texture_position(tex_pos),
			layer_index(layer_index)
		{
			return;
		};
	} VERTEX_BUFFER_ELEMENT;

private:

public:

protected:
	void Release(void);

public:
	ScreenModel();
	virtual ~ScreenModel();

	virtual void Init(void);
	INT Create(const tml::graphic::ScreenModelDesc &);

	tml::graphic::ScreenModelStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	tml::graphic::ScreenModelStage *GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::ScreenModelStage> &);
};
}
}


/**
 * @brief GetStage�֐�
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=���s
 */
inline tml::graphic::ScreenModelStage *tml::graphic::ScreenModel::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (static_cast<tml::graphic::ScreenModelStage *>(tml::graphic::Model::GetStage(type)));
}


/**
 * @brief GetStageFast�֐�
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=���s
 */
inline tml::graphic::ScreenModelStage *tml::graphic::ScreenModel::GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (static_cast<tml::graphic::ScreenModelStage *>(tml::graphic::Model::GetStageFast(type)));
}


/**
 * @brief SetStage�֐�
 * @param type (type)
 * @param stage (stage)
 */
inline void tml::graphic::ScreenModel::SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type, tml::unique_ptr<tml::graphic::ScreenModelStage> &stage)
{
	tml::unique_ptr<tml::graphic::ModelStage> tmp_stage = std::move(stage);

	tml::graphic::Model::SetStage(type, tmp_stage);

	return;
}
