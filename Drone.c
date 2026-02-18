#include <includes.h>  // 프로젝트에 필요한 모든 헤더 파일 포함

/*
*********************************************************************************************************
*                                             DEFINES
*********************************************************************************************************
*/
#define     TASK_STK_SIZE      OS_TASK_DEF_STK_SIZE   // 각 작업(Task)의 스택 크기를 설정
#define     N_TASKS             5                    // 생성할 작업 수

#define     TASK_START_ID       0                     // 시작 작업(TaskStart)의 ID
#define     TASK_1_ID           1                     // 작업 1(Task1)의 ID
#define     TASK_2_ID           2                     // 작업 2(Task2)의 ID
#define     TASK_3_ID           3                     // 작업 3(Task3)의 ID
#define     TASK_4_ID           4                     // 작업 4(Task4)의 ID
#define     TASK_5_ID           5                     // 작업 5(Task5)의 ID

#define     TASK_START_PRIO    10                     // 시작 작업(TaskStart)의 우선순위
#define     TASK_1_PRIO        11                     // 작업 1(Task1)의 우선순위
#define     TASK_2_PRIO        12                     // 작업 2(Task2)의 우선순위
#define     TASK_3_PRIO        13                     // 작업 3(Task3)의 우선순위
#define     TASK_4_PRIO        14                     // 작업 4(Task4)의 우선순위
#define     TASK_5_PRIO        15                     // 작업 5(Task5)의 우선순위

/*
*********************************************************************************************************
*                                             DATA TYPES
*********************************************************************************************************
*/
typedef struct {                                      // 각 작업의 데이터를 저장하기 위한 구조체
   char    TaskName[30];                             // 작업의 이름
   INT16U  TaskCtr;                                  // 작업 실행 횟수
   INT16U  TaskExecTime;                             // 작업 실행 시간
   INT32U  TaskTotExecTime;                          // 작업 총 실행 시간
} TASK_USER_DATA;                                     // 데이터 타입 이름을 `TASK_USER_DATA`로 정의

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/
OS_STK   TaskStartStk[TASK_STK_SIZE];                // TaskStart 작업의 스택
OS_STK   Task1Stk[TASK_STK_SIZE];                   // Task1 작업의 스택
OS_STK   Task2Stk[TASK_STK_SIZE];                   // Task2 작업의 스택
OS_STK   Task3Stk[TASK_STK_SIZE];                   // Task3 작업의 스택
OS_STK   Task4Stk[TASK_STK_SIZE];                   // Task4 작업의 스택
OS_STK   Task5Stk[TASK_STK_SIZE];                   // Task5 작업의 스택

OS_EVENT   *Sync;                                    // 작업 간 동기화를 위한 세마포어
OS_EVENT   *GLcdSem;                                 // GLCD(그래픽 LCD) 접근을 위한 세마포어
OS_EVENT   *TxMbox;                                  // Task1에서 Task2로 메시지 전달하는 메일박스
OS_EVENT   *Tx1Mbox;                                 // Task2에서 Task3로 메시지 전달하는 메일박스
OS_EVENT   *Tx2Mbox;                                 // Task3에서 Task4로 메시지 전달하는 메일박스
OS_EVENT   *Tx3Mbox;                                 // Task4에서 Task5로 메시지 전달하는 메일박스
OS_EVENT   *Tx4Mbox;                                 // Task5에서 Task1로 메시지 전달하는 메일박스

extern __IO uint16_t ADCConvertedValue[5];           // 가변저항 값 저장 배열

/*
위 변수들은 작업(Task) 간의 통신 및 동기화를 지원하며, 작업의 상태를 관리하기 위해 사용됩니다.
*/
void  TaskStart(void *data);               // TaskStart 작업의 함수 원형 선언. 초기 작업을 정의.
void  Task1(void *data);                  // Task1 작업의 함수 원형 선언. 작업 1의 동작 정의.
void  Task2(void *data);                  // Task2 작업의 함수 원형 선언. 작업 2의 동작 정의.
void  Task3(void *data);                  // Task3 작업의 함수 원형 선언. 작업 3의 동작 정의.
void  Task4(void *data);                  // Task4 작업의 함수 원형 선언. 작업 4의 동작 정의.
void  Task5(void *data);                  // Task5 작업의 함수 원형 선언. 작업 5의 동작 정의.
void   Delay(void);                        // Delay 함수의 원형 선언. 일정 시간 대기 기능을 제공.
int buzzer_state = 1;                      // 버저의 상태를 나타내는 변수. 초기값 1로 설정.
int led_state = 1;                         // LED의 상태를 나타내는 변수. 초기값 1로 설정.


