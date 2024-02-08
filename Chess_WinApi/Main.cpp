#include <Windows.h>
#include <stdlib.h>
#include <wchar.h>
#include <windowsx.h>
#include "Main.h"

#pragma comment(lib, "Msimg32.lib")

int board[8][8] =
{
	21, 31, 41, 55, 66, 42, 32, 22,
	11, 12, 13, 14, 15, 16, 17, 18,
	0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,
	-11,-12,-13,-14,-15,-16,-17,-18,
	-21,-31,-41,-55,-66,-42,-32,-22
};

bool justForTest = true;

bool clicked = false;

int click{};															/*click count*/

int isMoving{};															/*piece in move*/

int move = 0;															/*0 -> white is moving; 1 -> black is moving*/

int size = 100;															/*size of a chess piece*/

int checkWhite = 0, checkBlack = 0;										/*checkmate*/

int x{}, y{};															/*position on board*/

int noMovePiece{};														/*chosen piece*/

int rightWhiteRookM = 0, leftWhiteRookM = 0, whiteKingFirstMove = 0;	/*white king swap*/

int rightBlackRookM = 0, leftBlackRookM = 0, blackKingFirstMove = 0;	/*black king swap*/

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

POINT pos, oldPoz, whiteKing, blackKing;

HDC hdc, bufDC;				// handler display context
PAINTSTRUCT ps;
HBITMAP bufbmp;

HBITMAP boardBmp;
HDC boardDC;
RECT boardRect;

// BLACK

HBITMAP blackRookBmp, blackKnightBmp, blackBishopBmp, blackQueenBmp, blackKingBmp, blackPawnBmp;
HDC blackRookDC, blackKnightDC, blackBishopDC, blackQueenDC, blackKingDC, blackPawnDC;
RECT blackRookRect1, blackKnightRect1, blackBishopRect1, blackQueenRect, blackKingRect, blackBishopRect2, blackKnightRect2, blackRookRect2;
RECT blackPawnRect1, blackPawnRect2, blackPawnRect3, blackPawnRect4, blackPawnRect5, blackPawnRect6, blackPawnRect7, blackPawnRect8;

// WHITE

HBITMAP whiteRookBmp, whiteKnightBmp, whiteBishopBmp, whiteQueenBmp, whiteKingBmp, whitePawnBmp;
HDC whiteRookDC, whiteKnightDC, whiteBishopDC, whiteQueenDC, whiteKingDC, whitePawnDC;
RECT whiteRookRect1, whiteKnightRect1, whiteBishopRect1, whiteQueenRect, whiteKingRect, whiteBishopRect2, whiteKnightRect2, whiteRookRect2;
RECT whitePawnRect1, whitePawnRect2, whitePawnRect3, whitePawnRect4, whitePawnRect5, whitePawnRect6, whitePawnRect7, whitePawnRect8;

