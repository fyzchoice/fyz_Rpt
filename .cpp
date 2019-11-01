#include<stdio.h>
int Num_Pyramid_Base[3][150];//��������߽���������ż���������������������������в�����ʹ�õ��ķ�����
int Max_Base[3];//�����������ֽ������ڸ�������󷽿����µ����base
char Current_Pyramid_Sort[3];//���浱ǰ������������
int Depth; //ȫ�����
int Num_Cube; //�������ķ�����
int Save_Base[10];  //������������Ľ�������base
int Save_Pyramid_No[10]; //������������Ľ�������������
bool flag_complete;  //Ѱ����ɵı�־
bool read_cube() //���뷽����
{
	scanf_s("%d", &Num_Cube);
	if (Num_Cube == 0)
		return false;
	flag_complete = false;
	return true;
}
/*
��������DBF_Search
���ܣ�����������ȱ�������Ϲ�ȱ����������������Ľ�����
Current_cube_num����ǰ��ʹ�õķ�����
Current_Depth����ǰ��ʹ�����
Max_Base0����ǰ�߽��������������base
Max_Base1����ǰ���������������������base
Max_Base2����ǰ��ż�����������������base
*/
void DBF_Search(int Current_cube_num, int Current_Depth, int Max_Base0, int Max_Base1, int Max_Base2)	
{
	if (Current_cube_num == 0)
	{
		flag_complete = true;
		return;
	}
	for (int temp0 = Max_Base0, temp1 = Max_Base1, temp2 = Max_Base2; temp0 > 1 || temp1 > 1 || temp2 > 1;)
	{
		int Current_Pyramid_No, Current_Base;//current_pyramid_no����ǰ������������
											 //current_base����ǰ�����ŵĽ�������base
		/*
		�ҳ��߽�������������������ż�����������Ե����base����Ӧ�ķ����������ֵ
		*/
		if (Num_Pyramid_Base[0][temp0] >= Num_Pyramid_Base[1][temp1] && Num_Pyramid_Base[0][temp0] >= Num_Pyramid_Base[2][temp2])
		{
			Current_Pyramid_No = 0;
			Current_Base = temp0;
			temp0--;
		}
		else if (Num_Pyramid_Base[1][temp1] >= Num_Pyramid_Base[0][temp0] && Num_Pyramid_Base[1][temp1] >= Num_Pyramid_Base[2][temp2])
		{
			Current_Pyramid_No = 1;
			Current_Base = temp1;
			temp1--;
		}
		else
		{
			Current_Pyramid_No = 2;
			Current_Base = temp2;
			temp2--;
		}
		if (Num_Pyramid_Base[Current_Pyramid_No][Current_Base] * Current_Depth < Current_cube_num)
			return;																	//���ҵ�С�ڵ�ǰ��������Ӧ��base�󣬿�ʼ�ڶ���ֵ�Ĳ���
		if (Num_Pyramid_Base[Current_Pyramid_No][Current_Base] > Current_cube_num)
			continue;																//����ǰ������base��Ӧ�ķ��������ڵ�ǰ������ʱ������Ѱ��
		Save_Pyramid_No[Depth - Current_Depth + 1] = Current_Pyramid_No;			
		Save_Base[Depth - Current_Depth + 1] = Current_Base;
		DBF_Search(Current_cube_num - Num_Pyramid_Base[Current_Pyramid_No][Current_Base], Current_Depth - 1, temp0, temp1, temp2);
		if (flag_complete)
			return;
	}
}
int main()
{
	int Case = 0;
	for (Max_Base[0] = 0; Num_Pyramid_Base[0][Max_Base[0]] <= 1000000; Max_Base[0]++)
		Num_Pyramid_Base[0][Max_Base[0] + 1] = Num_Pyramid_Base[0][Max_Base[0]] + (Max_Base[0] + 1) * (Max_Base[0] + 1);				//��Max_Base0���<1000000�ĸ����������
	for (Max_Base[1] = 0; Num_Pyramid_Base[1][Max_Base[1]] <= 1000000; Max_Base[1]++)
		Num_Pyramid_Base[1][Max_Base[1] + 1] = Num_Pyramid_Base[1][Max_Base[1]] + (Max_Base[1] * 2 + 1) * (Max_Base[1] * 2 + 1);		//��Max_Base0��ĸ�����������ĵ����������
	for (Max_Base[2] = 0; Num_Pyramid_Base[2][Max_Base[2]] <= 1000000; Max_Base[2]++)
		Num_Pyramid_Base[2][Max_Base[2] + 1] = Num_Pyramid_Base[2][Max_Base[2]] + (Max_Base[2] + 1) * (Max_Base[2] + 1) * 4;			//��Max_Base0��ĸ������ż���ĵ����������
	Current_Pyramid_Sort[0] = 'H';
	Current_Pyramid_Sort[1] = Current_Pyramid_Sort[2] = 'L';
	while (read_cube())
	{
		for (Depth = 1; Depth <= 10 && !flag_complete; Depth++)
			DBF_Search(Num_Cube, Depth, Max_Base[0], Max_Base[1], Max_Base[2]);
		Depth--;
		printf("Case %d: ", ++Case);
		if (!flag_complete)
			printf("impossible\n");
		else
		{
			for (int i = 1; i < Depth; i++)
				printf("%d%c ", Save_Base[i] * ((Save_Pyramid_No[i] + 1) / 2 + 1) - (Save_Pyramid_No[i] & 1), Current_Pyramid_Sort[Save_Pyramid_No[i]]);
			printf("%d%c", Save_Base[Depth] * ((Save_Pyramid_No[Depth] + 1) / 2 + 1) - (Save_Pyramid_No[Depth] & 1), Current_Pyramid_Sort[Save_Pyramid_No[Depth]]);
			printf("\n");
		}
	}
	return 0;
}
