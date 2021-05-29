/**
 * @file
 * @brief Base2DNodeヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathPosition.h"
#include "Node.h"


namespace tml {
namespace scene {
/**
 * @brief Base2DNodeDescクラス
 */
class Base2DNodeDesc : public tml::scene::NodeDesc
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
	Base2DNodeDesc();
	virtual ~Base2DNodeDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::scene::Base2DNodeDesc::Release(void)
{
	tml::scene::NodeDesc::Release();

	return;
}


namespace tml {
namespace scene {
/**
 * @brief Base2DNodeクラス
 */
class Base2DNode : public tml::scene::Node
{
public: Base2DNode(const tml::scene::Base2DNode &) = delete;
public: tml::scene::Base2DNode &operator =(const tml::scene::Base2DNode &) = delete;
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
	Base2DNode();
	virtual ~Base2DNode();

	virtual void Init(void);
	INT Create(const tml::scene::Base2DNodeDesc &);

	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);
};
}
}
