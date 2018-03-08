// ExuiSkinPacker.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <stdlib.h>;
#include <fstream>;
#include <iostream>;
using namespace std;

#include ".\CSkin\Include.h";
#pragma warning(disable:4996)

void DemoParse(){
	CExuiSkin ces(L"..\\Skins\\�����б��");
	if (!ces.IsUnpack()) return ;
	cout << (ces.IsUnpack() ? "����ɹ���\n" : "���ʧ�ܣ�") << endl;

	cout << "Ƥ���汾��" << ces.m_esSkin->uVersion << endl;
	cout << "�زĳ��ȣ�" << ces.m_esdData.uMaterialLength << endl;
	cout << "���߳��ȣ�" << ces.m_esdData.uAuthorLength << endl;
	cout << "���ӳ��ȣ�" << ces.m_esdData.uPropertyLength << endl;



	cout << "\n========�ز���Ϣ=======\n" << endl;

	CExuiSkinMaterial cesm(&ces);
	cout << (cesm.IsUnpack() ? "����ɹ���" : "���ʧ�ܣ�") << endl << endl;
	cout << "������" << cesm.GetCount() << endl;

	for (int i = 0; i < cesm.GetCount(); i++){
		EXUI_SKIN_MATERIAL* esm = cesm.GetValue(i);
		cout << "[" << i << "]�زĳ��ȣ�" << esm->uDataLength << endl;
		cout << "[" << i << "]�ز�ͷ���ȣ�" << esm->uHeaderLength << endl;
		cout << "[" << i << "]�ز�ͼƬ���ȣ�" << esm->uImageLength << endl;
		cout << "[" << i << "]�زİ汾��" << esm->uVersion << endl;
		cout << "[" << i << "]�ز����ԣ�" << esm->attr << endl;
		cout << endl;

		if (esm->uDataLength == 0 || esm->uImageLength == 0)
			continue;

		char fileName[255];
		unsigned long hash = CExuiSkinMaterial::GetHash(esm->lpImage, esm->uImageLength);
		//sprintf(fileName, "..\\Skins\\img\\%08x_%03", hash, i);
		sprintf(fileName, "..\\Skins\\img\\%08x", hash);
		strcat(fileName, ".jpg");
		ofstream rs(fileName, ios::binary);
		rs.write((char*)(esm->lpImage), esm->uImageLength);
		rs.close();
	}



	cout << "\n========������Ϣ=======\n" << endl;

	CExuiSkinAuthor cesa(&ces);
	cout << (cesa.IsUnpack() ? "����ɹ���" : "���ʧ�ܣ�") << endl << endl;

	cout << "Ƥ�����ͣ�" << cesa.m_esac.szType << endl;
	cout << "Ƥ�����ƣ�" << cesa.m_esac.szName << endl;
	cout << "Ƥ�����ߣ�" << cesa.m_esac.szAuthor << endl;
	cout << "Ƥ����飺" << cesa.m_esac.szIntro << endl;
	cout << "Ƥ��GUID��" << cesa.m_esac.szGuid << endl;



	cout << "\n========������Ϣ=======\n" << endl;

	CExuiSkinProperty cesp(&ces);
	cout << (cesp.IsUnpack() ? "����ɹ���" : "���ʧ�ܣ�") << endl << endl;
	cout << "������" << cesp.GetCount() << endl;

	for (int i = 0; i < cesp.GetCount(); i++){
		cout << "ֵ[" << i << "]: " << cesp.GetValue(i) << endl;
	}

	cout << "\n=====================\n" << endl;
}

void DemoLoad(){
	cout << "\n========�ز���Ϣ=======\n" << endl;
	LARGE_INTEGER freq;
	LARGE_INTEGER start_t, stop_t;
	double exe_time;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_t);

	/*������ʼ*/
	CExuiSkinPaint Skin(CExuiSkin(L"..\\Skins\\�����б��"));
	//CExuiSkinPaint Skin(CExuiSkin(�ֽڼ�ָ��, ����, false));
	/*��������*/

	/*ȡ�������ݿ�ʼ*/
	cout << "�ز�������" << Skin.GetMaterialCount() << endl;
	for (int i = 0; i < Skin.GetMaterialCount(); i++){
		cout << "[" << i << "]hBitmap: " << Skin.GetMaterial(i).hBitmap << endl;
		cout << "[" << i << "]attrDrawMode: " << Skin.GetMaterial(i).attr.lDrawMode << endl;
	}
	cout << "����������" << Skin.GetPropertyCount() << endl;
	for (int i = 0; i < Skin.GetPropertyCount(); i++){
		cout << "ֵ[" << i << "]: " << Skin.GetProperty(i) << endl;
	}
	/*ȡ�������ݽ���*/

	QueryPerformanceCounter(&stop_t);
	exe_time = 1e3*(stop_t.QuadPart - start_t.QuadPart) / freq.QuadPart;
	fprintf(stdout, "use a class: %fms.\n\n", exe_time);

}

int _tmain(int argc, _TCHAR* argv[])
{
	do{
		DemoLoad();
	}while(0);

	system("pause");
	return 0;
}
