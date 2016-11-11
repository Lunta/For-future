#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_LINE_2013182030 19
#define RISK_0_2013182030 1.0f
#define RISK_1_2013182030 10.0f
#define RISK_2_2013182030 100.0f
#define RISK_3_2013182030 1000.0f
#define RISK_4_2013182030 10000.0f
#define RISK_5_2013182030 100000.0f
#define TIME_SEED_2013182030 0
 ///////////////////////////////////////콘솔창 최대화 필수// 0 : Off // 1 : riskcheck // 2 : foulcheck //////////////////
/*//////////////////////////////////*/int Debug_2013182030 = 0;//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	EMPTY_2013182030 = 0, BLACK_2013182030 = 1, WHITE_2013182030 = 2,
}KindOfStone_2013182030;
typedef enum
{
	FNULL_2013182030 = 0, F33_2013182030 = 1, F44_2013182030 = 10
}KindOfFoul_2013182030;
int m_board_2013182030[BOARD_LINE_2013182030][BOARD_LINE_2013182030];
float m_riskboard_2013182030[BOARD_LINE_2013182030][BOARD_LINE_2013182030];
int m_Bfoulboard_2013182030[BOARD_LINE_2013182030][BOARD_LINE_2013182030];
int m_Wfoulboard_2013182030[BOARD_LINE_2013182030][BOARD_LINE_2013182030];
int m_riskcheck[6];
int m_foulcheck[5];

int X_2013182030[10];
int Y_2013182030[10];
int idx_2013182030;
bool start_2013182030 = false;
bool set_2013182030 = false;
bool Bturn_2013182030 = false;
bool Wturn_2013182030 = false;

int CheckRisk_2013182030(int riskcheckstone, int *x, int *y);

void BCheckFoul_2013182030();
void WCheckFoul_2013182030();

void CheckWidthLineRiskA_2013182030(int riskcheckstone, int x, int y);
void CheckWidthLineRiskB_2013182030(int riskcheckstone, int x, int y);
void CheckHeightLineRiskA_2013182030(int riskcheckstone, int x, int y);
void CheckHeightLineRiskB_2013182030(int riskcheckstone, int x, int y);
void CheckDiagLineRiskA_2013182030(int riskcheckstone, int x, int y);
void CheckDiagLineRiskB_2013182030(int riskcheckstone, int x, int y);
void CheckRevDiagLineRiskA_2013182030(int riskcheckstone, int x, int y);
void CheckRevDiagLineRiskB_2013182030(int riskcheckstone, int x, int y);

void BlackAttack_2013182030이상기 (int *x, int *y);
void BlackDefence_2013182030이상기(int  x, int  y);
void WhiteAttack_2013182030이상기 (int *x, int *y);
void WhiteDefence_2013182030이상기(int  x, int  y);

