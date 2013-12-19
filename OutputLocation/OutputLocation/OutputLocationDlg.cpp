
// OutputLocationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OutputLocation.h"
#include "OutputLocationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const int SRC_FEA_NUM = 324;
const int DES_FEA_NUM = 55;
const CString PCA_FILE_NAME = ".\\pca_55.txt";


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COutputLocationDlg 对话框




COutputLocationDlg::COutputLocationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COutputLocationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COutputLocationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COutputLocationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENFILE, &COutputLocationDlg::OnBnClickedOpenfile)
	ON_BN_CLICKED(IDC_OPENFOLDER, &COutputLocationDlg::OnBnClickedOpenfolder)
	ON_BN_CLICKED(IDC_BUTTONOPENFILEWITHOUTINIT, &COutputLocationDlg::OnBnClickedButtonopenfilewithoutinit)
	ON_BN_CLICKED(IDC_BUTTONOPENFOLDERWITHOURINIT, &COutputLocationDlg::OnBnClickedButtonopenfolderwithourinit)
	ON_BN_CLICKED(IDC_KEYHOG, &COutputLocationDlg::OnBnClickedKeyhog)
END_MESSAGE_MAP()


// COutputLocationDlg 消息处理程序

BOOL COutputLocationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void COutputLocationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COutputLocationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COutputLocationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COutputLocationDlg::OnBnClickedOpenfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath = getFolderPath();
	if(filePath.Find("oni") != -1)
	{
		outputLocation(filePath);
	}
}


void COutputLocationDlg::OnBnClickedOpenfolder()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath = getFolderPath();
	if(filePath != "")
	{
		dealInFolder(filePath);
	}
}

void COutputLocationDlg::dealInFolder(CString filePath)
{
	if(filePath.Find("oni") == -1)
	{
		CFileFind fileFind;
		bool bFound = fileFind.FindFile(filePath + "\\*.*");
		while(bFound)
		{
			bFound = fileFind.FindNextFileA();
			CString fileName = fileFind.GetFilePath();
			if(fileFind.IsDirectory() && !fileFind.IsDots())
			{
				if(fileName.Find("oni") != -1)
				{
					outputLocation(fileName);
				}
				else
				{
					dealInFolder(fileName);
				}
			}
		}
	}
	else
	{
		outputLocation(filePath);
	}
}


CString COutputLocationDlg::getFolderPath(void)
{
	CString strPath = "";
	BROWSEINFO bInfo;
	ZeroMemory(&bInfo,sizeof(bInfo));
	bInfo.hwndOwner = m_hWnd;
	bInfo.lpszTitle = "choose the file path";

	LPITEMIDLIST lpDlist;
	lpDlist = SHBrowseForFolder(&bInfo);
	if(lpDlist != NULL)
	{
		TCHAR chPath[255];
		SHGetPathFromIDList(lpDlist,chPath);
		strPath = chPath;
	}
	return strPath;
}


void COutputLocationDlg::outputLocation(CString filePath)
{
	ifstream skeletonFileReader;
	skeletonFileReader.open(filePath+"\\skeleton.dat",ios::binary);
	if(skeletonFileReader == NULL)
		return;
	SLR_ST_Skeleton mSkeleton;
	CString oniName = filePath.Right(25);
	mkdir(".\\D3");
	mkdir(".\\D2");
	CString pName = oniName.Left(3);
	mkdir(".\\D3\\"+pName);
	mkdir(".\\D2\\"+pName);
	fstream f3(".\\D3\\" + pName + "\\" + oniName + ".txt",ios::out);
	fstream f2(".\\D2\\" + pName + "\\" + oniName + ".txt",ios::out);
	int index = 0;
	while( !skeletonFileReader.eof() )
	{
		skeletonFileReader.read((char*)&mSkeleton,sizeof(mSkeleton));
		if( skeletonFileReader.fail() )
			break;
		if( index == 0)
		{
			f2 << mSkeleton._2dPoint[3].x << " " << mSkeleton._2dPoint[3].y << endl;
			f3 << (int)(1000*mSkeleton._3dPoint[3].x) << " " << (int)(1000*mSkeleton._3dPoint[3].y) << " " << (int)(1000*mSkeleton._3dPoint[3].z) << endl;
		}
		f2 << mSkeleton._2dPoint[7].x << " " << mSkeleton._2dPoint[7].y << " " 
			<< mSkeleton._2dPoint[11].x << " " << mSkeleton._2dPoint[11].y << " " 
			<< endl;
		f3 << (int)(1000*mSkeleton._3dPoint[7].x) << " " << (int)(1000*mSkeleton._3dPoint[7].y) << " " << (int)(1000*mSkeleton._3dPoint[7].z) << " "
			<< (int)(1000*mSkeleton._3dPoint[11].x) << " " << (int)(1000*mSkeleton._3dPoint[11].y) << " " << (int)(1000*mSkeleton._3dPoint[11].z) 
			<< endl;

		index++;
	}

	skeletonFileReader.close();
	f2.close();
	f3.close();
}