/*
*********************************************************************************************************
*                                               MAIN
*********************************************************************************************************
*/
int main(void)
{
   INT8U  os_err = 0;                                // OS 함수 호출 오류 저장 변수

   os_err = os_err;                                  // 경고 방지 코드
   BSP_Init();                                       // 보드 초기화

   // GLCD 초기화
   DelayMS(300);                                    // 안정화 시간 제공
   GLCD_init();                                      // GLCD 초기화
   GLCD_clear();                                     // GLCD 화면 초기화
   GLCD_xy(0, 0); printf(" THE FINAL ");            // GLCD 첫 줄 출력
   GLCD_xy(1, 16); printf("Time                      "); // 2번째 줄 출력

   TxMbox = OSMboxCreate((void *)0);                 // 작업 간 메시지 교환을 위한 메일박스 생성

   LCD_initialize();                                 // 문자형 LCD 초기화
   
   LCD_string(0x80, (uint8_t *)"Low-altitude");   
   LCD_string(0xC0, (uint8_t *)"Drone Alert Sys");   // 저고도 측정 드론 비상 알림 시스템

   OSInit();                                         // uC/OS-II 운영체제 초기화
   KeyInit();                                        // 키 입력 초기화

   os_err = OSTaskCreate(TaskStart, (void *)0, (void *)&TaskStartStk[TASK_STK_SIZE - 1], 0); // TaskStart 생성
   OSStart();                                        // 다중 작업 스케줄링 시작

   return 0;                                         // 메인 종료
}

void TaskStart (void *pdata)                  // TaskStart 함수 정의. 시스템 초기화와 여러 작업 생성 담당.
{
   OS_CPU_SR cpu_sr;                          // CPU 상태 레지스터를 저장하기 위한 변수 선언.
   pdata = pdata;                            // 전달된 매개변수 pdata 사용 방지 경고 제거.

   OS_ENTER_CRITICAL();                      // 임계 영역 진입. 인터럽트를 비활성화하여 동기화 작업 수행.
   SysTick_Configuration();                  // SysTick 타이머를 1ms 단위로 설정하여 주기적인 인터럽트 발생.
   OS_EXIT_CRITICAL();                       // 임계 영역 종료. 인터럽트를 다시 활성화.

   OSStatInit();                             // 운영체제 상태 통계 정보 초기화 함수 호출.
   Sync = OSSemCreate(0);                    // 세마포어 생성. 초기 값 0. 작업 간 동기화를 위해 사용.
   GLcdSem = OSSemCreate(1);                 // 세마포어 생성. 초기 값 1. GLCD 접근 동기화를 위해 사용.
   CommInit();                               // 통신 초기화 함수 호출. 시리얼 통신 등 하드웨어 설정 수행.
   
   OSTaskCreate(Task1, (void *)0, (void *)&Task1Stk[TASK_STK_SIZE - 1], TASK_1_PRIO);
   // Task1 작업 생성. 스택은 Task1Stk 사용, 우선순위 TASK_1_PRIO(11).
   OSTaskCreate(Task2, (void *)0, (void *)&Task2Stk[TASK_STK_SIZE - 1], TASK_2_PRIO);
   // Task2 작업 생성. 스택은 Task2Stk 사용, 우선순위 TASK_2_PRIO(12).
   OSTaskCreate(Task3, (void *)0, (void *)&Task3Stk[TASK_STK_SIZE - 1], TASK_3_PRIO);
   // Task3 작업 생성. 스택은 Task3Stk 사용, 우선순위 TASK_3_PRIO(13).
   OSTaskCreate(Task4, (void *)0, (void *)&Task4Stk[TASK_STK_SIZE - 1], TASK_4_PRIO);
   // Task4 작업 생성. 스택은 Task4Stk 사용, 우선순위 TASK_4_PRIO(14).
   OSTaskCreate(Task5, (void *)0, (void *)&Task5Stk[TASK_STK_SIZE - 1], TASK_5_PRIO);
   // Task5 작업 생성. 스택은 Task5Stk 사용, 우선순위 TASK_5_PRIO(15).

   for (;;) {                                 // 무한 루프 시작. TaskStart 작업은 종료되지 않음.
      OSCtxSwCtr = 0;                       // 작업 전환 카운터 초기화. 1초 동안의 작업 전환 횟수를 계산.
      OSTimeDlyHMSM(0, 0, 1, 0);            // 1초 대기. 작업 전환 및 다른 작업 실행을 허용.
   }
}

