# MinigameStudy
2학년 1학기 게임프로그래밍 수업 미니게임

***

## Color Shooter

![image](https://user-images.githubusercontent.com/64309516/131824867-35daa6d2-7fc9-403f-a9dc-1920ab6f6b22.png)

[기획 PPT 링크](https://docs.google.com/presentation/d/1z0kYO1fVlEHQ4A2nHjZTZOtBh9jBAEY04vx-BPuNoUE/edit?usp=sharing)

### 게임 설명

게임 우측 UI의 적과 아군 색상을 보고 판단하며 플레이<br/>
게임창 아래의 벽인 ☆이 적이 닿으면 파괴함<br/>
벽이 없는 곳에 적군이 넘어갈 시 HP 줄어들고, 아군에 닿으면 수리됨<br/>
아군을 죽일 시 HP 줄어듬<br/>
아군을 죽이지말고 적군을 죽여 최대 스코어를 넘겨보자~~

### 객체 설명
+ ▼: 유닛(적또는 아군 *색으로 구분)<br/>
	+ 유닛의 위치, 적, 아군 판단 변수, 움직임 구현<br/>
+ ▲: 플레이어<br/>
	+ 플레이어의 위치, 이동 구현<br/>
+ ☆: 총알(플레이어)<br/>
	+ 플레이어가 발사하는 총알 유닛과 같은 객체지만 변수로 다르게 움직임<br/>
+ GameManager: 게임메니져<br/>
	+ 게임의 UI, 맵 들을 그려주고, hp, score, highScore같은 변수와 게임의 거의 모든 시스템을 구현<br/>

***
