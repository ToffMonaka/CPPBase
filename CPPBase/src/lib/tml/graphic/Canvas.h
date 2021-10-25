/**
 * @file
 * @brief Canvasヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief CanvasDescクラス
 */
class CanvasDesc : public tml::graphic::ManagerResourceDesc
{
public:

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
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::CANVAS);

private:
	tml::ConstantUtil::GRAPHIC::CANVAS_TYPE type_;
	bool draw_set_flg_;

private:
	void Release(void);

public:
	Canvas();
	virtual ~Canvas();

	virtual void Init(void);
	INT Create(const tml::graphic::CanvasDesc &);

	tml::ConstantUtil::GRAPHIC::CANVAS_TYPE GetType(void) const;
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
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::CANVAS_TYPE tml::graphic::Canvas::GetType(void) const
{
	return (this->type_);
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
