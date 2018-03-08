#include "CExuiSkinMaterial.h";
#include <map>;

//#pragma warning(disable:4996)
#pragma once

namespace EXUI_SKIN_IMAGE{
	typedef struct NODE
	{
		unsigned long hBitmap;
		unsigned long nWidth;
		unsigned long nHeight;
		unsigned long nUsed;

	} NODE;

	std::map<unsigned long, NODE*> m_esi;

	NODE* Add(const EXUI_SKIN_MATERIAL* esm){
		if (esm->uImageLength == 0){
			return NULL;
		}
		if (m_esi.count(esm->uImageHash) > 0){
			m_esi[esm->uImageHash]->nUsed++;
			return m_esi[esm->uImageHash];
		}
		NODE* esi = new NODE;

		/*加载图片开始*/
		esi->hBitmap = (unsigned long)esm->lpData;
		esi->nWidth = 100;
		esi->nHeight = 100;
		esi->nUsed = 0;
		/*加载图片结束*/

		m_esi[esm->uImageHash] = esi;
		return esi;
	}

	void Delete(const unsigned long uHash){
		delete m_esi[uHash];
		m_esi.erase(uHash);
	}
}