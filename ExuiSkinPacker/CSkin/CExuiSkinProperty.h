#include "CExuiSkin.h";

//#pragma warning(disable:4996)
#pragma once

class CExuiSkinProperty
{
private:
	//¸½¼ÓÐÅÏ¢
	long *			m_lpProperties;

private:
	CExuiSkin *		m_ces;
	size_t			m_sProperties;

public:
	CExuiSkinProperty(CExuiSkin *ces){
		m_ces = ces;
		this->Unpack();
	}
	~CExuiSkinProperty(){
		
	}

	bool Unpack()
	{
		if (!m_ces->IsUnpack()){
			m_lpProperties = NULL;
			m_sProperties = 0;
			return false;
		}

		m_lpProperties = (long*)m_ces->m_esdData.lpProperty;
		m_sProperties = m_ces->m_esdData.uPropertyLength / sizeof(*m_lpProperties);
		return true;
	}

	bool IsUnpack(){
		return m_lpProperties != NULL;
	}

	size_t GetCount(){
		return this->m_sProperties;
	}

	long GetValue(size_t nIndex){
		if (nIndex > m_sProperties) return 0;
		return m_lpProperties[nIndex];
	}

public:
	long * Copy(){
		size_t sCount = this->GetCount();
		if (sCount == 0)
			return NULL;
		long * lpProperty = new long[sCount];
		memcpy(lpProperty, this->m_lpProperties, this->m_ces->m_esdData.uPropertyLength);
		return lpProperty;
	}
};