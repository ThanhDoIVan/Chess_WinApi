#pragma once

#define LENGTH 7

#define	BLACK_PAWN1  11
#define	BLACK_PAWN2  12
#define	BLACK_PAWN3  13
#define	BLACK_PAWN4  14
#define	BLACK_PAWN5  15
#define	BLACK_PAWN6  16
#define	BLACK_PAWN7  17
#define	BLACK_PAWN8  18

#define	WHITE_PAWN1 -11
#define	WHITE_PAWN2 -12
#define	WHITE_PAWN3 -13
#define	WHITE_PAWN4 -14
#define	WHITE_PAWN5 -15
#define	WHITE_PAWN6 -16
#define	WHITE_PAWN7 -17
#define	WHITE_PAWN8 -18

#define BLACK_ROOK1     21
#define BLACK_ROOK2     22
#define WHITE_ROOK1    -21
#define WHITE_ROOK2    -22
#define	BLACK_KNIGHT1   31
#define	BLACK_KNIGHT2   32
#define WHITE_KNIGHT1  -31
#define WHITE_KNIGHT2  -32
#define	BLACK_BISHOP1   41
#define	BLACK_BISHOP2   42

#define WHITE_BISHOP1  -41
#define WHITE_BISHOP2  -42
#define	BLACK_QUEEN     55
#define WHITE_QUEEN    -55
#define	BLACK_KING		66
#define WHITE_KING	   -66

void loadImages();
void loadPlayBoard(int);

int PawnW(int, int, int, int);
int PawnB(int, int, int, int);

int RookW(int, int, int, int);
int RookB(int, int, int, int);

int KnightW(int, int, int, int);
int KnightB(int, int, int, int);

int BishopW(int, int, int, int);
int BishopB(int, int, int, int);

int QueenW(int, int, int, int);
int QueenB(int, int, int, int);

int WhiteKing(int, int, int, int);
int BlackKing(int, int, int, int);

int PawnWCheck(int, int, int, int);
int PawnBCheck(int, int, int, int);

int RookWCheck(int, int, int, int);
int RookBCheck(int, int, int, int);

int KnightWCheck(int, int, int, int);
int KnightBCheck(int, int, int, int);

int BishopWCheck(int, int, int, int);
int BishopBCheck(int, int, int, int);

int QueenWCheck(int, int, int, int);
int QueenBCheck(int, int, int, int);

int WhiteKingCheck(int, int);
int BlackKingCheck(int, int);

void posWhiteKing();
void posBlackKing();