#include "stdafx.h"

#include "MainScene.h"
#include "Practice11.h"
#include "Practice12.h"
#include "Practice13.h"
#include "Practice14.h"
#include "Practice15.h"
#include "Practice16.h"
#include "Practice17.h"
#include "Practice18.h"
#include "Practice19.h"
#include "Practice20.h"
#include "Practice21.h"
#include "Practice22.h"
#include "Practice23.h"
#include "Practice24.h"
#include "Practice25.h"
#include "Practice26.h"
#include "Practice27.h"
#include "Practice28.h"

using namespace std;

CMainScene::CMainScene()
{
	
}
CMainScene::~CMainScene()
{
}

void CMainScene::Update(float fTimeElapsed)
{
	m_pCurrentPractice->Update(fTimeElapsed);
}

void CMainScene::Rendering()
{
	m_pCurrentPractice->Rendering();
}

bool CMainScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrentPractice != nullptr)
		m_pCurrentPractice->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	}
	return false;
}

bool CMainScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrentPractice != nullptr)
		m_pCurrentPractice->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		//m_pFramework->ChangeScene(CScene::CurrentScene::Tutering);
		break;
	case WM_MOUSEMOVE:
		break;
	}
	return false;
}

bool CMainScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrentPractice != nullptr)
		m_pCurrentPractice->OnProcessingWindowMessage(hWnd, nMessageID, wParam, lParam);
	switch (nMessageID)
	{
	case WM_SIZE:
		break;
	case WM_DESTROY:
		break;
	}
	return false;
}

void CMainScene::BuildObjects(CFramework * myFramework, HWND hWnd, CurrentScene tag)
{
	CScene::BuildObjects(myFramework, hWnd, tag);
	BuildPractices();
}

void CMainScene::ReleaseObjects()
{
}

void CMainScene::BuildPractices()
{
	/*
	m_arrPractice[GetPracticeEnumInt(Practice_11)] = new CPractice11();
	m_arrPractice[GetPracticeEnumInt(Practice_11)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_11);
	
	m_arrPractice[GetPracticeEnumInt(Practice_12)] = new CPractice12();
	m_arrPractice[GetPracticeEnumInt(Practice_12)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_12);
	
	m_arrPractice[GetPracticeEnumInt(Practice_13)] = new CPractice13();
	m_arrPractice[GetPracticeEnumInt(Practice_13)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_13);
	
	m_arrPractice[GetPracticeEnumInt(Practice_14)] = new CPractice14();
	m_arrPractice[GetPracticeEnumInt(Practice_14)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_14);
	
	m_arrPractice[GetPracticeEnumInt(Practice_15)] = new CPractice15();
	m_arrPractice[GetPracticeEnumInt(Practice_15)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_15);
	
	m_arrPractice[GetPracticeEnumInt(Practice_16)] = new CPractice16();
	m_arrPractice[GetPracticeEnumInt(Practice_16)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_16);
	
	m_arrPractice[GetPracticeEnumInt(Practice_17)] = new CPractice17();
	m_arrPractice[GetPracticeEnumInt(Practice_17)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_17);
	
	m_arrPractice[GetPracticeEnumInt(Practice_18)] = new CPractice18();
	m_arrPractice[GetPracticeEnumInt(Practice_18)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_18);
	
	m_arrPractice[GetPracticeEnumInt(Practice_19)] = new CPractice19();
	m_arrPractice[GetPracticeEnumInt(Practice_19)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_19);

	m_arrPractice[GetPracticeEnumInt(Practice_20)] = new CPractice20();
	m_arrPractice[GetPracticeEnumInt(Practice_20)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_20);

	m_arrPractice[GetPracticeEnumInt(Practice_21)] = new CPractice21();
	m_arrPractice[GetPracticeEnumInt(Practice_21)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_21);

	m_arrPractice[GetPracticeEnumInt(Practice_22)] = new CPractice22();
	m_arrPractice[GetPracticeEnumInt(Practice_22)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_22);

	m_arrPractice[GetPracticeEnumInt(Practice_23)] = new CPractice23();
	m_arrPractice[GetPracticeEnumInt(Practice_23)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_23);

	m_arrPractice[GetPracticeEnumInt(Practice_24)] = new CPractice24();
	m_arrPractice[GetPracticeEnumInt(Practice_24)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_24);
	*/
	m_arrPractice[GetPracticeEnumInt(Practice_25)] = new CPractice25();
	m_arrPractice[GetPracticeEnumInt(Practice_25)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_25);

	m_arrPractice[GetPracticeEnumInt(Practice_26)] = new CPractice26();
	m_arrPractice[GetPracticeEnumInt(Practice_26)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_26);

	m_arrPractice[GetPracticeEnumInt(Practice_27)] = new CPractice27();
	m_arrPractice[GetPracticeEnumInt(Practice_27)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_27);

	m_arrPractice[GetPracticeEnumInt(Practice_28)] = new CPractice28();
	m_arrPractice[GetPracticeEnumInt(Practice_28)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_28);

	m_pCurrentPractice = m_arrPractice[GetPracticeEnumInt(Practice_26)]; // 현재신은 타이틀로 초기화
}

