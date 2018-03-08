#include <tchar.h>
#pragma once

typedef struct EXUI_SKIN
{
	unsigned char	lpHeader[12];	//�ļ�ͷ
	unsigned long	uVersion;		//�汾��
	unsigned long	uReserved;		//���ݳ���+4
	unsigned long	uValidLength;	//���ݳ���
	unsigned char	lpData[];		//����...

} EXUI_SKIN;


typedef struct EXUI_SKIN_DATA
{
	unsigned long	uReversed1;			//�زĳ���+4
	unsigned long	uMaterialLength;	//�زĳ���
	unsigned char*	lpMaterial;			//�ز�...

	unsigned long	uReversed2;			//���߳���+4
	unsigned long	uAuthorLength;		//���߳���
	unsigned char*	lpAuthor;			//����...

	unsigned long	uPropertyLength;	//���ӳ���
	unsigned char*	lpProperty;			//����...

} EXUI_SKIN_DATA;


class CExuiSkin
{
public:
	//���ؿ�Ƥ��
	CExuiSkin();

	//�����ļ�·��
	CExuiSkin(const _TCHAR[]);

	//�����ֽڼ�
	CExuiSkin(unsigned char*, const size_t, bool bCopy = true);

	~CExuiSkin();

private:
	//��ǰƤ���ļ�·��
	_TCHAR*			m_szSkinFile = NULL;

	//��ǰƤ���ֽڼ�����
	size_t			m_sSkinLength = 0;

	//��ǰƤ���ֽڼ�
	unsigned char*	m_lpSkin = NULL;

	//��ǰƤ���Ƿ񸱱�
	bool			m_bCopy = false;

	//�Ƿ����Ƥ��
	bool IsLoad(){ return m_lpSkin != NULL&&m_sSkinLength != 0; };

public:
	//��ǰƤ���ṹ��
	EXUI_SKIN*			m_esSkin;

	//��ǰƤ�����ݽṹ��
	EXUI_SKIN_DATA		m_esdData;
	
public:
	//Ƥ�����
	bool Unpack();

	//�õ���ǰƤ���ļ�·��
	_TCHAR*	GetSkinFile(){ return this->m_szSkinFile; }

	//�õ���ǰƤ���ֽڼ�
	unsigned char*	GetSkin(){ return this->m_lpSkin; }

	//�õ���ǰƤ���ֽڼ�����
	size_t	GetSkinLength(){ return this->m_sSkinLength; }

	//�Ƿ���Ƥ��
	bool IsUnpack(){ return this->m_esSkin != NULL; };

};