/*
*********************************************************************************************************
*                                               TASK 1
*********************************************************************************************************
*/
void Task1(void *data)                              // Task1: 고도 값 기준 경고 상태 판별(normal)
{
   INT8U err;                                       // OS 에러 코드 저장 변수
   int32_t count = 0;                               // 카운터 변수 초기화
   data = data;                                     // 매개변수 사용 방지 경고 제거
   int *rxmsg;                                      // 메일박스 수신 메시지 포인터
   int txmsg;                                       // 메일박스 송신 데이터(카운터 값)

   for (;;) {
      rxmsg = (int *)OSMboxPend(TxMbox, 0, &err);   // Task1에서 메시지 수신
      OSSemPend(GLcdSem, 0, &err);                  // GLCD 세마포어 획득
      GLCD_xy(2, 6); printf("%4d m", ADCConvertedValue[2]);  // 고도 값 표시 (가변저항 값 사용)
      GLCD_xy(2, 12); printf("%8d", count++);        // 카운터 값 표시

      if (count > 9999) count = 0;                  // 카운터가 9999 초과하면 초기화

      if (ADCConvertedValue[2] > 2000)             // 고도가 임계값 이상일 경우
         LED_ON(1);                                 // LED1 켜기
      else 
         LED_OFF(1);                                // LED1 끄기
      
      uint32_t sum = ADCConvertedValue[2] + ADCConvertedValue[3]; // 두 가변저항(ADC) 합산 값 계산
        if (sum >= 0 && sum < 4000) {               // 합산 값이 NORMAL 범위인지 확인
            GLCD_xy(4, 6); printf("NORMAL  ");      // GLCD에 NORMAL 상태 출력
        }
      OSSemPost(GLcdSem);                           // GLCD 세마포어 반환
      
      txmsg = count;                                // 현재 카운터 값을 보냄
      OSMboxPost(Tx1Mbox, (void*)&txmsg);          // Task2로 메시지 전달
      OSTimeDlyHMSM(0, 0, 0, 100);                  // 100ms 대기
   }
}

/*
*********************************************************************************************************
*                                               TASK 2
*********************************************************************************************************
*/
void Task2(void *data)                              // Task2: 고도 값 기준 경고 상태 판별(warning)
{
   int *rxmsg;                                      // Task1에서 전달된 메시지 수신 포인터
   INT8U err;                                       // OS 에러 코드 저장 변수
   int32_t count = 0;                               // Task2 카운터(표시/전달용)
   data = data;                                     // 매개변수 사용 방지 경고 제거

   for (;;) {
      rxmsg = (int *)OSMboxPend(Tx1Mbox, 0, &err);  // Task1에서 메시지 수신
      OSSemPend(GLcdSem, 0, &err);                  // GLCD 세마포어 획득
      GLCD_xy(3, 6); printf("%4d m", ADCConvertedValue[3]);  // 고도 값 표시 (가변저항 값 사용)
      GLCD_xy(3, 12); printf("%8d", count++);        // 카운터 값 표시
      

      if (count > 9999) count = 0;                  // 카운터 오버플로 방지(9999 초과 시 초기화)

      // 고도 상태 판별 
      uint32_t sum = ADCConvertedValue[2] + ADCConvertedValue[3]; // 두 가변저항(ADC) 합산 값 계산
            if (sum >= 4000 && sum < 6000) {         // 합산 값이 WARNING 범위인지 확인
                GLCD_xy(4, 6); printf("WARNING ");   // GLCD에 WARNING 상태 출력
                LED_ON(2);                           // LED2 켜기
            }
            else if(sum > 1 && sum < 4000 )          // 합산 값이 NORMAL 범위로 내려왔는지 확인
                LED_OFF(2);                                // LED1 끄기
                                         
      OSSemPost(GLcdSem);                           // GLCD 세마포어 반환


      OSMboxPost(Tx2Mbox, (void *)&count);          // Task3로 메시지 전달
      OSTimeDlyHMSM(0, 0, 0, 200);                    // 200ms 대기
   }
}