HBITMAP movePieceBmp;
HDC movePieceDC;
RECT movePiece;
RECT rect;

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow)
{
	WNDCLASSW wc{};

	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return EXIT_FAILURE;

	CreateWindow(wc.lpszClassName, L"Chess", WS_VISIBLE | WS_SYSMENU,
		350, 20, 816, 839, NULL, NULL, wc.hInstance, NULL);

	MSG msg{};

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
	{
		pos.x = GET_X_LPARAM(lp);
		pos.y = GET_Y_LPARAM(lp);

		x = pos.x / size;
		y = pos.y / size;

		break;
	}

	case WM_LBUTTONDOWN:
	{
		click++;

		if (!justForTest)									// click test (remove ! to test)
		{
			wchar_t text[20];
			//wsprintf(text, L"(%i, %i)", x, y);			// cell coord
			wsprintf(text, L"(%i)", board[y][x]);			// cell num
			//wsprintf(text, L"%i", click);
			MessageBox(hWnd, text, L"Info", MB_OK);
			//MessageBeep(MB_OK);
		}

		if (click % 2 == 1)
		{
			clicked = true;

			if (board[y][x] != 0)
			{
				// BLACK

				if (move == 1)
				{
					if (board[y][x] == BLACK_PAWN1)
					{
						noMovePiece = BLACK_PAWN1;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_PAWN2)
					{
						noMovePiece = BLACK_PAWN2;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_PAWN3)
					{
						noMovePiece = BLACK_PAWN3;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_PAWN4)
					{
						noMovePiece = BLACK_PAWN4;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_PAWN5)
					{
						noMovePiece = BLACK_PAWN5;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_PAWN6)
					{
						noMovePiece = BLACK_PAWN6;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_PAWN7)
					{
						noMovePiece = BLACK_PAWN7;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_PAWN8)
					{
						noMovePiece = BLACK_PAWN8;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_ROOK1)
					{
						noMovePiece = BLACK_ROOK1;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_ROOK2)
					{
						noMovePiece = BLACK_ROOK2;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_KNIGHT1)
					{
						noMovePiece = BLACK_KNIGHT1;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_KNIGHT2)
					{
						noMovePiece = BLACK_KNIGHT2;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_BISHOP1)
					{
						noMovePiece = BLACK_BISHOP1;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_BISHOP2)
					{
						noMovePiece = BLACK_BISHOP2;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_QUEEN)
					{
						noMovePiece = BLACK_QUEEN;
						board[y][x] = 0;
					}

					if (board[y][x] == BLACK_KING)
					{
						noMovePiece = BLACK_KING;
						board[y][x] = 0;
					}
				}

				// WHITE

				if (move == 0)
				{
					if (board[y][x] == WHITE_PAWN1)
					{
						noMovePiece = WHITE_PAWN1;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_PAWN2)
					{
						noMovePiece = WHITE_PAWN2;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_PAWN3)
					{
						noMovePiece = WHITE_PAWN3;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_PAWN4)
					{
						noMovePiece = WHITE_PAWN4;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_PAWN5)
					{
						noMovePiece = WHITE_PAWN5;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_PAWN6)
					{
						noMovePiece = WHITE_PAWN6;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_PAWN7)
					{
						noMovePiece = WHITE_PAWN7;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_PAWN8)
					{
						noMovePiece = WHITE_PAWN8;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_ROOK1)
					{
						noMovePiece = WHITE_ROOK1;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_ROOK2)
					{
						noMovePiece = WHITE_ROOK2;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_KNIGHT1)
					{
						noMovePiece = WHITE_KNIGHT1;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_KNIGHT2)
					{
						noMovePiece = WHITE_KNIGHT2;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_BISHOP1)
					{
						noMovePiece = WHITE_BISHOP1;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_BISHOP2)
					{
						noMovePiece = WHITE_BISHOP2;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_QUEEN)
					{
						noMovePiece = WHITE_QUEEN;
						board[y][x] = 0;
					}

					if (board[y][x] == WHITE_KING)
					{
						noMovePiece = WHITE_KING;
						board[y][x] = 0;
					}
				}

				if (board[y][x] == 0)
				{
					isMoving = 1;
					oldPoz.x = x;
					oldPoz.y = y;
				}
			}

		}

		if (click % 2 == 0)
		{
			clicked = false;
			int ok = 2;

			if (isMoving == 1)
			{
				// BLACK

				if (noMovePiece == BLACK_PAWN1 || noMovePiece == BLACK_PAWN2 || noMovePiece == BLACK_PAWN3 || noMovePiece == BLACK_PAWN4 ||
					noMovePiece == BLACK_PAWN5 || noMovePiece == BLACK_PAWN6 || noMovePiece == BLACK_PAWN7 || noMovePiece == BLACK_PAWN8 )
				{
					ok = PawnB(oldPoz.x, oldPoz.y, x, y);
				}

				if (noMovePiece == BLACK_ROOK1 || noMovePiece == BLACK_ROOK2)
				{
					ok = RookB(oldPoz.x, oldPoz.y, x, y);

					if (ok == 1 && rightBlackRookM == 0 && oldPoz.y == 0 && oldPoz.x == 7)
						rightBlackRookM = 1;
					if (ok == 1 && leftBlackRookM == 0 && oldPoz.y == 0 && oldPoz.x == 0)
						leftBlackRookM = 1;
				}

				if (noMovePiece == BLACK_KNIGHT1 || noMovePiece == BLACK_KNIGHT2)
				{
					ok = KnightB(oldPoz.x, oldPoz.y, x, y);
				}

				if (noMovePiece == BLACK_BISHOP1 || noMovePiece == BLACK_BISHOP2)
				{
					ok = BishopB(oldPoz.x, oldPoz.y, x, y);
				}

				if (noMovePiece == BLACK_QUEEN)
				{
					ok = QueenB(oldPoz.x, oldPoz.y, x, y);
				}

				if (noMovePiece == BLACK_KING)
				{
					ok = BlackKing(oldPoz.x, oldPoz.y, x, y);
					if (ok == 1 && blackKingFirstMove == 0)
						blackKingFirstMove = 1;
				}

				// WHITE

				if (noMovePiece == WHITE_PAWN1 || noMovePiece == WHITE_PAWN2 || noMovePiece == WHITE_PAWN3 || noMovePiece == WHITE_PAWN4 ||
					noMovePiece == WHITE_PAWN5 || noMovePiece == WHITE_PAWN6 || noMovePiece == WHITE_PAWN7 || noMovePiece == WHITE_PAWN8)
				{
					ok = PawnW(oldPoz.x, oldPoz.y, x, y);
				}

				if (noMovePiece == WHITE_ROOK1 || noMovePiece == WHITE_ROOK2)
				{
					ok = RookW(oldPoz.x, oldPoz.y, x, y);

					if (ok == 1 && leftWhiteRookM == 0 && oldPoz.y == 7 && oldPoz.x == 0)
						leftWhiteRookM = 1;
					if (ok == 1 && rightWhiteRookM == 0 && oldPoz.y == 7 && oldPoz.x == 7)
						rightWhiteRookM = 1;
				}

				if (noMovePiece == WHITE_KNIGHT1 || noMovePiece == WHITE_KNIGHT2)
				{
					ok = KnightW(oldPoz.x, oldPoz.y, x, y);
				}

				if (noMovePiece == WHITE_BISHOP1 || noMovePiece == WHITE_BISHOP2)
				{
					ok = BishopW(oldPoz.x, oldPoz.y, x, y);
				}

				if (noMovePiece == WHITE_QUEEN)
				{
					ok = QueenW(oldPoz.x, oldPoz.y, x, y);
				}

				if (noMovePiece == WHITE_KING)
				{
					ok = WhiteKing(oldPoz.x, oldPoz.y, x, y);
					if (ok == 1 && whiteKingFirstMove == 0)
						whiteKingFirstMove = 1;
				}
			}

			if (ok == 1)
			{
				loadPlayBoard(NULL);	
				
				int nr = board[y][x];
				board[y][x] = noMovePiece;

				if (move == 0)
				{
					if (checkWhite == 1)
					{
						posWhiteKing();
						int s = WhiteKingCheck(whiteKing.x, whiteKing.y);
						if (s == 0)
						{
							board[oldPoz.y][oldPoz.x] = noMovePiece;
							board[y][x] = nr;
						}
						else
						{
							checkWhite = 0;
							posBlackKing();
							int check = BlackKingCheck(blackKing.x, blackKing.y);

							if (check == 0)
								checkBlack = 1;

							move = 1;
						}

					}													
					else
					{
						posWhiteKing();
						int sa = WhiteKingCheck(whiteKing.x, whiteKing.y);
						if (sa == 0)
						{
							board[oldPoz.y][oldPoz.x] = noMovePiece;
							board[y][x] = nr;
						}
						else
						{
							posBlackKing();
							int check = BlackKingCheck(blackKing.x, blackKing.y);
							if (check == 0)
								checkBlack = 1;

							move = 1;
						}
					}
				}
				else
				{
					if (checkBlack == 1)
					{
						posBlackKing();
						int s = BlackKingCheck(blackKing.x, blackKing.y);
						if (s == 0)
						{
							board[oldPoz.y][oldPoz.x] = noMovePiece;
							board[y][x] = nr;
						}
						else
						{
							checkBlack = 0;
							posWhiteKing();
							int check = WhiteKingCheck(whiteKing.x, whiteKing.y);
							if (check == 0)
								checkWhite = 1;
							move = 0;

						}

					}											
					else
					{
						posBlackKing();
						int sa = BlackKingCheck(blackKing.x, blackKing.y);
						if (sa == 0)
						{
							board[oldPoz.y][oldPoz.x] = noMovePiece;
							board[y][x] = nr;
						}
						else
						{
							posWhiteKing();
							int check = WhiteKingCheck(whiteKing.x, whiteKing.y);
							if (check == 0)
								checkWhite = 1;
							move = 0;
						}
					}
				}

				loadPlayBoard(100);		
			}
			else if (ok == 0)
			{
				loadPlayBoard(NULL);	// clear playboard

				board[oldPoz.y][ oldPoz.x] = noMovePiece;

				loadPlayBoard(100);		// re-draw playboard
			}

			isMoving = 0;

			InvalidateRect(hWnd, NULL, 0);
		}

		break;
	}

	case WM_KEYDOWN:
	{
		if (wp == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	}

	case WM_CREATE:
	{
		loadImages();

		hdc = GetDC(hWnd);
		boardDC = CreateCompatibleDC(hdc);

		SelectObject(boardDC, boardBmp);
		GetClientRect(hWnd, &boardRect);

		bufDC = CreateCompatibleDC(hdc);
		bufbmp = CreateCompatibleBitmap(hdc, boardRect.right, boardRect.bottom);
		SelectObject(bufDC, bufbmp);

		blackRookDC = CreateCompatibleDC(hdc);
		blackKnightDC = CreateCompatibleDC(hdc);
		blackBishopDC = CreateCompatibleDC(hdc);
		blackQueenDC = CreateCompatibleDC(hdc);
		blackKingDC = CreateCompatibleDC(hdc);
		blackPawnDC = CreateCompatibleDC(hdc);

		SelectObject(blackRookDC, blackRookBmp);
		SelectObject(blackKnightDC, blackKnightBmp);
		SelectObject(blackBishopDC, blackBishopBmp);
		SelectObject(blackQueenDC, blackQueenBmp);
		SelectObject(blackKingDC, blackKingBmp);
		SelectObject(blackPawnDC, blackPawnBmp);

		whiteRookDC = CreateCompatibleDC(hdc);
		whiteKnightDC = CreateCompatibleDC(hdc);
		whiteBishopDC = CreateCompatibleDC(hdc);
		whiteQueenDC = CreateCompatibleDC(hdc);
		whiteKingDC = CreateCompatibleDC(hdc);
		whitePawnDC = CreateCompatibleDC(hdc);

		SelectObject(whiteRookDC, whiteRookBmp);
		SelectObject(whiteKnightDC, whiteKnightBmp);
		SelectObject(whiteBishopDC, whiteBishopBmp);
		SelectObject(whiteQueenDC, whiteQueenBmp);
		SelectObject(whiteKingDC, whiteKingBmp);
		SelectObject(whitePawnDC, whitePawnBmp);

		loadPlayBoard(100);

		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}

	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);	//BeginPaint

		TransparentBlt(bufDC, boardRect.left, boardRect.top, boardRect.right, boardRect.bottom, boardDC, 0, 0, 800, 800, SRCCOPY);

		// BLACK0

		TransparentBlt(bufDC, blackRookRect1.left, blackRookRect1.top, blackRookRect1.right, blackRookRect1.bottom, blackRookDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackKnightRect1.left, blackKnightRect1.top, blackKnightRect1.right, blackKnightRect1.bottom, blackKnightDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackBishopRect1.left, blackBishopRect1.top, blackBishopRect1.right, blackBishopRect1.bottom, blackBishopDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackQueenRect.left, blackQueenRect.top, blackQueenRect.right, blackQueenRect.bottom, blackQueenDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackKingRect.left, blackKingRect.top, blackKingRect.right, blackKingRect.bottom, blackKingDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackBishopRect2.left, blackBishopRect2.top, blackBishopRect2.right, blackBishopRect2.bottom, blackBishopDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackKnightRect2.left, blackKnightRect2.top, blackKnightRect2.right, blackKnightRect2.bottom, blackKnightDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackRookRect2.left, blackRookRect2.top, blackRookRect2.right, blackRookRect2.bottom, blackRookDC, 0, 0, size, size, RGB(150, 150, 150));

		TransparentBlt(bufDC, blackPawnRect1.left, blackPawnRect1.top, blackPawnRect1.right, blackPawnRect1.bottom, blackPawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackPawnRect2.left, blackPawnRect2.top, blackPawnRect2.right, blackPawnRect2.bottom, blackPawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackPawnRect3.left, blackPawnRect3.top, blackPawnRect3.right, blackPawnRect3.bottom, blackPawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackPawnRect4.left, blackPawnRect4.top, blackPawnRect4.right, blackPawnRect4.bottom, blackPawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackPawnRect5.left, blackPawnRect5.top, blackPawnRect5.right, blackPawnRect5.bottom, blackPawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackPawnRect6.left, blackPawnRect6.top, blackPawnRect6.right, blackPawnRect6.bottom, blackPawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackPawnRect7.left, blackPawnRect7.top, blackPawnRect7.right, blackPawnRect7.bottom, blackPawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, blackPawnRect8.left, blackPawnRect8.top, blackPawnRect8.right, blackPawnRect8.bottom, blackPawnDC, 0, 0, size, size, RGB(150, 150, 150));

		// WHITE

		TransparentBlt(bufDC, whiteRookRect1.left, whiteRookRect1.top, whiteRookRect1.right, whiteRookRect1.bottom, whiteRookDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whiteKnightRect1.left, whiteKnightRect1.top, whiteKnightRect1.right, whiteKnightRect1.bottom, whiteKnightDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whiteBishopRect1.left, whiteBishopRect1.top, whiteBishopRect1.right, whiteBishopRect1.bottom, whiteBishopDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whiteQueenRect.left, whiteQueenRect.top, whiteQueenRect.right, whiteQueenRect.bottom, whiteQueenDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whiteKingRect.left, whiteKingRect.top, whiteKingRect.right, whiteKingRect.bottom, whiteKingDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whiteBishopRect2.left, whiteBishopRect2.top, whiteBishopRect2.right, whiteBishopRect2.bottom, whiteBishopDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whiteKnightRect2.left, whiteKnightRect2.top, whiteKnightRect2.right, whiteKnightRect2.bottom, whiteKnightDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whiteRookRect2.left, whiteRookRect2.top, whiteRookRect2.right, whiteRookRect2.bottom, whiteRookDC, 0, 0, size, size, RGB(150, 150, 150));

		TransparentBlt(bufDC, whitePawnRect1.left, whitePawnRect1.top, whitePawnRect1.right, whitePawnRect1.bottom, whitePawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whitePawnRect2.left, whitePawnRect2.top, whitePawnRect2.right, whitePawnRect2.bottom, whitePawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whitePawnRect3.left, whitePawnRect3.top, whitePawnRect3.right, whitePawnRect3.bottom, whitePawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whitePawnRect4.left, whitePawnRect4.top, whitePawnRect4.right, whitePawnRect4.bottom, whitePawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whitePawnRect5.left, whitePawnRect5.top, whitePawnRect5.right, whitePawnRect5.bottom, whitePawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whitePawnRect6.left, whitePawnRect6.top, whitePawnRect6.right, whitePawnRect6.bottom, whitePawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whitePawnRect7.left, whitePawnRect7.top, whitePawnRect7.right, whitePawnRect7.bottom, whitePawnDC, 0, 0, size, size, RGB(150, 150, 150));
		TransparentBlt(bufDC, whitePawnRect8.left, whitePawnRect8.top, whitePawnRect8.right, whitePawnRect8.bottom, whitePawnDC, 0, 0, size, size, RGB(150, 150, 150));

		BitBlt(hdc, boardRect.left, boardRect.top, boardRect.right, boardRect.bottom, bufDC, boardRect.left, boardRect.top, SRCCOPY);

		EndPaint(hWnd, &ps);			// EndPaint
		break;
	}
	}

	return DefWindowProcW(hWnd, msg, wp, lp);
}

