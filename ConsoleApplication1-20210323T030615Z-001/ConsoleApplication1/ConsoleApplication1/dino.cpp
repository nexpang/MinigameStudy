#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define DINO_BOTTOM_Y   12
#define TREE_BOTTOM_X   45
#define TREE_BOTTOM_Y   20

#define BIRD_BOTTOM_X   45
#define BIRD_BOTTOM_Y   9

void gotoXY(int x, int y)
{
    HANDLE hOut;
    COORD Cur;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Cur.X = x * 2;
    Cur.Y = y;
    SetConsoleCursorPosition(hOut, Cur);
}

void clrscr()
{
    system("cls");
}

bool legFlag;

void setConsleView() {
    system("mode con:cols=100 lines=25");
    system("title 공룡 게임");
}

void drawScore(int score)
{
    gotoXY(43, 1);
    cout << "SCORE : " << score;

    gotoXY(43, 3);
    cout << "Q : 종료";
}

void drawDino(int dinoY)
{
    gotoXY(0, dinoY);
    cout << "        $$$$$$$ " << endl;
    cout << "       $$ $$$$$$" << endl;
    cout << "       $$$$$$$$$" << endl;
    cout << "$      $$$      " << endl;
    cout << "$$     $$$$$$$  " << endl;
    cout << "$$$   $$$$$     " << endl;
    cout << " $$  $$$$$$$$$$ " << endl;
    cout << " $$$$$$$$$$$    " << endl;
    cout << "  $$$$$$$$$$    " << endl;
    cout << "    $$$$$$$$    " << endl;
    cout << "     $$$$$$     " << endl;
    if (!legFlag) {
        cout << "     $    $$$   " << endl;
        cout << "     $$         ";
    }
    else {
        cout << "     $$$  $     " << endl;
        cout << "          $$    ";
    }
    legFlag = !legFlag;
}

void drawTree(int treeX)
{
    gotoXY(treeX, TREE_BOTTOM_Y);
    cout << "$$$$";
    gotoXY(treeX, TREE_BOTTOM_Y + 1);
    cout << " $$";
    gotoXY(treeX, TREE_BOTTOM_Y + 2);
    cout << " $$";
    gotoXY(treeX, TREE_BOTTOM_Y + 3);
    cout << " $$";
    gotoXY(treeX, TREE_BOTTOM_Y + 4);
    cout << " $$";
}

void drawBird(int birdX) {
    gotoXY(birdX, BIRD_BOTTOM_Y);
    cout << "  $     $ ";
    gotoXY(birdX, BIRD_BOTTOM_Y + 1);
    cout << " $$$   $$$";
    gotoXY(birdX, BIRD_BOTTOM_Y + 2);
    cout << "$   $$$   $";
}

void drawBullet(int bulletX, int bulletY)
{
    gotoXY(bulletX, bulletY);
    cout << "##";
    gotoXY(bulletX, bulletY + 1);
    cout << "##";
}

int getKeyDown()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }

    return 0;
}

int main(void)
{
    while (true) {
        legFlag = false;

        int score = 0;

        bool gameOver = false;
        bool isJumping = false;
        bool isGround = true;
        const int gravity = 3;

        int dinoY = DINO_BOTTOM_Y;

        bool treeActive = true;
        int treeX = TREE_BOTTOM_X;
        int treeCool = 0;

        bool birdActive = true;
        int birdX = TREE_BOTTOM_X;
        int birdCool = 0;

        int bulletX = 14;
        int bulletY = dinoY + 8;
        bool fire = false;

        setConsleView();

        while (true)
        {
            if (gameOver) {
                gotoXY(20, 12);
                cout << "GAME OVER";
                if (getKeyDown() == 'r')
                {
                    gameOver = false;
                    break;
                }
            }
            else {
                int ch = getKeyDown();
                if (ch == 'j' && isGround)
                {
                    isJumping = true;
                    isGround = false;
                }
                else if (ch == 'a' && !fire)
                {
                    bulletX = 8;
                    bulletY = dinoY + 8;
                    fire = true;
                }
                else if (ch == 'r')
                {
                    break;
                }
                else if (ch == 'q')
                {
                    cout << "종료";
                    _getch();
                    exit(0);
                }

                if (isJumping)
                {
                    dinoY -= gravity;
                }
                else
                {
                    dinoY += gravity;
                }

                if (dinoY >= DINO_BOTTOM_Y)
                {
                    dinoY = DINO_BOTTOM_Y;
                    isGround = true;
                }
                else if (dinoY <= 2)
                {
                    isJumping = false;
                }
                if (birdActive) {
                    birdX -= 2;
                    if (birdX <= 7 && dinoY + 12 >= BIRD_BOTTOM_Y && dinoY <= BIRD_BOTTOM_Y + 2) {
                        gameOver = true;
                        birdX = BIRD_BOTTOM_X;
                    }
                    else if (birdX <= 0)
                    {
                        birdX = BIRD_BOTTOM_X;
                    }
                    drawBird(birdX);
                }
                else {
                    if (birdCool >= 50) {
                        birdCool = 0;
                        birdActive = true;
                    }
                    birdCool++;
                }
                if (treeActive) {
                    treeX -= 4;
                    if (treeX <= 7 && dinoY + 12 >= TREE_BOTTOM_Y) {
                        gameOver = true;
                        treeX = TREE_BOTTOM_X;
                    }
                    else if (treeX <= 0)
                    {
                        treeX = TREE_BOTTOM_X;
                    }
                    drawTree(treeX);
                }
                else {
                    if (treeCool >= 30) {
                        treeCool = 0;
                        treeActive = true;
                    }
                    treeCool++;
                }

                if (fire)
                {
                    if (bulletX + 3 >= treeX && (bulletY + 1 >= TREE_BOTTOM_Y && bulletY <= TREE_BOTTOM_Y + 4)) {
                        treeX = 50; // 그냥 맵넘어서
                        treeActive = false;
                        fire = false;
                        score++;
                    }
                    else if (bulletX + 3 >= birdX && (bulletY + 1 >= BIRD_BOTTOM_Y && bulletY <= BIRD_BOTTOM_Y + 2)) {
                        birdX = 50; // 그냥 맵넘어서
                        birdActive = false;
                        fire = false;
                        score++;
                    }
                    else if (bulletX >= 45) {
                        fire = false;
                    }
                    else {
                        bulletX += 2;
                    }

                    drawBullet(bulletX, bulletY);
                }

                drawDino(dinoY);
                drawScore(score);

                Sleep(80);
                clrscr();

            }
        }

    }

    return 0;
}