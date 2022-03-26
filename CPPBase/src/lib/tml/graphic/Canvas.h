/**
 * @file
 * @brief Canvasヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/Transform.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief CanvasDescクラス
 */
class CanvasDesc : public tml::graphic::ManagerResourceDesc
{
public:
	INT draw_priority;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	CanvasDesc();
	virtual ~CanvasDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::CanvasDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Canvasクラス
 *
 * インターフェースパターン
 */
class Canvas : public tml::graphic::ManagerResource
{
public: Canvas(const tml::graphic::Canvas &) = delete;
public: tml::graphic::Canvas &operator =(const tml::graphic::Canvas &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	static const UINT RESOURCE_TYPE = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::CANVAS);

private:
	const tml::graphic::CanvasDesc *desc_;
	tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE dimension_type_;
	INT draw_priority_;
	bool draw_set_flg_;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);
	void SetDimensionType(const tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE);

public:
	Canvas();
	virtual ~Canvas();

	virtual void Init(void);

	const tml::graphic::CanvasDesc *GetDesc(void) const;
	tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE GetDimensionType(void) const;
	INT GetDrawPriority(void) const;
	void SetDrawPriority(const INT);
	bool IsDrawSet(void) const;
	void SetDrawSet(void);
	void ClearDrawSet(void);

	virtual void Draw(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Canvas::Release(void)
{
	return;
}


/**
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::CanvasDesc *tml::graphic::Canvas::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetDimensionType関数
 * @return dimension_type (dimension_type)
 */
inline tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE tml::graphic::Canvas::GetDimensionType(void) const
{
	return (this->dimension_type_);
}


/**
 * @brief SetDimensionType関数
 * @param dimension_type (dimension_type)
 */
inline void tml::graphic::Canvas::SetDimensionType(const tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE dimension_type)
{
	this->dimension_type_ = dimension_type;

	return;
}


/**
 * @brief GetDrawPriority関数
 * @return draw_priority (draw_priority)
 */
inline INT tml::graphic::Canvas::GetDrawPriority(void) const
{
	return (this->draw_priority_);
}


/**
 * @brief SetDrawPriority関数
 * @param draw_priority (draw_priority)
 */
inline void tml::graphic::Canvas::SetDrawPriority(const INT draw_priority)
{
	this->draw_priority_ = draw_priority;

	return;
}


/**
 * @brief IsDrawSet関数
 * @return result_flg (result_flag)<br>
 * false=セット無し,true=セット有り
 */
inline bool tml::graphic::Canvas::IsDrawSet(void) const
{
	return (this->draw_set_flg_);
}


/**
 * @brief SetDrawSet関数
 */
inline void tml::graphic::Canvas::SetDrawSet(void)
{
	this->draw_set_flg_ = true;

	return;
}


/**
 * @brief ClearDrawSet関数
 */
inline void tml::graphic::Canvas::ClearDrawSet(void)
{
	this->draw_set_flg_ = false;

	return;
}
