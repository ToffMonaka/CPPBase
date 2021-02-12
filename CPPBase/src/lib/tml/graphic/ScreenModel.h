/**
 * @file
 * @brief ScreenModelヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "Model.h"


namespace tml {
namespace graphic {
/**
 * @brief ScreenModelLayerクラス
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
 * @brief Release関数
 */
inline void tml::graphic::ScreenModelLayer::Release(void)
{
	tml::graphic::ModelLayer::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ScreenModelStageクラス
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
	void SetLayer(const UINT, tml::unique_ptr<tml::graphic::ScreenModelLayer> &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ScreenModelStage::Release(void)
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
inline tml::graphic::ScreenModelLayer *tml::graphic::ScreenModelStage::GetLayer(const UINT index)
{
	return (static_cast<tml::graphic::ScreenModelLayer *>(tml::graphic::ModelStage::GetLayer(index)));
}


/**
 * @brief SetLayer関数
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
 * @brief ScreenModelDescクラス
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
 * @brief Release関数
 */
inline void tml::graphic::ScreenModelDesc::Release(void)
{
	tml::graphic::ModelDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief ScreenModelクラス
 */
class ScreenModel : public tml::graphic::Model
{
public: ScreenModel(const tml::graphic::ScreenModel &) = delete;
public: tml::graphic::ScreenModel &operator =(const tml::graphic::ScreenModel &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	ScreenModel();
	virtual ~ScreenModel();

	virtual void Init(void);
	INT Create(const tml::graphic::ScreenModelDesc &);

	tml::graphic::ScreenModelStage *GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE);
	void SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE, tml::unique_ptr<tml::graphic::ScreenModelStage> &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::ScreenModel::Release(void)
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
inline tml::graphic::ScreenModelStage *tml::graphic::ScreenModel::GetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type)
{
	return (static_cast<tml::graphic::ScreenModelStage *>(tml::graphic::Model::GetStage(type)));
}


/**
 * @brief SetStage関数
 * @param type (type)
 * @param stage (stage)
 */
inline void tml::graphic::ScreenModel::SetStage(const tml::ConstantUtil::GRAPHIC::DRAW_STAGE_TYPE type, tml::unique_ptr<tml::graphic::ScreenModelStage> &stage)
{
	tml::unique_ptr<tml::graphic::ModelStage> tmp_stage = std::move(stage);

	tml::graphic::Model::SetStage(type, tmp_stage);

	return;
}
