/**
 * @file
 * @brief Object2DModelヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathINT.h"
#include "../math/XNAMathPosition.h"
#include "Model.h"


namespace tml {
namespace graphic {
/**
 * @brief Object2DModelLayerクラス
 */
class Object2DModelLayer : public tml::graphic::ModelLayer
{
public: Object2DModelLayer(const tml::graphic::Object2DModelLayer &) = delete;
public: tml::graphic::Object2DModelLayer &operator =(const tml::graphic::Object2DModelLayer &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	Object2DModelLayer();
	virtual ~Object2DModelLayer();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Object2DModelLayer::Release(void)
{
	tml::graphic::ModelLayer::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Object2DModelStageクラス
 */
class Object2DModelStage : public tml::graphic::ModelStage
{
public: Object2DModelStage(const tml::graphic::Object2DModelStage &) = delete;
public: tml::graphic::Object2DModelStage &operator =(const tml::graphic::Object2DModelStage &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	Object2DModelStage();
	virtual ~Object2DModelStage();

	virtual void Init(void);
	INT Create(tml::graphic::Manager *);

	tml::graphic::Object2DModelLayer *GetLayer(const UINT);
	tml::graphic::Object2DModelLayer *GetLayerFast(const UINT);
	void SetLayer(const UINT, tml::unique_ptr<tml::graphic::Object2DModelLayer> &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Object2DModelStage::Release(void)
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
inline tml::graphic::Object2DModelLayer *tml::graphic::Object2DModelStage::GetLayer(const UINT index)
{
	return (static_cast<tml::graphic::Object2DModelLayer *>(tml::graphic::ModelStage::GetLayer(index)));
}


/**
 * @brief GetLayerFast関数
 * @param index (index)
 * @return layer (layer)<br>
 * nullptr=失敗
 */
inline tml::graphic::Object2DModelLayer *tml::graphic::Object2DModelStage::GetLayerFast(const UINT index)
{
	return (static_cast<tml::graphic::Object2DModelLayer *>(tml::graphic::ModelStage::GetLayerFast(index)));
}


/**
 * @brief SetLayer関数
 * @param index (index)
 * @param layer (layer)
 */
inline void tml::graphic::Object2DModelStage::SetLayer(const UINT index, tml::unique_ptr<tml::graphic::Object2DModelLayer> &layer)
{
	tml::unique_ptr<tml::graphic::ModelLayer> tmp_layer = std::move(layer);

	tml::graphic::ModelStage::SetLayer(index, tmp_layer);

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Object2DModelDescクラス
 */
class Object2DModelDesc : public tml::graphic::ModelDesc
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
	Object2DModelDesc();
	virtual ~Object2DModelDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Object2DModelDesc::Release(void)
{
	tml::graphic::ModelDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Object2DModelクラス
 */
class Object2DModel : public tml::graphic::Model
{
public: Object2DModel(const tml::graphic::Object2DModel &) = delete;
public: tml::graphic::Object2DModel &operator =(const tml::graphic::Object2DModel &) = delete;
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
	tml::shared_ptr<tml::graphic::Object2DModelShaderStructuredBuffer> ssb_;
	tml::shared_ptr<tml::graphic::Object2DModelLayerShaderStructuredBuffer> layer_ssb_;

public:
	tml::XMPosition2D position;
	tml::XMFLOAT2EX size;
	tml::XMFLOAT2EX scale;
	tml::XMFLOAT4EX color;

protected:
	void Release(void);

public:
	Object2DModel();
	virtual ~Object2DModel();

	virtual void Init(void);
	INT Create(const tml::graphic::Object2DModelDesc &);

	tml::graphic::Object2DModelStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	tml::graphic::Object2DModelStage *GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::Object2DModelStage> &);

	virtual void DrawStageInit(void);
	virtual void DrawStageForward2D(void);

	bool IsHitByMouse(const tml::XMINT2EX &);
};
}
}


/**
 * @brief GetStage関数
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=失敗
 */
inline tml::graphic::Object2DModelStage *tml::graphic::Object2DModel::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (static_cast<tml::graphic::Object2DModelStage *>(tml::graphic::Model::GetStage(type)));
}


/**
 * @brief GetStageFast関数
 * @param type (type)
 * @return stage (stage)<br>
 * nullptr=失敗
 */
inline tml::graphic::Object2DModelStage *tml::graphic::Object2DModel::GetStageFast(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (static_cast<tml::graphic::Object2DModelStage *>(tml::graphic::Model::GetStageFast(type)));
}


/**
 * @brief SetStage関数
 * @param type (type)
 * @param stage (stage)
 */
inline void tml::graphic::Object2DModel::SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type, tml::unique_ptr<tml::graphic::Object2DModelStage> &stage)
{
	tml::unique_ptr<tml::graphic::ModelStage> tmp_stage = std::move(stage);

	tml::graphic::Model::SetStage(type, tmp_stage);

	return;
}
