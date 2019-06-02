CRITICAL_SECTION Ball_CRT;
int BallCount=0;

struct BallStruct{
	float x, y, dx, dy;
	BOOL Grabbed;
	struct BallStruct *next, *back;
};

struct BallStruct *FirstBall = NULL; // 시작 지점
struct BallStruct *LastBall = FirstBall; // 추가를 위해 필요

BallStruct* CreateBall(float x,float y,float dx, float dy){		
	EnterCriticalSection(&Ball_CRT);
	struct BallStruct NewBall;
	NewBall.x=x;
	NewBall.y=y;
	NewBall.dx=dx;
	NewBall.dy=dy;
	NewBall.Grabbed=FALSE;
	NewBall.next=NULL;
	NewBall.back=NULL;	//초기값이 반드시 있어야함	
	BallCount++;
	if(FirstBall == NULL)
	{// 새 메모리 할당
		FirstBall=(BallStruct*)malloc(sizeof(BallStruct));
		*FirstBall = NewBall;	// 새로 만든 미사일을 할당된 메모리 공간으로 복사
		LastBall = FirstBall;	// Tail도 Head와 동일한 위치로 업데이트
	}
	else{//헤드가 아닌 경우
		// 새로운 공간을 할당하여 Tail->Next에 붙임
		
		NewBall.back = LastBall;
		LastBall->next = (BallStruct*)malloc(sizeof(BallStruct));
		LastBall = LastBall->next; // 새 공간을 마지막으로 지정
		*LastBall = NewBall;
	}
	LeaveCriticalSection(&Ball_CRT);
	return LastBall;	// 맨 마지막 것(새로 만든 것)을 반환값으로 지정
}

void DeleteBall(BallStruct* DeadBall){//가독성 증가
		if(DeadBall==NULL) return;
	//동기화, return되면 못 빠져나오므로 신중히
	EnterCriticalSection(&Ball_CRT);
	BallCount--;
	if(DeadBall->back==NULL){
		if(DeadBall->next==NULL){	// 유일
			//free(DeadBall);
			FirstBall=NULL;
			LastBall=NULL;
			DeadBall=NULL;
		}
		else{					// 선두			
			FirstBall=DeadBall->next;	// 오류 방지		
			//free(DeadBall->back);
			FirstBall->back=NULL;	//헤드 인증
		}
	}
	else{
		if(DeadBall->next==NULL){	// 맨끝
			
			LastBall=DeadBall->back;
			LastBall->next=NULL;
			//free(DeadBall);			
		}
		else{								// 중간
			DeadBall->back->next= DeadBall->next;	//와우!
			DeadBall->next->back= DeadBall->back;			
			//free(DeadBall);			
		}
	}
	free(DeadBall);
	LeaveCriticalSection(&Ball_CRT);
}
