#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct student 
{
	char name[20];
	int score;
	int rank;
} Rank;

int start_screen(void);
void start_game();
int set_card(int card[], int my_card[], int sum, int my_c[]);
int s_sort(int my_card[], int sum);
void print_my_card(int my_c[], int sum);
void print_your_card(int your_c[], int your_open[], int sum);
void save_score(char name[], int score);
void delete_user();
void print_rank();
void print_explain();
void add_card(int who_card[], int who_c[], int card[], int sum);
int get_line();
void file_sort();

int main(void)
{	 
	start_screen();
}

int start_screen(void)
{
	int s;	
	 
	printf("______________________________\n\n");
	printf("	1. ���Ӽ���\n");
	printf("	2. ����� ����\n");
	printf("	3. ���� ����\n");
	printf("	4. ��ŷ ��ȸ\n");
	printf("______________________________\n\n");
	printf("�޴��� �����ϼ���. >>  ");
	scanf("%d", &s);
	printf("\n\n");
	
	if ( s==1 )
		print_explain();
	else if ( s==2 )
		delete_user();
	else if ( s==3 )
		start_game();
	else if ( s==4 )
		print_rank();
}

void start_game()
{
	int card[26] = {0};
	
	int my_card[13] = {0};
	int your_card[13] = {0};
	
	int your_open[13] = {0};
	
	int my_c[26] = {0};
	int your_c[26] = {0};
	
	char name[20];
	int i,j, my_sum=4, your_sum = 4, score=0;
	int h_card, number;
	int num = get_line();
	int your;
	FILE *fp;
	Rank arr[100];
	
	printf("������� �̸��� �Է��ϼ���. >> ");
	scanf("%s", name);
	
	fp = fopen("Rank.txt", "r");
	for(i=0; i<num; i++)
	{
		fscanf(fp, "%d %s %d", &arr[i].rank, &arr[i].name, &arr[i].score);
		if(strcmp(arr[i].name, name)==0)
		{
			printf("�̸��� �ߺ��˴ϴ�. �ٽ� �Է��ϼ���. ");
			return;
		}
	}
	printf("\n\n");
	
	for(i=0; i<26; i++)
		card[i] = i;
	set_card(card, my_card, my_sum, my_c);
	set_card(card, your_card, your_sum, your_c);
	
	while(score!=my_sum || score!=your_sum)
	{
		printf("	��MY CARD : ");
		print_my_card(my_c, my_sum);
		printf("\n");
		printf("	��YOUR CARD : ");
		print_your_card(your_c, your_open, your_sum);
		
		printf("\n");
		for(i=1; i<=your_sum; i++)   
			printf("%d ", your_c[(i-1)*2+1]);
		
		printf("\n\n	��  MY TURN  ��\n\n");
		printf("	    �� ��° ī��?  >>  ");
		scanf("%d", &h_card);
		printf("	    ���ڴ�?  >>  ");
		scanf("%d", &number);
		
		if(your_c[(h_card*2)-1] == number)
		{
			printf("�����Դϴ�!.\n");
			your_open[h_card] = 1;
			score += 1;
			printf("�����Ϻ��� ī�尡 �����˴ϴ�.\n");
			/* next? */
		}
		else 
		{
			printf("�����Դϴ�. ���� �Ѿ�ϴ�.\n");
			my_sum += 1;
			add_card(my_card, my_c, card, my_sum);
		}
		
		srand((unsigned int)time(NULL));
		your = rand() % 2;
	
		if( your == 0 )
		{
			printf("��밡 �� ī�带 ������ϴ�.");
/*	  	  	  your_sum += 1;
			add_card(your_card, your_c, card, your_sum);  re */
		}
		else if ( your == 1 )  
		{
			printf("��밡 �� ī�带 ������ ���߽��ϴ�. ");
/*	  	  	  your_sum += 1;
    	   	add_card(your_card, your_c, card, your_sum);
	   	   	i = rand() % your_sum+1;
			your_open[i] = 1;  re */
		}
		printf("\n\n");
	}
	printf("Win~~~~");
	
	save_score(name, score);
}

int set_card(int card[], int my_card[], int sum, int my_c[])
{
	int temp, i;
	
	srand((unsigned)time(NULL));
	for(i=0; i<sum; i++)
	{
		temp = rand() % 26;
		if ( card[temp] != -1 )
		{
			my_card[i] = temp;
			card[temp] = -1;
		}
		else if ( card[temp] == -1 )
			i--;
	}
	s_sort(my_card, sum);
	
	for(i=1; i<=sum; i++)
	{
		if ( my_card[i-1]%2 == 0 )
			my_c[(i-1)*2] = 66;
		else 
			my_c[(i-1)*2] = 87;
		my_c[(i-1)*2+1] = my_card[i-1]/2;
	}
}

void print_my_card(int my_c[], int sum)
{
	int i;
	
	for(i=1; i<=sum; i++)
	{
		printf("%c%d ", my_c[(i-1)*2], my_c[(i-1)*2+1]);
	}
	printf("\n");
}

void print_your_card(int your_c[], int your_open[], int sum)
{
	int i;
	
	for(i=1; i<=sum; i++)
	{
		if(your_open[i] == 1)
		{
			printf("%c%d ", your_c[(i-1)*2], your_c[(i-1)*2+1]);
		}
		else
		{
			printf("%c   ", your_c[(i-1)*2]);
		}
	}
	printf("\n");
}