void loadImages()
{
	boardBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/Board.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	blackRookBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/BlackRook.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	blackKnightBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/BlackKnight.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	blackBishopBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/BlackBishop.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	blackQueenBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/BlackQueen.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	blackKingBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/BlackKing.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	blackPawnBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/BlackPawn.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	whiteRookBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/WhiteRook.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	whiteKnightBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/WhiteKnight.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	whiteBishopBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/WhiteBishop.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	whiteQueenBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/WhiteQueen.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	whiteKingBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/WhiteKing.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	whitePawnBmp = (HBITMAP)LoadImageA(NULL, "Images24bit/WhitePawn.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void loadPlayBoard(int size)
{
	for (int i = 0; i <= LENGTH; i++)
	{
		for (int j = 0; j <= LENGTH; j++)
		{
			int cell = board[i][j];

			if (cell != 0)
			{
				if (cell == BLACK_PAWN1)
					SetRect(&blackPawnRect1, j * size, i * size, size, size);
				if (cell == BLACK_PAWN2)
					SetRect(&blackPawnRect2, j * size, i * size, size, size);
				if (cell == BLACK_PAWN3)
					SetRect(&blackPawnRect3, j * size, i * size, size, size);
				if (cell == BLACK_PAWN4)
					SetRect(&blackPawnRect4, j * size, i * size, size, size);
				if (cell == BLACK_PAWN5)
					SetRect(&blackPawnRect5, j * size, i * size, size, size);
				if (cell == BLACK_PAWN6)
					SetRect(&blackPawnRect6, j * size, i * size, size, size);
				if (cell == BLACK_PAWN7)
					SetRect(&blackPawnRect7, j * size, i * size, size, size);
				if (cell == BLACK_PAWN8)
					SetRect(&blackPawnRect8, j * size, i * size, size, size);

				if (cell == BLACK_ROOK1)
					SetRect(&blackRookRect1, j * size, i * size, size, size);
				if (cell == BLACK_ROOK2)
					SetRect(&blackRookRect2, j * size, i * size, size, size);
				if (cell == BLACK_KNIGHT1)
					SetRect(&blackKnightRect1, j * size, i * size, size, size);
				if (cell == BLACK_KNIGHT2)
					SetRect(&blackKnightRect2, j * size, i * size, size, size);
				if (cell == BLACK_BISHOP1)
					SetRect(&blackBishopRect1, j * size, i * size, size, size);
				if (cell == BLACK_BISHOP2)
					SetRect(&blackBishopRect2, j * size, i * size, size, size);
				if (cell == BLACK_QUEEN)
					SetRect(&blackQueenRect, j * size, i * size, size, size);
				if (cell == BLACK_KING)
					SetRect(&blackKingRect, j * size, i * size, size, size);

				if (cell == WHITE_PAWN1)
					SetRect(&whitePawnRect1, j * size, i * size, size, size);
				if (cell == WHITE_PAWN2)
					SetRect(&whitePawnRect2, j * size, i * size, size, size);
				if (cell == WHITE_PAWN3)
					SetRect(&whitePawnRect3, j * size, i * size, size, size);
				if (cell == WHITE_PAWN4)
					SetRect(&whitePawnRect4, j * size, i * size, size, size);
				if (cell == WHITE_PAWN5)
					SetRect(&whitePawnRect5, j * size, i * size, size, size);
				if (cell == WHITE_PAWN6)
					SetRect(&whitePawnRect6, j * size, i * size, size, size);
				if (cell == WHITE_PAWN7)
					SetRect(&whitePawnRect7, j * size, i * size, size, size);
				if (cell == WHITE_PAWN8)
					SetRect(&whitePawnRect8, j * size, i * size, size, size);

				if (cell == WHITE_ROOK1)
					SetRect(&whiteRookRect1, j * size, i * size, size, size);
				if (cell == WHITE_ROOK2)
					SetRect(&whiteRookRect2, j * size, i * size, size, size);
				if (cell == WHITE_KNIGHT1)
					SetRect(&whiteKnightRect1, j * size, i * size, size, size);
				if (cell == WHITE_KNIGHT2)
					SetRect(&whiteKnightRect2, j * size, i * size, size, size);
				if (cell == WHITE_BISHOP1)
					SetRect(&whiteBishopRect1, j * size, i * size, size, size);
				if (cell == WHITE_BISHOP2)
					SetRect(&whiteBishopRect2, j * size, i * size, size, size);
				if (cell == WHITE_QUEEN)
					SetRect(&whiteQueenRect, j * size, i * size, size, size);
				if (cell == WHITE_KING)
					SetRect(&whiteKingRect, j * size, i * size, size, size);
			}
		}
	}

}

int PawnW(int ox, int oy, int nx, int ny) // old x,y; new x,y
{
	if (oldPoz.y == 6)
	{
		if ((ny == oy - 1 && nx == ox && board[oy - 1][ox] == 0) || (ny == oy - 2 && nx == ox && board[oy - 1][ox] == 0 && board[oy - 2][ox] == 0))
			return 1;		
	}
	else
		if (ny == oy - 1 && nx == ox && board[oy - 1][ox] == 0)
			return 1;		

	if (board[oy - 1][ox - 1] > 0)
		if (ny == oy - 1 && nx == ox - 1)
			return 1;		

	if (board[oy - 1][ox + 1] > 0)
		if (ny == oy - 1 && nx == ox + 1)
			return 1;
	return 0;
}

int PawnB(int ox, int oy, int nx, int ny) // old x,y; new x,y
{
	if (oldPoz.y == 1)
	{
		if ((ny == oy + 1 && nx == ox && board[oy + 1][ox] == 0) || (ny == oy + 2 && nx == ox && board[oy + 1][ox] == 0 && board[oy + 2][ox] == 0))
			return 1;		
	}
	else
		if (ny == oy + 1 && nx == ox && board[oy + 1][ox] == 0)
			return 1;	

	if (board[oy + 1][ox - 1] < 0)
		if (ny == oy + 1 && nx == ox - 1)
			return 1;		

	if (board[oy + 1][ox + 1] < 0)
		if (ny == oy + 1 && nx == ox + 1)
			return 1;
	return 0;
}

int RookW(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--)			// to left
	{
		if (board[oy][i] >= 0 && (nx == i && ny == oy))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy - 1; i >= 0; i--)			// up
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	for (int i = ox + 1; i <= LENGTH; i++)		// to right
	{
		if (board[oy][i] >= 0 && (ny == oy && nx == i))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy + 1; i <= LENGTH; i++)		// down
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	return 0;
}

int RookB(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--)			// to left
	{
		if (board[oy][i] <= 0 && (nx == i && ny == oy))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy - 1; i >= 0; i--)			// up
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	for (int i = ox + 1; i <= LENGTH; i++)		// to right
	{
		if (board[oy][i] <= 0 && (ny == oy && nx == i))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy + 1; i <= LENGTH; i++)		// down
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	return 0;
}

