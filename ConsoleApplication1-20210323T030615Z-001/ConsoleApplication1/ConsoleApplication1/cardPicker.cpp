#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

void gotoXY(int x, int y) {
    HANDLE hOut;
    COORD Cur;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(hOut, Cur);
}
int main()
{
    srand((unsigned)time(NULL));

    const int num = 20;
    int Number[num] = { 0, };
    int sameNum = 0;
    bool bSame = false;

    // 숫자 섞기
    for (int i = 0; i < num; i++) {
        do {
            bSame = false;
            Number[i] = rand() % 10 + 1;

            if (i > 1) {
                sameNum = 0;
                for (int j = 0; j < i; j++) {
                    if (Number[i] == Number[j]) {
                        sameNum++;
                    }
                }
            }
            if (sameNum > 1) {
                bSame = true;
            }
        } while (bSame);
    }

    // 숫자 배치
    /*for (int i = 0; i < num / 5; i++) {
        for (int j = 0; j < num / (num / 5); j++) {
            cout << Number[j+(i*5)] << "\t";
        }
        cout << endl;
    }*/
    for (int i = 0; i < num; i++) {
        gotoXY((i % 5) * 5, i / 5);
        cout << Number[i];
    }
    Sleep(3000);
    system("cls");
    // 가리기
    for (int i = 0; i < num; i++) {
        gotoXY((i % 5) * 5, i / 5);
        cout << "?";
    }

    int key;
    int x, y;
    x = 0;
    y = 0;
    bool check = false;
    int saveCheck = 0;

    while (1) {
        gotoXY(x, y);
        key = _getch();
        if (key == 27) {
            break;
        }
        else if (key == 13) {
            system("cls");
            if (check == false) {
                for (int i = 0; i < num; i++) {
                    gotoXY((i % 5) * 5, i / 5);
                    if (((x / 5) + (y * 5)) == i) {
                        if (Number[i] == 0) {
                            cout << " ";
                            check = false;
                        }
                        else {
                            cout << Number[i];
                            check = true;
                        }
                    }
                    else if (Number[i] == 0) {
                        cout << " ";
                    }
                    else {
                        cout << "?";
                    }
                }
                saveCheck = ((x / 5) + (y * 5));
            }
            else {
                for (int i = 0; i < num; i++) {
                    gotoXY((i % 5) * 5, i / 5);
                    if (((x / 5) + (y * 5)) == i) {
                        if (Number[i] == 0) {
                            cout << " ";
                            check = true;
                        }
                        else {
                            cout << Number[i];
                            check = false;
                        }
                    }
                    else if (Number[i] == 0) {
                        cout << " ";
                    }
                    else if (saveCheck != i) {
                        cout << "?";
                    }
                    if (saveCheck == i && saveCheck != (x / 5) + (y * 5)) {
                        cout << Number[i];
                    }
                }
                if (Number[x / 5 + y * 5] == Number[saveCheck]) {
                    if (saveCheck != (x / 5) + (y * 5)) {
                        Number[x / 5 + y * 5] = 0;
                        Number[saveCheck] = 0;
                    }
                    else {
                        cout << "\n 같은 카드를 누르지 마시오" << endl;
                    }
                }
                if (check == false)
                    Sleep(500);
                system("cls");
                for (int i = 0; i < num; i++) {
                    gotoXY((i % 5) * 5, i / 5);
                    if (Number[i] == 0) {
                        cout << " ";
                    }
                    else if (saveCheck == i && check == true) {
                        cout << Number[i];
                    }
                    else {
                        cout << "?";
                    }
                }
                if (check == false)
                    saveCheck = 0;
            }
            int total = 0;
            for (int i = 0; i < num; i++) {
                if (Number[i] == 0)
                    total++;
            }
            // 이김
            if (total == 20) {
                cout << "\nWIN\n끝";
                return 0;
            }
        }
        else {
            switch (key)
            {
            case 75:
                //cout << "왼쪽";
                if (x > 4) {
                    x -= 5;
                }
                break;
            case 80:
                //cout << "아래";
                if (y < 3) {
                    y++;
                }
                break;
            case 77:
                //cout << "오른쪽";
                if (x < 20) {
                    x += 5;
                }
                break;
            case 72:
                //cout << "위";
                if (y > 0) {
                    y--;
                }
                break;
            default:
                break;
            }
        }
    }
    return 0;
}