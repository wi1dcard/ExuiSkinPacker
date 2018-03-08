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
	size_t							m_sMaterial;		//�ز�����
	EXUI_SKIN_PAINT_MATERIAL *		m_lpMaterial;		//�ز�����

	size_t							m_sProperty;		//��������
	long *							m_lpProperty;		//��������

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
				/*�����زĿ�ʼ*/
				m_lpMaterial[i].attr = *esm->attr;
				/*�����زĽ���*/
			}
			else{
				/*���زĿ�ʼ*/
				m_lpMaterial[i].attr = {};
				/*���زĽ���*/
			}

			EXUI_SKIN_IMAGE::NODE* esi = EXUI_SKIN_IMAGE::Add(esm);
			if (esi){
				/*����ͼƬ��ʼ*/
				m_lpMaterial[i].hBitmap = esi->hBitmap;
				/*����ͼƬ����*/
			}
			else{
				/*��ͼƬ��ʼ*/
				m_lpMaterial[i].hBitmap = 0;
				/*��ͼƬ����*/
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