int s_sort(int my_card[], int sum)
{
	int i,j,temp;
	
	for (i=0; i<sum-1; i++)
	{
		for (j=i+1; j<sum; j++)
		{
			if (my_card[i] > my_card[j])
			{
				temp = my_card[i];
				my_card[i] = my_card[j];
				my_card[j] = temp;
			}
		}
	}
}

void add_card(int who_card[], int who_c[], int card[], int sum)
{   /* re  */
	int temp, i;
	
	srand((unsigned)time(NULL));
	temp = rand() % 26;
	if ( card[temp] != -1 )
	{
		who_card[sum] = temp;
		card[temp] = -1;
	}
	else if ( card[temp] == -1 )
		i--;

	s_sort(who_card, sum);
	
	for(i=1; i<=sum; i++)
	{
		if ( who_card[i-1]%2 == 0 )
			who_c[(i-1)*2] = 66;
		else 
			who_c[(i-1)*2] = 87;
		who_c[(i-1)*2+1] = who_card[i-1]/2;
	}
}

void save_score(char name[], int score)
{
	FILE *fp;
	
	fp = fopen("Rank.txt", "a");
	fprintf(fp, "%d %s %d\n", 1, name, score);
	
	fclose(fp);
}

void delete_user()
{
	FILE *fp;
	Rank arr[100];
	char name[20];
	int i, j;
	int num = get_line();
	
	fp = fopen("Rank.txt", "r");
	if(fp == NULL)
	{
		printf("��ŷ�� ����ֽ��ϴ�.");
		return ;
	}
	
	
	printf("������ ������� �̸��� �Է��ϼ���. >> ");
	scanf("%s", name);   
		
	for(i=0; i<num; i++)
	{	 fscanf(fp, "%d %s %d", &arr[i].rank, &arr[i].name, &arr[i].score);	 }
	
	for(i=0; i<num; i++)
	{
		arr[i].rank = 1;
		for(j=0; j<num; j++)
		{
			if(arr[i].score < arr[j].score)
			{	
				arr[i].rank++;
			}
		}
	}
	
	for(i=0; i<num; i++)
	{
		if(strcmp(arr[i].name, name)==0)
		{
			for(j=i;j<num;j++) 
				arr[j] = arr[j+1];
		}
	}			
	
	
	fp = fopen("Rank.txt", "w");
	for(i=0;i<num-1;i++)
	{
		fprintf(fp, "%d %s %d\n", arr[i].rank, arr[i].name, arr[i].score); 
		printf("%3d st : %8s %4d\n", arr[i].rank, arr[i].name, arr[i].score);
	}
	
	printf("%s ������� ����� �����Ǿ����ϴ�.",name);
	fclose(fp);
}

void print_rank()
{
	FILE *fp;
	Rank arr[100];
	Rank temp;
	int i, j;
	char name[20];
	int num = get_line();
	
	fp = fopen("Rank.txt", "r");
	if(fp == NULL)
	{
		printf("��ŷ�� ����ֽ��ϴ�.");
		return ;
	}
	
	for(i=0; i<num; i++)
	{	 fscanf(fp, "%d %s %d", &arr[i].rank, &arr[i].name, &arr[i].score);	 }
	
	for(i=0; i<num; i++)
	{
		arr[i].rank = 1;
		for(j=0; j<num; j++)
		{
			if(arr[i].score < arr[j].score)
			{	
				arr[i].rank++;
			}
		}
	}
	
	fp = fopen("Rank.txt", "w");
	
	for(j=0;j<num;j++)
	{
		for(i=0; i<num-1-j; i++)
		{
			if(arr[i].rank > arr[i+1].rank)
			{
				temp = arr[i+1];
				arr[i+1] = arr[i];
				arr[i] = temp;
			}
		}	 
	}
	
	for(i=0;i<num;i++)
	{
		fprintf(fp, "%d %s %d\n", arr[i].rank, arr[i].name, arr[i].score); 
		printf("%3d st : %8s %4d\n", arr[i].rank, arr[i].name, arr[i].score);
	}
	
	printf("�˻��� ����� �̸��� �Է��ϼ���. >> ");
	scanf("%s", name);
	for(i=0; i<num; i++)
	{
		if(strcmp(arr[i].name, name)==0)
		{
			printf("%3d st : %8s %4d", arr[i].rank, arr[i].name, arr[i].score);
		}
	}
	fclose(fp);
}

void print_explain()
{
	printf("\n");
	printf("0. ī��� �ߺ����� �ʴ´�.\n0-1. ī���� ��� -> ex) B1(������ 1), W2(�Ͼ�� 2)\n");	
	printf("\n1. ������ �����ϰ� ���� ������ ���� 4���� ī�带 �ο��޴´�.\n1-1. ������ ī��� ���� �� �� �ִ�. -> ex) B W W B\n");	
	printf("\n2. ���� ���� ���ƿ� �� ���� 1���� ī�带 �ο��޴´�.\n");	
	printf("\n3. ���� �Ͽ� �߸��� �����ϸ� �ο����� 1���� ī�带 �����Ѵ�.\n");	   
	printf("\n4. ������ ���� �� ���� 2�� 3�� �ݺ��Ѵ�.");
	printf("\n");
}

int get_line()
{
	FILE *fp;
  	int line=0;
  	char c;
	
  	fp=fopen("Rank.txt","r");
  	while((c=fgetc(fp))!=EOF)
    	if(c=='\n') line++;
  	fclose(fp);
	return line;
}

