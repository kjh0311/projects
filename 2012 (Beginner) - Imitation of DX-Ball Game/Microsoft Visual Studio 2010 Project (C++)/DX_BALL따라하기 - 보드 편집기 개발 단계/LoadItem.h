HBITMAP *Item, Item_EightBall, Item_ExpandPaddle, Item_ExtraEnergy, Item_ExtraLife, Item_FallingBrick;
HBITMAP Item_SlowerBall, Item_FasterBall, Item_FireBall, Item_GrabPaddle, Item_Shooting, Item_ShrinkPaddle;
HBITMAP Item_SplitBall, Item_ThruBrick;
HBITMAP Item_BigBall, Item_MiniBall;
HBITMAP Item_UppingBrick;
HBITMAP Item_Empty;

void LoadItemBitmap(){
//HBITMAP EightBall, ExpandPaddle, ExtraEnergy, ExtraLife, FallingBrick, 
	//FasterBall, FireBall, GrabPaddle, Shooting, ShrinkPaddle, SplitBall, ThruBrick;
Item_EightBall=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_EightBall));
Item_ExpandPaddle=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_ExpandPaddle));
Item_ExtraEnergy=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_ExtraEnergy));
Item_ExtraLife=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_ExtraLife));
Item_FallingBrick=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_FallingBrick));
Item_FasterBall=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_FasterBall));
Item_FireBall=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_FireBall));
Item_GrabPaddle=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_GrabPaddle));
Item_Shooting=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_Shooting));
Item_ShrinkPaddle=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_ShrinkPaddle));
Item_SplitBall=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_SplitBall));
Item_ThruBrick=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_ThruBrick));
Item_BigBall=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_BigBall));
Item_MiniBall=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_MiniBall));
Item_SlowerBall=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_SlowerBall));
Item_UppingBrick=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_UppingBrick));
Item_Empty=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_Item_Empty));
}

HBITMAP* RandItem(){	
	//static int srandCount=0;
	//if(srandCount==0)
	//srandCount++;
	//if(srandCount>5) srandCount=0;
	int r;
	//r = 0;
		r = rand()%17;
			switch(r){
			case 0:
				Item=&Item_EightBall;
				break;
			case 1:
				Item=&Item_ExpandPaddle;
				break;
			case 2:
				Item=&Item_ExtraEnergy;
				break;
			case 3:
				Item=&Item_ExtraLife;
				break;
			case 4:
				Item=&Item_FallingBrick;
				break;
			case 5:
				Item=&Item_FasterBall;
				break;
			case 6:
				Item=&Item_FireBall;
				break;
			case 7:
				Item=&Item_GrabPaddle;
				break;
			case 8:
				Item=&Item_Shooting;
				break;
			case 9:
				Item=&Item_ShrinkPaddle;
				break;
			case 10:
				Item=&Item_SplitBall;
				break;
			case 11:
				Item=&Item_ThruBrick;
				break;
			case 12:
				Item=&Item_BigBall;
				break;
			case 13:
				Item=&Item_MiniBall;
				break;
			case 14:
				Item=&Item_SlowerBall;
				break;
			case 15:
				Item=&Item_UppingBrick;
				break;
			case 16:
				Item=&Item_Empty;
				break;
			}
			return Item;
}