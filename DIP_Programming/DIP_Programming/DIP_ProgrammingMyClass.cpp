#include "stdafx.h"
#include "DIP_ProgrammingMyClass.h"


CDIP_ProgrammingMyClass::CDIP_ProgrammingMyClass(void)
	:m_ppcBMPToShow	(NULL)
	,m_ppcLoadedImage (NULL)
	,m_ppcModifiedImage (NULL)
	,m_ppcPaddedImage(NULL)
	,m_pcSaveImage(NULL)
	,m_ppcWindow(NULL)
	,m_uiHeight (0)
	,m_uiWidth  (0)
	,m_fRead	(NULL)
	,m_fWrite	(NULL)
	,m_pcLogMap (NULL)
	,m_bLogTransform(0)
	,m_uiFilterSelection(0)
	,m_uiGaussianFilterMaskSize(0)
	,m_uiMedianFilterMaskSize(0)
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
	MyClass_MemoryFree(m_ppcLoadedImage);
	MyClass_MemoryFree(m_ppcModifiedImage);
	MyClass_MemoryFree(m_ppcPaddedImage);
}

void CDIP_ProgrammingMyClass::MyClass_MakeBMP()
{
	UINT32 i=0, j=0;

	
	m_ppcModifiedImage=MyClass_MemoryAlloc2D(m_uiHeight, m_uiWidth);

	for(int i=0;i<m_uiHeight;i++)
	{
		for(int j=0;j<m_uiWidth;j++)
			m_ppcModifiedImage[i][j]=0;
	}


	if(m_bLogTransform)
	{
		MyClass_EnhancementLogTransformation();
	}

	else if(m_uiFilterSelection==0)
	{
		if(m_ppcModifiedImage!=NULL)
			delete []m_ppcModifiedImage;
		
		m_ppcModifiedImage=m_ppcLoadedImage;
	}

	else if(m_uiFilterSelection==1)
	{
		MyClass_EnhancementMedianFilter();
	}

	else if(m_uiFilterSelection==2)
	{
		MyClass_EnhancementGaussianFilter();
	}


	/* DONT TOUCH FROM NEXT LINE!*/

	for(i=0;i<m_uiHeight;i++)
	{
		for(j=0;j<m_uiWidth;j++)	
		{
			//vertically inverted
			m_ppcBMPToShow[i][j*3]   =m_ppcModifiedImage[m_uiHeight-i-1][j];
			m_ppcBMPToShow[i][j*3+1] =m_ppcModifiedImage[m_uiHeight-i-1][j];
			m_ppcBMPToShow[i][j*3+2] =m_ppcModifiedImage[m_uiHeight-i-1][j];
		}
	}
		

	//MyClass_MemoryFree(m_pcLoadedImage);	//free temporary buffer memory
}

void CDIP_ProgrammingMyClass::MyClass_EnhancementLogTransformation(void)
{

	m_pcLogMap=new UCHAR[256];
	

	for(int i=0;i<256;i++)
	{
		m_pcLogMap[i]=255*(log10(i+1)/log10(256));
	}

	for(int i=0;i<m_uiHeight;i++)
	{
		for(int j=0;j<m_uiWidth;j++)	
		{
			m_ppcModifiedImage[i][j]   =m_pcLogMap[m_ppcLoadedImage[i][j]];
		}
	}

	m_pcSaveImage=new UCHAR[m_uiHeight*m_uiWidth];

	for(int i=0;i<m_uiHeight;i++)
	{
		for(int j=0;j<m_uiWidth;j++)
		{
			m_pcSaveImage[i*m_uiWidth+j]=m_ppcModifiedImage[i][j];
		}

	}



	ofstream fWrite("../LOGTRANSFORMATION.raw", ios::out | ios::binary);


	fWrite.write((const char*) m_pcSaveImage, m_uiHeight*m_uiWidth);

	fWrite.close();

	m_bLogTransform=FALSE;

	delete []m_pcLogMap;
	delete []m_pcSaveImage;
}

