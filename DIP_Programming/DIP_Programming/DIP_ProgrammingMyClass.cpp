#include "stdafx.h"
#include "DIP_ProgrammingMyClass.h"


CDIP_ProgrammingMyClass::CDIP_ProgrammingMyClass(void)
	:m_pcBMP	(NULL)
	,m_pcImgBuf (NULL)
	,m_uiHeight (0)
	,m_uiWidth  (0)
{
	//setting bitmap header
	m_BMPHeader.biSize			= sizeof(BITMAPINFOHEADER);
	m_BMPHeader.biPlanes		= 1;
	m_BMPHeader.biBitCount		= 24;
	m_BMPHeader.biCompression	= BI_RGB;
	m_BMPHeader.biSizeImage		= 0;
	m_BMPHeader.biXPelsPerMeter	= 0;
	m_BMPHeader.biYPelsPerMeter	= 0;
	m_BMPHeader.biClrUsed		= 0;
	m_BMPHeader.biClrImportant	= 0;
}


CDIP_ProgrammingMyClass::~CDIP_ProgrammingMyClass(void)
{
}

void CDIP_ProgrammingMyClass::MyClass_MakeBMP()
{
	UINT32 i=0, j=0;

	for(i=0;i<m_uiHeight;i++)
	{
		for(j=0;j<m_uiWidth;j++)	
		{
			//vertically inverted
			m_pcBMP[i][j*3]   =m_pcImgBuf[m_uiHeight-i-1][j];
			m_pcBMP[i][j*3+1] =m_pcImgBuf[m_uiHeight-i-1][j];
			m_pcBMP[i][j*3+2] =m_pcImgBuf[m_uiHeight-i-1][j];
		}
	}

	MyClass_MemoryFree(m_pcImgBuf);	//free temporary buffer memory
}

void CDIP_ProgrammingMyClass::MyClass_ReadFile(CString filepath)
{
	m_fp=fopen(filepath, "rb");	//open input file

	fseek(m_fp,0,SEEK_END);	//go to end of the file
	m_uiFileTotalSize=ftell(m_fp);	//get total file size
	rewind(m_fp);	//go back to start point

	m_pcImgBuf=MyClass_MemoryAlloc2D(m_uiHeight,m_uiWidth);

	if(m_pcImgBuf==NULL)	//already allocated?!
		return ;

	fread(&m_pcImgBuf[0][0],sizeof(UINT8), m_uiWidth*m_uiHeight, m_fp);

	if(m_pcBMP!=NULL)	//if fail to allocate	
		MyClass_MemoryFree(m_pcBMP);	//free allocated memory

	if(!(m_uiWidth%4))	
		m_pcBMP=MyClass_MemoryAlloc2D(m_uiHeight, m_uiWidth*3);
	else
		m_pcBMP=MyClass_MemoryAlloc2D(m_uiHeight, m_uiWidth*3+(4-m_uiWidth%4));	//if it's not multiple of 4

	if(m_pcBMP==NULL)	//if fail to allocate	
		return ;

	fread(&m_pcImgBuf[0][0],sizeof(UINT8), m_uiWidth*m_uiHeight, m_fp);	//read only one frame

	MyClass_MakeBMP();	//make bitmap format

	fclose(m_fp);
}

/*   ***********
	 memory related functions
*/
UCHAR** CDIP_ProgrammingMyClass::MyClass_MemoryAlloc2D(UINT32 height, UINT32 width)
{
	UCHAR** pp=0;

	pp=(UCHAR**)malloc(sizeof(UCHAR*)*height);

	if(pp == 0)
	{
		return NULL;
	}

	*pp=(UCHAR*)malloc(sizeof(UCHAR)*width*height);

	if((*pp) == 0)
	{
		free(pp);
		return NULL;
	}

	for(UINT32 i=1;i<height;i++)
	{
		pp[i]=pp[i-1]+width;
	}

	return pp;
}

void CDIP_ProgrammingMyClass::MyClass_MemoryFree(UCHAR** pp)
{
	if(pp==0)	//nothing allocated
		return ;

	free(pp[0]);
	free(pp);
}