void COutputLocationDlg::OnBnClickedButtonopenfilewithoutinit()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath = getFolderPath();
	if(filePath.Find("oni") != -1)
	{
		outputLocationWithoutInit(filePath);
	}
}


void COutputLocationDlg::OnBnClickedButtonopenfolderwithourinit()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath = getFolderPath();
	if(filePath != "")
	{
		dealInFolderWithouInit(filePath);
	}
}

void COutputLocationDlg::dealInFolderWithouInit(CString filePath)

{
	if(filePath.Find("oni") == -1)
	{
		CFileFind fileFind;
		bool bFound = fileFind.FindFile(filePath + "\\*.*");
		while(bFound)
		{
			bFound = fileFind.FindNextFileA();
			CString fileName = fileFind.GetFilePath();
			if(fileFind.IsDirectory() && !fileFind.IsDots())
			{
				if(fileName.Find("oni") != -1)
				{
					outputLocationWithoutInit(fileName);
				}
				else
				{
					dealInFolderWithouInit(fileName);
				}
			}
		}
	}
	else
	{
		outputLocation(filePath);
	}
}

void COutputLocationDlg::outputLocationWithoutInit(CString filePath)

{
	ifstream skeletonFileReader;
	skeletonFileReader.open(filePath+"\\skeleton.dat",ios::binary);
	if(skeletonFileReader == NULL)
		return;
	SLR_ST_Skeleton mSkeleton;

	CString oniName = filePath.Right(25);
	mkdir(".\\D3_withoutInit");
	mkdir(".\\D2_withoutInit");

	CString pName = oniName.Left(3);
	pName = pName.Right(2);
	oniName = oniName.Left(8);
	oniName = oniName.Right(4);
	CString wordName;
	wordName.Format("w%s_%s.txt",oniName,pName);

	fstream f3(".\\D3_withoutInit\\"  + wordName,ios::out);
	fstream f2(".\\D2_withoutInit\\"  + wordName,ios::out);
	int index = 0;
	int beginY = 0;

	vector<SLR_ST_Skeleton> vSke;
	while( !skeletonFileReader.eof() )
	{
		skeletonFileReader.read((char*)&mSkeleton,sizeof(mSkeleton));
		if( skeletonFileReader.fail() )
			break;
		if(index == 0)
		{
			beginY = min( mSkeleton._2dPoint[7].y, mSkeleton._2dPoint[11].y);
		}
		if( mSkeleton._2dPoint[7].y < beginY - 20 ||  mSkeleton._2dPoint[11].y < beginY - 20)
		{
			vSke.push_back(mSkeleton);
		}

		index++;
	}
	f2 << vSke.size() << endl << 4 << endl;
	f3 << vSke.size() << endl << 6 << endl;
	for(int i=0; i<vSke.size(); i++)
	{
		mSkeleton = vSke[i];
		f2 << mSkeleton._2dPoint[7].x << " " << mSkeleton._2dPoint[7].y << " " 
			<< mSkeleton._2dPoint[11].x << " " << mSkeleton._2dPoint[11].y << " " 
			<< endl;
		f3 << mSkeleton._3dPoint[7].x << " " << mSkeleton._3dPoint[7].y << " " << mSkeleton._3dPoint[7].z << " "
			<< mSkeleton._3dPoint[11].x << " " << mSkeleton._3dPoint[11].y << " " << mSkeleton._3dPoint[11].z
			<< endl;
	}

	skeletonFileReader.close();
	f2.close();
	f3.close();
}

bool cmp(CString str1, CString str2)
{
	int index1 = str1.Find("_");
	CString tp1 = str1.Left(index1);
	int i1 = atoi(tp1);
	int index2 = str2.Find("_");
	CString tp2 = str2.Left(index2);
	int i2 = atoi(tp2);
	if(i1 == i2)
	{
		return str1[index1+1]<str2[index2+1];
	}
	else
	{
		return i1<i2;
	}
}