int CheckRisk_2013182030(int riskcheckstone, int *x, int *y)
{
	int max = -1, r = 0;
	srand((unsigned)time(TIME_SEED_2013182030));
	for (int i = 0; i < BOARD_LINE_2013182030; i++)
		for (int j = 0; j < BOARD_LINE_2013182030; j++)
		{
			m_riskboard_2013182030[i][j] = 0.0f;
			m_Bfoulboard_2013182030[i][j] = 0;
			m_Wfoulboard_2013182030[i][j] = 0;
		}
	BCheckFoul_2013182030();
	WCheckFoul_2013182030();
	for (int i = 0; i < BOARD_LINE_2013182030; i++)
		for (int j = 0; j < BOARD_LINE_2013182030; j++)
		{
			if (j < BOARD_LINE_2013182030 - 5)
				CheckWidthLineRiskA_2013182030(riskcheckstone, j, i);
			if (i < BOARD_LINE_2013182030 - 5)
				CheckHeightLineRiskA_2013182030(riskcheckstone, j, i);
			if (i < BOARD_LINE_2013182030 - 5 && j < BOARD_LINE_2013182030 - 5)
				CheckDiagLineRiskA_2013182030(riskcheckstone, j, i);
			if (i < BOARD_LINE_2013182030 - 5 && j > 4)
				CheckRevDiagLineRiskA_2013182030(riskcheckstone, j, i);
		}
	for (int i = BOARD_LINE_2013182030 - 1; i >= 0; i--)
		for (int j = BOARD_LINE_2013182030 - 1; j >= 0; j--)
		{
			if (j > 4)
				CheckWidthLineRiskB_2013182030(riskcheckstone, j, i);
			if (i > 4)
				CheckHeightLineRiskB_2013182030(riskcheckstone, j, i);
			if (i > 4 && j > 4)
				CheckDiagLineRiskB_2013182030(riskcheckstone, j, i);
			if (i > 4 && j < BOARD_LINE_2013182030 - 5)
				CheckRevDiagLineRiskB_2013182030(riskcheckstone, j, i);
		}
	for (int i = 0; i < BOARD_LINE_2013182030; i++)
		for (int j = 0; j < BOARD_LINE_2013182030; j++)
		{
			if (m_board_2013182030[i][j] != EMPTY_2013182030) {
				m_riskboard_2013182030[i][j] = -1;
				m_Bfoulboard_2013182030[i][j] = -1;
				m_Wfoulboard_2013182030[i][j] = -1;
			}
			if (riskcheckstone == WHITE_2013182030) 
			{
				if ((m_Wfoulboard_2013182030[i][j] % 10) > F33_2013182030)
					m_riskboard_2013182030[i][j] += RISK_4_2013182030;
				if ((m_Wfoulboard_2013182030[i][j] / F44_2013182030) >= F33_2013182030 * 2)
					m_riskboard_2013182030[i][j] += RISK_4_2013182030;
				if (m_Wfoulboard_2013182030[i][j] == 11)
					m_riskboard_2013182030[i][j] += RISK_4_2013182030/2;
			}
			else if (riskcheckstone == BLACK_2013182030)
			{
				if ((m_Bfoulboard_2013182030[i][j] % 10) > F33_2013182030)
					m_riskboard_2013182030[i][j] -= RISK_5_2013182030 * 10;
				if ((m_Bfoulboard_2013182030[i][j] / F44_2013182030) >= F33_2013182030 * 2)
					m_riskboard_2013182030[i][j] -= RISK_5_2013182030 * 10;
				if (m_Bfoulboard_2013182030[i][j] == 11)
					m_riskboard_2013182030[i][j] += RISK_4_2013182030/2;
			}
		}
	for (int i = 0; i < BOARD_LINE_2013182030; i++)
		for (int j = 0; j < BOARD_LINE_2013182030; j++)
		{
			if (Bturn_2013182030)
			{
				if (riskcheckstone == BLACK_2013182030)
				{
					if ((m_Bfoulboard_2013182030[i][j] % 10) > F33_2013182030)
						m_riskboard_2013182030[i][j] -= RISK_5_2013182030 * 10;
					if ((m_Bfoulboard_2013182030[i][j] / F44_2013182030) >= F33_2013182030 * 2)
						m_riskboard_2013182030[i][j] -= RISK_5_2013182030 * 10;
					if (max < m_riskboard_2013182030[i][j]) {
						max = m_riskboard_2013182030[i][j];
						*x = j;
						*y = i;
						for (int k = 0; k < 10; k++)
						{
							X_2013182030[idx_2013182030] = 0;
							Y_2013182030[idx_2013182030] = 0;
						}
						idx_2013182030 = 0;
					}
					else if (max == m_riskboard_2013182030[i][j])
					{
						X_2013182030[idx_2013182030] = j;
						Y_2013182030[idx_2013182030] = i;
						if (idx_2013182030 < 9)idx_2013182030++;
					}
				}
				else if (riskcheckstone == WHITE_2013182030) 
				{
					if ((m_Bfoulboard_2013182030[i][j] % 10) > F33_2013182030)
						m_riskboard_2013182030[i][j] -= RISK_5_2013182030 * 10;
					if ((m_Bfoulboard_2013182030[i][j] / F44_2013182030) >= F33_2013182030 * 2)
						m_riskboard_2013182030[i][j] -= RISK_5_2013182030 * 10;
					if (m_Bfoulboard_2013182030[i][j] == 11)
						m_riskboard_2013182030[i][j] += RISK_4_2013182030 / 2;
					if (m_Wfoulboard_2013182030[i][j] == 11)
						m_riskboard_2013182030[i][j] += RISK_4_2013182030 / 2;
					if (max < m_riskboard_2013182030[i][j]) {
						max = m_riskboard_2013182030[i][j];
						*x = j;
						*y = i;
						for (int k = 0; k < 10; k++)
						{
							X_2013182030[idx_2013182030] = 0;
							Y_2013182030[idx_2013182030] = 0;
						}
						idx_2013182030 = 0;
					}
					else if (max == m_riskboard_2013182030[i][j])
					{
						X_2013182030[idx_2013182030] = j;
						Y_2013182030[idx_2013182030] = i;
						if (idx_2013182030 < 9)idx_2013182030++;
					}
				}
			}
			else if(Wturn_2013182030)
			{
				if (riskcheckstone == WHITE_2013182030)
				{
					if ((m_Bfoulboard_2013182030[i][j] % 10) > F33_2013182030)
						m_riskboard_2013182030[i][j] -= RISK_5_2013182030 * 3;
					if ((m_Wfoulboard_2013182030[i][j] % 10) > F33_2013182030)
						m_riskboard_2013182030[i][j] += RISK_4_2013182030 * 2;
					if ((m_Wfoulboard_2013182030[i][j] / F44_2013182030) >= F33_2013182030 * 2)
						m_riskboard_2013182030[i][j] += RISK_5_2013182030 * 2;
					if (m_Wfoulboard_2013182030[i][j] == 11)
						m_riskboard_2013182030[i][j] += RISK_4_2013182030;
					if (max < m_riskboard_2013182030[i][j]) {
						max = m_riskboard_2013182030[i][j];
						*x = j;
						*y = i;
						for (int k = 0; k < 10; k++)
						{
							X_2013182030[idx_2013182030] = 0;
							Y_2013182030[idx_2013182030] = 0;
						}
						idx_2013182030 = 0;
					}
					else if (max == m_riskboard_2013182030[i][j])
					{
						X_2013182030[idx_2013182030] = j;
						Y_2013182030[idx_2013182030] = i;
						if (idx_2013182030 < 9)idx_2013182030++;
					}
				}
				else if (riskcheckstone == BLACK_2013182030)
				{
					if ((m_Bfoulboard_2013182030[i][j] % 10) > F33_2013182030)
						m_riskboard_2013182030[i][j] -= RISK_5_2013182030 * 3;
					if ((m_Bfoulboard_2013182030[i][j] / F44_2013182030) >= F33_2013182030 * 2)
						m_riskboard_2013182030[i][j] -= RISK_5_2013182030 * 2;
					if (max < m_riskboard_2013182030[i][j]) {
						max = m_riskboard_2013182030[i][j];
						*x = j;
						*y = i;
						for (int k = 0; k < 10; k++)
						{
							X_2013182030[idx_2013182030] = 0;
							Y_2013182030[idx_2013182030] = 0;
						}
						idx_2013182030 = 0;
					}
					else if (max == m_riskboard_2013182030[i][j])
					{
						X_2013182030[idx_2013182030] = j;
						Y_2013182030[idx_2013182030] = i;
						if (idx_2013182030 < 9)idx_2013182030++;
					}
				}
			}
		}
	if (idx_2013182030 != 0)
	{
		int r = rand() % (idx_2013182030);
		*x = X_2013182030[r];
		*y = Y_2013182030[r];
	}
	return max;
}

