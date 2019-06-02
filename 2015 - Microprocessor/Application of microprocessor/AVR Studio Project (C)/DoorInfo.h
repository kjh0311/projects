

typedef int State;

 #ifndef SHORT_INT
 #define SHORT_INT
typedef	unsigned char	shortInt;
typedef	unsigned char	ShortInt;
#endif

typedef struct{
	ShortInt sec, tenMili; 
} SecondAndTenMili;

typedef struct
{
	State mode;
	SecondAndTenMili openingStartTime;
	SecondAndTenMili openedStartTime;
	SecondAndTenMili closingStartTime;
	//int openingCount;
	//int openedCount;
} DoorInfo;

