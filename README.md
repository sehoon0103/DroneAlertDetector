# DroneAlertDetector (RTOS STM32 Emergency Alert)

RTOS(uC/OS-II) 기반 STM32 키트에서 가변저항(고도 모사) 입력을 실시간 모니터링하여
임계값 이하 시 LED/BUZZER 경고 + GLCD 상태 표시, 스위치/통신으로 해제·초기화가 가능한
실시간 비상 알림 시스템입니다.

---

## 프로젝트 요약

| 항목 | 내용 |
|---|---|
| 인원 / 역할 | 3명 / 팀 리더(총괄), 전체 코드 기반 작성 및 보고서 작성 |
| 핵심 키워드 | uC/OS-II, Task 설계, MBox, Semaphore, ADC, GLCD, UART, SysTick |
| 동작 개념 | NORMAL/WARNING/DANGER/MUTE 상태 기반 제어(표시/경고/해제) |

---

## 시스템 구성

- 입력
  - 가변저항(ADC): 고도 값 모사
  - 스위치: 경고 해제/상태 제어
  - UART: 문자 수신/표시, 특정 입력('!')로 초기화
- 출력
  - GLCD: 상태/값 표시
  - LED: 상태별 점등
  - BUZZER: DANGER 구간 경고음

---

## RTOS 설계 (Task / 동기화)

- Task 분할: Start Task + Task1~Task5 형태로 역할 분리
- Task 간 통신: MBox로 데이터 전달
- 동기화: GLCD 접근은 Semaphore(GLcdSem)로 보호(동시 접근 충돌 방지)

---

## 상태(State) / 동작 요약

- NORMAL: 정상 표시
- WARNING: 경고 표시(조건 만족 시)
- DANGER: 위험 경고(LED/BUZZER 활성)
- MUTE: 경고 해제(스위치 또는 조건에 따른 상태 제어)

> 상태 전환 기준(임계값/구간)은 보고서의 시험 케이스 기준으로 구현되었습니다.

---

## 검증(시험 케이스)

- VR(가변저항) 값 구간에 따라 NORMAL/WARNING/DANGER 표시 확인
- DANGER 구간에서 BUZZER 울림 확인
- 스위치 입력으로 Warning Off / 상태 제어 확인
- UART 문자 수신/표시 및 '!' 입력 시 초기화 동작 확인

---

## Demo / Evidence

- 보고서에 보드 실물 동작 사진(케이스별) 및 구조도/흐름도 포함
- (추가 예정) 시연 영상/사진 링크

---

## References (근거/검증용)

- Final Report (PDF): (레포에 PDF가 있으면 링크 추가)
- 핵심 키워드/구조 근거:
  - uC/OS-II 초기화/시작(OSInit/OSStart), Task 생성, SysTick 1ms
  - ADC 기반 입력, GLCD 표시, UART 통신, MBox, GLCD Semaphore
