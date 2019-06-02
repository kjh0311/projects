/********************************************************************
* Copyright (C) 2016 Microchip Technology Inc. and its subsidiaries
* (Microchip).  All rights reserved.
*
* You are permitted to use the software and its derivatives with Microchip
* products. See the license agreement accompanying this software, if any, for
* more info about your rights and obligations.
*
* SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
* MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
* PURPOSE. IN NO EVENT SHALL MICROCHIP, SMSC, OR ITS LICENSORS BE LIABLE OR
* OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH
* OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY FOR ANY DIRECT OR INDIRECT
* DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
* INDIRECT OR CONSEQUENTIAL DAMAGES, OR OTHER SIMILAR COSTS. To the fullest
* extend allowed by law, Microchip and its licensors liability will not exceed
* the amount of fees, if any, that you paid directly to Microchip to use this
* software.
*************************************************************************
*
*                           lorawan_na.c
*
* LoRaWAN NA file
*
******************************************************************************/

/****************************** INCLUDES **************************************/
#include <stdio.h>
#include "lorawan.h"
#include "lorawan_aes.h"
#include "lorawan_aes_cmac.h"
#include "lorawan_defs.h"
#include "lorawan_private.h"
#include "AES.h"
#include "radio_interface.h"
#include "sw_timer.h"
#include "lorawan_na.h"
#include "../../region_defines.h"
#include "../../UART_Print_Functions.h"

/****************************** VARIABLES *************************************/
#ifdef REGION_NA
const uint8_t rxWindowSize[] = {5, 5, 7, 12, 22, 0, 0, 0, 5, 5, 7, 12, 22, 42};

// Max Payload Size 
const uint8_t maxPayloadSize[14] = {11, 53, 129, 242, 242, 0, 0, 0, 53, 129, 242, 242, 242, 242};

// Channels by ism band
ChannelParams_t Channels[MAX_US_CHANNELS];

static const int8_t rxWindowOffset[] = {12, 6, 1, -2, -4, 0, 0, 0, 12, 6, 1, -2, -4, -4};

// Tx power possibilities by ism band
static const int8_t txPower915[] = {30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10};

// Spreading factor possibilities
static const uint8_t spreadingFactor[] = {10, 9, 8, 7, 8, 0, 0, 0, 12, 11, 10, 9, 8, 7};

static const ChannelParams_t DefaultChannels915 [MAX_US_CHANNELS] =   {  LC0_915,  LC1_915,  LC2_915,  LC3_915,  LC4_915,  LC5_915,
                                                                         LC6_915,  LC7_915,  LC8_915,  LC9_915,  LC10_915, LC11_915,
                                                                         LC12_915, LC13_915, LC14_915, LC15_915, LC16_915, LC17_915,
                                                                         LC18_915, LC19_915, LC20_915, LC21_915, LC22_915, LC23_915,
                                                                         LC24_915, LC25_915, LC26_915, LC27_915, LC28_915, LC29_915,
                                                                         LC30_915, LC31_915, LC32_915, LC33_915, LC34_915, LC35_915,
                                                                         LC36_915, LC37_915, LC38_915, LC39_915, LC40_915, LC41_915,
                                                                         LC42_915, LC43_915, LC44_915, LC45_915, LC46_915, LC47_915,
                                                                         LC48_915, LC49_915, LC50_915, LC51_915, LC52_915, LC53_915,
                                                                         LC54_915, LC55_915, LC56_915, LC57_915, LC58_915, LC59_915,
                                                                         LC60_915, LC61_915, LC62_915, LC63_915, LC64_915, LC65_915,
                                                                         LC66_915, LC67_915, LC68_915, LC69_915, LC70_915, LC71_915 };
#else
const uint8_t rxWindowSize[] =  {8, 10, 14, 26, 49, 88};
//const uint8_t rxWindowSize[] =  {88, 88, 88, 88, 88, 88};

const uint8_t maxPayloadSize[6] = {51, 51, 51, 115, 242, 242};

// Channels by ism band
ChannelParams_t Channels[MAX_KR_CHANNELS];

static const int8_t rxWindowOffset[] = {-33, -50, -58, -62, -66, -68};
//static const int8_t rxWindowOffset[] = {12, 6, 1, -2, -4, 0};

//static const int8_t txPowerUpper922[] = {14, 12, 10, 8, 6, 4, 2, 0};
static const int8_t txPowerUpper922[] = {20, 14, 11, 8, 5, 2};

static const int8_t txPowerLower922[] = {10, 8, 6, 4, 2, 0, -2, -4};

// Spreading factor possibilities 
static const uint8_t spreadingFactor[] = {12, 11, 10, 9, 8, 7};// Spreading factor possibilities


static const ChannelParams_t DefaultChannels922 [MAX_KR_CHANNELS] =
	{  LC0_922,  LC1_922,  LC2_922,  LC3_922,  LC4_922,  LC5_922,  LC6_922,
	   LC7_922,  LC8_922,  LC9_922,  LC10_922, LC11_922, LC12_922 };

#endif
/************************ PRIVATE FUNCTION PROTOTYPES *************************/

static void CreateAllSoftwareTimers (void);

static void SetCallbackSoftwareTimers (void);

static void StopAllSoftwareTimers (void);
#ifdef REGION_NA
static void InitDefault915Channels (void);
#else
static void InitDefault922Channels (void);
#endif
static void UpdateDataRange (uint8_t channelId, uint8_t dataRangeNew);

static void UpdateChannelIdStatus (uint8_t channelId, bool statusNew);

static LorawanError_t ValidateRxOffset (uint8_t rxOffset);

static LorawanError_t ValidateFrequency (uint32_t frequencyNew);

static LorawanError_t ValidateDataRange (uint8_t channelId, uint8_t dataRangeNew);

static LorawanError_t ValidateChannelId (uint8_t channelId);

#ifdef REGION_NA
static LorawanError_t ValidateChannelMaskCntl (uint8_t channelMaskCntl, uint16_t channelMask);
#else
static LorawanError_t ValidateChannelMaskCntl (uint8_t channelMaskCntl);
static LorawanError_t ValidateChannelMask (uint16_t channelMask);
#endif

static void EnableChannels (uint16_t channelMask, uint8_t channelMaskCntl);

static void UpdateCurrentDataRateAfterDataRangeChanges (void);
#ifdef REGION_NA
static uint32_t GenerateUSFrequency1 (uint8_t channelIndex);

static uint32_t GenerateUSFrequency2 (uint8_t channelIndex);

static uint32_t GenerateUSFrequencyReception (uint8_t channelIndex);
#else
static uint32_t GenerateKRFrequency (uint8_t channelIndex);
#endif
static void EnableChannels2 (uint8_t startIndex, uint8_t endIndex, uint16_t channelMask);