void BCheckFoul_2013182030()
{
	int lcount = 0, rcount = 0;
	int recount = 0, lecount = 0;
	int s = 0;
	bool rempty = false;
	bool lempty = false; 

	for (int i = 0; i < BOARD_LINE_2013182030; i++)
		for (int j = 0; j < BOARD_LINE_2013182030; j++) {
			if (m_board_2013182030[i][j] == EMPTY_2013182030)
			{
////////////////////////////////////////////////////////////////// 가로 //////////////////////////////////////////////////////
				rcount = 0;
				lcount = 0;
				recount = 0;
				lecount = 0;
				lempty = false;
				rempty = false;
				s = 0;
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0; ((j + a < BOARD_LINE_2013182030) && (a < 5)); a++)
				{
					m_foulcheck[a] = m_board_2013182030[i][j + a];
				}
				for (int a = 0; ((j + a < BOARD_LINE_2013182030) && (a < 5)); a++)
				{
					if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (recount < 3)
							rcount++;
						if (recount == 2 && a == 4)
							rcount--;
						recount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						rempty = true;
						recount++;
					}
					else if (m_foulcheck[a] == WHITE_2013182030)
					{
						if(recount < 1)
							rempty = false;
						break;
					}
				}
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0; ((j - a >= 0) && (a < 5)); a++)
				{
					m_foulcheck[a] = m_board_2013182030[i][j - a];
				}
				for (int a = 0; ((j - a >= 0) && (a < 5)); a++)
				{
					if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (lecount < 3)
							lcount++;
						if (lecount == 2 && a == 4)
							lcount--;
						lecount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						lempty = true;
						lecount++;
					}
					else if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (lecount < 1)
							lempty = false;
						break;
					}
				}
				s = lcount + rcount;
				if (rempty && lempty && s == 2)
				{
					m_Bfoulboard_2013182030[i][j] += F33_2013182030;
				}
				if ((rempty || lempty) && s == 3)
				{
					m_Bfoulboard_2013182030[i][j] += F44_2013182030;
				}
////////////////////////////////////////////////////////////////// 가로 //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////// 세로 //////////////////////////////////////////////////////
				rcount = 0;
				lcount = 0;
				recount = 0;
				lecount = 0;
				lempty = false;
				rempty = false;
				s = 0;
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5)); a++)
				{
					m_foulcheck[a] = m_board_2013182030[i + a][j];
				}
				for (int a = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5)); a++)
				{
					if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (recount < 3)
							rcount++;
						if (recount == 2 && a == 4)
							rcount--;
						recount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						rempty = true;
						recount++;
					}
					else if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (recount < 1)
							rempty = false;
						break;
					}
				}
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0; ((i - a >= 0) && (a < 5)); a++)
				{
					m_foulcheck[a] = m_board_2013182030[i - a][j];
				}
				for (int a = 0; ((i - a >= 0) && (a < 5)); a++)
				{
					if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (lecount < 3)
							lcount++;
						if (lecount == 2 && a == 4)
							lcount--;
						lecount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						lempty = true;
						lecount++;
					}
					else if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (lecount < 1)
							lempty = false;
						break;
					}
				}
				s = lcount + rcount;
				if (rempty && lempty && s == 2)
				{
					m_Bfoulboard_2013182030[i][j] += F33_2013182030;
				}
				if ((rempty || lempty) && s == 3)
				{
					m_Bfoulboard_2013182030[i][j] += F44_2013182030;
				}
////////////////////////////////////////////////////////////////// 세로 //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// 대각선 //////////////////////////////////////////////////////
				rcount = 0;
				lcount = 0;
				recount = 0;
				lecount = 0;
				lempty = false;
				rempty = false;
				s = 0;
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0, b = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5) && (j + b < BOARD_LINE_2013182030) && (b < 5)); a++, b++)
				{
					m_foulcheck[a] = m_board_2013182030[i + a][j + b];
				}
				for (int a = 0, b = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5) && (j + b < BOARD_LINE_2013182030) && (b < 5)); a++, b++)
				{
					if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (recount < 3)
							rcount++;
						if (recount == 2 && a == 4)
							rcount--;
						recount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						rempty = true;
						recount++;
					}
					else if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (recount < 1)
							rempty = false;
						break;
					}
				}
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0, b = 0; ((i - a >= 0) && (a < 5) && (j - b >= 0) && (b < 5)); a++, b++)
				{
					m_foulcheck[a] = m_board_2013182030[i - a][j - b];
				}
				for (int a = 0, b = 0; ((i - a >= 0) && (a < 5) && (j - b >= 0) && (b < 5)); a++, b++)
				{
					if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (lecount < 3)
							lcount++;
						if (lecount == 2 && a == 4)
							lcount--;
						lecount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						lempty = true;
						lecount++;
					}
					else if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (lecount < 1)
							lempty = false;
						break;
					}
				}
				s = lcount + rcount;
				if (rempty && lempty && s == 2)
				{
					m_Bfoulboard_2013182030[i][j] += F33_2013182030;
				}
				if ((rempty || lempty) && s == 3)
				{
					m_Bfoulboard_2013182030[i][j] += F44_2013182030;
				}
