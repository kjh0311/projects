BOOL CALLBACK BackDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	OPENFILENAME OFN;
	TCHAR str[256];
	TCHAR lpstrFile[MAX_PATH]="";
//	HBITMAP hBit;
	RECT bitRect;	
	HBRUSH MyBrush,OldBrush;
	CHOOSECOLOR COL;
	
	int i;

	switch(iMessage){
	case WM_INITDIALOG:	//한 번만 작동
		CheckRadioButton(hDlg,IDC_RADIO1,IDC_RADIO5,IDC_RADIO1);		
		return true;
	case WM_PAINT:		
		hdc=BeginPaint(hDlg, &ps);
		MyBrush=CreateSolidBrush(Color);
		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		Rectangle(hdc,17,17,477,339);
		SelectObject(hdc,OldBrush);
		DeleteObject(MyBrush);
		switch (Option){
		case 1:
			DrawBitmap(hdc,17,17,BitFile);
			break;
		case 2:
			DrawCenterBitmap(hdc,239,170,BitFile);
			break;
		case 3:
			DrawTileBitmap(hdc,17,17,460,322,BitFile);
			break;
		case 4:
			DrawStretchBitmap(hdc,17,17,460,322,BitFile);
			break;
		case 5:
			DrawFixBitmap(hdc,17,17,460,322,BitFile);
			break;		
		//DrawBitmap(hdc,12,12,BitFile);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)){
		case ID_OPEN:
			memset(&OFN,0,sizeof(OPENFILENAME));
			OFN.lStructSize=sizeof(OPENFILENAME);
			OFN.hwndOwner=hDlg;
			OFN.lpstrFilter=TEXT("비트맵 파일(*.BMP)\0*.bmp\0");
			OFN.lpstrFile=lpstrFile;
			OFN.nMaxFile=MAX_PATH;
			if (GetOpenFileName(&OFN)!=0){
				BitFile=(HBITMAP)LoadImage(g_hInst,TEXT(OFN.lpstrFile),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			//	SetRect(&bitRect,7,7,500,400);
			//	InvalidateRect(hDlg,&bitRect,TRUE);	
				wsprintf(str,TEXT("%s 파일을 선택했습니다."),OFN.lpstrFile);
				MessageBox(hDlg,str,TEXT("파일 열기 성공"),MB_OK);
			}			
			break;
		case ID_COLOR:
			memset(&COL,0,sizeof(CHOOSECOLOR));
			COL.lStructSize=sizeof(CHOOSECOLOR);
			COL.hwndOwner=hDlg;
			COL.lpCustColors=crTemp;
			COL.Flags=CC_FULLOPEN;
			if(ChooseColor(&COL)!=0){
				Color=COL.rgbResult;
			}
			break;
		case IDC_RADIO1:
			Option=1;
			break;
		case IDC_RADIO2:
			Option=2;
			break;
		case IDC_RADIO3:
			Option=3;
			break;
		case IDC_RADIO4:
			Option=4;
			break;
		case IDC_RADIO5:
			Option=5;
			break;
//		default:
//			EndDialog(hDlg,ID_OPEN);
		}
		SetRect(&bitRect,17,17,500,400);
		InvalidateRect(hDlg,&bitRect,TRUE);
		break;
	case WM_CLOSE:
		EndDialog(hDlg,TRUE);
		break;
	}
	return FALSE;
}

BOOL CALLBACK HelpDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam){
	HDC hdc;
	PAINTSTRUCT ps;
	switch(iMessage){
	case WM_INITDIALOG:	//한 번만 작동
		return true;
	case WM_PAINT:		
		hdc=BeginPaint(hDlg, &ps);
		EndPaint(hDlg,&ps);
		
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)){
		case IDOK:
			;
	}	
		//break;
	case WM_CLOSE:
		EndDialog(hDlg,TRUE);
		break;
	}
	return FALSE;
}