static LorawanError_t ValidateDataRateReception (uint8_t dataRate);

static void Retransmissions (void);

static void TransmissionErrorCallback (uint8_t param);

/****************************** FUNCTIONS *************************************/

void LORAWAN_Init(RxAppDataCb_t RxPayload, RxJoinResponseCb_t RxJoinResponse) // this function resets everything to the default values
{
    // Allocate software timers and their callbacks
    if (loRa.macInitialized == DISABLED)
    {
        CreateAllSoftwareTimers ();
        SetCallbackSoftwareTimers ();
        loRa.macInitialized = ENABLED;
    }
    else
    {
        StopAllSoftwareTimers ();
    }

    rxPayload.RxAppData = RxPayload;
    rxPayload.RxJoinResponse = RxJoinResponse;

#ifdef REGION_NA
    RADIO_Init(&radioBuffer[16], NA915_CALIBRATION_FREQ);
#else
	RADIO_Init(&radioBuffer[16], KR922_CALIBRATION_FREQ);
#endif
    srand (RADIO_ReadRandom ());  // for the loRa random function we need a seed that is obtained from the radio

    LORAWAN_Reset ();

    }

 void LORAWAN_Reset (void)
{
    if (loRa.macInitialized == ENABLED)
    {
        StopAllSoftwareTimers ();
    }

    loRa.syncWord = 0x34;
    RADIO_SetLoRaSyncWord(loRa.syncWord);

    loRa.macStatus.value = 0;
    loRa.linkCheckMargin = 255; // reserved
    loRa.linkCheckGwCnt = 0;
    loRa.lastTimerValue = 0;
    loRa.lastPacketLength = 0;
    loRa.fCntDown.value = 0;
    loRa.fCntUp.value = 0;
    loRa.devNonce = 0;
    loRa.prescaler = 1;
    loRa.adrAckCnt = 0;
    loRa.counterAdrAckDelay = 0;
    loRa.offset = 0; 
    loRa.lastTimerValue = 0;

    // link check mechanism should be disabled
    loRa.macStatus.linkCheck = DISABLED;

    //flags all 0-es
    loRa.macStatus.value = 0;
    loRa.lorawanMacStatus.value = 0;

    loRa.maxRepetitionsConfirmedUplink = 7; // 7 retransmissions should occur for each confirmed frame sent until ACK is received
    loRa.maxRepetitionsUnconfirmedUplink = 0; // 0 retransmissions should occur for each unconfirmed frame sent until a response is received
    loRa.counterRepetitionsConfirmedUplink = 1;
    loRa.counterRepetitionsUnconfirmedUplink = 1;

    loRa.batteryLevel = BATTERY_LEVEL_INVALID; // the end device was not able to measure the battery level
#ifdef REGION_NA
    // initialize default channels
    RADIO_Init(&radioBuffer[16], NA915_CALIBRATION_FREQ);
	
    InitDefault915Channels ();
  
    loRa.txPower = 6;
	
	//initialize receive window 2 parameters
    loRa.receiveWindow2Parameters.frequency = NA915_DEFAULT_RX_WINDOW2_FREQ;
    loRa.receiveWindow2Parameters.dataRate = NA915_DEFAULT_RX_WINDOW2_DR;   
#else
	RADIO_Init(&radioBuffer[16], KR922_CALIBRATION_FREQ);
	
	InitDefault922Channels ();
	
	loRa.txPower = 0;
	
	//initialize receive window 2 parameters
    loRa.receiveWindow2Parameters.frequency = KR922_DEFAULT_RX_WINDOW2_FREQ;
    loRa.receiveWindow2Parameters.dataRate = KR922_DEFAULT_RX_WINDOW2_DR;
#endif
    loRa.currentDataRate = DR0;

    UpdateMinMaxChDataRate ();

    //keys will be filled with 0
    loRa.macKeys.value = 0;  //no keys are set
    memset (&loRa.activationParameters, 0, sizeof(loRa.activationParameters));

    //protocol parameters receive the default values
    loRa.protocolParameters.receiveDelay1 = RECEIVE_DELAY1;
    loRa.protocolParameters.receiveDelay2 = RECEIVE_DELAY2;
    loRa.protocolParameters.joinAcceptDelay1 = JOIN_ACCEPT_DELAY1;
    loRa.protocolParameters.joinAcceptDelay2 = JOIN_ACCEPT_DELAY2;
    loRa.protocolParameters.ackTimeout = ACK_TIMEOUT;
    loRa.protocolParameters.adrAckDelay = ADR_ACK_DELAY;
    loRa.protocolParameters.adrAckLimit = ADR_ACK_LIMIT;
    loRa.protocolParameters.maxFcntGap = MAX_FCNT_GAP;

    LORAWAN_LinkCheckConfigure (DISABLED); // disable the link check mechanism

    RADIO_SetPABoost (1);
}

LorawanError_t LORAWAN_SetReceiveWindow2Parameters (uint32_t frequency, uint8_t dataRate)
{
    LorawanError_t result = OK;

#ifdef REGION_NA
    if ( (ValidateFrequency (frequency) == OK) && (ValidateDataRateReception (dataRate) == OK) )
#else
	if ( (ValidateFrequency (frequency) == OK) && (ValidateDataRate (dataRate) == OK) )	
#endif
    {
        UpdateReceiveWindow2Parameters (frequency, dataRate);
    }
    else
    {
        result = INVALID_PARAMETER;
    }
    return result;
}

uint32_t LORAWAN_GetFrequency (uint8_t channelId)
{
    uint32_t result = 0;
#ifdef REGION_NA
    if (channelId < MAX_US_CHANNELS_BANDWIDTH_125)		
    {
        result = GenerateUSFrequency1 (channelId);
    }
    else if ( (channelId < loRa.maxChannels) && (channelId >= MAX_US_CHANNELS_BANDWIDTH_125) )
    {
        result = GenerateUSFrequency2 (channelId);
    }
#else
	result = GenerateKRFrequency (channelId);
#endif

    return result;
}

LorawanError_t LORAWAN_SetDataRange (uint8_t channelId, uint8_t dataRangeNew)
{
    LorawanError_t result = OK;

    if (ValidateDataRange (channelId, dataRangeNew) != OK)
    {
        result = INVALID_PARAMETER;
    }
    else
    {
       UpdateDataRange (channelId, dataRangeNew);
    }

    return result;
}

uint8_t LORAWAN_GetDataRange (uint8_t channelId)
{
    uint8_t result = 0xFF;

    if (ValidateChannelId (channelId) == OK)
    {
        result = Channels[channelId].dataRange.value;
    }
    return result;
 }
 
