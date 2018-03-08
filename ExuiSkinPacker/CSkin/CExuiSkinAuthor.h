#include "CExuiSkin.h";
#include <string.h>

//#pragma warning(disable:4996)
#pragma once

typedef struct EXUI_SKIN_AUTHOR
{
	unsigned long	uTypeLength;			//类型长度
	char *			lpType;					//类型

	unsigned long	uNameLength;			//名称长度
	char *			lpName;					//名称

	unsigned long	uAuthorLength;			//作者长度
	char *			lpAuthor;				//作者

	unsigned long	uIntroLength;			//简介长度
	char *			lpIntro;				//简介

	unsigned long	uGuidLength;			//GUID长度
	char *			lpGuid;					//GUID

} EXUI_SKIN_AUTHOR;


typedef struct EXUI_SKIN_AUTHOR_COPY
{
	char *			szType;					//类型
	char *			szName;					//名称
	char *			szAuthor;				//作者
	char *			szIntro;				//简介
	char *			szGuid;					//GUID

} EXUI_SKIN_AUTHOR_COPY;


class CExuiSkinAuthor
{
private:
	//作者信息
	EXUI_SKIN_AUTHOR		m_esa;

private:
	CExuiSkin *		m_ces;
	bool			bUnpack = false;

public:
	CExuiSkinAuthor(CExuiSkin *ces){
		m_ces = ces;
		this->Unpack();
	}
	~CExuiSkinAuthor(){
		this->ReleaseCopy();
	}

	bool Unpack()
	{
		if (!m_ces->IsUnpack()){
			return bUnpack = false;
		}

		const size_t sLong = sizeof(unsigned long);
		unsigned long uOffset = 0;
		unsigned char* lpAuthor = m_ces->m_esdData.lpAuthor;
		unsigned long uAuthorLength = m_ces->m_esdData.uAuthorLength;

		//类型
		m_esa.uTypeLength = *(unsigned long*)(lpAuthor + uOffset);
		uOffset += sLong;
		m_esa.lpType = (char*)(lpAuthor + uOffset);
		uOffset += m_esa.uTypeLength;
		if (uOffset > uAuthorLength){
			return bUnpack = false;
		}
		
		//名称
		m_esa.uNameLength = *(unsigned long*)(lpAuthor + uOffset);
		uOffset += sLong;
		m_esa.lpName = (char*)(lpAuthor + uOffset);
		uOffset += m_esa.uNameLength;
		if (uOffset > uAuthorLength){
			return bUnpack = false;
		}

		//作者
		m_esa.uAuthorLength = *(unsigned long*)(lpAuthor + uOffset);
		uOffset += sLong;
		m_esa.lpAuthor = (char*)(lpAuthor + uOffset);
		uOffset += m_esa.uAuthorLength;
		if (uOffset > uAuthorLength){
			return bUnpack = false;
		}

		//简介
		m_esa.uIntroLength = *(unsigned long*)(lpAuthor + uOffset);
		uOffset += sLong;
		m_esa.lpIntro = (char*)(lpAuthor + uOffset);
		uOffset += m_esa.uIntroLength;
		if (uOffset > uAuthorLength){
			return bUnpack = false;
		}

		//GUID
		m_esa.uGuidLength = *(unsigned long*)(lpAuthor + uOffset);
		uOffset += sLong;
		m_esa.lpGuid = (char*)(lpAuthor + uOffset);
		uOffset += m_esa.uGuidLength;
		if (uOffset > uAuthorLength){
			return bUnpack = false;
		}

		this->Copy();
		return bUnpack = true;
	}

	bool IsUnpack(){
		return this->bUnpack;
	}

	EXUI_SKIN_AUTHOR_COPY	m_esac;

private:
	void Copy(){
		this->ReleaseCopy();
		//类型
		m_esac.szType = new char[m_esa.uTypeLength + 1];
		strncpy_s(m_esac.szType, m_esa.uTypeLength + 1, m_esa.lpType, m_esa.uTypeLength);

		//名称
		m_esac.szName = new char[m_esa.uNameLength + 1];
		strncpy_s(m_esac.szName, m_esa.uNameLength + 1, m_esa.lpName, m_esa.uNameLength);

		//作者
		m_esac.szAuthor = new char[m_esa.uAuthorLength + 1];
		strncpy_s(m_esac.szAuthor, m_esa.uAuthorLength + 1, m_esa.lpAuthor, m_esa.uAuthorLength);

		//简介
		m_esac.szIntro = new char[m_esa.uIntroLength + 1];
		strncpy_s(m_esac.szIntro, m_esa.uIntroLength + 1, m_esa.lpIntro, m_esa.uIntroLength);

		//GUID
		m_esac.szGuid = new char[m_esa.uGuidLength + 1];
		strncpy_s(m_esac.szGuid, m_esa.uGuidLength + 1, m_esa.lpGuid, m_esa.uGuidLength);
	}

	void ReleaseCopy(){
		if (m_esac.szType) delete m_esac.szType, m_esac.szType = NULL;
		if (m_esac.szName) delete m_esac.szName, m_esac.szName = NULL;
		if (m_esac.szAuthor) delete m_esac.szAuthor, m_esac.szAuthor = NULL;
		if (m_esac.szIntro) delete m_esac.szIntro, m_esac.szIntro = NULL;
		if (m_esac.szGuid) delete m_esac.szGuid, m_esac.szGuid = NULL;
	}
};