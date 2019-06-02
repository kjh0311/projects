void InitializeGame(){
	// 죽기전과 죽기 후 Paddle 그림 업데이트
		SetRect(&Paddle,pos,310,(pos+LengthOfBar+speed),(310+HeightOfGrab));
		InvalidateRect(hWndMain,&Paddle,FALSE);
		bGrabbed=true;
		speed = INIT_SPEED;
		//Frame = INIT_FRAME;
		CreateBall(INIT_X,INIT_Y,INIT_DX,INIT_DY);
		FirstBall->Grabbed=TRUE;
		pos= INIT_POS;
		LengthOfBar=INIT_LENGTH;
		BallSize=INIT_BALL_SIZE;
		BoolGrab=FALSE;
		BoolShootingPaddle=FALSE;
		Pierce=FALSE;
		bFireBall=FALSE;
		bFallingBrick=FALSE;
		bUppingBrick=FALSE;
		SetRect(&Paddle,pos,310,(pos+LengthOfBar+speed),(310+HeightOfGrab));
		InvalidateRect(hWndMain,&Paddle,FALSE);
		energy=MAX_ENERGY;
		for (int i=0;i<energy;i++){
			SetRect(&RCenergy,(545-11*i),20,(555-11*i),25);
			InvalidateRect(hWndMain,&RCenergy,FALSE);
		}
}