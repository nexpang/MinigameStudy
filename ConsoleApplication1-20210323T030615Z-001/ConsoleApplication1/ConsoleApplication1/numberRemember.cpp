#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;
int main()
{
    srand((unsigned)time(NULL));
    const int num = 10;
    int answer[num] = { 0, };
    int initAnswer[num] = { 0, };
    int total = 0;

    for (int i = 0; i < num; i++) {
        answer[i] = rand() % 100 + 1;
        cout << answer[i] << " ";
        Sleep(1000);
    }
    cout << endl;
    system("cls");
    for (int i = 0; i < num; i++) {
        cin >> initAnswer[i];
        if (answer[i] != initAnswer[i]) {
            cout << "틀렸습니다." << endl;
            break;
        }
        else {
            total++;
        }
    }
    if(total == num)
        cout << "모두 맞췄습니다.";
    else {
        cout << total << "번 맞췄습니다.";
    }
    return 0;
}