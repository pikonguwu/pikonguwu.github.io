#include <graphics.h>  
#include <conio.h>
#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 210;
 
int fx[8] = {-1,-1,-1,0,0,1,1,1}, fy[8] = {-1,0,1,-1,1,-1,0,1};
 
int n,m,c,flag[N][N],cnt[N][N],fcnt = 0,num = 0;

char s[N][N];
  
ExMessage msg;

IMAGE imgnum[10],imgmine,imgflag,cell,win[3];

int check(int x,int y)
{
    if(x <= n && x >= 1 && y <= m && y >= 1) return 1;
    else return 0;
}
 
int click(int x,int y)
{
    if(!check(x,y)) return 0; 
    if(s[x][y] == '*') return 1;
    else{
        flag[x][y] = 1;
        {//打开普通格子
        	putimage((x-1)*20,(y-1)*20,imgnum+cnt[x][y]);
		}
        if(cnt[x][y] == 0){
            for(int k=0;k<8;k++){
                if((flag[x+fx[k]][y+fy[k]] ==0 || flag[x+fx[k]][y+fy[k]]==3) && check(x+fx[k],y+fy[k])) click(x+fx[k],y+fy[k]);
            }
        }
    }
    return 0;   
}

void Draw(){
	initgraph(n*20,(m+4)*20,EW_DBLCLKS);//创建窗口
	setbkcolor(BLUE);
	cleardevice();
	IMAGE img;
	loadimage(&img,"./cell.jpg",20,20);
	for(int i=0;i<n*20;i+=20){
		for(int j=0;j<m*20;j+=20){
			putimage(i,j,&img);
		}
	}
	return ;
}

void my_putimage(int x)
{
	if(x == 1)
		putimage(0,0,win+0);
	if(x == 2)
		putimage(0,0,win+1);
	if(x == 3)
		putimage(0,0,win+2);
	if(x == 4) return;
}