///////////////////////////////////////////////////////////////// 대각선 //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////// 역대각선 //////////////////////////////////////////////////////
				rcount = 0;
				lcount = 0;
				recount = 0;
				lecount = 0;
				lempty = false;
				rempty = false;
				s = 0;
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0, b = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5) && (j - b < BOARD_LINE_2013182030) && (b < 5)); a++, b++)
				{
					m_foulcheck[a] = m_board_2013182030[i + a][j - b];
				}
				for (int a = 0, b = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5) && (j - b < BOARD_LINE_2013182030) && (b < 5)); a++, b++)
				{
					if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (recount < 3)
							rcount++;
						if (recount == 2 && a == 4)
							rcount--;
						recount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						rempty = true;
						recount++;
					}
					else if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (recount < 1)
							rempty = false;
						break;
					}
				}
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0, b = 0; ((i - a >= 0) && (a < 5) && (j + b >= 0) && (b < 5)); a++, b++)
				{
					m_foulcheck[a] = m_board_2013182030[i - a][j + b];
				}
				for (int a = 0, b = 0; ((i - a >= 0) && (a < 5) && (j + b >= 0) && (b < 5)); a++, b++)
				{
					if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (lecount < 3)
							lcount++;
						if (lecount == 2 && a == 4)
							lcount--;
						lecount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						lempty = true;
						lecount++;
					}
					else if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (lecount < 1)
							lempty = false;
						break;
					}
				}
				s = lcount + rcount;
				if (rempty && lempty && s == 2)
				{
					m_Bfoulboard_2013182030[i][j] += F33_2013182030;
				}
				if ((rempty || lempty) &&s == 3)
				{
					m_Bfoulboard_2013182030[i][j] += F44_2013182030;
				}
//////////////////////////////////////////////////////////////// 역대각선 //////////////////////////////////////////////////////
			}
		}
}
void WCheckFoul_2013182030()
{
	int lcount = 0, rcount = 0;
	int recount = 0, lecount = 0;
	int s = 0;
	bool rempty = false;
	bool lempty = false;

	for (int i = 0; i < BOARD_LINE_2013182030; i++)
		for (int j = 0; j < BOARD_LINE_2013182030; j++) {
			if (m_board_2013182030[i][j] == EMPTY_2013182030)
			{
////////////////////////////////////////////////////////////////// 가로 //////////////////////////////////////////////////////
				rcount = 0;
				lcount = 0;
				recount = 0;
				lecount = 0;
				lempty = false;
				rempty = false;
				s = 0;
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0; ((j + a < BOARD_LINE_2013182030) && (a < 5)); a++)
				{
					m_foulcheck[a] = m_board_2013182030[i][j + a];
				}
				for (int a = 0; ((j + a < BOARD_LINE_2013182030) && (a < 5)); a++)
				{
					if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (recount < 3)
							rcount++;
						if (recount == 2 && a == 4)
							rcount--;
						recount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						rempty = true;
						recount++;
					}
					else if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (recount < 1)
							rempty = false;
						break;
					}
				}
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0; ((j - a >= 0) && (a < 5)); a++)
				{
					m_foulcheck[a] = m_board_2013182030[i][j - a];
				}
				for (int a = 0; ((j - a >= 0) && (a < 5)); a++)
				{
					if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (lecount < 3)
							lcount++;
						if (lecount == 2 && a == 4)
							lcount--;
						lecount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						lempty = true;
						lecount++;
					}
					else if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (lecount < 1)
							lempty = false;
						break;
					}
				}
				s = lcount + rcount;
				if (rempty && lempty && s == 2)
				{
					m_Wfoulboard_2013182030[i][j] += F33_2013182030;
				}
				if ((rempty || lempty) && s == 3)
				{
					m_Wfoulboard_2013182030[i][j] += F44_2013182030;
				}
////////////////////////////////////////////////////////////////// 가로 //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////// 세로 //////////////////////////////////////////////////////
				rcount = 0;
				lcount = 0;
				recount = 0;
				lecount = 0;
				lempty = false;
				rempty = false;
				s = 0;
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5)); a++)
				{
					m_foulcheck[a] = m_board_2013182030[i + a][j];
				}
				for (int a = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5)); a++)
				{
					if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (recount < 3)
							rcount++;
						if (recount == 2 && a == 4)
							rcount--;
						recount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						rempty = true;
						recount++;
					}
					else if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (recount < 1)
							rempty = false;
						break;
					}
				}
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0; ((i - a >= 0) && (a < 5)); a++)
				{
					m_foulcheck[a] = m_board_2013182030[i - a][j];
				}
				for (int a = 0; ((i - a >= 0) && (a < 5)); a++)
				{
					if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (lecount < 3)
							lcount++;
						if (lecount == 2 && a == 4)
							lcount--;
						lecount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						lempty = true;
						lecount++;
					}
					else if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (lecount < 1)
							lempty = false;
						break;
					}
				}
				s = lcount + rcount;
				if (rempty && lempty && s == 2)
				{
					m_Wfoulboard_2013182030[i][j] += F33_2013182030;
				}
				if ((rempty || lempty) && s == 3)
				{
					m_Wfoulboard_2013182030[i][j] += F44_2013182030;
				}
////////////////////////////////////////////////////////////////// 세로 //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////// 대각선 //////////////////////////////////////////////////////
				rcount = 0;
				lcount = 0;
				recount = 0;
				lecount = 0;
				lempty = false;
				rempty = false;
				s = 0;
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0, b = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5) && (j + b < BOARD_LINE_2013182030) && (b < 5)); a++, b++)
				{
					m_foulcheck[a] = m_board_2013182030[i + a][j + b];
				}
				for (int a = 0, b = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5) && (j + b < BOARD_LINE_2013182030) && (b < 5)); a++, b++)
				{
					if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (recount < 3)
							rcount++;
						if (recount == 2 && a == 4)
							rcount--;
						recount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						rempty = true;
						recount++;
					}
					else if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (recount < 1)
							rempty = false;
						break;
					}
				}
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0, b = 0; ((i - a >= 0) && (a < 5) && (j - b >= 0) && (b < 5)); a++, b++)
				{
					m_foulcheck[a] = m_board_2013182030[i - a][j - b];
				}
				for (int a = 0, b = 0; ((i - a >= 0) && (a < 5) && (j - b >= 0) && (b < 5)); a++, b++)
				{
					if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (lecount < 3)
							lcount++;
						if (lecount == 2 && a == 4)
							lcount--;
						lecount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						lempty = true;
						lecount++;
					}
					else if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (lecount < 1)
							lempty = false;
						break;
					}
				}
				s = lcount + rcount;
				if (rempty && lempty && s == 2)
				{
					m_Wfoulboard_2013182030[i][j] += F33_2013182030;
				}
				if ((rempty || lempty) && s == 3)
				{
					m_Wfoulboard_2013182030[i][j] += F44_2013182030;
				}
