#pragma once
#pragma warning (disable:4996 )
class CDIP_ProgrammingMyClass
{
public:
	CDIP_ProgrammingMyClass(void);
	~CDIP_ProgrammingMyClass(void);

	void MyClass_MakeBMP(void);



	void MyClass_ReadFile(CString filepath);

	//memory related functions
	UCHAR** MyClass_MemoryAlloc2D(UINT32 height, UINT32 width);

	void MyClass_MemoryFree(UCHAR** pp);

	BITMAPINFOHEADER m_BMPHeader;
	UCHAR**			 m_pcBMP;
	UCHAR**			 m_pcImgBuf;
	UINT			 m_uiHeight;
	UINT			 m_uiWidth;


	FILE*           m_fp;
	UINT32          m_uiFileTotalSize;
};

