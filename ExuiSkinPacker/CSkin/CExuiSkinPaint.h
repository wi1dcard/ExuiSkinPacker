#include "CExuiSkinImage.h";
#include "CExuiSkinProperty.h";

//#pragma warning(disable:4996)
#pragma once

typedef struct EXUI_SKIN_PAINT_MATERIAL
{
	unsigned long			hBitmap;
	EXUI_SKIN_MATERIAL_ATTR	attr;

} EXUI_SKIN_PAINT_MATERIAL;

class CExuiSkinPaint
{
private:
	size_t							m_sMaterial;		//素材数量
	EXUI_SKIN_PAINT_MATERIAL *		m_lpMaterial;		//素材数组

	size_t							m_sProperty;		//附加数量
	long *							m_lpProperty;		//附加数组

public:
	CExuiSkinPaint(CExuiSkin &ces){
		if (!ces.IsUnpack()){
			return;
		}

		CExuiSkinMaterial cesm(&ces);
		CExuiSkinProperty cesp(&ces);

		m_sMaterial = cesm.GetCount();
		m_lpMaterial = new EXUI_SKIN_PAINT_MATERIAL[m_sMaterial];
		for (size_t i = 0; i < m_sMaterial; i++){
			EXUI_SKIN_MATERIAL* esm = cesm.GetValue(i);

			if (esm->uDataLength){
				/*复制素材开始*/
				m_lpMaterial[i].attr = *esm->attr;
				/*复制素材结束*/
			}
			else{
				/*空素材开始*/
				m_lpMaterial[i].attr = {};
				/*空素材结束*/
			}

			EXUI_SKIN_IMAGE::NODE* esi = EXUI_SKIN_IMAGE::Add(esm);
			if (esi){
				/*复制图片开始*/
				m_lpMaterial[i].hBitmap = esi->hBitmap;
				/*复制图片结束*/
			}
			else{
				/*空图片开始*/
				m_lpMaterial[i].hBitmap = 0;
				/*空图片结束*/
			}
		}

		m_sProperty = cesp.GetCount();
		m_lpProperty = cesp.Copy();
	}

	~CExuiSkinPaint(){
		if (m_lpMaterial){
			delete[] m_lpMaterial;
		}
		if (m_lpProperty){
			delete[] m_lpProperty;
		}
	}

	unsigned long GetMaterialCount(){
		return m_sMaterial;
	}

	unsigned long GetPropertyCount(){
		return m_sProperty;
	}

	EXUI_SKIN_PAINT_MATERIAL GetMaterial(size_t nIndex){
		EXUI_SKIN_PAINT_MATERIAL espm;
		memset(&espm, 0, sizeof(espm));
		return nIndex < m_sMaterial ? m_lpMaterial[nIndex] : espm;
	}

	unsigned long GetProperty(size_t nIndex){
		return nIndex < m_sProperty ? m_lpProperty[nIndex] : 0;
	}
};