#include <stdio.h>
#include <string.h>
#define MAX_NUM 100


struct phone // ��ȭ��ȣ�ο� ���� ����ü ����
{
	char name[20]; // �ִ� 19��(19 + NULL����)
	char number[20]; // �ִ� 19��(19 + NULL����)
};

int main(void)
{
	FILE* fp;
	int num_start;
	int cnt = 0; // ��ȭ��ȣ�ο� ���� ��ȭ��ȣ(�̸�)�� ��������
	int i, j; // for ���� ���Ǵ� �ݺ�����
	char name_search[20]; // �̸� �˻��� ���Ǵ� ���ڿ�
	char name_delete[20]; // �̸� ������ ���Ǵ� ���ڿ�
	struct phone table[MAX_NUM] = { 0 }; // ��ȭ��ȣ�� �ִ� MAX_NUM������ ����, �ʱⰪ 0���� �ʱ�ȭ

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
	getchar(); // ���� ����


	switch (num_start)
	{
	case 1:
		if (cnt < MAX_NUM) // ��ȭ��ȣ�ο� ����� �� ���� �ʾ��� ��
		{
			printf("\n[INSERT]\n");
			printf("Input Name: ");
			gets_s(table[cnt].name, sizeof(table[cnt].name)); // �̸� ���


			printf("Input Tel Number: ");
			gets_s(table[cnt].number, sizeof(table[cnt].number)); // ��ȣ ���
			cnt += 1; // ��ȭ��ȣ�� ���� ������ ũ�� 1 ���� 
			printf("---> Data Inserted\n");

			goto start;
		}
		else // 100���� ����� �� á�� ��
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
			if (strcmp(table[i].name, name_delete) == 0) // Input Name�� ��ȭ��ȣ�� ���� �̸��� ��ġ�ϴ� ���� ���� ������ for�� �ݺ�
			{
				for (j = i; j < cnt - 1; j++) // ���� j = cnt - 1 �� ��쿡�� for�� ��ü�� ���ư��� ���� ä ����ǰ� cnt--; �� �Ǿ� �� �� �ڷᰡ �����ǹǷ� ���α׷��� �̻� ���� 
				{
					table[j] = table[j + 1]; // ��ġ�ϴ� �� ã����, ���� �ڷḦ ������ ���
				} // �� ������ �ݺ���
				cnt--; // for�� ����Ǹ� �� �ڷ��� ũ�Ⱑ 1�� �پ���� �ϹǷ�, ��ȭ��ȣ�� �� ��ϵ� ��ȣ ���� 1�� ���ҽ�Ŵ 
				printf("---> Data Deleted\n\n");
				goto start;
			}
		}
		printf("\nNo Person Found\n\n");
		goto start;
		break;


	case 3:
		if (strcmp(table[0].name, "\0") == 0) // �ڷᰡ ���� ��
		{
			printf("\n---> No data!\n");
			goto start;
		}
		else // �ڷᰡ ���� ��
		{
			printf("\n[Search]\n");
			printf("Input Name : ");
			gets_s(name_search, sizeof(name_search));


			for (i = 0; i < cnt; i++)
			{
				if (strcmp(table[i].name, name_search) == 0) // Input Name�� ��ȭ��ȣ�� ���� �̸��� ��ġ�ϴ� ���� ���� ������ for�� �ݺ�
				{
					printf("Name : %s // Tel : %s\n", table[i].name, table[i].number);
					printf("---> Data Found\n\n");
					goto start;
				}
			}
			printf("\n No Person Found\n\n"); // ��ȭ��ȣ�� �� �̸��� ���ٸ� ���
			goto start;
		}
		break;

	case 4:
		if (strcmp(table[0].name, "\0") == 0) // �ڷᰡ ���� ��
		{
			printf("\n---> No data!\n");
			goto start;
		}
		else // �ڷᰡ ���� ��
		{
			printf("\n[Print All]\n");
			for (i = 0; i < cnt; i++)
			{
				printf("Name : %s // Tel : %s\n", table[i].name, table[i].number); // ����ü(��ȭ��ȣ��) ���� ����Ǿ��ִ� �̸��� ��ȭ��ȣ ��� ���
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

	default: // �߸��� ���� �Է� ��
		printf("\nError! ReTry!\n\n");
		goto start;
		break;
	}

	return 0;
}