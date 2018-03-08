// ExuiSkinPacker.cpp : 定义控制台应用程序的入口点。
//

#include <stdlib.h>;
#include <fstream>;
#include <iostream>;
using namespace std;

#include ".\CSkin\Include.h";
#pragma warning(disable:4996)

void DemoParse(){
	CExuiSkin ces(L"..\\Skins\\超级列表框");
	if (!ces.IsUnpack()) return ;
	cout << (ces.IsUnpack() ? "解包成功！\n" : "解包失败！") << endl;

	cout << "皮肤版本：" << ces.m_esSkin->uVersion << endl;
	cout << "素材长度：" << ces.m_esdData.uMaterialLength << endl;
	cout << "作者长度：" << ces.m_esdData.uAuthorLength << endl;
	cout << "附加长度：" << ces.m_esdData.uPropertyLength << endl;



	cout << "\n========素材信息=======\n" << endl;

	CExuiSkinMaterial cesm(&ces);
	cout << (cesm.IsUnpack() ? "解包成功！" : "解包失败！") << endl << endl;
	cout << "数量：" << cesm.GetCount() << endl;

	for (int i = 0; i < cesm.GetCount(); i++){
		EXUI_SKIN_MATERIAL* esm = cesm.GetValue(i);
		cout << "[" << i << "]素材长度：" << esm->uDataLength << endl;
		cout << "[" << i << "]素材头长度：" << esm->uHeaderLength << endl;
		cout << "[" << i << "]素材图片长度：" << esm->uImageLength << endl;
		cout << "[" << i << "]素材版本：" << esm->uVersion << endl;
		cout << "[" << i << "]素材属性：" << esm->attr << endl;
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



	cout << "\n========作者信息=======\n" << endl;

	CExuiSkinAuthor cesa(&ces);
	cout << (cesa.IsUnpack() ? "解包成功！" : "解包失败！") << endl << endl;

	cout << "皮肤类型：" << cesa.m_esac.szType << endl;
	cout << "皮肤名称：" << cesa.m_esac.szName << endl;
	cout << "皮肤作者：" << cesa.m_esac.szAuthor << endl;
	cout << "皮肤简介：" << cesa.m_esac.szIntro << endl;
	cout << "皮肤GUID：" << cesa.m_esac.szGuid << endl;



	cout << "\n========附加信息=======\n" << endl;

	CExuiSkinProperty cesp(&ces);
	cout << (cesp.IsUnpack() ? "解包成功！" : "解包失败！") << endl << endl;
	cout << "数量：" << cesp.GetCount() << endl;

	for (int i = 0; i < cesp.GetCount(); i++){
		cout << "值[" << i << "]: " << cesp.GetValue(i) << endl;
	}

	cout << "\n=====================\n" << endl;
}

void DemoLoad(){
	cout << "\n========素材信息=======\n" << endl;
	LARGE_INTEGER freq;
	LARGE_INTEGER start_t, stop_t;
	double exe_time;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start_t);

	/*解析开始*/
	CExuiSkinPaint Skin(CExuiSkin(L"..\\Skins\\超级列表框"));
	//CExuiSkinPaint Skin(CExuiSkin(字节集指针, 长度, false));
	/*解析结束*/

	/*取解析数据开始*/
	cout << "素材数量：" << Skin.GetMaterialCount() << endl;
	for (int i = 0; i < Skin.GetMaterialCount(); i++){
		cout << "[" << i << "]hBitmap: " << Skin.GetMaterial(i).hBitmap << endl;
		cout << "[" << i << "]attrDrawMode: " << Skin.GetMaterial(i).attr.lDrawMode << endl;
	}
	cout << "附加数量：" << Skin.GetPropertyCount() << endl;
	for (int i = 0; i < Skin.GetPropertyCount(); i++){
		cout << "值[" << i << "]: " << Skin.GetProperty(i) << endl;
	}
	/*取解析数据结束*/

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