int main()
{
	loadimage(imgnum+0,"./0.jpg",20,20);
	loadimage(imgnum+1,"./1.jpg",20,20);
	loadimage(imgnum+2,"./2.jpg",20,20);
	loadimage(imgnum+3,"./3.jpg",20,20);
	loadimage(imgnum+4,"./4.jpg",20,20);
	loadimage(imgnum+5,"./5.jpg",20,20);
	loadimage(imgnum+6,"./6.jpg",20,20);
	loadimage(imgnum+7,"./7.jpg",20,20);
	loadimage(imgnum+8,"./8.jpg",20,20);
	loadimage(&imgmine,"./mine.jpg",20,20);
	loadimage(&imgflag,"./flag.jpg",20,20);
	loadimage(&cell,"./cell.jpg",20,20);
	loadimage(win+0,"./miku.jpg",180,180);
	loadimage(win+1,"./original god.jpg",320,320);
	loadimage(win+2,"./donadona.jpg",512,320);
	initgraph(600,600,EW_DBLCLKS);
	setbkcolor(BLUE);
	cleardevice();
	settextcolor(RGB(0,255,13));
	LOGFONT f;
	gettextstyle(&f);						
	f.lfHeight = 30;						// 字体高度
	f.lfQuality = ANTIALIASED_QUALITY;		 
	settextstyle(&f);						// 字体样式
	outtextxy(10,10,"请输入你的游戏难度:");
	outtextxy(10,50,"1为初级 2为中级 3为高级 4为自定义");
	Sleep(2000);
	wchar_t ss[50];
	InputBox((LPTSTR)ss,10,"请输入难度");
    int T; T = _wtoi(ss);
    if(T == 1){
        n = 9; m = 9; c = 10;       
    }
    if(T == 2){
        n = 16; m = 16; c = 40;
    }
    if(T == 3){
        m = 16;  n= 30; c = 99;
    }
    if(T == 4){
    	char tt[50],pp[50],qq[50];
        InputBox((LPTSTR)tt,10,"请输入行数");
        m = atoi(tt);
        InputBox((LPTSTR)pp,10,"请输入列数");
        n = atoi(pp);
        InputBox((LPTSTR)qq,10,"请输入雷数");
        c = atoi(qq);
    }
    closegraph();
    //创建初始的棋盘样式，之后根据用户点击来随机布雷。
//    cout<<T<<" "<<n<<" "<<m<<" "<<c;
    Draw();
    //创建初始棋盘结束。
    //点第一下
	int tx,ty,op;
	bool en = false;
    while(1)
    {	
    	bool book = false;
    	while(peekmessage(&msg)){//peekmessage
			tx = msg.x/20 + 1; ty = msg.y/20 + 1;
    		switch(msg.message){
    		case WM_LBUTTONDOWN:
    		{
    			book = true;
			    srand(time(0));
				int tt = 0;
				while(tt < c){
					int x1 = rand()%n + 1; int y1 = rand()%m + 1;
					if(s[x1][y1] != '*' && (x1 != tx || y1 != ty)){
						tt++;
				 		s[x1][y1] = '*';
					} 	
				}	
				// 
			    for(int i=1;i<=n;i++){
			        for(int j=1;j<=m;j++){
						if(s[i][j] != '*') s[i][j] = '.';	
			            for(int k=0;k<8;k++){
			                if(s[i+fx[k]][j+fy[k]] == '*'&&check(i+fx[k],j+fy[k])) cnt[i][j] ++;
			            }
			        } 
			    }
			    //处理第一次点击
			    click(tx,ty);	 
				int book = 0;
		        for(int i=1;i<=n;i++){
		            for(int j=1;j<=m;j++){
		                if(s[i][j] == '.' && flag[i][j] != 1) book = 1;
		            }
		        }
		        if(!book){//游戏胜利 
		            en = 1;
		            printf("Game over, you win\n");
		            printf("%d %d\n",num,c - fcnt);
		            for(int i=1;i<=n;i++){
		                for(int j=1;j<=m;j++){
		                    if(s[i][j] == '*') putimage((i-1)*20,(j-1)*20,&imgmine);
		                }
		            }
		            Sleep(1000);
            		my_putimage(T);
		            Sleep(20000);
		            en = true;
		            break;
		        }
		        else{
		            printf("Game in progress\n");
		            printf("%d %d\n",num,c - fcnt);
		        }
				break;	
			}
    			
			}
		}
		if(book) break;
	}
	int t1 = clock();
    while(1){
    	int x,y;
    	
    	while(1){
			int nowt = clock() - t1;
     	    nowt /= 1000;
     	    char ts[10],ns[10];
      	    sprintf(ts, "%d", nowt);
      	    int ttmp; ttmp = c - fcnt;
      	    gettextstyle(&f);						
			f.lfHeight = 20;						// 字体高度
			f.lfQuality = ANTIALIASED_QUALITY;		 
			settextstyle(&f);
      	    outtextxy(10,m*20,"我是计时器：");
			outtextxy(120,m*20,ts);
			sprintf(ns, "%d", ttmp);
			outtextxy(10,(m+2)*20,"剩余雷数：");
			if(ttmp >= 10) outtextxy(120,(m+2)*20,ns);
			else{
				outtextxy(120,(m+2)*20,"0");
				outtextxy(130,(m+2)*20,ns);
			} 
			BeginBatchDraw();
    		bool boo = false;
    		while(peekmessage(&msg)){//peekmessage
				
    			switch(msg.message){
    			case WM_LBUTTONDOWN:
    			{
					x = msg.x/20 + 1; y = msg.y/20 + 1;
					op = 1;	boo = true;
		    		if(flag[x][y] == 0 || flag[x][y] == 3){
		                int book = 0; 
		                book = click(x,y);
		                if(book){
		                    printf("Hit mine, you lose\n");
		                    printf("%d %d\n",num,c - fcnt);
		                    for(int i=1;i<=n;i++){
		                        for(int j=1;j<=m;j++){
		                        	if(s[i][j] == '*') putimage((i-1)*20,(j-1)*20,&imgmine);
		                        }
		                    }
		                    en = true;
		                    break;
		                }
		            }	
				
					break;
				}
				case WM_RBUTTONDOWN:
				{
					
					x = msg.x/20 + 1; y = msg.y/20 + 1;
					op = 2; boo = true;
					if(flag[x][y] == 0){
		            	putimage((x-1)*20,(y-1)*20,&imgflag);
						flag[x][y] = 2,fcnt ++;  	
					} 	
					else if(flag[x][y] == 2){
						putimage((x-1)*20,(y-1)*20,&cell);
						flag[x][y] = 0,fcnt --;
					}
					
					break;
				}
				case WM_LBUTTONDBLCLK:
				{
					x = msg.x/20 + 1; y = msg.y/20 + 1;
					op = 9; boo = true;
					int tmp = 0;
		            for(int k=0;k<8;k++){
		                if(flag[x+fx[k]][y+fy[k]] == 2&&check(x+fx[k],y+fy[k])) tmp ++;
		            }
		            if(tmp == cnt[x][y] && flag[x][y] == 1){
		                int book = 0;
		                for(int k=0;k<8;k++){
		                    if(s[x+fx[k]][y+fy[k]] == '*' && flag[x+fx[k]][y+fy[k]] != 2 && check(x+fx[k],y+fy[k])){
		                        book = 1;
		                    }
		                }
		                if(book){
		                    en = true;
		                    printf("Hit mine, you lose\n");
		                    printf("%d %d\n",num,c - fcnt);
		                    for(int i=1;i<=n;i++){
		                        for(int j=1;j<=m;j++){
		                            if(s[i][j] == '*') putimage((i-1)*20,(j-1)*20,&imgmine);
		                        }
		                    }
		                    en = true;
		                    break;
		                }
		                else{
		                    for(int k=0;k<8;k++){
		                        if((flag[x+fx[k]][y+fy[k]] ==0 || flag[x+fx[k]][y+fy[k]]==3)&& check(x+fx[k],y+fy[k])){
		                            click(x+fx[k],y+fy[k]);
		                        }
		                    }
		                }
		            }
					break;
				}
					
				}
			}
			EndBatchDraw();
			if(boo) break;
		}
        int book = 0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s[i][j] == '.' && flag[i][j] != 1) book = 1;
            }
        }
        if(!book){//游戏胜利 
            en = 1;
            printf("Game over, you win\n");
            printf("%d %d\n",num,c - fcnt);
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    if(s[i][j] == '*') putimage((i-1)*20,(j-1)*20,&imgmine);
                }
            }
            Sleep(1500);
            my_putimage(T);
            en = 1;
        }
        else{
            printf("Game in progress\n");
            printf("%d %d\n",num,c - fcnt);
        }
        if(en == true) while(1);
    }
     
     
    return 0;
}