void CMainScene::ChangePractice(CPractice::CurrentPractice Tag, bool bDestroy)
{
	const int tag = GetEnumValueByType(Tag);
	if (bDestroy)
	{
		int d_tag = GetEnumValueByType(m_pCurrentPractice->GetMyTag());
		delete m_pCurrentPractice;
		m_pCurrentPractice = nullptr;
		m_arrPractice[d_tag] = nullptr;
	}
	// 만약 nullptr가 아닐 경우
	if (m_arrPractice[tag])
	{
		m_pCurrentPractice = m_arrPractice[tag];
	}
	else
	{
		switch (Tag)
		{/*
		case CPractice::CurrentPractice::Practice_11:
			m_arrPractice[GetPracticeEnumInt(Practice_11)] = new CPractice11();
			m_arrPractice[GetPracticeEnumInt(Practice_11)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_11);
			break;
		case CPractice::CurrentPractice::Practice_12:
			m_arrPractice[GetPracticeEnumInt(Practice_12)] = new CPractice12();
			m_arrPractice[GetPracticeEnumInt(Practice_12)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_12);
			break;
		case CPractice::CurrentPractice::Practice_13:
			m_arrPractice[GetPracticeEnumInt(Practice_13)] = new CPractice13();
			m_arrPractice[GetPracticeEnumInt(Practice_13)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_13);
			break;
		case CPractice::CurrentPractice::Practice_14:
			m_arrPractice[GetPracticeEnumInt(Practice_14)] = new CPractice14();
			m_arrPractice[GetPracticeEnumInt(Practice_14)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_14);
			break;
		case CPractice::CurrentPractice::Practice_15:
			m_arrPractice[GetPracticeEnumInt(Practice_15)] = new CPractice15();
			m_arrPractice[GetPracticeEnumInt(Practice_15)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_15);
			break;
		case CPractice::CurrentPractice::Practice_16:
			m_arrPractice[GetPracticeEnumInt(Practice_16)] = new CPractice16();
			m_arrPractice[GetPracticeEnumInt(Practice_16)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_16);
			break;
		case CPractice::CurrentPractice::Practice_17:
			m_arrPractice[GetPracticeEnumInt(Practice_17)] = new CPractice17();
			m_arrPractice[GetPracticeEnumInt(Practice_17)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_17);
			break;
		case CPractice::CurrentPractice::Practice_18:
			m_arrPractice[GetPracticeEnumInt(Practice_18)] = new CPractice18();
			m_arrPractice[GetPracticeEnumInt(Practice_18)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_18);
			break;
			
		case CPractice::CurrentPractice::Practice_19:
			m_arrPractice[GetPracticeEnumInt(Practice_19)] = new CPractice19();
			m_arrPractice[GetPracticeEnumInt(Practice_19)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_19);
			break;
		case CPractice::CurrentPractice::Practice_20:
			m_arrPractice[GetPracticeEnumInt(Practice_20)] = new CPractice20();
			m_arrPractice[GetPracticeEnumInt(Practice_20)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_20);
			break;
		case CPractice::CurrentPractice::Practice_21:
			m_arrPractice[GetPracticeEnumInt(Practice_21)] = new CPractice21();
			m_arrPractice[GetPracticeEnumInt(Practice_21)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_21);
			break;
		case CPractice::CurrentPractice::Practice_22:
			m_arrPractice[GetPracticeEnumInt(Practice_22)] = new CPractice22();
			m_arrPractice[GetPracticeEnumInt(Practice_22)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_22);
			break;
		case CPractice::CurrentPractice::Practice_23:
			m_arrPractice[GetPracticeEnumInt(Practice_23)] = new CPractice23();
			m_arrPractice[GetPracticeEnumInt(Practice_23)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_23);
			break;
		case CPractice::CurrentPractice::Practice_24:
			m_arrPractice[GetPracticeEnumInt(Practice_24)] = new CPractice24();
			m_arrPractice[GetPracticeEnumInt(Practice_24)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_24);
			break;*/
		case CPractice::CurrentPractice::Practice_25:
			m_arrPractice[GetPracticeEnumInt(Practice_25)] = new CPractice25();
			m_arrPractice[GetPracticeEnumInt(Practice_25)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_25);
			break;
		case CPractice::CurrentPractice::Practice_26:
			m_arrPractice[GetPracticeEnumInt(Practice_26)] = new CPractice26();
			m_arrPractice[GetPracticeEnumInt(Practice_26)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_26);
			break;
		case CPractice::CurrentPractice::Practice_27:
			m_arrPractice[GetPracticeEnumInt(Practice_27)] = new CPractice27();
			m_arrPractice[GetPracticeEnumInt(Practice_27)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_27);
			break;
		case CPractice::CurrentPractice::Practice_28:
			m_arrPractice[GetPracticeEnumInt(Practice_28)] = new CPractice28();
			m_arrPractice[GetPracticeEnumInt(Practice_28)]->BuildPractice(this, m_hWnd, CPractice::CurrentPractice::Practice_28);
			break;

		}

		m_pCurrentPractice = m_arrPractice[tag];

	}
}