///////////////////////////////////////////////////////////////// 대각선 //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////// 역대각선 //////////////////////////////////////////////////////
				rcount = 0;
				lcount = 0;
				recount = 0;
				lecount = 0;
				lempty = false;
				rempty = false;
				s = 0;
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0, b = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5) && (j - b < BOARD_LINE_2013182030) && (b < 5)); a++, b++)
				{
					m_foulcheck[a] = m_board_2013182030[i + a][j - b];
				}
				for (int a = 0, b = 0; ((i + a < BOARD_LINE_2013182030) && (a < 5) && (j - b < BOARD_LINE_2013182030) && (b < 5)); a++, b++)
				{
					if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (recount < 3)
							rcount++;
						if (recount == 2 && a == 4)
							rcount--;
						recount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						rempty = true;
						recount++;
					}
					else if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (recount < 1)
							rempty = false;
						break;
					}
				}
				for (int a = 0; a < 5; a++)
					m_foulcheck[a] = 0;
				for (int a = 0, b = 0; ((i - a >= 0) && (a < 5) && (j + b >= 0) && (b < 5)); a++, b++)
				{
					m_foulcheck[a] = m_board_2013182030[i - a][j + b];
				}
				for (int a = 0, b = 0; ((i - a >= 0) && (a < 5) && (j + b >= 0) && (b < 5)); a++, b++)
				{
					if (m_foulcheck[a] == WHITE_2013182030)
					{
						if (lecount < 3)
							lcount++;
						if (lecount == 2 && a == 4)
							lcount--;
						lecount = 0;
					}
					else if (m_foulcheck[a] == EMPTY_2013182030)
					{
						lempty = true;
						lecount++;
					}
					else if (m_foulcheck[a] == BLACK_2013182030)
					{
						if (lecount < 1)
							lempty = false;
						break;
					}
				}
				s = lcount + rcount;
				if (rempty && lempty && s == 2)
				{
					m_Wfoulboard_2013182030[i][j] += F33_2013182030;
				}
				if ((rempty || lempty) && s == 3)
				{
					m_Wfoulboard_2013182030[i][j] += F44_2013182030;
				}
//////////////////////////////////////////////////////////////// 역대각선 //////////////////////////////////////////////////////
			}
		}
}

