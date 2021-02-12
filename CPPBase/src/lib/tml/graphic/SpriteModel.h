/**
 * @file
 * @brief SpriteModelヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "Model.h"


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelLayerクラス
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
 * @brief Release関数
 */
inline void tml::graphic::SpriteModelLayer::Release(void)
{
	tml::graphic::ModelLayer::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelStageクラス
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
 * @brief Release関数
 */
inline void tml::graphic::SpriteModelStage::Release(void)
{
	tml::graphic::ModelStage::Release();

	return;
}


/**
 * @brief GetLayer関数
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=失敗
 */
inline tml::graphic::SpriteModelLayer *tml::graphic::SpriteModelStage::GetLayer(const UINT index)
{
	return (static_cast<tml::graphic::SpriteModelLayer *>(tml::graphic::ModelStage::GetLayer(index)));
}


/**
 * @brief SetLayer関数
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
 * @brief SpriteModelDescクラス
 */
class SpriteModelDesc : public tml::graphic::ModelDesc
{
public:
	tml::XMPosition2D position;
	tml::XMFLOAT2EX size;
	tml::XMFLOAT2EX scale;

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
 * @brief Release関数
 */
inline void tml::graphic::SpriteModelDesc::Release(void)
{
	tml::graphic::ModelDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief SpriteModelクラス
 */
class SpriteModel : public tml::graphic::Model
{
public: SpriteModel(const tml::graphic::SpriteModel &) = delete;
public: tml::graphic::SpriteModel &operator =(const tml::graphic::SpriteModel &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	/**
	 * @brief VERTEX_BUFFER_ELEMENT構造体
	 */
	typedef struct VERTEX_BUFFER_ELEMENT_
	{
		tml::XMFLOAT4EX position;
		tml::XMFLOAT2EX texture_position;
		UINT layer_index;

		/**
		 * @brief コンストラクタ
		 */
		VERTEX_BUFFER_ELEMENT_() :
			layer_index(0U)
		{
			return;
		};

		/**
		 * @brief コンストラクタ
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
	tml::shared_ptr<tml::graphic::ModelShaderStructuredBuffer> ssb_;
	tml::shared_ptr<tml::graphic::ModelLayerShaderStructuredBuffer> layer_ssb_;

public:
	tml::XMPosition2D position;
	tml::XMFLOAT2EX size;
	tml::XMFLOAT2EX scale;

protected:
	void Release(void);

public:
	SpriteModel();
	virtual ~SpriteModel();

	virtual void Init(void);
	INT Create(const tml::graphic::SpriteModelDesc &);

	tml::graphic::SpriteModelStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::SpriteModelStage> &);

	virtual void DrawStageInit(void);
	virtual void DrawStageForward2D(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::SpriteModel::Release(void)
{
	tml::graphic::Model::Release();

	return;
}


/**
 * @brief GetStage関数
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=失敗
 */
inline tml::graphic::SpriteModelStage *tml::graphic::SpriteModel::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (static_cast<tml::graphic::SpriteModelStage *>(tml::graphic::Model::GetStage(type)));
}


/**
 * @brief SetStage関数
 * @param type (type)
 * @param stage (stage)
 */
inline void tml::graphic::SpriteModel::SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type, tml::unique_ptr<tml::graphic::SpriteModelStage> &stage)
{
	tml::unique_ptr<tml::graphic::ModelStage> tmp_stage = std::move(stage);

	tml::graphic::Model::SetStage(type, tmp_stage);

	return;
}