int BishopW(int ox, int oy, int nx, int ny)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)			// left up
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] < 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)			// right up
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] < 0)
				break;
		j++;
	}

	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)		// left down
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] < 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)		// right down
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] < 0)
				break;
		j++;
	}

	return 0;
}

int BishopB(int ox, int oy, int nx, int ny)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)			// left up
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)			// right up
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)		// left down
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)		// right down
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	return 0;
}

int QueenW(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--)			// to left
	{
		if (board[oy][i] >= 0 && (nx == i && ny == oy))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy - 1; i >= 0; i--)			// up
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	for (int i = ox + 1; i <= LENGTH; i++)		// to right
	{
		if (board[oy][i] >= 0 && (ny == oy && nx == i))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}


	for (int i = oy + 1; i <= LENGTH; i++)		// down
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)			// left up
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)			// right up
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)		// left down
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)		// right down
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	return 0;
}

int QueenB(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--)			// to left
	{
		if (board[oy][i] <= 0 && (nx == i && ny == oy))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy - 1; i >= 0; i--)			// up
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	for (int i = ox + 1; i <= LENGTH; i++)		// to right
	{
		if (board[oy][i] <= 0 && (ny == oy && nx == i))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy + 1; i <= LENGTH; i++)		// down
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)			// left up
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)			// right up
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)		// left down
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)		// right down
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	return 0;
}