void CDIP_ProgrammingMyClass::MyClass_EnhancementMedianFilter(void)
{
	UCHAR** ppTemp;

	UCHAR** ppMedianMask;

	int masksize=m_uiMedianFilterMaskSize*m_uiMedianFilterMaskSize;

	ppMedianMask=MyClass_MemoryAlloc2D(m_uiMedianFilterMaskSize, m_uiMedianFilterMaskSize);

	m_ppcPaddedImage=MyClass_MemoryAlloc2D(m_uiHeight+m_uiMedianFilterMaskSize-1, m_uiWidth+m_uiMedianFilterMaskSize-1);

	ppTemp=m_ppcModifiedImage;

	MyClass_Padding(m_ppcLoadedImage);

	m_ppcWindow=MyClass_MemoryAlloc2D(m_uiMedianFilterMaskSize, m_uiMedianFilterMaskSize);

	UCHAR *ucSorted=new UCHAR[masksize];


	for(int i=0;i<m_uiHeight;i++)
	{
		for(int j=0;j<m_uiWidth;j++)
		{
			MyClass_Window(i, j);
			for(int k=0;k<masksize;k++)
			{
				ucSorted[k]=m_ppcWindow[0][k];
			}
			sort(ucSorted, ucSorted+masksize);
			
			ppTemp[i][j]=ucSorted[(masksize)>>1];
			
		}
	}


	m_pcSaveImage=new UCHAR[m_uiHeight*m_uiWidth];

	for(int i=0;i<m_uiHeight;i++)
	{
		for(int j=0;j<m_uiWidth;j++)
		{
			m_pcSaveImage[i*m_uiWidth+j]=m_ppcModifiedImage[i][j];
		}

	}

	char filename[100]="../MedianFilter_";
	char cMasksize[3]="";
	itoa(m_uiMedianFilterMaskSize, cMasksize, 10);
	strcat(filename, cMasksize);
	strcat(filename, ".raw");

	ofstream fWrite(filename, ios::out | ios::binary);



	fWrite.write((const char*) m_pcSaveImage, m_uiHeight*m_uiWidth);

	fWrite.close();

	delete []m_pcSaveImage;

}