LorawanError_t LORAWAN_SetChannelIdStatus (uint8_t channelId, bool statusNew)
{
    LorawanError_t result = OK;

    if (ValidateChannelId (channelId) == OK) 
    {
        UpdateChannelIdStatus (channelId, statusNew);
    }
    else
    {
        result = INVALID_PARAMETER;
    }
    
    return result;
}

bool LORAWAN_GetChannelIdStatus (uint8_t channelId)
{
    bool result = DISABLED;

    if (ValidateChannelId (channelId) == OK)
    {
        result = Channels[channelId].status;
    }
    return result;
}

void LORAWAN_TxDone (uint16_t timeOnAir)
{
    if (loRa.macStatus.macPause == DISABLED)
    {
	    uint8_t i;
	    uint32_t delta = 0, ticks;	
		
        //This flag is used when the reception in RX1 is overlapping the opening of RX2
        loRa.rx2DelayExpired = 0;

        loRa.macStatus.macState = BEFORE_RX1;

        i = loRa.lastUsedChannelIndex;

        if (loRa.lorawanMacStatus.joining == 1)
        {
            SwTimerSetTimeout(loRa.joinAccept1TimerId, MS_TO_TICKS_SHORT(loRa.protocolParameters.joinAcceptDelay1 + rxWindowOffset[loRa.receiveWindow1Parameters.dataRate]));
            SwTimerSetTimeout(loRa.joinAccept2TimerId, MS_TO_TICKS_SHORT(loRa.protocolParameters.joinAcceptDelay2 + rxWindowOffset[loRa.receiveWindow2Parameters.dataRate]));
            
            SwTimerStart(loRa.joinAccept1TimerId);
            SwTimerStart(loRa.joinAccept2TimerId);
        }
        else
        {
            SwTimerSetTimeout(loRa.receiveWindow1TimerId, MS_TO_TICKS_SHORT(loRa.protocolParameters.receiveDelay1 + rxWindowOffset[loRa.receiveWindow1Parameters.dataRate]));
            SwTimerSetTimeout(loRa.receiveWindow2TimerId, MS_TO_TICKS_SHORT(loRa.protocolParameters.receiveDelay2 + rxWindowOffset[loRa.receiveWindow2Parameters.dataRate]));

            SwTimerStart(loRa.receiveWindow1TimerId);
            SwTimerStart(loRa.receiveWindow2TimerId);
        }
    }
    else
    {
        if ((RADIO_GetStatus() & RADIO_FLAG_TIMEOUT) != 0)
        {
            // Radio transmission ended by watchdog timer
            rxPayload.RxAppData( NULL, 0, RADIO_NOT_OK );
        }
        else
        {
            //Standalone radio transmissions finished OK, using the same callback as in LoRaWAN tx
            if ( rxPayload.RxAppData != NULL )
            {
                rxPayload.RxAppData( NULL, 0, RADIO_OK );
            }
        }
    }
}

// this function is called by the radio when the first or the second receive window expired without receiving any message (either for join accept or for message)
void LORAWAN_RxTimeout(void)
{
    if (loRa.macStatus.macPause == 0)
    {
        // if the timeout is after the first receive window, we have to wait for the second receive window....
        if ( loRa.macStatus.macState == RX1_OPEN )
        {
            loRa.macStatus.macState = BETWEEN_RX1_RX2;
        }
        else
        {
        // if last message sent was a join request, the join was not accepted after the second window expired
            if (loRa.lorawanMacStatus.joining == 1)
            {
                SetJoinFailState();
            }
            // if last message sent was a data message, and there was no reply...
            else if (loRa.macStatus.networkJoined == 1)
            {
                Retransmissions ();
            }
        }
    }
    else
    {
        //Standalone radio reception NOK, using the same callback as in LoRaWAN rx
        if (rxPayload.RxAppData != NULL)
        {
            rxPayload.RxAppData(NULL, 0, RADIO_NOT_OK);
        }
    }
}

LorawanError_t ValidateDataRate (uint8_t dataRate)
{
    LorawanError_t result = OK;
#ifdef REGION_NA
    if (dataRate > DR4)
#else
	if (dataRate > DR5)
#endif
    {
        result = INVALID_PARAMETER;
    }
      
    return result;
}

LorawanError_t ValidateTxPower (uint8_t txPowerNew)
{
    LorawanError_t result = OK;
#ifdef REGION_NA
    if ((txPowerNew < 5) || (txPowerNew > 10) || (txPowerNew == 6))
#else
	if ( txPowerNew > 7)
#endif
    {
        result = INVALID_PARAMETER;
    }

    return result;
}

uint8_t* ExecuteDutyCycle (uint8_t *ptr)
{
    uint8_t maxDCycle;

    maxDCycle = *(ptr++);

    if (maxDCycle == 255)
    {
        loRa.macStatus.silentImmediately = ENABLED;
    }

    return ptr;
}

