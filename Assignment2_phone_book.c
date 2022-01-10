#include <stdio.h>
#include <string.h>
#define MAX_NUM 100


struct phone // 전화번호부에 대한 구조체 정의
{
	char name[20]; // 최대 19자(19 + NULL문자)
	char number[20]; // 최대 19자(19 + NULL문자)
};

int main(void)
{
	FILE* fp;
	int num_start;
	int cnt = 0; // 전화번호부에 들어가는 전화번호(이름)의 누적변수
	int i, j; // for 문에 사용되는 반복변수
	char name_search[20]; // 이름 검색에 사용되는 문자열
	char name_delete[20]; // 이름 삭제에 사용되는 문자열
	struct phone table[MAX_NUM] = { 0 }; // 전화번호는 최대 MAX_NUM개까지 저장, 초기값 0으로 초기화

start:
	printf("\n***** Menu *****\n");
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Search\n");
	printf("4. Print All\n");
	printf("5. Save Data\n");
	printf("6. Load Data\n");
	printf("7. Exit\n");
	printf("Choose the item : ");
	scanf_s("%d", &num_start);
	getchar(); // 버퍼 비우기


	switch (num_start)
	{
	case 1:
		if (cnt < MAX_NUM) // 전화번호부에 사람이 다 차지 않았을 때
		{
			printf("\n[INSERT]\n");
			printf("Input Name: ");
			gets_s(table[cnt].name, sizeof(table[cnt].name)); // 이름 등록


			printf("Input Tel Number: ");
			gets_s(table[cnt].number, sizeof(table[cnt].number)); // 번호 등록
			cnt += 1; // 전화번호부 내의 정보의 크기 1 증가 
			printf("---> Data Inserted\n");

			goto start;
		}
		else // 100명의 사람이 다 찼을 때
		{
			printf("\n---> Data Full\n\n");
			goto start;
		}
		break;

	case 2:
		printf("\n[Delete]\n");
		printf("Input Name : ");
		gets_s(name_delete, sizeof(name_delete));

		for (i = 0; i < cnt; i++)
		{
			if (strcmp(table[i].name, name_delete) == 0) // Input Name과 전화번호부 내의 이름이 일치하는 값이 있을 때까지 for문 반복
			{
				for (j = i; j < cnt - 1; j++) // 만약 j = cnt - 1 인 경우에는 for문 자체가 돌아가지 않은 채 종료되고 cnt--; 가 되어 맨 끝 자료가 삭제되므로 프로그램에 이상 없음 
				{
					table[j] = table[j + 1]; // 일치하는 값 찾으면, 뒤의 자료를 앞으로 당김
				} // 이 과정을 반복함
				cnt--; // for문 종료되면 총 자료의 크기가 1이 줄어들어야 하므로, 전화번호부 상에 등록된 번호 개수 1개 감소시킴 
				printf("---> Data Deleted\n\n");
				goto start;
			}
		}
		printf("\nNo Person Found\n\n");
		goto start;
		break;


	case 3:
		if (strcmp(table[0].name, "\0") == 0) // 자료가 없을 때
		{
			printf("\n---> No data!\n");
			goto start;
		}
		else // 자료가 있을 때
		{
			printf("\n[Search]\n");
			printf("Input Name : ");
			gets_s(name_search, sizeof(name_search));


			for (i = 0; i < cnt; i++)
			{
				if (strcmp(table[i].name, name_search) == 0) // Input Name과 전화번호부 내의 이름이 일치하는 값이 있을 때까지 for문 반복
				{
					printf("Name : %s // Tel : %s\n", table[i].name, table[i].number);
					printf("---> Data Found\n\n");
					goto start;
				}
			}
			printf("\n No Person Found\n\n"); // 전화번호부 상에 이름이 없다면 출력
			goto start;
		}
		break;

	case 4:
		if (strcmp(table[0].name, "\0") == 0) // 자료가 없을 때
		{
			printf("\n---> No data!\n");
			goto start;
		}
		else // 자료가 있을 때
		{
			printf("\n[Print All]\n");
			for (i = 0; i < cnt; i++)
			{
				printf("Name : %s // Tel : %s\n", table[i].name, table[i].number); // 구조체(전화번호부) 내에 저장되어있는 이름과 전화번호 모두 출력
			}
			printf("---> Data Print\n\n");
			goto start;
		}
		break;

	case 5:
		printf("\n[Saving File]\n\n");
		fopen_s(&fp, "data.txt", "wt");
		for (i = 0; i < cnt; i++)
		{
			fprintf(fp, "%s %s\n", table[i].name, table[i].number);
		}
		fclose(fp);
		printf("---> Data Saved\n");
		goto start;
		break;

	case 6:
		printf("\n[Loading File]\n\n");
		fopen_s(&fp, "data.txt", "rt");
		if (fp == NULL)
		{
			printf("Error! No saved data\n");
			goto start;
		}
		i = 0;
		while (EOF != fscanf_s(fp, "%s %s", table[i].name, sizeof(table[i].name), table[i].number, sizeof(table[i].number)))
		{
			i++;
		}
		cnt += i;
		fclose(fp);
		printf("---> Data Loaded\n");
		goto start;
		break;

	case 7:
		break;

	default: // 잘못된 숫자 입력 시
		printf("\nError! ReTry!\n\n");
		goto start;
		break;
	}

	return 0;
}