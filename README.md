[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mgMZ6iar)
## 📌 개요
- 예외 처리 구문을 직접 작성해 봅니다. 
- Sington 패턴을 이용하여 게임 로깅 기능을 추가합니다.

---

## 1️⃣ 예외처리 

### 수정할 클래스 (character.h)
1. Staff 생성자
  - character가 Wizard가 아닌 경우, invalid_argument 예외를 발생시킵니다.
  - 예외 메시지: "Staff requires Wizard"

2. Bow 생성자
  - character가 Archer나 Knight가 아닌 경우, invalid_argument 예외를 발생시킵니다. 
  - 예외 메시지: "Bow requires Archer or Knight" 
---

### 수정할 함수 (main.cpp)
1. `equip_test1`, `equip_test2`, `equip_test3` 함수
  - try/catch 문을 이용해 예외를 처리합니다. 
  - 예외 처리시 출력 형식: "Invalid equip: <예외 메시지>"


### 예상 출력
```
-------------------------------------------------------------
Knight + Armor + Boots + Sword | Attack: 25 | Speed: 11 | Defense: 30
Knight + Armor + Bow | Attack: 22 | Speed: 8 | Defense: 30
Invalid equip: Staff requires Wizard
-------------------------------------------------------------
Wizard + Armor + Boots + Sword | Attack: 30 | Speed: 13 | Defense: 20
Invalid equip: Bow requires Archer or Knight
Wizard + Boots + Staff | Attack: 28 | Speed: 15 | Defense: 10
-------------------------------------------------------------
Archer + Armor + Boots + Sword | Attack: 28 | Speed: 18 | Defense: 18
Archer + Armor + Bow | Attack: 25 | Speed: 15 | Defense: 18
Invalid equip: Staff requires Wizard
-------------------------------------------------------------
Delete Character: Knight
Delete Character: Wizard
Delete Character: Archer
```

---


## 2️⃣ Sington 패턴 구현 

Logger 클래스를 구현하여 게임 이벤트를 파일에 기록합니다.

### 구현할 코드 (logger.h)
1. 생성자
   - Test/output2.txt 파일을 std::ios::trunc 모드로 오픈합니다.
   - 초기화 메시지: "[Init] Logger started."

2. 소멸자
   - 종료 메시지 기록 후 파일을 닫습니다.
   - 종료 메시지: "[Shutdown] Logger closed." 

3. getInstance() 메소드 (static 메소드)
   - 최초 호출시 Logger 생성자를 이용해 instance를 생성합니다. 
   - init_mtx를 이용해 초기화 과정을 동기화 합니다.  
   - 이후 호출에서는 기존 인스턴스를 반환합니다.  

4. log(const std::string& message) 메소드
   - 로그 메시지를 파일에 기록합니다.
   - write_mtx를 이용해 쓰기 과정을 동기화 합니다. 

### 클래스 수정 (character.h)
1.  Knight/Wizard/Archer 생성자
   - 로그 메시지 "[Create] <캐릭터>"를 로그 파일에 기록합니다.

2. EquipDeco 생성자
   - 로그 메시지 "[Trying to Equip] <장비명>"을 로그 파일에 기록합니다.

### 수정할 함수 (main.cpp)
1. `equip_test1`, `equip_test2`, `equip_test3` 함수
  - try/catch 문을 이용해 예외를 처리합니다.
  - 예외 처리시 출력 형식: "Invalid equip: <예외 메시지>"   
  - 로그 메시지 `[Fail to Equip]`를 로그 파일에 기록합니다.


### 예상 출력(Test\output2.txt)
```
[Init] Logger started.
[Create] Knight
[Create] Wizard
[Create] Archer
[Trying to Equip] Knight + Armor
[Trying to Equip] Knight + Armor + Boots
[Trying to Equip] Knight + Armor + Boots + Sword
[Trying to Equip] Knight + Armor
[Trying to Equip] Knight + Armor + Bow
[Trying to Equip] Knight + Boots
[Trying to Equip] Knight + Boots + Staff
[Fail to Equip] 
[Trying to Equip] Wizard + Armor
[Trying to Equip] Wizard + Armor + Boots
[Trying to Equip] Wizard + Armor + Boots + Sword
[Trying to Equip] Wizard + Armor
[Trying to Equip] Wizard + Armor + Bow
[Fail to Equip] 
[Trying to Equip] Wizard + Boots
[Trying to Equip] Wizard + Boots + Staff
[Trying to Equip] Archer + Armor
[Trying to Equip] Archer + Armor + Boots
[Trying to Equip] Archer + Armor + Boots + Sword
[Trying to Equip] Archer + Armor
[Trying to Equip] Archer + Armor + Bow
[Trying to Equip] Archer + Boots
[Trying to Equip] Archer + Boots + Staff
[Fail to Equip] 
[Shutdown] Logger closed.
```

---

## 💡 생각해 보기
- unique_ptr가 아닌 일반 포인터로 instance 정의할 경우, 실행결과가 어떻게 달라질까요? 


## 🧪 테스트 방법

모든 함수 구현 후, 아래 명령어를 통해 테스트를 실행하세요:

Windows:
```bash
./test12.bat
```
MacOS/Linux:
```bash
/bin/bash test12.sh
```
