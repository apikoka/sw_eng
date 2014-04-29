#pragma once
#pragma warning (disable:4996 )

#include <cmath>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;

class CDIP_ProgrammingMyClass
{
public:
	CDIP_ProgrammingMyClass(void);
	~CDIP_ProgrammingMyClass(void);

	BITMAPINFOHEADER m_BMPHeader;
	UCHAR**			 m_ppcBMPToShow;
	UCHAR**			 m_ppcLoadedImage;
	UCHAR**			 m_ppcModifiedImage;
	UCHAR**			 m_ppcPaddedImage;
	UCHAR**			 m_ppcWindow;
	UCHAR*			 m_pcSaveImage;

	UINT			 m_uiHeight;
	UINT			 m_uiWidth;

	FILE*           m_fRead;
	FILE*			m_fWrite;

	UINT32          m_uiFileTotalSize;

	UINT			m_uiGaussianFilterMaskSize;
	UINT			m_uiMedianFilterMaskSize;
	BOOL			m_bLogTransform;
	UINT			m_uiFilterSelection;
	UCHAR*			m_pcLogMap;


	void MyClass_MakeBMP(void);

	void MyClass_ReadFile(CString filepath);
	void MyClass_WriteFile();

	//memory related functions
	UCHAR** MyClass_MemoryAlloc2D(UINT32 height, UINT32 width);
	void MyClass_MemoryFree(UCHAR** pp);

	void MyClass_EnhancementLogTransformation(void);
	void MyClass_EnhancementGaussianFilter(void);
	void MyClass_EnhancementMedianFilter(void);

	void MyClass_Padding(UCHAR** pp);
	void MyClass_Window(UINT32 height, UINT32 width);
};

