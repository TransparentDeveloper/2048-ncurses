# 2048-ncurses
 이탈리아의 웹 개발자 Gabriele Cirulli이 javascript와 css를 이용해 개발한 블록 퍼즐 게임 <2048> 이라는 게임을 c를 이용해 콘솔 환경에서 구현했습니다.

## 프로젝트 설명
_* 광운대학교 2022년 2학기 <자료구조실습> 교과목의 프로젝트 결과물입니다._

 - 제안서: [제안서.pdf](https://github.com/TransparentDeveloper/2048-ncurses/files/11185636/default.pdf)
 - 최종보고서: [최종보고서.pdf](https://github.com/TransparentDeveloper/2048-ncurses/files/11185635/default.pdf)

## 게임 규칙
이 게임은 4x4 보드 판 위에 놓인 블록들을 이동시켜 같은 값을 가진 블록들을 합치고, 최종적으로 2048 값을 만들어내는 게임입니다. 사용자는 [‘w’,’a’,’s’,’d’]의 입력을 통해 블록들을 위, 아래, 좌측, 우측 방향으로 이동시킬 수 있습니다. 게임은 한 번의 입력에 따라 블록들이 모두 같은 방향으로 이동되며, 빈 칸에는 각 term마다 무작위로 2 또는 4의 값을 가진 블록이 생성됩니다.

같은 값을 가진 블록들이 만나면 두 블록은 소멸되고 새로운 블록이 생성됩니다. 이 새로운 블록은 이전에 소멸된 블록 중 입력 방향에 끝에 있던 블록의 위치에서 생성됩니다. 게임은 Undo 기능을 제공하여 이전 term으로 되돌아갈 수 있습니다. 이를 통해 사용자는 잘못된 판단으로 인해 게임이 끝나는 것을 미리 방지할 수 있습니다. 

## 주요 기능
- 파일 입출력
게임 실행 시, 역대 가장 높은 점수를 파일에 저장하고 게임 진행마다 최신화하여 출력합니다.

- Stack(자료구조)
undo 기능 실행 시, 이전 term의 블록 배치를 복구하기 위해 스택 구조를 활용하였습니다. 각 term마다 블록의 값, 위치, 점수에 대한 정보를 저장하고, 블록의 움직임이 확정되면, 해당 정보를 스택에 쌓습니다. 반대로 undo 기능을 실행하면, 현재 term이 1이 아닌 경우에만 그 값을 출력하고 스택에서 제거합니다.

## 실행화면
- In Game
<div align="center">
<img width="300" height="300" alt="스크린샷 2023-04-09 오후 11 33 30" src="https://user-images.githubusercontent.com/50646145/230779217-2b2a9719-1414-4ad5-b193-ff2fd84aa794.png">
<img width="300" height="300" alt="스크린샷 2023-04-09 오후 11 37 17" src="https://user-images.githubusercontent.com/50646145/230779238-176f4a24-575f-4d53-bbb1-a2160291f8b8.png">
<img width="300" height="300" alt="스크린샷 2023-04-09 오후 11 37 31" src="https://user-images.githubusercontent.com/50646145/230779253-1c2d575a-5481-4fd1-b6f1-02137ab4b310.png">
 </div>

- Game Over
<div align="center">
<img width="300" height="300" alt="스크린샷 2023-04-09 오후 11 34 54" src="https://user-images.githubusercontent.com/50646145/230779227-ee2148aa-7783-4a78-893f-ed7ad35e0cb6.png">
</div>

- Update records
<div align="center">
<img width="300" height="300" alt="스크린샷 2023-04-09 오후 11 37 57" src="https://user-images.githubusercontent.com/50646145/230779270-ba6b5281-bf84-443b-b0ef-3805ddff01c8.png">
</div>


## 라이선스
본 프로그램은 MIT 라이선스를 따릅니다. 자세한 내용은 LICENSE 파일을 참고해주세요.

## 기여하기
개선하고 싶은 부분이 있다면 Pull Request를 날려주시거나 Issue를 등록해주세요!