uint8_t* ExecuteLinkAdr (uint8_t *ptr)
{
    uint8_t txPower, dataRate;
    uint16_t channelMask, auxChannelMask;
    uint8_t auxMinDataRate = DR7, auxMaxDataRate = DR0, i;
    uint8_t startingIndex, endingIndex;
	uint8_t txPowerNew;

    txPower = *(ptr) & LAST_NIBBLE;
    dataRate = ( *(ptr) & FIRST_NIBBLE ) >> SHIFT4;
    ptr++;
    channelMask = (*((uint16_t*)ptr));
    auxChannelMask = channelMask;
    ptr = ptr + sizeof (channelMask);
    Redundancy_t *redundancy;
    redundancy = (Redundancy_t*)(ptr++);
	
	
	#ifdef REGION_NA
	if (ENABLED == loRa.macStatus.adr)
	{
		if (ValidateChannelMaskCntl(redundancy->chMaskCntl, channelMask) == OK)  // If the ChMask field value is one of values meaning RFU, the end-device should reject the command and unset the Channel mask ACK bit in its response.
		{
			loRa.macCommands[loRa.crtMacCmdIndex].channelMaskAck = 1;
			switch (redundancy->chMaskCntl)
			{
				
				case 0:
				case 1:
				case 2:
				case 3:
				{
					 startingIndex = redundancy->chMaskCntl << SHIFT4;
					 endingIndex = startingIndex + 16;
					 for (i = startingIndex; i < endingIndex; i++)
					 {
						if ((Channels[i].dataRange.min < auxMinDataRate) && (((auxChannelMask & 0x0001) == 0x0001) || (auxChannelMask == 0)))
						{
							auxMinDataRate = Channels[i].dataRange.min;
						}
						if ((Channels[i].dataRange.max > auxMaxDataRate) && (((auxChannelMask & 0x0001) == 0x0001) || (auxChannelMask == 0)))
						{
							auxMaxDataRate = Channels[i].dataRange.max;
						}
						auxChannelMask = auxChannelMask >> SHIFT1;
					}
				} break;

				case 4:
				case 7:
				{
					auxMinDataRate = DR4;
					auxMaxDataRate = DR4;
				} break;

				case 6:
				{
					// verify channels 0 to 63 for min/max datarate
					for (i = 0; i < 64; i++)
					{
						if (Channels[i].dataRange.min < auxMinDataRate) 
						{
							auxMinDataRate = Channels[i].dataRange.min;
						}
						if (Channels[i].dataRange.max > auxMaxDataRate)  
						{
							auxMaxDataRate = Channels[i].dataRange.max;
						}
					}
					if (channelMask != 0)    // if there is at least one channel enabled with DR4
					{
						auxMaxDataRate = DR4;
					}
				} break;				
			}           
		}

		if ( (ValidateDataRate (dataRate) == OK) &&  (dataRate >= auxMinDataRate) && (dataRate <= auxMaxDataRate) )
		{
			loRa.macCommands[loRa.crtMacCmdIndex].dataRateAck = 1;
		}

		if ((txPower <= 10) && (txPower != 6))
		{
			loRa.macCommands[loRa.crtMacCmdIndex].powerAck = 1;
		}

		if ( (loRa.macCommands[loRa.crtMacCmdIndex].powerAck == 1) && (loRa.macCommands[loRa.crtMacCmdIndex].dataRateAck == 1) && (loRa.macCommands[loRa.crtMacCmdIndex].channelMaskAck == 1) )
		{
			EnableChannels (channelMask, redundancy->chMaskCntl);

			if(txPower < 5)
			{
				txPowerNew = 5;
			}
			else
			{
				txPowerNew = txPower;
			}
			UpdateTxPower (txPowerNew);

			loRa.macStatus.txPowerModified = ENABLED; // the current tx power was modified, so the user is informed about the change via this flag
			UpdateCurrentDataRate (dataRate);

			if (redundancy->nbRep == 0)
			{
				loRa.maxRepetitionsUnconfirmedUplink = 0;
			}
			else
			{
				loRa.maxRepetitionsUnconfirmedUplink = redundancy->nbRep - 1;
			}
			loRa.macStatus.nbRepModified = 1;
		}
	}
    else
    {
        loRa.macCommands[loRa.crtMacCmdIndex].channelMaskAck = 0;
        loRa.macCommands[loRa.crtMacCmdIndex].dataRateAck = 0;
        loRa.macCommands[loRa.crtMacCmdIndex].powerAck = 0;
    }	
	#else
	 if (ENABLED == loRa.macStatus.adr)
    {
        if ( (ValidateChannelMaskCntl(redundancy->chMaskCntl) == OK) && (ValidateChannelMask(channelMask) == OK) )  // If the ChMask field value is one of values meaning RFU, the end-device should reject the command and unset the Channel mask ACK bit in its response.
        {
            loRa.macCommands[loRa.crtMacCmdIndex].channelMaskAck = 1;
        }

        if ( (ValidateDataRate (dataRate) == OK) &&  (dataRate >= loRa.minDataRate) && (dataRate <= loRa.maxDataRate) )
        {
            loRa.macCommands[loRa.crtMacCmdIndex].dataRateAck = 1;
        }

        if (ValidateTxPower (txPower) == OK)
        {
            loRa.macCommands[loRa.crtMacCmdIndex].powerAck = 1;
        }

        if ( (loRa.macCommands[loRa.crtMacCmdIndex].powerAck == 1) && (loRa.macCommands[loRa.crtMacCmdIndex].dataRateAck == 1) && (loRa.macCommands[loRa.crtMacCmdIndex].channelMaskAck == 1) )
        {
            EnableChannels (channelMask, redundancy->chMaskCntl);

            UpdateTxPower (txPower);
            loRa.macStatus.txPowerModified = ENABLED; // the current tx power was modified, so the user is informed about the change via this flag
            UpdateCurrentDataRate (dataRate);

            if (redundancy->nbRep == 0)
            {
                loRa.maxRepetitionsUnconfirmedUplink = 0;
            }
            else
            {
                loRa.maxRepetitionsUnconfirmedUplink = redundancy->nbRep - 1;
            }
            loRa.macStatus.nbRepModified = 1;
        }
    }
    else
    {
        loRa.macCommands[loRa.crtMacCmdIndex].channelMaskAck = 0;
        loRa.macCommands[loRa.crtMacCmdIndex].dataRateAck = 0;
        loRa.macCommands[loRa.crtMacCmdIndex].powerAck = 0;
    }
	#endif
    return ptr;
}

#ifndef REGION_NA
static LorawanError_t ValidateChannelMask (uint16_t channelMask)
{
   uint8_t i = 0;

   if(channelMask != 0x0000U)
   {
        for (i = 0; i < MAX_KR_CHANNELS; i++)
        {
            if ( ( (channelMask & BIT0) == BIT0) ) //&& ( (Channels[i].parametersDefined & (FREQUENCY_DEFINED | DATA_RANGE_DEFINED | DUTY_CYCLE_DEFINED) ) != (FREQUENCY_DEFINED | DATA_RANGE_DEFINED | DUTY_CYCLE_DEFINED) ) )  // if the channel mask sent enables a yet undefined channel, the command is discarded and the device state is not changed
            {
                return INVALID_PARAMETER;
            }
            else
            {
                channelMask = channelMask >> SHIFT1;
            }
        }

      return OK;
   }
   else
   {
       //ChMask set to 0x0000 in ADR may be used as a DoS attack so receiving this results in an error
       return INVALID_PARAMETER;
   }
}
#endif




uint8_t* ExecuteDevStatus (uint8_t *ptr)
{
    return ptr;
}