int KnightW(int ox, int oy, int nx, int ny)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && ny == oy - 2 && nx == ox - 1 && board[ny][nx] >= 0)
		return 1;		// left up
	if (oy - 2 >= 0 && ox + 1 <= LENGTH && ny == oy - 2 && nx == ox + 1 && board[ny][nx] >= 0)
		return 1;		// right up
	if (oy - 1 >= 0 && ox + 2 <= LENGTH && ny == oy - 1 && nx == ox + 2 && board[ny][nx] >= 0)
		return 1;		// right 1
	if (oy + 1 >= 0 && ox + 2 <= LENGTH && ny == oy + 1 && nx == ox + 2 && board[ny][nx] >= 0)
		return 1;		// right 2
	if (oy + 2 <= LENGTH && ox + 1 <= LENGTH && ny == oy + 2 && nx == ox + 1 && board[ny][nx] >= 0)
		return 1;		// down 1
	if (oy + 2 <= LENGTH && ox - 1 >= 0 && ny == oy + 2 && nx == ox - 1 && board[ny][nx] >= 0)
		return 1;		// down 2
	if (oy + 1 <= LENGTH && ox - 2 >= 0 && ny == oy + 1 && nx == ox - 2 && board[ny][nx] >= 0)
		return 1;		// left 1
	if (oy - 1 >= 0 && ox - 2 >= 0 && ny == oy - 1 && nx == ox - 2 && board[ny][nx] >= 0)
		return 1;		// left 2

	return 0;
}

int KnightB(int ox, int oy, int nx, int ny)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && ny == oy - 2 && nx == ox - 1 && board[ny][nx] <= 0)
		return 1;
	if (oy - 2 >= 0 && ox + 1 <= LENGTH && ny == oy - 2 && nx == ox + 1 && board[ny][nx] <= 0)
		return 1;
	if (oy - 1 >= 0 && ox + 2 <= LENGTH && ny == oy - 1 && nx == ox + 2 && board[ny][nx] <= 0)
		return 1;
	if (oy + 1 >= 0 && ox + 2 <= LENGTH && ny == oy + 1 && nx == ox + 2 && board[ny][nx] <= 0)
		return 1;
	if (oy + 2 <= LENGTH && ox + 1 <= LENGTH && ny == oy + 2 && nx == ox + 1 && board[ny][nx] <= 0)
		return 1;
	if (oy + 2 <= LENGTH && ox - 1 >= 0 && ny == oy + 2 && nx == ox - 1 && board[ny][nx] <= 0)
		return 1;
	if (oy + 1 <= LENGTH && ox - 2 >= 0 && ny == oy + 1 && nx == ox - 2 && board[ny][nx] <= 0)
		return 1;
	if (oy - 1 >= 0 && ox - 2 >= 0 && ny == oy - 1 && nx == ox - 2 && board[ny][nx] <= 0)
		return 1;

	return 0;
}

// Checkmate Check

int PawnBCheck(int ox, int oy, int kingx, int kingy)
{
	if (board[oy + 1][ox - 1] <= 0)
		if (kingy == oy + 1 && kingx == ox - 1)
			return 1;

	if (board[oy + 1][ox + 1] <= 0)
		if (kingy == oy + 1 && kingx == ox + 1)
			return 1;

	return 0;
}

