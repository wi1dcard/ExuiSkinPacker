#include "CExuiSkin.h";
#include <Windows.h>;

//#pragma warning(disable:4996)
#pragma once

typedef struct EXUI_SKIN_MATERIAL_ATTR
{
	long			lDrawMode;			//绘画模式
	RECT			rcClip;				//裁剪区
	RECT			rcGrid;				//九宫区
	RECT			rcClient;			//客户区
	unsigned long	uFillMode;			//填充模式
	unsigned long	uBrushMode;			//画刷风格
	unsigned long	clrBg1;				//底色一
	unsigned long	clrBg2;				//底色二
	unsigned long	uOutlineMode;		//边线风格
	unsigned long	clrOutline1;		//边线色一
	unsigned long	clrOutline2;		//边线色二
	unsigned long	clrOutline3;		//边线色三

} EXUI_SKIN_MATERIAL_ATTR;


typedef struct EXUI_SKIN_MATERIAL
{
	unsigned long				uDataLength;	//素材长度
	unsigned char *				lpData;			//素材指针

	unsigned long				uImageLength;	//素材图片长度
	unsigned char *				lpImage;		//素材图片指针
	unsigned long				uImageHash;		//素材图片哈希值

	unsigned long				uHeaderLength;	//素材头长度
	unsigned char *				lpHeader;		//素材头指针

	unsigned long				uVersion;		//素材版本
	EXUI_SKIN_MATERIAL_ATTR *	attr;			//素材属性

} EXUI_SKIN_MATERIAL;


class CExuiSkinMaterial
{
private:
	//素材信息
	EXUI_SKIN_MATERIAL *	m_esm;

private:
	CExuiSkin *				m_ces;
	size_t					m_sMaterial;

public:
	CExuiSkinMaterial(CExuiSkin *ces){
		m_ces = ces;
		Unpack();
	}
	~CExuiSkinMaterial(){
		this->Release();
	}

	bool Unpack()
	{
		this->Release();
		if (!m_ces->IsUnpack()){
			return false;
		}

		unsigned long	uMaterialLength = m_ces->m_esdData.uMaterialLength;
		unsigned char*	lpMaterial = m_ces->m_esdData.lpMaterial;

		//统计素材数量
		unsigned long	uOffset = 0;
		size_t			sMaterial = 0;
		const size_t	sLong = sizeof(unsigned long);
		do{
			uOffset += sLong + *(unsigned long*)(lpMaterial + uOffset);
			sMaterial++;
		} while (uOffset < uMaterialLength);

		//检查素材总长度
		if (uOffset > uMaterialLength){
			return false;
		}

		//重定义数组
		this->m_sMaterial = sMaterial;
		m_esm = new EXUI_SKIN_MATERIAL[sMaterial];
		
		static const unsigned char lpCorrectHeader1[] = { 0xCB, 0xD8, 0xB2, 0xC4, 0xD0, 0xC5, 0xCF, 0xA2, 0xCE, 0xC4, 0xBC, 0xFE, 0xCD, 0xB7 };
		static const unsigned char lpCorrectHeader2[] = { 0x65, 0x78, 0x75, 0x69, 0xCB, 0xD8, 0xB2, 0xC4, 0x2D, 0x32 };

		uOffset = 0;
		for (size_t i = 0; i < sMaterial; i++){
			//素材长度
			m_esm[i].uDataLength = *(unsigned long*)(lpMaterial + uOffset);
			uOffset += sLong;
			m_esm[i].lpData = lpMaterial + uOffset;
			uOffset += m_esm[i].uDataLength;

			//素材版本
			m_esm[i].lpHeader = m_esm[i].lpData + m_esm[i].uDataLength - sizeof(*m_esm->attr) - sizeof(lpCorrectHeader2);
			if (m_esm[i].lpHeader < m_esm[i].lpData){
				m_esm[i].lpHeader = NULL;
				m_esm[i].uHeaderLength = 0;
				m_esm[i].uVersion = 0;
			}
			else if (memcmp(m_esm[i].lpHeader, lpCorrectHeader2, m_esm[i].uHeaderLength = sizeof(lpCorrectHeader2)) == 0){
				m_esm[i].uVersion = 2;
			}
			else if (memcmp(m_esm[i].lpHeader, lpCorrectHeader1, m_esm[i].uHeaderLength = sizeof(lpCorrectHeader1)) == 0){
				m_esm[i].uVersion = 1;
			}
			else{
				m_esm[i].uHeaderLength = 0;
				m_esm[i].uVersion = 0;
			}

			if (m_esm[i].uVersion > 0){
				//素材属性
				m_esm[i].attr = (EXUI_SKIN_MATERIAL_ATTR *)(m_esm[i].lpHeader + m_esm[i].uHeaderLength);

				//素材图片
				m_esm[i].uImageLength = m_esm[i].lpHeader - m_esm[i].lpData;
				if (m_esm[i].uImageLength == 0){
					m_esm[i].lpImage = NULL;
					m_esm[i].uImageHash = 0;
				}
				else{
					switch (m_esm[i].attr->lDrawMode){
					case -1:
						/*引用图片*/
						m_esm[i].uImageHash = *(unsigned long *)m_esm[i].lpData;
						m_esm[i].uImageLength = 0;
						m_esm[i].lpImage = NULL;
						//寻找真实图片
						for (size_t j = i - 1; j != -1; j--){
							if (m_esm[i].uImageHash == m_esm[j].uImageHash){
								//复制指针
								m_esm[i].uImageLength = m_esm[j].uImageLength;
								m_esm[i].lpImage = m_esm[j].lpImage;
								break;
							}
						}
						if (m_esm[i].lpImage == NULL){
							this->Release();
							return false;
						}
						break;
					case -2:
						/*图片路径*/
						break;
					default:
						/*真实图片*/
						m_esm[i].lpImage = m_esm[i].lpData;
						m_esm[i].uImageHash = this->GetHash(m_esm[i].lpImage, m_esm[i].uImageLength);
						break;
					}
				}
			}
			else{
				m_esm[i].uImageLength = m_esm[i].uDataLength;
				m_esm[i].lpImage = NULL;
				m_esm[i].attr = NULL;
			}
		}
		return true;
	}

	bool IsUnpack(){
		return this->m_esm != NULL;
	}

	size_t GetCount(){
		return m_sMaterial;
	}

	EXUI_SKIN_MATERIAL* GetValue(size_t nIndex){
		return nIndex > m_sMaterial ? NULL : this->m_esm + nIndex;
	}

private:
	void Release(){
		if (IsUnpack()){
			delete[] this->m_esm;
			this->m_esm = NULL;
			m_sMaterial = 0;
		}
	}

public:
	static unsigned long GetHash(unsigned char * pInput, size_t sCount){
		if (sCount == 0){
			return 0;
		}
		unsigned long uRes = 0;
		for (size_t i = 0; i < sCount; i++){
			uRes *= 0x1F;
			uRes += pInput[i];
		}
		return uRes;
	}
};

