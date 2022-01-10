#include <stdio.h>
#include <stdlib.h> //rand() 함수 포함 라이브러리 추가
#include <time.h> // time에 대한 헤더파일
#include <string.h> 


struct User
{
	int set_total, set_win;
	int game_total, game_win, game_draw, game_lose;
	int game_rock_total, game_rock_win;
	int game_scissors_total, game_scissors_win;
	int game_paper_total, game_paper_win;
};

int main(void)
{
	FILE* fp;
	int num_start, num_1, choice, random;
	int score_me, score_computer;

	struct User statistics;
	struct User* ps;
	ps = &statistics;

	memset(&statistics, 0, sizeof(struct User)); // 초기값 0 초기화


	srand(time(NULL)); // cmd 창을 매번 새롭게 실행시킬 때마다 다른 난수가 나오도록 함


start:


	printf("Please Enter Number\n\n");
	printf("1 : Play Game\n");
	printf("2 : Show Statistics\n");
	printf("3 : Save Current Data\n");
	printf("4 : Load Saved Data\n");
	printf("5 : Exit Program\n");
	printf("--> ");
	scanf_s("%d", &num_start);

	switch (num_start)
	{
	case 1:
	play_game:

		printf("\nPlease Enter Number\n\n");
		printf("1 : Play New Game\n");
		printf("2 : Continue\n");
		printf("--> ");
		scanf_s("%d", &num_1);
		switch (num_1)
		{
		case 1: // 새로운 게임 시작(모든 데이터 리셋)
			score_me = 0, score_computer = 0;
			memset(&statistics, 0, sizeof(struct User));

			printf("\nExisting Data Deleted. Playing New Game.\n");
			printf("\n---------------------------------------\n\n");

		replay:

			if (score_me < 3 && score_computer < 3) // 나 혹은 컴퓨터가 승점이 3점이 될때까지 진행
			{
				random = rand() % 3 + 1; // 컴퓨터가 1~3 사이의 임의의 숫자를 냄(가위바위보)
				printf("\nPlease Enter Number\n\n");
				printf("1 : rock\n");
				printf("2 : scissors\n");
				printf("3 : paper\n");
				printf("--> ");
				scanf_s("%d", &choice);
				switch (choice)
				{

				case 1: // 내가 주먹 냈을 때
					statistics.game_total += 1; // 게임 횟수 1 증가
					statistics.game_rock_total += 1; // 게임에서 주먹 낸 횟수 1 증가

					if (random == 2) // 내가 주먹 내고 컴퓨터가 가위 냈을 때
					{
						score_me += 1;
						statistics.game_rock_win += 1; // 게임에서 주먹 내서 이긴 횟수 1 증가
						statistics.game_win += 1; // 게임에서 이긴 횟수 1 증가
						printf("\n--- Win! ---\n\n");
						printf("You : rock\n");
						printf("Computer : scissors\n\n");
						printf("Current Score -> You : Computer = %d : %d\n", score_me, score_computer);
						goto replay;
					}
					else if (random == 1) // 내가 주먹 내고 컴퓨터도 주먹 냈을 때
					{
						statistics.game_draw += 1; // 게임에서 비긴 횟수 1 증가
						printf("\n--- Draw! ---\n\n");
						printf("You : rock\n");
						printf("Computer : rock\n\n");
						printf("Current Score -> You : Computer = %d : %d\n", score_me, score_computer);
						goto replay;
					}
					else if (random == 3) // 내가 주먹 내고 컴퓨터가 보 냈을 때
					{
						statistics.game_lose += 1; // 게임에서 진 횟수 1 증가
						score_computer += 1;
						printf("\n--- Lose! ---\n\n");
						printf("You : rock\n");
						printf("Computer : paper\n\n");
						printf("Current Score -> You : Computer = %d : %d\n", score_me, score_computer);
						goto replay;
					}
					break;

				case 2: // 내가 가위 냈을 때
					statistics.game_total += 1; // 게임 횟수 1 증가
					statistics.game_scissors_total += 1; // 게임에서 가위 낸 횟수 1 증가

					if (random == 1) // 내가 가위 내고 컴퓨터가 주먹 냈을 때
					{
						statistics.game_lose += 1; // 게임에서 진 횟수 1 증가
						score_computer += 1;
						printf("\n--- Lose! ---\n\n");
						printf("You : scissors\n");
						printf("Computer : rock\n\n");
						printf("Current Score -> You : Computer = %d : %d\n", score_me, score_computer);
						goto replay;
					}
					else if (random == 2) // 내가 가위 내고 컴퓨터도 가위 냈을 때
					{
						statistics.game_draw += 1; // 게임에서 비긴 횟수 1 증가
						printf("\n--- Draw! ---\n\n");
						printf("You : scissors\n");
						printf("Computer : scissors\n\n");
						printf("Current Score -> You : Computer = %d : %d\n", score_me, score_computer);
						goto replay;
					}
					else if (random == 3) // 내가 가위 내고 컴퓨터가 보 냈을 때
					{
						statistics.game_win += 1; // 게임에서 이긴 횟수 1 증가
						statistics.game_scissors_win += 1; // 게임에서 가위 내서 이긴 횟수 1 증가
						score_me += 1;
						printf("\n--- Win! ---\n\n");
						printf("You : scissors\n");
						printf("Computer : paper\n\n");
						printf("Current Score -> You : Computer = %d : %d\n", score_me, score_computer);
						goto replay;
					}
					break;

				case 3: // 내가 보 냈을 때
					statistics.game_total += 1; // 게임 횟수 1 증가
					statistics.game_paper_total += 1; // 게임에서 보 낸 횟수 1 증가

					if (random == 1) // 내가 보 내고 컴퓨터가 주먹 냈을 때
					{
						statistics.game_win += 1; // 게임에서 이긴 횟수 1 증가
						statistics.game_paper_win += 1; // 게임에서 보 내고 이긴 횟수 1 증가
						score_me += 1;
						printf("\n--- Win! ---\n\n");
						printf("You : paper\n");
						printf("Computer : rock\n\n");
						printf("Current Score -> You : Computer = %d : %d\n", score_me, score_computer);
						goto replay;
					}
					else if (random == 2) // 내가 보 내고 컴퓨터가 가위 냈을 때
					{
						statistics.game_lose += 1; // 게임에서 진 횟수 1 증가
						score_computer += 1;
						printf("\n--- Lose! ---\n\n");
						printf("You : paper\n");
						printf("Computer : scissors\n\n");
						printf("Current Score -> You : Computer = %d : %d\n", score_me, score_computer);
						goto replay;
					}
					else if (random == 3) // 내가 보 내고 컴퓨터도 보 냈을 때
					{
						statistics.game_draw += 1; // 게임에서 비긴 횟수 1 증가
						printf("\n--- Draw! ---\n\n");
						printf("You : paper\n");
						printf("Computer : paper\n\n");
						printf("Current Score -> You : Computer = %d : %d\n", score_me, score_computer);
						goto replay;
					}
					break;

				default: // 내가 잘못된 숫자 입력했을 때
					printf("Wrong number!\n");
					goto replay;
					break;

				} // 가위바위보 게임에 대한 switch문 종료

			} // 승점이 3점이 될 때까지 진행되는 if문 종료

			else // 승점이 3점이 된 순간 게임종료
			{
				statistics.set_total += 1; // 삼세판 한 세트 횟수 1 증가
				if (score_me == 3)
				{
					statistics.set_win += 1;
				}
				printf("\nGame Ended With Score %d : %d\n\n", score_me, score_computer);
				printf("-----------------------------\n");
				goto start; // 게임 종료 후 시작화면으로 복귀
			}
			break;

		case 2: // 게임 이어서 하기(continue)
			score_me = 0, score_computer = 0; // 삼세판 관련 변수만 0으로 초기화
			printf("\nContinue With Existing Data.\n");
			printf("\n---------------------------------------\n\n");
			goto replay;
			break;

		default: // 숫자 잘못 입력
			printf("Wrong number!\n");
			goto play_game;
			break;

		} // 1 : Play Game 에 대한 case 종료


	case 2: // 2 : Show Statistics
		if (statistics.set_total == 0)
		{
			printf("\n\n--- No Data. Try After Playing Games. --- \n\n\n");
			goto start;
		}
		else
		{
			printf("\n-----------------------------------------------\n");
			printf("Total Set Played : %d\n", statistics.set_total);
			printf("Win : %d, Total : %d\n", statistics.set_win, statistics.set_total);
			printf("--->   Set Win Rate : %.1f%%\n\n", (float)(statistics.set_win) / (float)(statistics.set_total) * 100.0);
			printf("Total Game Played : %d\n", statistics.game_total);
			printf("Win : %d Draw : %d Lose : %d\n\n", statistics.game_win, statistics.game_draw, statistics.game_lose);
			printf("Win Rate : %.1f%%\n", (float)(statistics.game_win) / (float)(statistics.game_total) * 100.0);
			printf("--->       Rock : %5.1f%%   Win : %2d,  Total : %2d\n", (float)(statistics.game_rock_win) / (float)(statistics.game_rock_total) * 100.0, statistics.game_rock_win, statistics.game_rock_total);
			printf("--->   Scissors : %5.1f%%   Win : %2d,  Total : %2d\n", (float)(statistics.game_scissors_win) / (float)(statistics.game_scissors_total) * 100.0, statistics.game_scissors_win, statistics.game_scissors_total);
			printf("--->      Paper : %5.1f%%   Win : %2d,  Total : %2d\n", (float)(statistics.game_paper_win) / (float)(statistics.game_paper_total) * 100.0, statistics.game_paper_win, statistics.game_paper_total);
			printf("\n-----------------------------------------------\n\n\n");
			goto start;
		}
		break;


	case 3:
		printf("\nData saved to ./data.bin\n\n");
		fopen_s(&fp, "data.bin", "wb");
		fwrite(ps, sizeof(*ps), 1, fp);
		fclose(fp);
		goto start;
		break;

	case 4:
		printf("\nLoading data from ./data.bin\n\n");
		fopen_s(&fp, "data.bin", "rb");
		if (fp == NULL)
		{
			printf("Error! No saved data\n\n");
			goto start;
		}
		fread(ps, sizeof(*ps), 1, fp);
		fclose(fp);
		goto start;
		break;

	case 5:
		break;

	default:
		printf("Wrong Input. Try Again.\n\n\n");
		goto start;
		break;
	}


	return 0;
}