void COutputLocationDlg::OnBnClickedKeyhog()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath = getFolderPath();
	if(filePath == "")
	{
		return;
	}
	//fstream fr(".\\keyFrame.txt",ios::in);

	//keyFrame tmpKF;
	//string fileName;
	//int begin,end;
	//while(!fr.eof())
	//{
	//	fr >> fileName >> begin >> end;
	//	if(fr.fail()) break;
	//	tmpKF.fileName = fileName;
	//	tmpKF.begin = begin;
	//	tmpKF.end = end;
	//	vKeyFrame.push_back(tmpKF);
	//}

	//read PCA
	pcaMat = cvCreateMat(SRC_FEA_NUM,DES_FEA_NUM,CV_32FC1);
	fstream fr(PCA_FILE_NAME,ios::in);
	float data;
	for(int i=0; i<SRC_FEA_NUM; i++)
	{
		for(int j=0; j<DES_FEA_NUM; j++)
		{
			fr >> data;
			cvmSet(pcaMat,i,j,data);
			//fr >> pcaMat->data.db[i*1764+j];
		}
	}
	fr.close();
	retrieveHogFeature(filePath);
}


void COutputLocationDlg::retrieveHogFeature(CString filePath)
{
	CFileFind fileFind; 
	bool bFound = fileFind.FindFile(filePath + "\\*.*");
	while(bFound)
	{
		bFound = fileFind.FindNextFileA();
		CString fileName = fileFind.GetFilePath();
		if( fileFind.IsDirectory() && !fileFind.IsDots() )
		{
			CString oniName = fileName.Right(24);
			oniName = oniName.Left(2);
			if(fileFind.IsDirectory() && !fileFind.IsDots() && fileName.Find(".oni") != -1) // && oniName != "50") 
			{
				getHogFeatureSingle(fileName);
			}
			else
			{
				retrieveHogFeature(fileName);
			}
		}
	}
	fileFind.Close();
}


void COutputLocationDlg::getHogFeatureSingle(CString filePath)

{
	CFileFind fileFind;
	bool bFind = fileFind.FindFile(filePath + "\\*.jpg");

	vector<CString> vFileName;
	CString fileName;

	while(bFind)
	{	
		bFind = fileFind.FindNextFileA();
		fileName = fileFind.GetFileName();
		vFileName.push_back(fileName);

	}
	fileFind.Close();

	sort(vFileName.begin(),vFileName.end(),cmp);

	int index = filePath.ReverseFind('\\');
	CString folderName = filePath.Right(filePath.GetLength() - index -1);
	folderName = folderName.Left(8);
	CString wordName = folderName.Right(4);
	CString peopleName = folderName.Left(3);
	peopleName = peopleName.Right(2);
	CString hogFileName = "w" + wordName + "_" + peopleName + ".txt";

	fstream fw(hogFileName,ios::app);
	fw << vFileName.size()/2 << endl << DES_FEA_NUM << endl;
	fw.close();
	for(int i=0; i<vFileName.size();)
	{
		CString tmpFilePath = filePath + "\\"; //filePath.Left(filePath.GetLength()-5);
		//load left img
		CString dstFilePath = tmpFilePath + vFileName[i];
		IplImage *img1 = cvLoadImage(dstFilePath);
		int j = i;
		while(img1 == NULL && j >= 2)
		{
			cvReleaseImage(&img1);
			dstFilePath = tmpFilePath + vFileName[j-2];
			img1 = cvLoadImage(dstFilePath);
			j = j - 2;
		}
		if(img1 == NULL) img1 = cvLoadImage("black.jpg");
		
		//load right img
		dstFilePath = tmpFilePath + vFileName[i+1];
		IplImage *img2 = cvLoadImage(dstFilePath);
		j = i+1;
		while(img2 == NULL && j >= 2)
		{
			cvReleaseImage(&img2);
			dstFilePath = tmpFilePath + vFileName[j-2];
			img2 = cvLoadImage(dstFilePath);
			j = j - 2;
		}
		if(img2 == NULL) img2 = cvLoadImage("black.jpg");

		int SIZE = 64;

		IplImage *tmpImg1 = cvCreateImage(cvSize(SIZE,SIZE),img1->depth,img1->nChannels);
		cvResize(img1,tmpImg1);

		IplImage *tmpGray1 = cvCreateImage(cvSize(SIZE,SIZE),tmpImg1->depth,1);
		if(tmpImg1->nChannels == 3)
			cvCvtColor(tmpImg1,tmpGray1,CV_BGR2GRAY);
		else 
			cvCopy(tmpImg1,tmpGray1);

		IplImage *tmpImg2 = cvCreateImage(cvSize(SIZE,SIZE),img2->depth,img2->nChannels);
		cvResize(img2,tmpImg2);

		IplImage *tmpGray2 = cvCreateImage(cvSize(SIZE,SIZE),tmpImg2->depth,1);
		if(tmpImg2->nChannels == 3)
			cvCvtColor(tmpImg2,tmpGray2,CV_BGR2GRAY);
		else 
			cvCopy(tmpImg2,tmpGray2);

		IplImage *img = cvCreateImage(cvSize(SIZE*2,SIZE),tmpGray2->depth,tmpGray2->nChannels);
		CvRect roi = cvRect(0,0,SIZE,SIZE);
		cvSetImageROI(img,roi);
		cvCopy(tmpGray1,img);
		cvResetImageROI(img);

		roi = cvRect(SIZE,0,SIZE,SIZE);
		cvSetImageROI(img,roi);
		cvCopy(tmpGray2,img);
		cvResetImageROI(img);

		/*cvShowImage("test",img);
		cvWaitKey(3);*/

		writeHogFeature(img,hogFileName);

		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&tmpImg1);
		cvReleaseImage(&tmpImg2);
		cvReleaseImage(&tmpGray1);
		cvReleaseImage(&tmpGray2);
		cvReleaseImage(&img);

		i += 2;
	}
}