void CDIP_ProgrammingMyClass::MyClass_EnhancementGaussianFilter(void)
{

	UCHAR** ppTemp;

	//MyClass_Padding(m_ppcLoadedImage);

	DOUBLE** dGaussianMask;
	dGaussianMask=(DOUBLE**)malloc(sizeof(DOUBLE*)*m_uiGaussianFilterMaskSize);

	if(dGaussianMask == 0)
	{
		return ;
	}

	*dGaussianMask=(DOUBLE*)malloc(sizeof(DOUBLE)*m_uiGaussianFilterMaskSize*m_uiGaussianFilterMaskSize);

	if((*dGaussianMask) == 0)
	{
		free(dGaussianMask);
		return ;
	}

	for(UINT32 i=1;i<m_uiGaussianFilterMaskSize;i++)
	{
		dGaussianMask[i]=dGaussianMask[i-1]+m_uiGaussianFilterMaskSize;
	}

	double count=0;
	for(int i=0;i<m_uiGaussianFilterMaskSize;i++)
	{
		for(int j=0;j<m_uiGaussianFilterMaskSize;j++)
		{
			int tmp=((i-(m_uiGaussianFilterMaskSize/2))*(i-(m_uiGaussianFilterMaskSize/2))+(j-(m_uiGaussianFilterMaskSize/2))*(j-(m_uiGaussianFilterMaskSize/2)))*-1;
			dGaussianMask[i][j]=pow(exp(1.0),tmp/4);
			count+=dGaussianMask[i][j];
		}
	}

	double offset=1/count;

	count=0;
	for(int i=0;i<m_uiGaussianFilterMaskSize;i++)
	{
		for(int j=0;j<m_uiGaussianFilterMaskSize;j++)
		{
			dGaussianMask[i][j]*=offset;
			count+=dGaussianMask[i][j];
		}
	}
	
	m_ppcPaddedImage=MyClass_MemoryAlloc2D(m_uiHeight+m_uiGaussianFilterMaskSize-1, m_uiWidth+m_uiGaussianFilterMaskSize-1);

	if(m_ppcModifiedImage==NULL)
		ppTemp=m_ppcLoadedImage;
	else
		ppTemp=m_ppcModifiedImage;
	
	MyClass_Padding(m_ppcLoadedImage);



	m_ppcWindow=MyClass_MemoryAlloc2D(m_uiGaussianFilterMaskSize, m_uiGaussianFilterMaskSize);
	
	double sum=0;
	for(int i=0;i<m_uiHeight;i++)
	{
		for(int j=0;j<m_uiWidth;j++)
		{
			MyClass_Window(i, j);
			for(int k=0;k<m_uiGaussianFilterMaskSize*m_uiGaussianFilterMaskSize;k++)
			{
				sum+=m_ppcWindow[0][k]*dGaussianMask[0][k];
			}
			ppTemp[i][j]=sum;
			sum=0;
		}
	}


	m_pcSaveImage=new UCHAR[m_uiHeight*m_uiWidth];

	for(int i=0;i<m_uiHeight;i++)
	{
		for(int j=0;j<m_uiWidth;j++)
		{
			m_pcSaveImage[i*m_uiWidth+j]=m_ppcModifiedImage[i][j];
		}

	}

	char filename[100]="../GaussianFilter_";
	char cMasksize[3]="";
	itoa(m_uiGaussianFilterMaskSize, cMasksize, 10);
	strcat(filename, cMasksize);
	strcat(filename, ".raw");

	ofstream fWrite(filename, ios::out | ios::binary);

	fWrite.write((const char*) m_pcSaveImage, m_uiHeight*m_uiWidth);

	fWrite.close();
	

}
void CDIP_ProgrammingMyClass::MyClass_ReadFile(CString filepath)
{
	m_fRead=fopen(filepath, "rb");	//open input file

	fseek(m_fRead,0,SEEK_END);	//go to end of the file
	m_uiFileTotalSize=ftell(m_fRead);	//get total file size
	rewind(m_fRead);	//go back to start point

	m_ppcLoadedImage=MyClass_MemoryAlloc2D(m_uiHeight,m_uiWidth);

	if(m_ppcLoadedImage==NULL)	//already allocated?!
		return ;

	fread(&m_ppcLoadedImage[0][0],sizeof(UINT8), m_uiWidth*m_uiHeight, m_fRead);

	if(m_ppcBMPToShow!=NULL)	//if fail to allocate	
		MyClass_MemoryFree(m_ppcBMPToShow);	//free allocated memory

	if(!(m_uiWidth%4))	
		m_ppcBMPToShow=MyClass_MemoryAlloc2D(m_uiHeight, m_uiWidth*3);
	else
		m_ppcBMPToShow=MyClass_MemoryAlloc2D(m_uiHeight, m_uiWidth*3+m_uiWidth%4);	//if it's not multiple of 4

	if(m_ppcBMPToShow==NULL)	//if fail to allocate	
		return ;

	fread(&m_ppcLoadedImage[0][0],sizeof(UINT8), m_uiWidth*m_uiHeight, m_fRead);	//read only one frame

	MyClass_MakeBMP();	//make bitmap format

	fclose(m_fRead);
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

void CDIP_ProgrammingMyClass::MyClass_Padding(UCHAR** ppTemp)
{

	int PositionOffset;
	
	if(m_uiFilterSelection==1)
		PositionOffset=m_uiMedianFilterMaskSize/2;
	else if(m_uiFilterSelection==2)
		PositionOffset=m_uiGaussianFilterMaskSize/2;



	for(int i=0;i<m_uiHeight;i++)
	{
		for(int j=0;j<m_uiWidth;j++)
		{
			m_ppcPaddedImage[i+PositionOffset][j+PositionOffset]=ppTemp[i][j];
		}
	}


	for(int i=0;i<PositionOffset;i++)
	{
		for(int j=0;j<m_uiWidth;j++)
		{
			m_ppcPaddedImage[i][j+PositionOffset]=ppTemp[0][j];
			m_ppcPaddedImage[i+m_uiHeight+PositionOffset][j+PositionOffset]=ppTemp[m_uiHeight-1][j];
		}

		for(int k=0;k<m_uiHeight;k++)
		{
			m_ppcPaddedImage[k+PositionOffset][i]=ppTemp[k][0];
			m_ppcPaddedImage[k+PositionOffset][i+m_uiWidth+PositionOffset]=ppTemp[k][m_uiWidth-1];
		}
	}

	for(int i=0;i<PositionOffset;i++)
	{
		for(int j=0;j<PositionOffset;j++)
		{
			m_ppcPaddedImage[i][j]=ppTemp[0][0];
			m_ppcPaddedImage[i][j+m_uiWidth+PositionOffset]=ppTemp[0][m_uiWidth-1];
			m_ppcPaddedImage[i+m_uiHeight+PositionOffset][j]=ppTemp[m_uiHeight-1][0];
			m_ppcPaddedImage[i+m_uiHeight+PositionOffset][j+PositionOffset]=ppTemp[m_uiHeight-1][m_uiWidth-1];
		}
	}

}

void CDIP_ProgrammingMyClass::MyClass_Window(UINT32 height, UINT32 width)
{
	int offset=0;
	if(m_uiFilterSelection==1)
		offset=m_uiMedianFilterMaskSize;
	else if(m_uiFilterSelection==2)
		offset=m_uiGaussianFilterMaskSize;

	for(int i=0;i<offset;i++)
	{
		for(int j=0;j<offset;j++)
		{
			m_ppcWindow[i][j]=m_ppcPaddedImage[height+i][width+j];
		}
	}
}