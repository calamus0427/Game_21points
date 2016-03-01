/**************************************************
************
************
************       模拟21点扑克牌游戏
************
************
***************************************************/

#include<cstdlib>
#include<iostream>
#include<ctime>
using namespace std;
class CCard
{
public:
	CCard();
	void FirstPlayTwo();               //最初两张牌
	int GetNumber();                   //返回牌数
	int GetPip();                      //返回点数
	void DisplayPip();                 //依次全部显示牌面点数
	void DisplayPip(int);              //除了第一张牌，依次全部显示牌面点数（针对计算机牌的显示）
	void TurnPlay();                   //出一张牌
	void Win();                     
	void Lose();
	void Draw();
	int SetGamble(int);                 //设置赌本，赌本不够返回-1
	int GetMoney();
	void DisplayInfo();                 //打印必要的信息
	int GetCurrentCard();               //返回当前牌点
private:
	int naPip[5];           //一共5张牌
	int nNumber;            //发了多少张牌
	int nDollar;            //有多少钱
	int nGamble;            //赌注
	int nWin;               //赢局数
	int nLose;              //输局数
	int nDraw;              //平局数

};

CCard::CCard()
{
	nNumber=0;
	nDollar=100;
	for(int i=0;i<5;i++)
		naPip[i]=0;
	nGamble=0;
	nWin=nLose=nDraw=0;
}

int CCard::GetMoney(void)
{
	return nDollar;
}

void CCard::DisplayInfo()
{
	cout<<"您一共玩了"<<nWin+nLose+nDraw<<"局，"<<"赢了"<<nWin<<"局，"<<"输了"<<nLose<<"局，"<<"平局"<<nDraw<<"次。"<<endl;
	cout<<"你的赌本共计有$"<<nDollar<<endl;
}

int CCard::SetGamble(int gamble)
{
	if(nDollar-gamble<0)
		return -1;
	if(gamble<0)
	{
		if(nDollar-20<0)
			return -1;
		nGamble=20;
	}
	else nGamble=gamble;
	nDollar-=nGamble;
	return 0;
}

void CCard::FirstPlayTwo()
{
	naPip[0]=rand()%13+1;
	naPip[1]=rand()%13+1;
	nNumber=2;
}

int CCard::GetCurrentCard()
{
	return naPip[nNumber-1];
}

int CCard::GetNumber()
{
	return nNumber;
}

int CCard::GetPip()
{
	int nPip=0;
	for(int i=0;i<nNumber;i++)
	{
		if(naPip[i]>=10)
			nPip+=10;
		else 
			nPip+=naPip[i];
	}
	return nPip;
}

void CCard::DisplayPip()
{
	for(int i=0;i<nNumber;i++)
		cout<<naPip[i]<<'\t';
	cout<<endl;
}

void CCard::TurnPlay()
{
	nNumber++;
	naPip[nNumber-1]=rand()%13+1;
}

void CCard::Win()
{
	cout<<"赢家牌面：";
	DisplayPip();
	cout<<"牌面点数："<<GetPip()<<endl;
	nDollar=nDollar+2*nGamble;
	nWin++;
	cout<<"赌本：$"<<nDollar<<"赢了"<<"次，"<<"输了"<<nLose<<"次"<<"平局"<<nDraw<<"次"<<endl;
	cout<<endl<<endl;
}

void CCard::Lose()
{
	nLose++;
	cout<<"输家牌面：";
	DisplayPip();
	if(GetPip()>21)
		cout<<"爆了！\n";
	else 
		cout<<"牌面点数："<<GetPip()<<endl;
	cout<<"赌本：$"<<nDollar<<"赢了"<<nWin<<"次；"<<"输了"<<nLose<<"次；"<<"平局"<<nDraw<<"次。"<<endl;
	cout<<endl<<endl;

}

void CCard::Draw()
{
	nDraw++;
	nDollar+=nGamble;
	cout<<"平局牌面：";
	DisplayPip();
	if(GetPip()>21)
		cout<<"爆了！\n";
	else
		cout<<"赌本：$"<<nDollar<<"赢了"<<nWin<<"次；"<<"输了"<<nLose<<"次；"<<"平局"<<nDraw<<"次。"<<endl;
	cout<<endl<<endl;
}

void CCard::DisplayPip(int n)
{
	cout<<"[*]"<<'\t';
	for(int i=1;i<nNumber;i++)
		cout<<naPip[i]<<'\t';
	cout<<endl;
}

