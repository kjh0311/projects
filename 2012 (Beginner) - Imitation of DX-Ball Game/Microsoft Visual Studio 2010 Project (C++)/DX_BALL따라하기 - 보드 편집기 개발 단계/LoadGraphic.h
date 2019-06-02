HBITMAP GrabLaser, GrabPaddle, ShootingPaddle, Laser, PierceBall, FireBall;
HBITMAP Grabbed, bar, ball, bomb, brick[4], left, right, gameover, gamePaused, BitFile;

void LoadGraphic(){
	GrabLaser = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_GrabLaser));
	GrabPaddle = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_GrabPaddle));
	ShootingPaddle = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_ShootingPaddle));
	Laser = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Laser));
	PierceBall = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Pierce));
	FireBall = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_FireBall));
	gamePaused=LoadBitmap(g_hInst,MAKEINTRESOURCE(GamePaused));
	gameover=LoadBitmap(g_hInst,MAKEINTRESOURCE(GameOver));
	Grabbed=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Grabbed));
	bar=LoadBitmap(g_hInst,MAKEINTRESOURCE(Bar));
	ball=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Ball));
	bomb=LoadBitmap(g_hInst,MAKEINTRESOURCE(Bomb));
	left=LoadBitmap(g_hInst,MAKEINTRESOURCE(LeftPipe));
	right=LoadBitmap(g_hInst,MAKEINTRESOURCE(RightPipe));
	brick[4];
	for(i=0;i<4;i++)
		brick[i]=LoadBitmap(g_hInst,MAKEINTRESOURCE(Brick1+i));
}