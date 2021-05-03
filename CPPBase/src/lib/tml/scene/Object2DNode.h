/**
 * @file
 * @brief Object2DNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathPosition.h"
#include "Node.h"


namespace tml {
namespace scene {
/**
 * @brief Object2DNodeDescクラス
 */
class Object2DNodeDesc : public tml::scene::NodeDesc
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
	Object2DNodeDesc();
	virtual ~Object2DNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::Object2DNodeDesc::Release(void)
{
	tml::scene::NodeDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief Object2DNodeクラス
 */
class Object2DNode : public tml::scene::Node
{
public: Object2DNode(const tml::scene::Object2DNode &) = delete;
public: tml::scene::Object2DNode &operator =(const tml::scene::Object2DNode &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

public:
	tml::XMPosition2D position;
	tml::XMFLOAT2EX size;
	tml::XMFLOAT2EX scale;
	tml::XMFLOAT4EX color;

protected:
	void Release(void);

public:
	Object2DNode();
	virtual ~Object2DNode();

	virtual void Init(void);
	INT Create(const tml::scene::Object2DNodeDesc &);
};
}
}
