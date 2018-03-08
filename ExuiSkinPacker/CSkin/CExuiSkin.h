#include <tchar.h>
#pragma once

typedef struct EXUI_SKIN
{
	unsigned char	lpHeader[12];	//文件头
	unsigned long	uVersion;		//版本号
	unsigned long	uReserved;		//数据长度+4
	unsigned long	uValidLength;	//数据长度
	unsigned char	lpData[];		//数据...

} EXUI_SKIN;


typedef struct EXUI_SKIN_DATA
{
	unsigned long	uReversed1;			//素材长度+4
	unsigned long	uMaterialLength;	//素材长度
	unsigned char*	lpMaterial;			//素材...

	unsigned long	uReversed2;			//作者长度+4
	unsigned long	uAuthorLength;		//作者长度
	unsigned char*	lpAuthor;			//作者...

	unsigned long	uPropertyLength;	//附加长度
	unsigned char*	lpProperty;			//附加...

} EXUI_SKIN_DATA;


class CExuiSkin
{
public:
	//加载空皮肤
	CExuiSkin();

	//加载文件路径
	CExuiSkin(const _TCHAR[]);

	//加载字节集
	CExuiSkin(unsigned char*, const size_t, bool bCopy = true);

	~CExuiSkin();

private:
	//当前皮肤文件路径
	_TCHAR*			m_szSkinFile = NULL;

	//当前皮肤字节集长度
	size_t			m_sSkinLength = 0;

	//当前皮肤字节集
	unsigned char*	m_lpSkin = NULL;

	//当前皮肤是否副本
	bool			m_bCopy = false;

	//是否加载皮肤
	bool IsLoad(){ return m_lpSkin != NULL&&m_sSkinLength != 0; };

public:
	//当前皮肤结构体
	EXUI_SKIN*			m_esSkin;

	//当前皮肤数据结构体
	EXUI_SKIN_DATA		m_esdData;
	
public:
	//皮肤解包
	bool Unpack();

	//得到当前皮肤文件路径
	_TCHAR*	GetSkinFile(){ return this->m_szSkinFile; }

	//得到当前皮肤字节集
	unsigned char*	GetSkin(){ return this->m_lpSkin; }

	//得到当前皮肤字节集长度
	size_t	GetSkinLength(){ return this->m_sSkinLength; }

	//是否解包皮肤
	bool IsUnpack(){ return this->m_esSkin != NULL; };

};