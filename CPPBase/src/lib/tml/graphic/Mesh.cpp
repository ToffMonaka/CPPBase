/**
 * @file
 * @brief Meshコードファイル
 */


#include "Mesh.h"
#include "GraphicManager.h"


/**
 * @brief コンストラクタ
 */
tml::MeshDesc::MeshDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MeshDesc::~MeshDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::MeshDesc::Init(void)
{
	tml::GraphicResourceDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::Mesh::Mesh()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Mesh::~Mesh()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::Mesh::Release(void)
{
	tml::GraphicResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Mesh::Init(void)
{
	this->Release();

	tml::GraphicResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Mesh::Create(const tml::MeshDesc &desc)
{
	this->Init();

	if (tml::GraphicResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