uint8_t* ExecuteNewChannel (uint8_t *ptr)
{
    uint8_t channelIndex;
    DataRange_t drRange;
    uint32_t frequency = 0;

    channelIndex = *(ptr++);

    frequency = (*((uint32_t*)ptr)) & 0x00FFFFFF;
    frequency = frequency * 100;
    ptr = ptr + 3;  // 3 bytes for frequecy

    drRange.value = *(ptr++);
	
	
//	uint8_t test[100];	
//	sprintf(test, "channelIndex: %d, frequency: %lld, drRange.min: %d, drRange.max: %d", channelIndex, frequency, drRange.min, drRange.max);
//	UART_Put_Line(test);
	

    if (ValidateChannelId (channelIndex) == OK)
    {
#ifdef REGION_NA
        if ( (frequency == GenerateUSFrequency1 (channelIndex)) || (frequency == GenerateUSFrequency2 (channelIndex)) || (frequency == 0) )
#else
		if ( frequency == GenerateKRFrequency (channelIndex) )
#endif
        {
            loRa.macCommands[loRa.crtMacCmdIndex].channelFrequencyAck = 1;
        }

        if (ValidateDataRange (channelIndex, drRange.value) == OK)
        {
            loRa.macCommands[loRa.crtMacCmdIndex].dataRateRangeAck = 1;
        }
    }

    if ( (loRa.macCommands[loRa.crtMacCmdIndex].channelFrequencyAck == 1) && (loRa.macCommands[loRa.crtMacCmdIndex].dataRateRangeAck == 1) )
    {
        // a frequency value of 0 disables the channel
        if (frequency == 0)
        {
            LORAWAN_SetChannelIdStatus (channelIndex, DISABLED);
        }
        else
        { // change the data rate of the channel
            LORAWAN_SetDataRange (channelIndex, drRange.value);
        }
    }
    return ptr;
}

uint8_t* ExecuteRxParamSetupReq (uint8_t *ptr)
{
    DlSettings_t dlSettings;
    uint32_t frequency = 0;

    //In the status field (response) we have to include the following: channle ACK, RX2 data rate ACK, RX1DoffsetACK

    dlSettings.value = *(ptr++);

    frequency = (*((uint32_t*)ptr)) & 0x00FFFFFF;
    frequency = frequency * 100;
    ptr = ptr + 3; //3 bytes for frequency

    if (ValidateFrequency (frequency) == OK)
    {
        loRa.macCommands[loRa.crtMacCmdIndex].channelAck = 1;
    }
#ifdef REGION_NA
    if (ValidateDataRateReception (dlSettings.bits.rx2DataRate) == OK)
#else
	if (ValidateDataRate (dlSettings.bits.rx2DataRate) == OK)
#endif
    {
        loRa.macCommands[loRa.crtMacCmdIndex].dataRateReceiveWindowAck = 1;
    }

    if (ValidateRxOffset (dlSettings.bits.rx1DROffset) == OK)
    {
        loRa.macCommands[loRa.crtMacCmdIndex].rx1DROffestAck = 1;
    }

    if ( (loRa.macCommands[loRa.crtMacCmdIndex].dataRateReceiveWindowAck == 1) && (loRa.macCommands[loRa.crtMacCmdIndex].channelAck == 1) && (loRa.macCommands[loRa.crtMacCmdIndex].rx1DROffestAck == 1))
    {
        loRa.offset = dlSettings.bits.rx1DROffset;
        UpdateReceiveWindow2Parameters (frequency, dlSettings.bits.rx2DataRate);
        loRa.macStatus.secondReceiveWindowModified = 1;
    }

    return ptr;
}

LorawanError_t SearchAvailableChannel (uint8_t maxChannels, bool transmissionType, uint8_t* channelIndex)
{
    uint8_t randomNumberCopy, randomNumber, i;
    LorawanError_t result = OK;
    uint8_t startingIndex = 0;
#ifdef REGION_NA
    if (maxChannels == 8)
    {
        startingIndex = MAX_US_CHANNELS_BANDWIDTH_125;
    }
#else
	if (transmissionType==0)
	{
		maxChannels = 3;
		startingIndex = KR_DEFAULT_CHANNEL;
	}
#endif
    randomNumber = Random (maxChannels) + 1; //this is a guard so that randomNumber is not 0 and the search will happen
    randomNumberCopy = randomNumber;

    while (randomNumber)
    {
        for (i = startingIndex; (i < (startingIndex + maxChannels)) && (randomNumber != 0) ; i++)
        {
            if ( (loRa.currentDataRate >= Channels[i].dataRange.min) && (loRa.currentDataRate <= Channels[i].dataRange.max) && (Channels[i].status == ENABLED) )
            {
                randomNumber --;
            }
        }

        // if after one searching in all the vector no valid channel was found, exit the loop and return an error
        if ( randomNumber == randomNumberCopy )
        {
            result = NO_CHANNELS_FOUND;
            break;
        }
    }

    if (i != 0)
    {
        *channelIndex = i - 1;
    }
    else
    {
        *channelIndex = maxChannels - 1;
    }
	
	
	/*
	uint8_t test[50];
	const char*
		str_enabled = "ENABLED",
		str_disabled = "DISABLED";
	uint8_t last_index = startingIndex + maxChannels;
	
	for (uint8_t i=startingIndex; i < last_index; i++)
	{
		//char* str_enabled_or_not;
		if (Channels[i].status == ENABLED)
			sprintf(test, "Channels[%d].status: ENABLED", i);
		else
			sprintf(test, "Channels[%d].status: DISABLED", i);
		UART_Put_Line (test);
	}
	sprintf(test, "selected_channel_index: %d", *channelIndex);
	UART_Put_Line (test);
	*/
	
    return result;
}

void UpdateCfList (uint8_t bufferLength, JoinAccept_t *joinAccept)  
{

}

void ConfigureRadio(uint8_t dataRate, uint32_t freq)
{
    RADIO_SetModulation (MODULATION_LORA);
    RADIO_SetChannelFrequency (freq);
    RADIO_SetFrequencyHopPeriod(DISABLED);
    RADIO_SetSpreadingFactor (spreadingFactor[dataRate]);
#ifdef REGION_NA
    RADIO_SetBandwidth (BW_500KHZ);
#else
	RADIO_SetBandwidth (BW_125KHZ);
#endif
    RADIO_SetLoRaSyncWord(loRa.syncWord);     
}

uint32_t GetRx1Freq (void)
{
    uint8_t channelIndex;
#ifdef REGION_NA    
    channelIndex = loRa.lastUsedChannelIndex % 8; //the RX1 receive channel is a function of the upstream channel used to initiate the data exchange
    loRa.receiveWindow1Parameters.frequency = GenerateUSFrequencyReception (channelIndex); // generates a frequency for the US downstream starting at 923.3 MHz and incrementing linearly by 600 kHz to 927.5 MHz
#else
	channelIndex = loRa.lastUsedChannelIndex;
	
	//channelIndex = 5;
	loRa.receiveWindow1Parameters.frequency = GenerateKRFrequency (channelIndex);
	
	
	char result_buffer[50];
	sprintf(result_buffer, "GetRx1Freq: %lld\r\n", loRa.receiveWindow1Parameters.frequency);
	UART_Put_String(result_buffer);
	
#endif    
    return loRa.receiveWindow1Parameters.frequency;
}