/*
*********************************************************************************************************
*                                               TASK 3
*********************************************************************************************************
*/
void Task3(void *data)                              // Task3: 고도 값 기준 경고 상태 판별(danger)
{
   INT8U err;                                       // OS 에러 코드 저장 변수
   int count = 0;                                   // Task4로 전달할 데이터(현재는 0 고정)
   data = data;                                     // 매개변수 사용 방지 경고 제거

   for (;;) {
      uint32_t sum = ADCConvertedValue[2] + ADCConvertedValue[3]; // 두 가변저항(ADC) 합산 값 계산
      // 고도 상태에 따라 경고를 시각적 및 청각적으로 제공
      if (sum >= 6000 && sum < 8000) {              // 합산 값이 DANGER 범위인지 확인
         LED_ON(3);  // LED3 켜기
         OSSemPend(GLcdSem, 0, &err);                  // GLCD 세마포어 획득
         GLCD_xy(4, 6); printf("DANGER ");            // GLCD에 DANGER 상태 출력
         OSSemPost(GLcdSem);                           // GLCD 세마포어 반환
         GPIO_SetBits(GPIOD, GPIO_Pin_15);  // 부저 켜기
         OSTimeDlyHMSM(0, 0, 0, 500);     // 500ms 동안 부저 울림
         GPIO_ResetBits(GPIOD, GPIO_Pin_15);  // 부저 끄기
      } else {
         LED_OFF(3);  // LED3 끄기
         GLCD_xy(4, 6); printf("WARNING ");           // GLCD에 WARNING 상태 출력
      }

      OSMboxPost(Tx3Mbox, (void *)&count);  // Task4로 메시지 전달
      OSTimeDlyHMSM(0, 0, 0, 400);        // 400ms 대기
   }
}

/*
*********************************************************************************************************
*                                               TASK 4
*********************************************************************************************************
*/
void Task4(void *data)                              // Task4: 사용자 입력에 따른 경고 해제 및 초기화
{
   INT8U err;                                       // OS 에러 코드 저장 변수
   int *rxmsg;                                      // Task3에서 전달된 메시지 수신 포인터
   data = data;                                     // 매개변수 사용 방지 경고 제거

   for (;;) {
      rxmsg = (int *)OSMboxPend(Tx3Mbox, 0, &err); // Task3에서 메시지 수신

      // 사용자 스위치 입력 처리 (예: 경고 해제)
      if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) == 0) {
         LED_OFF(1);  // LED1 끄기
         LED_OFF(2);  // LED2 끄기
         LED_OFF(3);  // LED3 끄기
         GPIO_ResetBits(GPIOD, GPIO_Pin_15);  // 부저 끄기
         OSSemPend(GLcdSem, 0, &err);                  // GLCD 세마포어 획득
         GLCD_xy(5, 6); printf("Warning Off"); // GLCD에 "Warning Off" 메시지 출력
         OSSemPost(GLcdSem);                    // GLCD 세마포어 반환
      }

      OSMboxPost(Tx4Mbox, (void *)&rxmsg);  // Task5로 메시지 전달
      OSTimeDlyHMSM(0, 0, 0, 100);         // 100ms 대기
   }
}

/*
*********************************************************************************************************
*                                               TASK 5
*********************************************************************************************************
*/
void Task5(void *data)                              // Task5: UART 통신 및 시스템 초기화
{
   INT8U err;                                       // OS 에러 코드 저장 변수
   int *rxmsg;                                      // Task4에서 전달된 메시지 수신 포인터
   int c;                                           // UART 수신 문자 저장 변수
   data = data;                                     // 매개변수 사용 방지 경고 제거

   for (;;) {
      rxmsg = (int *)OSMboxPend(Tx4Mbox, 0, &err);  // Task4에서 메시지 수신
      OSSemPend(GLcdSem, 0, &err);          // // GLCD 세마포어 획득
      c = CommGetChar(COMM1, 20, &err);  // UART에서 문자 수신
      if (err == COMM_NO_ERR) {                    // 정상 수신 시에만 처리
         CommPutChar(COMM1, c, 100);  // Echo 기능: 수신된 문자 
         GLCD_xy(6, 4); printf("Received: %c", c);  // GLCD에 수신 문자 표시
         OSTimeDlyHMSM(0, 0, 3, 0);         // 100ms 대기
         GLCD_xy(6, 4); printf("                      "); // 수신_
