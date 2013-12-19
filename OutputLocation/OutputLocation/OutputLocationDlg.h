
// OutputLocationDlg.h : 头文件
//

#pragma once
#include <fstream>
#include <direct.h>
#include <vector>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <algorithm>

using namespace std;
using namespace cv;

typedef struct _Vector2i
{
	int x;
	int y;
}Vector2i;
typedef struct _Vector4f
{
	float x;
	float y;
	float z;
	float w;
} Vector4f;
struct SLR_ST_Skeleton
{
	Vector4f _3dPoint[20];
	Vector2i _2dPoint[20];
};

// COutputLocationDlg 对话框
class COutputLocationDlg : public CDialogEx
{
// 构造
public:
	COutputLocationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OUTPUTLOCATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnBnClickedOpenfolder();
	CString getFolderPath(void);
	void outputLocation(CString filePath);
	void dealInFolder(CString filePath);
	afx_msg void OnBnClickedButtonopenfilewithoutinit();
	afx_msg void OnBnClickedButtonopenfolderwithourinit();
	void outputLocationWithoutInit(CString filePath);
	void dealInFolderWithouInit(CString filePath);
	afx_msg void OnBnClickedKeyhog();
	void retrieveHogFeature(CString filePath);
	void getHogFeatureSingle(CString filePath);
	
	void writeHogFeature(IplImage* img, CString fileName);
	
private:
	CvMat *pcaMat;
public:
	bool bBlackImg(IplImage* img);
};
