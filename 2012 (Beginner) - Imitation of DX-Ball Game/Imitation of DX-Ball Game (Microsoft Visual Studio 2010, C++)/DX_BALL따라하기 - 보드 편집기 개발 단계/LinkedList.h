CRITICAL_SECTION crit;	//동기화 변수(FALSE로 시작해야함.)
CRITICAL_SECTION Brick_CRT;
CRITICAL_SECTION Sound_CRT;
int ItemCount=0;

struct DropingItem{
	int x, y;
	HBITMAP *rand;
	struct DropingItem *next;	
	struct DropingItem *back;
};

// 전역 데이터 선언.
//struct DropingItem DropingItemGlobal; 

struct DropingItem *DropingItemHead = NULL;		//포인터니까 NULL값이 가능한 것임.
									// NULL 값이란, 0번지 주소를 가리키는 것으로,
									// 통상 가리키는 데이터가 없다는 뜻으로 쓴다.
struct DropingItem *DropingItemTail=DropingItemHead;	// 처음에는 동일한 곳을 가리킴.
//포인터로 선언할 경우 DropingItemHead는 주소값. *DropingItemHead가 데이터.

DropingItem* CreateItem(int x,int y,HBITMAP *rand){
	//동기화
	EnterCriticalSection(&crit);
	struct DropingItem Item;	// 구조체 생성
	Item.x = x;
	Item.y = y;
	Item.rand=rand;
	Item.next = NULL;
	Item.back = NULL;
	if(DropingItemHead == NULL)		// Head가 초기값(NULL) 일 경우,
	{
		DropingItemHead=(DropingItem*)malloc(sizeof(DropingItem));
		*DropingItemHead = Item;
		DropingItemTail = DropingItemHead;
	}								// 생성한 아이템을 DropingItemHead가 
									// 가리키는 곳에 저장함.(주소전달 호출)
	//이 때 Tail은 Head와 동일
	else{
		Item.back=DropingItemTail;
		//next에다가 공간을 만듬.
		DropingItemTail->next = (DropingItem*)malloc(sizeof(DropingItem));
		DropingItemTail = DropingItemTail->next;	// Tail을 새 공간으로
		*DropingItemTail = Item;	// 새 공간에 자료를 저장
	}
	ItemCount++;
	LeaveCriticalSection(&crit);
	return DropingItemTail;
}

void DeleteItem(DropingItem *Item){	
	if(Item==NULL) return;
	//동기화, return되면 못 빠져나오므로 신중히
	EnterCriticalSection(&crit);
	if(Item->back==NULL){
		if(Item->next==NULL){	// 유일
			DropingItemHead=NULL;
			DropingItemTail=NULL;	// 포인터를 비움으로써 자료가 없음을 표시
		}
		else{					// 선두			
			DropingItemHead=Item->next;			
			DropingItemHead->back=NULL;	//헤드 인증
		}
	}
	else{
		if(Item->next==NULL){	// 맨끝			
			DropingItemTail=Item->back;
			DropingItemTail->next=NULL;			
		}
		else{								// 중간
			Item->back->next= Item->next;	//와우!
			Item->next->back= Item->back;			
		}
	}	
	free(Item);	// 다 쓴 것은 버림.
	LeaveCriticalSection(&crit);
}