int RookBCheck(int ox, int oy, int kingx, int kingy)
{
	for (int i = ox - 1; i >= 0; i--)
	{
		if (board[oy][i] <= 0 && (kingx == i && kingy == oy))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][ox] <= 0 && (kingy == i && kingx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	for (int i = ox + 1; i <= LENGTH; i++)
	{
		if (board[oy][i] <= 0 && (kingy == oy && kingx == i))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][ox] <= 0 && (kingy == i && kingx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	return 0;
}

int BishopBCheck(int ox, int oy, int kingx, int kingy)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	return 0;
}

int QueenBCheck(int ox, int oy, int kingx, int kingy)
{
	for (int i = ox - 1; i >= 0; i--)
	{
		if (board[oy][i] <= 0 && (kingx == i && kingy == oy))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][ox] <= 0 && (kingy == i && kingx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	for (int i = ox + 1; i <= LENGTH; i++)
	{
		if (board[oy][i] <= 0 && (kingy == oy && kingx == i))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][ox] <= 0 && (kingy == i && kingx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] <= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	return 0;
}

int KnightBCheck(int ox, int oy, int kingx, int kingy)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && kingy == oy - 2 && kingx == ox - 1 && board[kingy][kingx] <= 0)
		return 1;
	if (oy - 2 >= 0 && ox + 1 <= LENGTH && kingy == oy - 2 && kingx == ox + 1 && board[kingy][kingx] <= 0)
		return 1;
	if (oy - 1 >= 0 && ox + 2 <= LENGTH && kingy == oy - 1 && kingx == ox + 2 && board[kingy][kingx] <= 0)
		return 1;
	if (oy + 1 >= 0 && ox + 2 <= LENGTH && kingy == oy + 1 && kingx == ox + 2 && board[kingy][kingx] <= 0)
		return 1;
	if (oy + 2 <= LENGTH && ox + 1 <= LENGTH && kingy == oy + 2 && kingx == ox + 1 && board[kingy][kingx] <= 0)
		return 1;
	if (oy + 2 <= LENGTH && ox - 1 >= 0 && kingy == oy + 2 && kingx == ox - 1 && board[kingy][kingx] <= 0)
		return 1;
	if (oy + 1 <= LENGTH && ox - 2 >= 0 && kingy == oy + 1 && kingx == ox - 2 && board[kingy][kingx] <= 0)
		return 1;
	if (oy - 1 >= 0 && ox - 2 >= 0 && kingy == oy - 1 && kingx == ox - 2 && board[kingy][kingx] <= 0)
		return 1;

	return 0;
}

int KingBCheck(int ox, int oy, int kingx, int kingy)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && kingy == oy - 1 && kingx == ox - 1 && board[kingy][kingx] >= 0)
		return 1;	// left up
	if (ox - 1 >= 0 && kingx == ox && kingy == oy - 1 && board[kingy][kingx] >= 0)
		return 1;	// up
	if (oy - 1 >= 0 && ox + 1 <= LENGTH && kingx == ox + 1 && kingy == oy - 1 && board[kingy][kingx] >= 0)
		return 1;	// right up
	if (ox + 1 <= LENGTH && kingy == oy && kingx == ox + 1 && board[kingy][kingx] >= 0)
		return 1;	// right
	if (ox + 1 <= LENGTH && oy + 1 <= LENGTH && kingy == oy + 1 && kingx == ox + 1 && board[kingy][kingx] >= 0)
		return 1;	// right down
	if (oy + 1 <= LENGTH && kingy == oy + 1 && kingx == ox && board[kingy][kingx] >= 0)
		return 1;	// down
	if (ox - 1 >= 0 && oy + 1 <= LENGTH && kingx == ox - 1 && kingy == oy + 1 && board[kingy][kingx] >= 0)
		return 1;	// left down
	if (ox - 1 >= 0 && kingy == oy && kingx == ox - 1 && board[kingy][kingx] >= 0)
		return 1;	// down

	return 0;
}

int PawnWCheck(int ox, int oy, int kingx, int kingy)
{
	if (board[oy - 1][ox - 1] >= 0)
		if (oy - 1 == kingy && ox - 1 == kingx)
			return 1;
	if (board[oy - 1][ox + 1] >= 0)
		if (oy - 1 == kingy && ox + 1 == kingx)
			return 1;
	return 0;
}

int RookWCheck(int ox, int oy, int kingx, int kingy)
{
	for (int i = ox - 1; i >= 0; i--)
	{
		if (board[oy][i] >= 0 && (kingx == i && kingy == oy))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][ox] >= 0 && (kingy == i && kingx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	for (int i = ox + 1; i <= LENGTH; i++)
	{
		if (board[oy][i] >= 0 && (kingy == oy && kingx == i))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][ox] >= 0 && (kingy == i && kingx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	return 0;
}

int BishopWCheck(int ox, int oy, int kingx, int kingy)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	return 0;
}

int QueenWCheck(int ox, int oy, int kingx, int kingy)
{
	for (int i = ox - 1; i >= 0; i--)
	{
		if (board[oy][i] >= 0 && (kingx == i && kingy == oy))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][ox] >= 0 && (kingy == i && kingx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	for (int i = ox + 1; i <= LENGTH; i++)
	{
		if (board[oy][i] >= 0 && (kingy == oy && kingx == i))
			return 1;
		else
			if (board[oy][i] != 0)
				break;
	}

	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][ox] >= 0 && (kingy == i && kingx == ox))
			return 1;
		else
			if (board[i][ox] != 0)
				break;
	}

	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	j = ox - 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j--;
	}

	j = ox + 1;
	for (int i = oy + 1; i <= LENGTH; i++)
	{
		if (board[i][j] >= 0 && (kingy == i && kingx == j))
			return 1;
		else
			if (board[i][j] != 0)
				break;
		j++;
	}

	return 0;
}