void CheckWidthLineRiskA_2013182030(int riskcheckstone, int x, int y)
{
	int i;
	int checkstone = riskcheckstone;
	int lcount = 0, rcount = 0;
	int s = 0;
	bool lempty = false, rempty = false;;

	for (i = 0; i < 6; i++)
		m_riskcheck[i] = 0;
	for (i = 0; i < 6; i++)
	{
		m_riskcheck[i] = m_board_2013182030[y][x + i];
	}

	for (i = 0; i < 6; i++)
	{
		lcount = 0;
		rcount = 0;
		lempty = false;
		rempty = false;
		s = 0;
		if (m_riskcheck[i] == EMPTY_2013182030)
		{
			for (int j = i; j < 6; j++)
			{
				if (m_riskcheck[j] == checkstone)
				{
					rcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					rempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					rempty = false;
					break;
				}
			}
			for (int j = i; j > 0; j--)
			{
				if (m_riskcheck[j] == checkstone)
				{
					lcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					lempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					lempty = false;
					break;
				}
			}
			s = lcount + rcount;
			if (s == 5 && riskcheckstone == BLACK_2013182030) m_riskboard_2013182030[y][x + i] -= RISK_5_2013182030 * 5;
			if (s == 4)  m_riskboard_2013182030[y][x + i] += RISK_5_2013182030;
			if (rempty && lempty) s++;
			switch (s)
			{
			//case 0: m_riskboard_2013182030[y][x + i] += RISK_0_2013182030; break;
			case 1: m_riskboard_2013182030[y][x + i] += RISK_1_2013182030; break;
			case 2: m_riskboard_2013182030[y][x + i] += RISK_2_2013182030; break;
			case 3: m_riskboard_2013182030[y][x + i] += RISK_3_2013182030; break;
			case 4: m_riskboard_2013182030[y][x + i] += RISK_4_2013182030; break;
			case 5: m_riskboard_2013182030[y][x + i] += RISK_5_2013182030; break;
			}
		}
	}
}
void CheckWidthLineRiskB_2013182030(int riskcheckstone, int x, int y)
{
	int i;
	int checkstone = riskcheckstone;
	int lcount = 0, rcount = 0;
	int s = 0;
	bool lempty = false, rempty = false;;

	for (i = 0; i < 6; i++)
		m_riskcheck[i] = 0;
	for (i = 0; i < 6; i++)
	{
		m_riskcheck[i] = m_board_2013182030[y][x - i];
	}

	for (i = 0; i < 6; i++)
	{
		lcount = 0;
		rcount = 0;
		lempty = false;
		rempty = false;
		s = 0;
		if (m_riskcheck[i] == EMPTY_2013182030)
		{
			for (int j = i; j < 6; j++)
			{
				if (m_riskcheck[j] == checkstone)
				{
					rcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					rempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					rempty = false;
					break;
				}
			}
			for (int j = i; j > 0; j--)
			{
				if (m_riskcheck[j] == checkstone)
				{
					lcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					lempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					lempty = false;
					break;
				}
			}
			s = lcount + rcount;
			if (s == 5 && riskcheckstone == BLACK_2013182030) m_riskboard_2013182030[y][x - i] -= RISK_5_2013182030 * 10;
			if (s == 4)  m_riskboard_2013182030[y][x - i] += RISK_5_2013182030;
			if (rempty && lempty) s++;
			switch (s)
			{
			//case 0: m_riskboard_2013182030[y][x - i] += RISK_0_2013182030; break;
			case 1: m_riskboard_2013182030[y][x - i] += RISK_1_2013182030; break;
			case 2: m_riskboard_2013182030[y][x - i] += RISK_2_2013182030; break;
			case 3: m_riskboard_2013182030[y][x - i] += RISK_3_2013182030; break;
			case 4: m_riskboard_2013182030[y][x - i] += RISK_4_2013182030; break;
			case 5: m_riskboard_2013182030[y][x - i] += RISK_5_2013182030; break;
			}
		}
	}
}
void CheckHeightLineRiskA_2013182030(int riskcheckstone, int x, int y)
{
	int i;
	int checkstone = riskcheckstone;
	int lcount = 0, rcount = 0;
	int s = 0;
	bool lempty = false, rempty = false;;

	for (i = 0; i < 6; i++)
		m_riskcheck[i] = 0;
	for (i = 0; i < 6; i++)
	{
		m_riskcheck[i] = m_board_2013182030[y + i][x];
	}

	for (i = 0; i < 6; i++)
	{
		lcount = 0;
		rcount = 0;
		lempty = false;
		rempty = false;
		s = 0;
		if (m_riskcheck[i] == EMPTY_2013182030)
		{
			for (int j = i; j < 6; j++)
			{
				if (m_riskcheck[j] == checkstone)
				{
					rcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					rempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					rempty = false;
					break;
				}
			}
			for (int j = i; j > 0; j--)
			{
				if (m_riskcheck[j] == checkstone)
				{
					lcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					lempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					lempty = false;
					break;
				}
			}
			s = lcount + rcount;
			if (s == 5 && riskcheckstone == BLACK_2013182030) m_riskboard_2013182030[y + i][x] -= RISK_5_2013182030 *10;
			if (s == 4)  m_riskboard_2013182030[y + i][x] += RISK_5_2013182030;
			if (rempty && lempty) s++;
			switch (s)
			{
			//case 0: m_riskboard_2013182030[y + i][x] += RISK_0_2013182030; break;
			case 1: m_riskboard_2013182030[y + i][x] += RISK_1_2013182030; break;
			case 2: m_riskboard_2013182030[y + i][x] += RISK_2_2013182030; break;
			case 3: m_riskboard_2013182030[y + i][x] += RISK_3_2013182030; break;
			case 4: m_riskboard_2013182030[y + i][x] += RISK_4_2013182030; break;
			case 5: m_riskboard_2013182030[y + i][x] += RISK_5_2013182030; break;
			}
		}
	}
}
void CheckHeightLineRiskB_2013182030(int riskcheckstone, int x, int y)
{
	int i;
	int checkstone = riskcheckstone;
	int lcount = 0, rcount = 0;
	int s = 0;
	bool lempty = false, rempty = false;;

	for (i = 0; i < 6; i++)
		m_riskcheck[i] = 0;
	for (i = 0; i < 6; i++)
	{
		m_riskcheck[i] = m_board_2013182030[y - i][x];
	}

	for (i = 0; i < 6; i++)
	{
		lcount = 0;
		rcount = 0;
		lempty = false;
		rempty = false;
		s = 0;
		if (m_riskcheck[i] == EMPTY_2013182030)
		{
			for (int j = i; j < 6; j++)
			{
				if (m_riskcheck[j] == checkstone)
				{
					rcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					rempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					rempty = false;
					break;
				}
			}
			for (int j = i; j > 0; j--)
			{
				if (m_riskcheck[j] == checkstone)
				{
					lcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					lempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					lempty = false;
					break;
				}
			}
			s = lcount + rcount;
			if (s == 5 && riskcheckstone == BLACK_2013182030) m_riskboard_2013182030[y - i][x] -= RISK_5_2013182030 * 10;
			if (s == 4)  m_riskboard_2013182030[y - i][x] += RISK_5_2013182030;
			if (rempty && lempty) s++;
			switch (s)
			{
			//case 0: m_riskboard_2013182030[y - i][x] += RISK_0_2013182030; break;
			case 1: m_riskboard_2013182030[y - i][x] += RISK_1_2013182030; break;
			case 2: m_riskboard_2013182030[y - i][x] += RISK_2_2013182030; break;
			case 3: m_riskboard_2013182030[y - i][x] += RISK_3_2013182030; break;
			case 4: m_riskboard_2013182030[y - i][x] += RISK_4_2013182030; break;
			case 5: m_riskboard_2013182030[y - i][x] += RISK_5_2013182030; break;
			}
		}
	}
}
void CheckDiagLineRiskA_2013182030(int riskcheckstone, int x, int y)
{
	int i;
	int checkstone = riskcheckstone;
	int lcount = 0, rcount = 0;
	int s = 0;
	bool lempty = false, rempty = false;;

	for (i = 0; i < 6; i++)
		m_riskcheck[i] = 0;
	for (i = 0; i < 6; i++)
	{
		m_riskcheck[i] = m_board_2013182030[y + i][x + i];
	}

	for (i = 0; i < 6; i++)
	{
		lcount = 0;
		rcount = 0;
		lempty = false;
		rempty = false;
		s = 0;
		if (m_riskcheck[i] == EMPTY_2013182030)
		{
			for (int j = i; j < 6; j++)
			{
				if (m_riskcheck[j] == checkstone)
				{
					rcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					rempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					rempty = false;
					break;
				}
			}
			for (int j = i; j > 0; j--)
			{
				if (m_riskcheck[j] == checkstone)
				{
					lcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					lempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					lempty = false;
					break;
				}
			}
			s = lcount + rcount;
			if (s == 5 && riskcheckstone == BLACK_2013182030) m_riskboard_2013182030[y + i][x + i] -= RISK_5_2013182030 * 10;
			if (s == 4)  m_riskboard_2013182030[y + i][x + i] += RISK_5_2013182030;
			if (rempty && lempty) s++;
			switch (s)
			{
			//case 0: m_riskboard_2013182030[y + i][x + i] += RISK_0_2013182030; break;
			case 1: m_riskboard_2013182030[y + i][x + i] += RISK_1_2013182030; break;
			case 2: m_riskboard_2013182030[y + i][x + i] += RISK_2_2013182030; break;
			case 3: m_riskboard_2013182030[y + i][x + i] += RISK_3_2013182030; break;
			case 4: m_riskboard_2013182030[y + i][x + i] += RISK_4_2013182030; break;
			case 5: m_riskboard_2013182030[y + i][x + i] += RISK_5_2013182030; break;
			}
		}
	}
}
void CheckDiagLineRiskB_2013182030(int riskcheckstone, int x, int y)
{
	int i;
	int checkstone = riskcheckstone;
	int lcount = 0, rcount = 0;
	int s = 0;
	bool lempty = false, rempty = false;;

	for (i = 0; i < 6; i++)
		m_riskcheck[i] = 0;
	for (i = 0; i < 6; i++)
	{
		m_riskcheck[i] = m_board_2013182030[y - i][x - i];
	}

	for (i = 0; i < 6; i++)
	{
		lcount = 0;
		rcount = 0;
		lempty = false;
		rempty = false;
		s = 0;
		if (m_riskcheck[i] == EMPTY_2013182030)
		{
			for (int j = i; j < 6; j++)
			{
				if (m_riskcheck[j] == checkstone)
				{
					rcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					rempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					rempty = false;
					break;
				}
			}
			for (int j = i; j > 0; j--)
			{
				if (m_riskcheck[j] == checkstone)
				{
					lcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					lempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					lempty = false;
					break;
				}
			}
			s = lcount + rcount;
			if (s == 5 && riskcheckstone == BLACK_2013182030) m_riskboard_2013182030[y - i][x - i] -= RISK_5_2013182030 * 10;
			if (s == 4)  m_riskboard_2013182030[y - i][x - i] += RISK_5_2013182030;
			if (rempty && lempty) s++;
			switch (s)
			{
			//case 0: m_riskboard_2013182030[y - i][x - i] += RISK_0_2013182030; break;
			case 1: m_riskboard_2013182030[y - i][x - i] += RISK_1_2013182030; break;
			case 2: m_riskboard_2013182030[y - i][x - i] += RISK_2_2013182030; break;
			case 3: m_riskboard_2013182030[y - i][x - i] += RISK_3_2013182030; break;
			case 4: m_riskboard_2013182030[y - i][x - i] += RISK_4_2013182030; break;
			case 5: m_riskboard_2013182030[y - i][x - i] += RISK_5_2013182030; break;
			}
		}
	}

}
void CheckRevDiagLineRiskA_2013182030(int riskcheckstone, int x, int y)
{
	int i;
	int checkstone = riskcheckstone;
	int lcount = 0, rcount = 0;
	int s = 0;
	bool lempty = false, rempty = false;;

	for (i = 0; i < 6; i++)
		m_riskcheck[i] = 0;
	for (i = 0; i < 6; i++)
	{
		m_riskcheck[i] = m_board_2013182030[y + i][x - i];
	}

	for (i = 0; i < 6; i++)
	{
		lcount = 0;
		rcount = 0;
		lempty = false;
		rempty = false;
		s = 0;
		if (m_riskcheck[i] == EMPTY_2013182030)
		{
			for (int j = i; j < 6; j++)
			{
				if (m_riskcheck[j] == checkstone)
				{
					rcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					rempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					rempty = false;
					break;
				}
			}
			for (int j = i; j > 0; j--)
			{
				if (m_riskcheck[j] == checkstone)
				{
					lcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					lempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					lempty = false;
					break;
				}
			}
			s = lcount + rcount;
			if (s == 5 && riskcheckstone == BLACK_2013182030) m_riskboard_2013182030[y + i][x - i] -= RISK_5_2013182030 * 10;
			if (s == 4)  m_riskboard_2013182030[y + i][x - i] += RISK_5_2013182030;
			if (rempty && lempty) s++;
			switch (s)
			{
			//case 0: m_riskboard_2013182030[y + i][x - i] += RISK_0_2013182030; break;
			case 1: m_riskboard_2013182030[y + i][x - i] += RISK_1_2013182030; break;
			case 2: m_riskboard_2013182030[y + i][x - i] += RISK_2_2013182030; break;
			case 3: m_riskboard_2013182030[y + i][x - i] += RISK_3_2013182030; break;
			case 4: m_riskboard_2013182030[y + i][x - i] += RISK_4_2013182030; break;
			case 5: m_riskboard_2013182030[y + i][x - i] += RISK_5_2013182030; break;
			}
		}
	}
}
void CheckRevDiagLineRiskB_2013182030(int riskcheckstone, int x, int y)
{
	int i;
	int checkstone = riskcheckstone;
	int lcount = 0, rcount = 0;
	int s = 0;
	bool lempty = false, rempty = false;;

	for (i = 0; i < 6; i++)
		m_riskcheck[i] = 0;
	for (i = 0; i < 6; i++)
	{
		m_riskcheck[i] = m_board_2013182030[y - i][x + i];
	}

	for (i = 0; i < 6; i++)
	{
		lcount = 0;
		rcount = 0;
		lempty = false;
		rempty = false;
		s = 0;
		if (m_riskcheck[i] == EMPTY_2013182030)
		{
			for (int j = i; j < 6; j++)
			{
				if (m_riskcheck[j] == checkstone)
				{
					rcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					rempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					rempty = false;
					break;
				}
			}
			for (int j = i; j > 0; j--)
			{
				if (m_riskcheck[j] == checkstone)
				{
					lcount++;
				}
				else if (m_riskcheck[j] == EMPTY_2013182030)
				{
					lempty = true;
				}
				else if (m_riskcheck[j] != checkstone)
				{
					lempty = false;
					break;
				}
			}
			s = lcount + rcount;
			if (s == 5 && riskcheckstone == BLACK_2013182030) m_riskboard_2013182030[y - i][x + i] -= RISK_5_2013182030 * 10;
			if (s == 4)  m_riskboard_2013182030[y - i][x + i] += RISK_5_2013182030;
			if (rempty && lempty) s++;
			switch (s)
			{
			//case 0: m_riskboard_2013182030[y - i][x + i] += RISK_0_2013182030; break;
			case 1: m_riskboard_2013182030[y - i][x + i] += RISK_1_2013182030; break;
			case 2: m_riskboard_2013182030[y - i][x + i] += RISK_2_2013182030; break;
			case 3: m_riskboard_2013182030[y - i][x + i] += RISK_3_2013182030; break;
			case 4: m_riskboard_2013182030[y - i][x + i] += RISK_4_2013182030; break;
			case 5: m_riskboard_2013182030[y - i][x + i] += RISK_5_2013182030; break;
			}
		}
	}
}