void DisplayRule(void)
{
	cout<<"\t欢迎进入21点游戏世界！\n\n";
	cout<<"\t游戏规则：\n";
	cout<<"\t1.玩家最多可以要5张牌；\n";
	cout<<"\t2.如果牌点的总数超过21点则爆点，自动判定为输；\n";
	cout<<"\t3.赢家可得双倍赌注；\n";
	cout<<"\t4.计算机方在牌点大于等于16时不再要牌。\n\n";
	cout<<"祝您好运！\n";
	cout<<endl<<endl;
}

void Judge(CCard &cpu,CCard &player)
{
	cout<<endl;
	if((cpu.GetPip()>21&&player.GetPip()>21)||cpu.GetPip()==player.GetPip())
	{
		cout<<"\n\n平局！\n";
		cout<<"计算机数据：\t";
		cpu.DisplayPip();
		cout<<"牌面点数："<<cpu.GetPip()<<endl;
		cout<<"\n您的数据：\t";
		player.Draw();
		cout<<endl;
	}
	else if((cpu.GetPip()>21)||(player.GetPip()&&player.GetPip()<=21))
	{
		cout<<"\n\n恭喜您，您赢了！！\n";
		cout<<"计算机数据：\t";
		cpu.DisplayPip();
		cout<<"牌面点数："<<cpu.GetPip()<<endl;
		cout<<"\n您的数据：\t";
		player.Win();
		cout<<endl;
	}
	else
	{
		cout<<"\n\n很遗憾，您输了！\n";
		cout<<"计算机数据：\t";
		cpu.DisplayPip();
		cout<<"牌面点数："<<cpu.GetPip()<<endl;
		cout<<"\n您的数据：\t";
		player.Lose();
		cout<<endl;
	}
}

void PlayTurn(CCard &cpu,CCard &player)
{
	char chChoice;
	int blCpu=1,blPlayer=1;
	cpu.FirstPlayTwo();
	player.FirstPlayTwo();
	do
	{
		cout<<"您的牌点为：\t";
		player.DisplayPip();
		cout<<"计算机的牌点为：\t";
		cpu.DisplayPip(1);
		cout<<"您的牌面点数为："<<player.GetPip()<<endl;
		if(blPlayer)
		{
			cout<<"\n\n您是否继续要牌（Y/N）？";
			cin>>chChoice;
			if((chChoice=='Y'||chChoice=='y'))
			{
				if(player.GetNumber()<5)
				{
					player.TurnPlay();
					cout<<"您要的这张牌是："<<player.GetCurrentCard()<<endl;
					if(player.GetPip()>21)
						blPlayer=0;
				}
				else
				{
					cout<<"对不起，您已经要了5次牌了。不能再要牌了！";
					blPlayer=0;
				}
			}
		}
		if((chChoice=='N'||chChoice=='n'))
			blPlayer=0;
		if(cpu.GetPip()<16&&cpu.GetNumber()<5)
		{
			cpu.TurnPlay();
			cout<<"计算机要牌，牌点是："<<cpu.GetCurrentCard()<<endl;
		}
		else
			blCpu=0;
		if(blCpu&&player.GetNumber()<5&&player.GetPip()<21)
			blPlayer=1;
	}
	while(blCpu||blPlayer);
	Judge(cpu,player);
	return;
}


int main(void)
{
	srand((unsigned)time(NULL));
	CCard cpu,player;
	int blLogic;
	int nMoney;
	DisplayRule();
	char chChoice;
	cout<<"是否现在开始游戏(Y/N)？\n";
	cin>>chChoice;
	while(chChoice=='Y'||chChoice=='y')
	{
		do
		{
			cout<<"您现在有赌本：$"<<player.GetMoney();
			cout<<"\n请下注（赌注不能超过赌本）：";
			cin>>nMoney;
			blLogic=player.SetGamble(nMoney);
			if(blLogic)
				cout<<"您的赌本不够，请重新下注！\n";
		}
		while(blLogic);
		PlayTurn(cpu,player);
		cout<<"是否继续21点游戏（Y/N）？\n";
		cin>>chChoice;
	}
	player.DisplayInfo();
	cout<<"\n\n您是明智的，赌博是不好的！回去好好学习去~！\n"<<endl<<endl;
	cout<<"欢迎再次使用本程序，该程序由蒲大人抄录！\n\n";
	return 0;
}