int KnightWCheck(int ox, int oy, int kingx, int kingy)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && kingy == oy - 2 && kingx == ox - 1 && board[kingy][kingx] >= 0)
		return 1;
	if (oy - 2 >= 0 && ox + 1 <= LENGTH && kingy == oy - 2 && kingx == ox + 1 && board[kingy][kingx] >= 0)
		return 1;
	if (oy - 1 >= 0 && ox + 2 <= LENGTH && kingy == oy - 1 && kingx == ox + 2 && board[kingy][kingx] >= 0)
		return 1;
	if (oy + 1 >= 0 && ox + 2 <= LENGTH && kingy == oy + 1 && kingx == ox + 2 && board[kingy][kingx] >= 0)
		return 1;
	if (oy + 2 <= LENGTH && ox + 1 <= LENGTH && kingy == oy + 2 && kingx == ox + 1 && board[kingy][kingx] >= 0)
		return 1;
	if (oy + 2 <= LENGTH && ox - 1 >= 0 && kingy == oy + 2 && kingx == ox - 1 && board[kingy][kingx] >= 0)
		return 1;
	if (oy + 1 <= LENGTH && ox - 2 >= 0 && kingy == oy + 1 && kingx == ox - 2 && board[kingy][kingx] >= 0)
		return 1;
	if (oy - 1 >= 0 && ox - 2 >= 0 && kingy == oy - 1 && kingx == ox - 2 && board[kingy][kingx] >= 0)
		return 1;

	return 0;
}

int KingWCheck(int ox, int oy, int kingx, int kingy)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && kingy == oy - 1 && kingx == ox - 1 && board[kingy][kingx] <= 0)
		return 1;
	if (ox - 1 >= 0 && kingx == ox && kingy == oy - 1 && board[kingy][kingx] <= 0)
		return 1;
	if (oy - 1 >= 0 && ox + 1 <= LENGTH && kingx == ox + 1 && kingy == oy - 1 && board[kingy][kingx] <= 0)
		return 1;
	if (ox + 1 <= LENGTH && kingy == oy && kingx == ox + 1 && board[kingy][kingx] <= 0)
		return 1;
	if (ox + 1 <= LENGTH && oy + 1 <= LENGTH && kingy == oy + 1 && kingx == ox + 1 && board[kingy][kingx] <= 0)
		return 1;
	if (oy + 1 <= LENGTH && kingy == oy + 1 && kingx == ox && board[kingy][kingx] <= 0)
		return 1;
	if (ox - 1 >= 0 && oy + 1 <= LENGTH && kingx == ox - 1 && kingy == oy + 1 && board[kingy][kingx] <= 0)
		return 1;
	if (ox - 1 >= 0 && kingy == oy && kingx == ox - 1 && board[kingy][kingx] <= 0)
		return 1;

	return 0;
}

// Kings

int WhiteKingCheck(int posKingx, int posKingy)
{
	int ok = 0;
	for (int i = 0; i <= LENGTH; i++)
	{
		for (int j = 0; j <= LENGTH; j++)
		{
			if (board[i][j] > 0)
			{
				// Pawn
				if (board[i][j] == BLACK_PAWN1 || board[i][j] == BLACK_PAWN2 || board[i][j] == BLACK_PAWN3 || board[i][j] == BLACK_PAWN4 ||
					board[i][j] == BLACK_PAWN5 || board[i][j] == BLACK_PAWN6 || board[i][j] == BLACK_PAWN7 || board[i][j] == BLACK_PAWN8)
					ok = PawnBCheck(j, i, posKingx, posKingy);

				// Rook
				if (board[i][j] == BLACK_ROOK1 || board[i][j] == BLACK_ROOK2)
					ok = RookBCheck(j, i, posKingx, posKingy);

				// Knight
				if (board[i][j] == BLACK_KNIGHT1 || board[i][j] == BLACK_KNIGHT2)
					ok = KnightBCheck(j, i, posKingx, posKingy);

				// Bitshop
				if (board[i][j] == BLACK_BISHOP1 || board[i][j] == BLACK_BISHOP2)
					ok = BishopBCheck(j, i, posKingx, posKingy);

				// Queen
				if (board[i][j] == BLACK_QUEEN)
					ok = QueenBCheck(j, i, posKingx, posKingy);

				// King
				if (board[i][j] == BLACK_KING)
					ok = KingBCheck(j, i, posKingx, posKingy);


				if (ok == 1)
					return 0;
			}
		}
	}
	return 1;
}