void UpdateDLSettings(uint8_t dlRx2Dr, uint8_t dlRx1DrOffset)
{
#ifdef REGION_NA
    if ( (dlRx2Dr >= DR8) && (dlRx2Dr <= DR13) )
#else
	if ( dlRx2Dr <= DR5 )
#endif
    {
        loRa.receiveWindow2Parameters.dataRate = dlRx2Dr;
    }
#ifdef REGION_NA
    if (dlRx1DrOffset <= 3)
#else
	if (dlRx1DrOffset <= 5)
#endif
    {
        // update the offset between the uplink data rate and the downlink data rate used to communicate with the end device on the first reception slot
        loRa.offset = dlRx1DrOffset;  
    } 
}

void StartReTxTimer(void)
{
    
}

LorawanError_t SelectChannelForTransmission (bool transmissionType)  // transmission type is 0 means join request, transmission type is 1 means data message mode
{
    LorawanError_t result = OK;
    uint8_t channelIndex;
    uint32_t frequency;
    uint8_t lastDataRate;

    RADIO_SetLoRaSyncWord(loRa.syncWord);
    lastDataRate = loRa.currentDataRate;
#ifdef REGION_NA
    if (transmissionType == 1) // data message (not join request), it should search in all
    {
        result = SearchAvailableChannel (loRa.maxChannels, transmissionType, &channelIndex);
        RADIO_SetSpreadingFactor (spreadingFactor[loRa.currentDataRate]);

        loRa.receiveWindow1Parameters.dataRate = loRa.currentDataRate + 10 - loRa.offset; // equation according to table 22 - date rate mapping
        if (loRa.receiveWindow1Parameters.dataRate >= 14)
        {
            loRa.receiveWindow1Parameters.dataRate = DR13;
        }

    }
    else   // join request message, first should search between channels 0 - 63 using DR0, then 64 - 71 using DR4, and so on
    {
        if (loRa.lorawanMacStatus.alternativeChannelUs == 0)
        {
            loRa.currentDataRate = DR0; // DR0 is always used for join on 125 khz bandwidth
            result = SearchAvailableChannel (MAX_US_CHANNELS_BANDWIDTH_125, transmissionType, &channelIndex);
            RADIO_SetSpreadingFactor (SF_10); // DR0 is SF10
            loRa.receiveWindow1Parameters.dataRate = DR0 + 10 - loRa.offset;
            RADIO_SetBandwidth (BW_125KHZ);
        }
        else
        {
            loRa.currentDataRate = DR4; // this is a guard for join request, as the 500 kHz channels are only on DR4
            result = SearchAvailableChannel (MAX_US_CHANNELS_BANDWIDTH_500, transmissionType, &channelIndex);
            RADIO_SetSpreadingFactor (SF_8); // JoinReq message - alternatively on a random 125 kHz channel amongst the 64 channels defined using  DR0 and a random 500 kHz channel amongst the 8 channels defined using DR4.
            loRa.receiveWindow1Parameters.dataRate = DR4 + 10 - loRa.offset;
            if (loRa.receiveWindow1Parameters.dataRate >= 14)
            {
                loRa.receiveWindow1Parameters.dataRate = DR13;
            }
            RADIO_SetBandwidth (BW_500KHZ);
        }
        loRa.lorawanMacStatus.alternativeChannelUs = !loRa.lorawanMacStatus.alternativeChannelUs;		
    }
#else
	result = SearchAvailableChannel (loRa.maxChannels, transmissionType, &channelIndex);
	RADIO_SetSpreadingFactor (spreadingFactor[loRa.currentDataRate]);
	if (loRa.currentDataRate > loRa.offset)
	{
		loRa.receiveWindow1Parameters.dataRate = loRa.currentDataRate - loRa.offset;
	}
	else
	{
		loRa.receiveWindow1Parameters.dataRate = DR0;
	}
#endif
    loRa.currentDataRate = lastDataRate;

    if (result == OK)
    {
		#ifdef REGION_NA
        if (channelIndex < MAX_US_CHANNELS_BANDWIDTH_125)
        {
            frequency = GenerateUSFrequency1 (channelIndex);
            RADIO_SetBandwidth (BW_125KHZ);
            RADIO_SetOutputPower (txPower915[loRa.txPower]);
        }
        else
        {
            frequency = GenerateUSFrequency2 (channelIndex);
            RADIO_SetBandwidth (BW_500KHZ);

            //devices, when transmitting with 500 kHz BW may use a maximum of 26 dBm
            if (txPower915[loRa.txPower] <= 26)
            {
                RADIO_SetOutputPower (txPower915[loRa.txPower]);
            }
            else
            {
                RADIO_SetOutputPower (26);
            }
        }
		#else
		frequency = GenerateKRFrequency (channelIndex);
		
		/*
		char result_buffer[50];
		sprintf(result_buffer, "frequency: %lld\r\n", frequency);
		UART_Put_String(result_buffer);
		*/
		
        RADIO_SetBandwidth (BW_125KHZ);
		if ( channelIndex > 5 )
			RADIO_SetOutputPower (txPowerUpper922[loRa.txPower]);
		else
			RADIO_SetOutputPower (txPowerLower922[loRa.txPower]);
		#endif
        RADIO_SetChannelFrequency (frequency);
        RADIO_SetCRC(ENABLED);
        RADIO_SetIQInverted(DISABLED);
        loRa.lastUsedChannelIndex = channelIndex;
    }

    return result;
}

static void CreateAllSoftwareTimers (void)
{
    loRa.joinAccept1TimerId = SwTimerCreate();
    loRa.joinAccept2TimerId = SwTimerCreate();
    loRa.receiveWindow1TimerId = SwTimerCreate();
    loRa.receiveWindow2TimerId = SwTimerCreate();
    loRa.linkCheckTimerId = SwTimerCreate();
    loRa.ackTimeoutTimerId = SwTimerCreate();
    loRa.automaticReplyTimerId = SwTimerCreate();
    loRa.unconfirmedRetransmisionTimerId = SwTimerCreate();
    loRa.abpJoinTimerId = SwTimerCreate();
    loRa.transmissionErrorTimerId = SwTimerCreate();
}

