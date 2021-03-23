#include <iostream>
#include <time.h>

int answer[3];

void initAnswer() {

}

int main()
{
    srand(time(NULL));

    int answer[3] = { 0, };

    answer[0] = rand() % 9 + 1;

    do
    {
        answer[1] = rand() % 9 + 1;
    } while (answer[0] == answer[1]);

    do
    {
        answer[2] = rand() % 9 + 1;
    } while (answer[0] == answer[2] || answer[1] == answer[2]);

    std::cout << answer[0] << ", " << answer[1] << ", " << answer[2] << std::endl;

    int input[3] = { 0, };
    int strike, ball;

    while (true)
    {
        strike = 0;
        ball = 0;

        std::cin >> input[0] >> input[1] >> input[2];

        std::cout << answer[0] << ", " << answer[1] << ", " << answer[2] << std::endl;
        std::cout << input[0] << ", " << input[1] << ", " << input[2] << std::endl;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                //숫자의 값이 같은지 체크
                if (answer[i] == input[j]) {
                    //자리수가 같은지 체크
                    if (i == j) {
                        strike++;
                    }
                    else {
                        ball++;
                    }
                }
            }
        }

        if (strike == 3) {
            std::cout << "Win";
            return 0;
        }
        else if (strike == 0 && ball == 0) {
            std::cout << "Out" << std::endl;
        }
        else {
            std::cout << "strike : " << strike << std::endl;
            std::cout << "ball : " << ball << std::endl;
        }
    }

    return 0;
}