int WhiteKing(int ox, int oy, int nx, int ny)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && ny == oy - 1 && nx == ox - 1 && board[ny][nx] >= 0)
	{
		int ok = WhiteKingCheck(ox - 1, oy - 1);
		if (ok == 1)
			return 1;
	}
	if (ox - 1 >= 0 && nx == ox && ny == oy - 1 && board[ny][nx] >= 0)
	{
		int ok = WhiteKingCheck(ox, oy - 1);
		if (ok == 1)
			return 1;
	}
	if (oy - 1 >= 0 && ox + 1 <= LENGTH && nx == ox + 1 && ny == oy - 1 && board[ny][nx] >= 0)
	{
		int ok = WhiteKingCheck(ox + 1, oy - 1);
		if (ok == 1)
			return 1;
	}
	if (ox + 1 <= LENGTH && ny == oy && nx == ox + 1 && board[ny][nx] >= 0)
	{
		int ok = WhiteKingCheck(ox + 1, oy);
		if (ok == 1)
			return 1;
	}
	if (ox + 1 <= LENGTH && oy + 1 <= LENGTH && ny == oy + 1 && nx == ox + 1 && board[ny][nx] >= 0)
	{
		int ok = WhiteKingCheck(ox + 1, oy + 1);
		if (ok == 1)
			return 1;
	}
	if (oy + 1 <= LENGTH && ny == oy + 1 && nx == ox && board[ny][nx] >= 0)
	{
		int ok = WhiteKingCheck(ox, oy + 1);
		if (ok == 1)
			return 1;
	}

	if (ox - 1 >= 0 && oy + 1 <= LENGTH && nx == ox - 1 && ny == oy + 1 && board[ny][nx] >= 0)
	{
		int ok = WhiteKingCheck(ox - 1, oy + 1);
		if (ok == 1)
			return 1;
	}

	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] >= 0)
	{
		int ok = WhiteKingCheck(ox - 1, oy);
		if (ok == 1)
			return 1;
	}

	if (whiteKingFirstMove == 0 && rightWhiteRookM == 0 && board[7][5] == 0 && board[7][6] == 0 && ny == 7 && nx == 6)
	{
		int ok = WhiteKingCheck(4, 7);
		if (ok == 1)
		{
			ok = WhiteKingCheck(5, 7);
			if (ok == 1)
			{
				ok = WhiteKingCheck(6, 7);
				if (ok == 1)
				{
					board[7][7] = 0;
					board[7][5] = WHITE_ROOK2;
					whiteKingFirstMove = 1;
					rightWhiteRookM = 1;
					return 1;
				}
			}
		}
	}

	if (whiteKingFirstMove == 0 && rightWhiteRookM == 0 && board[7][3] == 0 && board[7][2] == 0 && board[7][1] == 0 && ny == 7 && ny == 2)
	{
		int ok = WhiteKingCheck(4, 7);
		if (ok == 1)
		{
			ok = WhiteKingCheck(3, 7);
			if (ok == 1)
			{
				ok = WhiteKingCheck(2, 7);
				if (ok == 1)
				{
					ok = WhiteKingCheck(1, 7);
					if (ok == 1)
					{
						board[7][0] = 0;
						board[7][3] = WHITE_ROOK1;
						whiteKingFirstMove = 1;
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

void posWhiteKing()
{
	for (int i = 0; i <= LENGTH; i++)
	{
		for (int j = 0; j <= LENGTH; j++)
		{
			if (board[i][j] == WHITE_KING)
			{
				whiteKing.x = j;
				whiteKing.y = i;
				break;
			}
		}
	}
}

int BlackKingCheck(int posKingx, int posKingy)
{
	int ok = 0;
	for (int i = 0; i <= LENGTH; i++)
	{
		for (int j = 0; j <= LENGTH; j++)
		{
			if (board[i][j] < 0)
			{
				// Pawn
				if (board[i][j] == WHITE_PAWN1 || board[i][j] == WHITE_PAWN2 || board[i][j] == WHITE_PAWN3 || board[i][j] == WHITE_PAWN4 ||
					board[i][j] == WHITE_PAWN5 || board[i][j] == WHITE_PAWN6 || board[i][j] == WHITE_PAWN7 || board[i][j] == WHITE_PAWN8)
					ok = PawnWCheck(j, i, posKingx, posKingy);

				// Rook
				if (board[i][j] == WHITE_ROOK1 || board[i][j] == WHITE_ROOK2)
					ok = RookWCheck(j, i, posKingx, posKingy);

				// Knight
				if (board[i][j] == WHITE_KNIGHT1 || board[i][j] == WHITE_KNIGHT2)
					ok = KnightWCheck(j, i, posKingx, posKingy);

				// Bitshop
				if (board[i][j] == WHITE_BISHOP1 || board[i][j] == WHITE_BISHOP2)
					ok = BishopWCheck(j, i, posKingx, posKingy);

				// Queen
				if (board[i][j] == WHITE_QUEEN)
					ok = QueenWCheck(j, i, posKingx, posKingy);

				// King
				if (board[i][j] == WHITE_KING)
					ok = KingWCheck(j, i, posKingx, posKingy);


				if (ok == 1)
					return 0;
			}
		}
	}
	return 1;
}

int BlackKing(int ox, int oy, int nx, int ny)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && ny == oy - 1 && nx == ox - 1 && board[ny][nx] <= 0)
	{
		int ok = BlackKingCheck(ox - 1, oy - 1);
		if (ok == 1)
			return 1;
	}
	if (oy - 1 >= 0 && nx == ox && ny == oy - 1 && board[ny][nx] <= 0)
	{
		int ok = BlackKingCheck(ox, oy - 1);
		if (ok == 1)
			return 1;
	}
	if (oy - 1 >= 0 && ox + 1 <= LENGTH && nx == ox + 1 && ny == oy - 1 && board[ny][nx] <= 0)
	{
		int ok = BlackKingCheck(ox + 1, oy - 1);
		if (ok == 1)
			return 1;
	}
	if (ox + 1 <= LENGTH && ny == oy && nx == ox + 1 && board[ny][nx] <= 0)
	{
		int ok = BlackKingCheck(ox + 1, oy);
		if (ok == 1)
			return 1;
	}
	if (ox + 1 <= LENGTH && oy + 1 <= LENGTH && ny == oy + 1 && nx == ox + 1 && board[ny][nx] <= 0)
	{
		int ok = BlackKingCheck(ox + 1, oy + 1);
		if (ok == 1)
			return 1;
	}
	if (oy + 1 <= LENGTH && ny == oy + 1 && nx == ox && board[ny][nx] <= 0)
	{
		int ok = BlackKingCheck(ox, oy + 1);
		if (ok == 1)
			return 1;
	}

	if (ox - 1 >= 0 && oy + 1 <= LENGTH && nx == ox - 1 && ny == oy + 1 && board[ny][nx] <= 0)
	{
		int ok = BlackKingCheck(ox - 1, oy + 1);
		if (ok == 1)
			return 1;
	}

	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] <= 0)
	{
		int ok = BlackKingCheck(ox - 1, oy);
		if (ok == 1)
			return 1;
	}

	if (rightBlackRookM == 0 && blackKingFirstMove == 0 && board[0][5] == 0 && board[0][6] == 0 && ny == 0 && ny == 6)
	{
		int ok = BlackKingCheck(4, 0);
		if (ok == 1)
		{
			ok = BlackKingCheck(5, 0);
			if (ok == 1)
			{
				ok = BlackKingCheck(6, 0);
				if (ok == 1)
				{
					blackKingFirstMove = 1;
					rightBlackRookM = 1;
					board[0][7] = 0;
					board[0][5] = BLACK_ROOK2;
					return 1;
				}
			}
		}
	}

	if (leftBlackRookM == 0 && blackKingFirstMove == 0 && board[0][3] == 0 && board[0][2] == 0 && board[0][1] == 0 && ny == 0 && nx == 2)
	{
		int ok = BlackKingCheck(4, 0);
		if (ok == 1)
		{
			ok = BlackKingCheck(3, 0);
			if (ok == 1)
			{
				ok = BlackKingCheck(2, 0);
				if (ok == 1)
				{
					blackKingFirstMove = 1;
					rightBlackRookM = 1;
					board[0][0] = 0;
					board[0][3] = BLACK_ROOK1;
					return 1;
				}

			}
		}
	}

	return 0;
}

void posBlackKing()
{
	for (int i = 0; i <= LENGTH; i++)
	{
		for (int j = 0; j <= LENGTH; j++)
		{
			if (board[i][j] == BLACK_KING)
			{
				blackKing.x = j;
				blackKing.y = i;
				break;
			}
		}
	}
}