static void SetCallbackSoftwareTimers (void)
{
    SwTimerSetCallback(loRa.joinAccept1TimerId, LORAWAN_ReceiveWindow1Callback, 0);
    SwTimerSetCallback(loRa.joinAccept2TimerId, LORAWAN_ReceiveWindow2Callback, 0);
    SwTimerSetCallback(loRa.linkCheckTimerId, LORAWAN_LinkCheckCallback, 0);
    SwTimerSetCallback(loRa.receiveWindow1TimerId, LORAWAN_ReceiveWindow1Callback, 0);
    SwTimerSetCallback(loRa.receiveWindow2TimerId, LORAWAN_ReceiveWindow2Callback, 0);
    SwTimerSetCallback(loRa.ackTimeoutTimerId, AckRetransmissionCallback, 0);
    SwTimerSetCallback(loRa.automaticReplyTimerId, AutomaticReplyCallback, 0);
    SwTimerSetCallback(loRa.unconfirmedRetransmisionTimerId, UnconfirmedTransmissionCallback, 0);
    SwTimerSetCallback(loRa.abpJoinTimerId, UpdateJoinSuccessState, 0);
    SwTimerSetCallback(loRa.transmissionErrorTimerId, TransmissionErrorCallback, 0);
}

static void StopAllSoftwareTimers (void)
{
    SwTimerStop(loRa.joinAccept1TimerId);
    SwTimerStop(loRa.joinAccept2TimerId);
    SwTimerStop(loRa.linkCheckTimerId);
    SwTimerStop(loRa.receiveWindow1TimerId);
    SwTimerStop(loRa.receiveWindow2TimerId);
    SwTimerStop(loRa.ackTimeoutTimerId);
    SwTimerStop(loRa.automaticReplyTimerId);
    SwTimerStop(loRa.unconfirmedRetransmisionTimerId);
    SwTimerStop(loRa.abpJoinTimerId);
    SwTimerStop(loRa.transmissionErrorTimerId);
}

#ifdef REGION_NA
static void InitDefault915Channels (void)
{
    memset (Channels, 0, sizeof(Channels) );
    memcpy (Channels, DefaultChannels915, sizeof(DefaultChannels915) );
    loRa.maxChannels = MAX_US_CHANNELS;
}
#else
static void InitDefault922Channels (void)
{
    memset (Channels, 0, sizeof(Channels) );
    memcpy (Channels, DefaultChannels922, sizeof(DefaultChannels922) );
    loRa.maxChannels = MAX_KR_CHANNELS;
}
#endif

static void UpdateDataRange (uint8_t channelId, uint8_t dataRangeNew)
{
    Channels[channelId].dataRange.value = dataRangeNew;
}

static void UpdateChannelIdStatus (uint8_t channelId, bool statusNew)
{
    Channels[channelId].status = statusNew;

    // after updating the status of a channel we need to check if the minimum dataRange has changed or not.
    UpdateMinMaxChDataRate ();
    // If the min/max data rate is changed and the current data rate is outside spec, then update the current data rate accordingly
    UpdateCurrentDataRateAfterDataRangeChanges ();
}

static LorawanError_t ValidateRxOffset (uint8_t rxOffset)
{
    LorawanError_t result =  OK;
#ifdef REGION_NA
    if (rxOffset > 3)  //the allowed values for RX1Droffset are in the 0-3 range, values in the range 4-7 are reserved for future use.
#else
	if (rxOffset > 5)  //the allowed values for RX1Droffset are in the 0-5 range, values in the range 6-7 are reserved for future use.
#endif
    {
        result = INVALID_PARAMETER;
    }

    return result;
}

static LorawanError_t ValidateFrequency (uint32_t frequencyNew)
{
    LorawanError_t result = OK;

    // this function is used only for reception frequencies, thus we have to check if the actual frequency is generated acc. to LoRaWAN spec
    //Downstream ? 8 channels numbered 0 to 7 utilizing LoRa 500 kHz BW at DR10 to
    // 14 DR13) starting at 923.3 MHz and incrementing linearly by 600 kHz to 927.5 MHz
#ifdef REGION_NA
    if ( (frequencyNew < FREQ_923300KHZ) || (frequencyNew > FREQ_927500KHZ) ||  ( ( (frequencyNew - FREQ_923300KHZ) % FREQ_600KHZ) != 0) )
#else
	if ( (frequencyNew < FREQ_920900KHZ) || (frequencyNew > FREQ_923300KHZ) ||  ( ( (frequencyNew - FREQ_920900KHZ) % FREQ_200KHZ) != 0) )
#endif
    {
        result = INVALID_PARAMETER ;
    }
    return result;
}

static LorawanError_t ValidateDataRange (uint8_t channelId, uint8_t dataRangeNew)
{
    LorawanError_t result = OK;
    uint8_t dataRateMax, dataRateMin;

    dataRateMin = dataRangeNew & LAST_NIBBLE;
    dataRateMax = (dataRangeNew & FIRST_NIBBLE) >> SHIFT4;
#ifdef REGION_NA
    if ( (ValidateDataRate (dataRateMax) != OK) || (ValidateDataRate (dataRateMin) != OK ) || (dataRateMax < dataRateMin) || 
         ((channelId < MAX_US_CHANNELS_BANDWIDTH_125) && ((dataRateMin == DR4) || (dataRateMax == DR4))) ||
         ((channelId >= MAX_US_CHANNELS_BANDWIDTH_125) && (channelId < MAX_US_CHANNELS) && (dataRateMin != DR4)) || 
         ((channelId >= MAX_US_CHANNELS_BANDWIDTH_125) && (channelId < MAX_US_CHANNELS) && (dataRateMax != DR4)))
#else
	if ( (ValidateDataRate (dataRateMax) != OK) || (ValidateDataRate (dataRateMin) != OK ) || (dataRateMax < dataRateMin) )
#endif        
	{
            result = INVALID_PARAMETER;
       }
    return result;
}

static LorawanError_t ValidateChannelId (uint8_t channelId)  //if allowedForDefaultChannels is 1, all the channels can be modified, if it is 0 channels 0, 1, 2 and 16, 17, and 18 (dual band) cannot be modified
{
    LorawanError_t result = OK;

    if (channelId >= loRa.maxChannels)
    {
        result = INVALID_PARAMETER ;
    }

    return result;
}


#ifdef REGION_NA
static LorawanError_t ValidateChannelMaskCntl (uint8_t channelMaskCntl, uint16_t channelMask)
{
    LorawanError_t result = OK;

    // 5 is RFU for channel mask for US
    if ((channelMaskCntl == 5) || (channelMaskCntl > 7))
    {
        result = INVALID_PARAMETER;
    }

    return result;
}
#else
static LorawanError_t ValidateChannelMaskCntl (uint8_t channelMaskCntl)
{
   LorawanError_t result = OK;

   if ( (channelMaskCntl != 0) && (channelMaskCntl != 6) )
   {
       result = INVALID_PARAMETER;
   }

  return result;
}
#endif