bool CMainScene::ProcessInput()
{
	bool bProcessedByScene = false;

	if (!bProcessedByScene)
	{
		static UCHAR pKeyBuffer[256];
		DWORD dwDirection = 0;

		bool bPushShift = false;
		bool bControll = false;

		if (GetKeyboardState(pKeyBuffer))
		{
			if (pKeyBuffer[VK_LSHIFT] & 0xF0)	  bPushShift = true;
			if (pKeyBuffer[VK_LEFT] & 0xF0)  	  dwDirection |= DIR_LEFT;
			if (pKeyBuffer[VK_RIGHT] & 0xF0)	  dwDirection |= DIR_RIGHT;
			if (pKeyBuffer[VK_UP] & 0xF0)		  dwDirection |= DIR_UP;
			if (pKeyBuffer[VK_DOWN] & 0xF0)		  dwDirection |= DIR_DOWN;

			if (pKeyBuffer['X'] & 0xF0) { bControll = true;}
			else if (pKeyBuffer['Y'] & 0xF0) { bControll = true;  }
			else if (pKeyBuffer['Z'] & 0xF0) { bControll = true;  }
			else if (pKeyBuffer['A'] & 0xF0) { bControll = true; }
			else if (pKeyBuffer['I'] & 0xF0) { bControll = true;  }
			else if (pKeyBuffer['Q'] & 0xF0) { bControll = true;  }
			if ((pKeyBuffer[VK_LEFT] & 0xF0) || (pKeyBuffer[VK_RIGHT] & 0xF0))
			{
				if (dwDirection & DIR_LEFT) { bControll = true; }
				if (dwDirection & DIR_RIGHT) { bControll = true;}
			}
			if ((pKeyBuffer[VK_UP] & 0xF0) || (pKeyBuffer[VK_DOWN] & 0xF0))
			{
				if (dwDirection & DIR_UP) { bControll = true; }
				if (dwDirection & DIR_DOWN) { bControll = true;  }
			}
		}

		if (!bControll)
		{

		}

		return bControll;
	}
	return false;
}
