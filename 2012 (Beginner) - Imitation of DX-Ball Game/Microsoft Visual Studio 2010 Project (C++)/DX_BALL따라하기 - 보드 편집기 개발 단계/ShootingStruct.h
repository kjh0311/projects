CRITICAL_SECTION Missile_CRT;

struct Missile{
	int x, y;
	struct Missile *next, *back;
};

struct Missile *MissileHead = NULL; // 시작 지점
struct Missile *MissileTail = MissileHead; // 추가를 위해 필요

Missile* CreateMissile(int x,int y){
	struct Missile newMissile;
	newMissile.x=x;
	newMissile.y=y;
	newMissile.next=NULL;
	newMissile.back=NULL;	//초기값이 반드시 있어야함
	EnterCriticalSection(&Missile_CRT);
	if(MissileHead == NULL)
	{// 새 메모리 할당
		MissileHead=(Missile*)malloc(sizeof(Missile));
		*MissileHead = newMissile;	// 새로 만든 미사일을 할당된 메모리 공간으로 복사
		MissileTail = MissileHead;	// Tail도 Head와 동일한 위치로 업데이트
	}
	else{//헤드가 아닌 경우
		// 새로운 공간을 할당하여 Tail->Next에 붙임
		newMissile.back = MissileTail;
		MissileTail->next = (Missile*)malloc(sizeof(Missile));
		MissileTail = MissileTail->next; // 새 공간을 마지막으로 지정
		*MissileTail = newMissile;
	}
	LeaveCriticalSection(&Missile_CRT);
	return MissileTail;	// 맨 마지막 것(새로 만든 것)을 반환값으로 지정
}

void DeleteMissile(Missile* usedMissile){//가독성 증가
	
		if(usedMissile==NULL) return;
	//동기화, return되면 못 빠져나오므로 신중히
	EnterCriticalSection(&Missile_CRT);
	if(usedMissile->back==NULL){
		if(usedMissile->next==NULL){	// 유일
			//free(usedMissile);
			MissileHead=NULL;
			MissileTail=NULL;
			//usedMissile=NULL;
		}
		else{					// 선두			
			MissileHead=usedMissile->next;			
			//free(usedMissile->back);
			MissileHead->back=NULL;	//헤드 인증
		}
	}
	else{
		if(usedMissile->next==NULL){	// 맨끝			
			MissileTail=usedMissile->back;
			MissileTail->next=NULL;
			//free(usedMissile);
			//usedMissile=NULL;
			
		}
		else{								// 중간
			usedMissile->back->next= usedMissile->next;	//와우!
			usedMissile->next->back= usedMissile->back;			
			//free(usedMissile);
			//usedMissile=NULL;		
		}
	}
	
	free(usedMissile);
	LeaveCriticalSection(&Missile_CRT);
	
	/*
//	return;
	if(usedMissile == NULL) return;
	EnterCriticalSection(&Missile_CRT);
	// 가장 일반적인 경우가 앞에 있어야 효율적임	
	if(usedMissile->back == NULL){ // 선두
		//if(usedMissile->next != NULL){
			MissileHead = usedMissile->next;
			if(usedMissile==MissileTail) //유일한 경우
				MissileTail=NULL;
			free(usedMissile);
			usedMissile=NULL;
	}
	else{	//앞이 존재할 때 (!=NULL이용)
		usedMissile->back->next= usedMissile->next;
		if(usedMissile->next != NULL){	//뒤가 존재할 때
			usedMissile->next->back = usedMissile->back;
		}		
		else{ // Tail인 경우
			MissileTail=usedMissile->back;
			MissileTail->next=NULL;
		}
		free(usedMissile);
		usedMissile=NULL;
	}
	LeaveCriticalSection(&Missile_CRT);
	*/
	
}