static void EnableChannels (uint16_t channelMask, uint8_t channelMaskCntl)
{
    uint8_t i, channel;

    channel = channelMaskCntl << SHIFT4;

    switch (channelMaskCntl)
    {
        case 0: //US Channels 125 khz are enabled
        case 1:
        case 2:
        case 3:
        case 4:
        {
            EnableChannels2 (channel, channel + 15, channelMask);
        } break;

        case 5:  //RFU, do nothing
        {
        } break;

        case 6: // All 125 kHz ON ChMask applies to channels 65 to 72
        {
            for (i = 0; i <= 63; i++)
            {
                UpdateChannelIdStatus (i, ENABLED);
            }
            EnableChannels2 (64, 71, channelMask);
        } break;

        case 7: //All 125 kHz OFF ChMask applies to channels 65 to 72
        {
            for (i = 0; i <= 63; i++)
            {
                UpdateChannelIdStatus (i, DISABLED);
            }
            EnableChannels2 (64, 71, channelMask);
        } break;
    }
}

static void UpdateCurrentDataRateAfterDataRangeChanges (void)
{
    if (loRa.currentDataRate > loRa.maxDataRate)
    {
        loRa.currentDataRate = loRa.maxDataRate;
    }

    if (loRa.currentDataRate < loRa.minDataRate)
    {
        loRa.currentDataRate = loRa.minDataRate;
    }
}

#ifdef REGION_NA
// Generates a frequency for US upstream, utilizing LoRa 125 kHz BW varying from SF7 to SF10 (DR0..DR3) starting at 902.3 MHz and incrementing linearly by 200 kHz to 914.9 MHz
static uint32_t GenerateUSFrequency1 (uint8_t channelIndex)   // channelIndex should be a random number between 0 and 63, generated with the random function
{
    uint32_t channelFrequency;

    channelFrequency = NA915_UPSTREAM_CH0 + FREQ_200KHZ * channelIndex;
    return channelFrequency;
}

// Generates a frequency for US upstream, utilizing LoRa 500 kHz BW at SF8 (DR4) starting at 903.0 MHz and incrementing linearly by 1.6 MHz to 914.2 MHz
static uint32_t GenerateUSFrequency2 (uint8_t channelIndex)
{
    uint32_t channelFrequency;

    channelFrequency = NA915_UPSTREAM_CH64 + FREQ_1600KHZ * (channelIndex - MAX_US_CHANNELS_BANDWIDTH_125);
    return channelFrequency;
}

static uint32_t GenerateUSFrequencyReception (uint8_t channelIndex)
{
    uint32_t channelFrequency;
    
    channelFrequency = NA915_DOWNSTREAM_CH0 + FREQ_600KHZ * channelIndex;
    return channelFrequency;
}
#else
static uint32_t GenerateKRFrequency (uint8_t channelIndex)   // channelIndex should be a random number between 0 and 63, generated with the random function
{
    uint32_t channelFrequency;
    channelFrequency = KR922_CH0_FREQ + FREQ_200KHZ * channelIndex;
    return channelFrequency;
}
#endif

static void EnableChannels2 (uint8_t startIndex, uint8_t endIndex, uint16_t channelMask)
{
    uint8_t i;

    for (i = startIndex; i <= endIndex; i++)
    {
        if ((channelMask & 0x0001) == 0x0001)
        {
             UpdateChannelIdStatus (i, ENABLED);
        }
        else
        {
            UpdateChannelIdStatus (i, DISABLED);
        }
        channelMask = channelMask >> SHIFT1;
    }
}
#ifdef REGION_NA
static LorawanError_t ValidateDataRateReception (uint8_t dataRate)
{
    LorawanError_t result = OK;

    if  ( (dataRate > DR13) || (dataRate < DR8) )
    {
        result = INVALID_PARAMETER;
    }

    return result;
}
#endif
static void Retransmissions (void)
{
    if (loRa.lorawanMacStatus.ackRequiredFromNextDownlinkMessage == ENABLED) // if last uplink packet was confirmed, we have to send this packet by the number indicated by NbRepConfFrames
    {
        if (loRa.counterRepetitionsConfirmedUplink <= loRa.maxRepetitionsConfirmedUplink)
        {
            UpdateRetransmissionAckTimeoutState ();
        }
        else
        {
            ResetParametersForConfirmedTransmission ();
            if (rxPayload.RxAppData != NULL)
            {
                rxPayload.RxAppData (NULL, 0, MAC_NOT_OK);
            }
        }
    }

    else
    {
        if (loRa.counterRepetitionsUnconfirmedUplink <= loRa.maxRepetitionsUnconfirmedUplink)
        {
        loRa.macStatus.macState = RETRANSMISSION_DELAY;

            if ( (SelectChannelForTransmission (1) == OK) )
            {
				//UART_Put_Line ("lorawan_na.c 1206 Retransmissions");
                if (RADIO_Transmit (&macBuffer[16], loRa.lastPacketLength) == OK)
                {
                    loRa.counterRepetitionsUnconfirmedUplink ++ ; //for each retransmission, the counter increments
                }
                else
                {
                    loRa.macStatus.macState = RETRANSMISSION_DELAY;
                    SwTimerSetTimeout(loRa.transmissionErrorTimerId, MS_TO_TICKS (2000UL));
                    SwTimerStart(loRa.transmissionErrorTimerId);     
                }
            }

            else
            // if no channels were found, then no more retransmissions will occur for this packet
            {
                ResetParametersForUnconfirmedTransmission ();
                if (rxPayload.RxAppData != NULL)
                {
                    rxPayload.RxAppData(NULL, 0, MAC_OK);  // inform the application layer that retransmissions have stopped
                }
            }
        }
        else
        {
            ResetParametersForUnconfirmedTransmission ();
            if (rxPayload.RxAppData != NULL)
            {
                rxPayload.RxAppData(NULL, 0, MAC_OK);  // inform the application layer that retransmissions have stopped
            }
        }
    }
}
 
static void TransmissionErrorCallback (uint8_t param)
{
    if ( (SelectChannelForTransmission (1) == OK) )
    {
        if (RADIO_Transmit (&macBuffer[16], loRa.lastPacketLength) == OK)
        {
            loRa.counterRepetitionsUnconfirmedUplink ++ ; //for each retransmission, the counter increments
        }
        else
        {
            loRa.macStatus.macState = RETRANSMISSION_DELAY;
            SwTimerSetTimeout(loRa.transmissionErrorTimerId, MS_TO_TICKS (2000UL));
            SwTimerStart(loRa.transmissionErrorTimerId);     
        }
    }

    else
    // if no channels were found, then no more retransmissions will occur for this packet
    {
        ResetParametersForUnconfirmedTransmission ();
        if (rxPayload.RxAppData != NULL)
        {
            rxPayload.RxAppData(NULL, 0, MAC_OK);  // inform the application layer that retransmissions have stopped
        }
    }
}