void COutputLocationDlg::writeHogFeature(IplImage* img, CString fileName)

{
	//const int FEA_NUM = 55; //need mofify
	if(img == NULL || bBlackImg(img))
	{
		fstream fw(fileName,ios::app);
		for(int i=0; i<DES_FEA_NUM; i++)
		{
			fw <<0 << " ";
		}
		fw << endl;
		fw.close();
		return;
	}
	int SIZE = 64;

	IplImage *tmpImg = cvCreateImage(cvSize(SIZE,SIZE),img->depth,img->nChannels);
	cvResize(img,tmpImg);

	IplImage *tmpGray = cvCreateImage(cvSize(SIZE,SIZE),tmpImg->depth,1);
	if(tmpImg->nChannels == 3)
		cvCvtColor(tmpImg,tmpGray,CV_BGR2GRAY);
	else 
		cvCopy(tmpImg,tmpGray);

	//need modify
	//HOGDescriptor *hog=new HOGDescriptor(cvSize(SIZE,SIZE),cvSize(16,16),cvSize(8,8),cvSize(8,8),9);
	HOGDescriptor *hog=new HOGDescriptor(cvSize(SIZE,SIZE),cvSize(32,32),cvSize(16,16),cvSize(16,16),9);
	/////////////////////window大ä¨®小?为a64*64，ê?block大ä¨®小?为a8*8，ê?block步?长¡è为a4*4，ê?cell大ä¨®小?为a4*4
	Mat handMat(tmpGray);

	vector<float> descriptors;

	hog->compute(handMat, descriptors,Size(0,0), Size(0,0));


	double total = 0;
	int i;
	for(i=0; i<descriptors.size(); i++)
	{
		total += descriptors[i];
	}
	CvMat *feas = cvCreateMat(1,descriptors.size(),CV_32FC1);
	for(i=0; i<descriptors.size(); i++)
	{
		cvmSet(feas,0,i,descriptors[i]/total);
	}

	CvMat *pcaFeas = cvCreateMat(1,DES_FEA_NUM,CV_32FC1);
	cvMatMul(feas,pcaMat,pcaFeas);

	fstream fw(fileName,ios::app);
	for(i=0; i<DES_FEA_NUM; i++)
	{
		fw << (cvmGet(pcaFeas,0,i) + 0.0295)/(0.0149 + 0.0295) << " ";
	}
	fw << endl;
	fw.close();

	cvReleaseMat(&feas);
	cvReleaseMat(&pcaFeas);

	cvReleaseImage(&tmpImg);
	cvReleaseImage(&tmpGray);
}


bool COutputLocationDlg::bBlackImg(IplImage* img)

{
	if(img->nChannels == 3)
	{
		for(int i=0; i<img->width; i++)
		{
			for(int j=0; j<img->height; j++)
			{
				if((int)((img->imageData + img->widthStep*j)[i*3+0]) != 0 ||
					(int)((img->imageData + img->widthStep*j)[i*3+1]) != 0 ||
					(int)((img->imageData + img->widthStep*j)[i*3+2]) != 0)
					return false;
			}
		}
		return true;
	}
	else
	{
		for(int i=0; i<img->width; i++)
		{
			for(int j=0; j<img->height; j++)
			{
				if((int)((img->imageData + img->widthStep*j)[i]) != 0)
					return false;
			}
		}
		return true;
	}

}
