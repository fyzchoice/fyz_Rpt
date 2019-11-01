#include<stdio.h>
int Num_Pyramid_Base[3][150];//用来保存高金字塔、低偶数金字塔、低奇数金字塔的所有层数所使用到的方块数
int Max_Base[3];//用来保存三种金字塔在给定的最大方块数下的最大base
char Current_Pyramid_Sort[3];//保存当前金字塔的种类
int Depth; //全局深度
int Num_Cube; //保存读入的方块数
int Save_Base[10];  //保存符合条件的金字塔的base
int Save_Pyramid_No[10]; //保存符合条件的金字塔的种类编号
bool flag_complete;  //寻找完成的标志
bool read_cube() //读入方块数
{
	scanf_s("%d", &Num_Cube);
	if (Num_Cube == 0)
		return false;
	flag_complete = false;
	return true;
}
/*
函数名：DBF_Search
功能：利用深度优先遍历，结合广度遍历搜索符合条件的金字塔
Current_cube_num：当前可使用的方块数
Current_Depth：当前可使用深度
Max_Base0：当前高金字塔的最大搜索base
Max_Base1：当前低奇数金字塔的最大搜索base
Max_Base2：当前低偶数金字塔的最大搜索base
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
		int Current_Pyramid_No, Current_Base;//current_pyramid_no：当前金字塔种类编号
											 //current_base：当前种类编号的金字塔的base
		/*
		找出高金字塔、奇数金字塔、偶数金字塔各自的最大base所对应的方块数的最大值
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
			return;																	//当找到小于当前方块数对应的base后，开始第二个值的查找
		if (Num_Pyramid_Base[Current_Pyramid_No][Current_Base] > Current_cube_num)
			continue;																//当当前金字塔base对应的方块数大于当前方块数时，重新寻找
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
		Num_Pyramid_Base[0][Max_Base[0] + 1] = Num_Pyramid_Base[0][Max_Base[0]] + (Max_Base[0] + 1) * (Max_Base[0] + 1);				//把Max_Base0层的<1000000的高塔存进数组
	for (Max_Base[1] = 0; Num_Pyramid_Base[1][Max_Base[1]] <= 1000000; Max_Base[1]++)
		Num_Pyramid_Base[1][Max_Base[1] + 1] = Num_Pyramid_Base[1][Max_Base[1]] + (Max_Base[1] * 2 + 1) * (Max_Base[1] * 2 + 1);		//将Max_Base0层的各层基底奇数的低塔存进数组
	for (Max_Base[2] = 0; Num_Pyramid_Base[2][Max_Base[2]] <= 1000000; Max_Base[2]++)
		Num_Pyramid_Base[2][Max_Base[2] + 1] = Num_Pyramid_Base[2][Max_Base[2]] + (Max_Base[2] + 1) * (Max_Base[2] + 1) * 4;			//将Max_Base0层的各层基底偶数的低塔存进数组
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
