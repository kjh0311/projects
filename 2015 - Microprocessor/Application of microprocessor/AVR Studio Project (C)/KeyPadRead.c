



#define KEY_DATA      (*(volatile unsigned char *)0x5400 )
#define KEY_SCAN      (*(volatile unsigned char *)0x5800 )


#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
// KEY PAD
extern volatile uint8_t tenMiliSec;
#include "Watch\Time.h"
extern 
unsigned char KeyPadScanL0(void) {
	
	unsigned char key_data = 0;
	static unsigned char prev_key = 0;
	unsigned char cur_key;


	KEY_DATA = 0x0e ;
	key_data = KEY_SCAN ;

	cur_key = ( unsigned char )(key_data &0x0f) ;
	return cur_key;	
}

unsigned char KeyPadScanL1(void)
{
	unsigned char key_data ;
	
	KEY_DATA = 0x0d ;
	key_data = KEY_SCAN ;     // sw5 ~ sw8 scan
	
	return ( unsigned char )(key_data &0x0f) ; 
}

unsigned char KeyPadScanH0(void) 
{
	unsigned char key_data ;
	
	KEY_DATA = 0x0b ;
	key_data = KEY_SCAN ;    // sw9 ~ sw12 scan
	
	return ( unsigned char )(key_data&0x0f) ; 
}

unsigned char KeyPadScanH1(void){
	unsigned char key_data ;
	
	KEY_DATA = 0x07 ;
	key_data = KEY_SCAN ;   // sw13 ~ sw16 scan
	
	return ( unsigned char )(key_data&0x0f) ; 
}

unsigned char KeyPadRead(void)
{
	unsigned char k0 , k1 , k2 , k3, retval ;
	
	k0 = KeyPadScanL0();
	k1 = KeyPadScanL1();
	k2 = KeyPadScanH0();
	k3 = KeyPadScanH1();
	
	if ( k0 != 0x0f )
	{
  		switch( k0 ) {                              
      		case 0x07 :   
      			retval = 1 ;
      			break ;	           
      		case 0x0b : 
      			retval = 2 ; 
        		break ;
      		case 0x0d : 
        		retval = 3 ; 
        		break ;
      		case 0x0e : 
      			retval = 4 ;
        		break ;
      		default :
				break ;
   		}
  	} else if ( k1 != 0x0f )
	{
  		switch( k1 ){                              
      		case 0x07 :   
      			retval = 5 ;
      			break ;	           
      		case 0x0b : 
      			retval = 6 ; 
        		break ;
      		case 0x0d : 
        		retval = 7 ; 
        		break ;
      		case 0x0e : 
      			retval = 8 ;
        		break ;
      		default :
				break ;
   		}
  	} else if ( k2 != 0x0f ) {
  		switch( k2 ){                              
      		case 0x07 :   
      			retval = 9 ;
      			break ;	           
      		case 0x0b : 
      			retval = 10 ; 
        		break ;
      		case 0x0d : 
        		retval = 11 ; 
        		break ;
      		case 0x0e : 
      			retval = 12 ;
        		break ;
      		default :
				break ;
   		}
	} else if ( k3 != 0x0f ) {
  		switch( k3 ) {                              
      		case 0x07 :   
      			retval = 13 ;
      			break ;	           
      		case 0x0b : 
      			retval = 14 ; 
        		break ;
      		case 0x0d : 
        		retval = 15 ; 
        		break ;
      		case 0x0e : 
      			retval = 16 ;
        		break ;
      		default :
				break ;
   		}
	} else return 0 ;

  	return retval;
}
