#include <fstream>
#include "CExuiSkin.h"
#include <windows.h>

CExuiSkin::CExuiSkin(){

}


CExuiSkin::CExuiSkin(const _TCHAR szSkinFile[]){
	std::ifstream t(szSkinFile, std::ios::binary);
	
	if (!t.is_open()){
		CExuiSkin();
		return;
	}
	t.seekg(0, std::ios::end);
	this->m_sSkinLength = (size_t)t.tellg();
	this->m_lpSkin = new unsigned char[this->m_sSkinLength];

	t.seekg(0, std::ios::beg);
	t.read((char *)m_lpSkin, this->m_sSkinLength);
	t.close();

	this->m_szSkinFile = new _TCHAR[lstrlen(szSkinFile) + 1];
	lstrcpy(this->m_szSkinFile, szSkinFile);

	new (this)CExuiSkin(this->m_lpSkin, this->m_sSkinLength);
}


CExuiSkin::CExuiSkin(unsigned char* lpSkin, const size_t sSkinLength, bool bCopy){
	this->m_bCopy = true;
	if (lpSkin != this->m_lpSkin){
		this->m_szSkinFile = NULL;
		this->m_sSkinLength = sSkinLength;
		if (bCopy){
			this->m_lpSkin = new unsigned char[sSkinLength];
			memcpy(this->m_lpSkin, lpSkin, sSkinLength);
		}
		else{
			this->m_bCopy = false;
			this->m_lpSkin = lpSkin;
		}
	}
	this->Unpack();
}


CExuiSkin::~CExuiSkin(){
	if (this->m_bCopy){
		if (this->m_lpSkin){
			delete[] m_lpSkin;
			m_lpSkin = NULL;
		}
		if (this->m_szSkinFile){
			delete[] m_szSkinFile;
			m_szSkinFile = NULL;
		}
	}
}


bool CExuiSkin::Unpack(){
	if (!this->IsLoad()){
		this->m_esSkin = NULL;
		return false;
	}
	this->m_esSkin = (EXUI_SKIN *)this->m_lpSkin;

	//校验皮肤文件头
	static const unsigned char lpCorrectHeader[] = { 0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x45, 0x58, 0x5F, 0x55, 0x49, 0x2D };

	if (memcmp(m_esSkin->lpHeader, lpCorrectHeader, sizeof(lpCorrectHeader)) != 0){
		this->m_esSkin = NULL;
		return false;
	}

	//校验皮肤长度
	if (this->m_sSkinLength != m_esSkin->uValidLength + sizeof(EXUI_SKIN)){
		this->m_esSkin = NULL;
		return false;
	}

	//解析皮肤数据
	const size_t sLong = sizeof(unsigned long);
	unsigned long uOffset = 0;

	//解析素材
	uOffset += sizeof(m_esdData.uReversed1);
	m_esdData.uMaterialLength = *(unsigned long*)(m_esSkin->lpData + uOffset);
	uOffset += sLong;
	m_esdData.lpMaterial = m_esSkin->lpData + uOffset;
	uOffset += m_esdData.uMaterialLength;
	if (uOffset > m_esSkin->uValidLength){
		this->m_esSkin = NULL;
		return false;
	}

	//解析作者
	uOffset += sizeof(m_esdData.uReversed2);
	m_esdData.uAuthorLength = *(unsigned long*)(m_esSkin->lpData + uOffset);
	uOffset += sLong;
	m_esdData.lpAuthor = m_esSkin->lpData + uOffset;
	uOffset += m_esdData.uAuthorLength;
	if (uOffset > m_esSkin->uValidLength){
		this->m_esSkin = NULL;
		return false;
	}

	//解析附加
	m_esdData.uPropertyLength = *(unsigned long*)(m_esSkin->lpData + uOffset);
	uOffset += sLong;
	m_esdData.lpProperty = m_esSkin->lpData + uOffset;
	uOffset += m_esdData.uPropertyLength;
	if (uOffset > m_esSkin->uValidLength){
		this->m_esSkin = NULL;
		return false;
	}

	return true;
}