void BlackAttack_2013182030이상기(int * x, int * y)
{
	int xPos = 0, yPos = 0;
	int Bmax = 0, Wmax = 0;
	Bturn_2013182030 = true;
	Wturn_2013182030 = false;
	if (!set_2013182030) {
		for (int i = 0; i < BOARD_LINE_2013182030; i++)
			for (int j = 0; j < BOARD_LINE_2013182030; j++)
				if (!start_2013182030)
					m_board_2013182030[i][j] = 0;
		set_2013182030 = true;
	}
	Bmax = CheckRisk_2013182030(BLACK_2013182030, &xPos, &yPos);
	Wmax = CheckRisk_2013182030(WHITE_2013182030, &xPos, &yPos);

	if (Bmax > RISK_5_2013182030 * 2 || Wmax < RISK_4_2013182030 * 2)
		CheckRisk_2013182030(BLACK_2013182030, &xPos, &yPos);
	if (Wmax > RISK_5_2013182030 * 2)
		CheckRisk_2013182030(WHITE_2013182030, &xPos, &yPos);

	m_board_2013182030[yPos][xPos] = BLACK_2013182030;
	*x = xPos;
	*y = yPos;
	
}
void BlackDefence_2013182030이상기(int x, int y)
{
	int xpos, ypos;
	m_board_2013182030[y][x] = WHITE_2013182030;
	CheckRisk_2013182030(WHITE_2013182030, &xpos, &ypos);
	printf("\n");
	for (int i = 0; i < BOARD_LINE_2013182030; i++) {
		printf("                                             ");
		for (int j = 0; j < BOARD_LINE_2013182030; j++)
		{
			if (Debug_2013182030 == 1)
			{
				printf("%4d ", m_riskboard_2013182030[i][j]);
			}
			if (Debug_2013182030 == 2)
			{
				printf("%2d ", m_Bfoulboard_2013182030[i][j]);
			}
		}
		printf("\n");
	}
}
void WhiteAttack_2013182030이상기(int * x, int * y)
{
	int xPos = 0, yPos = 0;
	int Bmax = 0, Wmax = 0;
	Bturn_2013182030 = false;
	Wturn_2013182030 = true;
	Wmax = CheckRisk_2013182030(WHITE_2013182030, &xPos, &yPos);
	Bmax = CheckRisk_2013182030(BLACK_2013182030, &xPos, &yPos);
	if (start_2013182030) {
		if (Wmax > RISK_5_2013182030 || Bmax < RISK_4_2013182030 * 2)
			CheckRisk_2013182030(WHITE_2013182030, &xPos, &yPos);
		if (Bmax > RISK_5_2013182030 * 2)
			CheckRisk_2013182030(BLACK_2013182030, &xPos, &yPos);
	}
	else
	{
		CheckRisk_2013182030(BLACK_2013182030, &xPos, &yPos);
		start_2013182030 = true;
	}
	m_board_2013182030[yPos][xPos] = WHITE_2013182030;
	*x = xPos;
	*y = yPos;
}
void WhiteDefence_2013182030이상기(int x, int y)
{
	int xpos, ypos;
	m_board_2013182030[y][x] = BLACK_2013182030;
	CheckRisk_2013182030(BLACK_2013182030, &xpos, &ypos);
	printf("\n");
	for (int i = 0; i < BOARD_LINE_2013182030; i++) {
		printf("                                             ");
		for (int j = 0; j < BOARD_LINE_2013182030; j++)
		{
			if (Debug_2013182030 == 1)
			{
				printf("%4d ", m_riskboard_2013182030[i][j]);
			}
			if (Debug_2013182030 == 2) {
				printf("%2d ", m_Bfoulboard_2013182030[i][j]);
			}
		}
		printf("\n");
	}
}