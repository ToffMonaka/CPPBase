/**
 * @file
 * @brief SpriteModel�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathPosition.h"
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
	tml::XMPosition2D position;
	tml::XMFLOAT2EX size;
	tml::XMFLOAT2EX scale;
	tml::XMFLOAT4EX color;

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
	tml::XMFLOAT2EX size_;
	tml::XMFLOAT2EX scale_;
	tml::XMFLOAT4EX col_;
	tml::shared_ptr<tml::graphic::SpriteModelShaderStructuredBuffer> ssb_;
	tml::shared_ptr<tml::graphic::SpriteModelLayerShaderStructuredBuffer> layer_ssb_;

public:
	tml::XMPosition2D position;

protected:
	void Release(void);

public:
	SpriteModel();
	virtual ~SpriteModel();

	virtual void Init(void);
	INT Create(const tml::graphic::SpriteModelDesc &);

	const tml::XMFLOAT2EX &GetSize(void) const;
	void SetSize(const tml::XMFLOAT2EX &);
	const tml::XMFLOAT2EX &GetScale(void) const;
	void SetScale(const tml::XMFLOAT2EX &);
	const tml::XMFLOAT4EX &GetColor(void) const;
	void SetColor(const tml::XMFLOAT4EX &);
	tml::graphic::SpriteModelStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::SpriteModelStage> &);

	virtual void DrawStageInit(void);
	virtual void DrawStageForward2D(void);
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
 * @brief GetSize�֐�
 * @return size (size)
 */
inline const tml::XMFLOAT2EX &tml::graphic::SpriteModel::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief SetSize�֐�
 * @param size (size)
 */
inline void tml::graphic::SpriteModel::SetSize(const tml::XMFLOAT2EX &size)
{
	this->size_ = size;
	
	return;
}


/**
 * @brief GetScale�֐�
 * @return scale (scale)
 */
inline const tml::XMFLOAT2EX &tml::graphic::SpriteModel::GetScale(void) const
{
	return (this->scale_);
}


/**
 * @brief SetScale�֐�
 * @param scale (scale)
 */
inline void tml::graphic::SpriteModel::SetScale(const tml::XMFLOAT2EX &scale)
{
	this->scale_ = scale;
	
	return;
}


/**
 * @brief GetColor�֐�
 * @return col (color)
 */
inline const tml::XMFLOAT4EX &tml::graphic::SpriteModel::GetColor(void) const
{
	return (this->col_);
}


/**
 * @brief SetColor�֐�
 * @param col (color)
 */
inline void tml::graphic::SpriteModel::SetColor(const tml::XMFLOAT4EX &col)
{
	this->col_ = col;
	
	return;
}


/**
 * @brief GetStage�֐�
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=���s
 */
inline tml::graphic::SpriteModelStage *tml::graphic::SpriteModel::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (static_cast<tml::graphic::SpriteModelStage *>(tml::graphic::Model::GetStage(type)));
}


/**
 * @brief SetStage�֐�
 * @param type (type)
 * @param stage (stage)
 */
inline void tml::graphic::SpriteModel::SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type, tml::unique_ptr<tml::graphic::SpriteModelStage> &stage)
{
	tml::unique_ptr<tml::graphic::ModelStage> tmp_stage = std::move(stage);

	tml::graphic::Model::SetStage(type, tmp_stage);

	return;
}
