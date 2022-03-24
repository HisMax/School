/*****************************
*   Name:Histone
*   Time: 15:17:49
*   Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
*   Ä¬×ÓÒªÔçË¯
*****************************/
#include<iostream>
#include<algorithm>
#include<deque>
#include<functional>
#include<iterator>
#include<vector>
#include<list>
#include<map>
#include<memory>
#include<numeric>
#include<queue>
#include<set>
#include<stack>
#include<utility>
using namespace std;
int n,m,f;
int dx[5] = {0,1,-1,0,0};
int dy[5] = {0,0,0,-1,1};
int mp[1024][1024];
int vis[1024][1024];
inline int read(){
    char ch=getchar();int x=0,f=1;
    while(ch<'0' || ch>'9')    {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
};
void dfs(int x,int y,int s){
    if(mp[x][y]==2){
        f = 1;
        return;
    }
    for(int i = 1;i <= 4;++i){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx>=1&&ny>=1&&nx<=n&&ny<=m&&mp[nx][ny]!=0&&!vis[nx][ny]){
            vis[nx][ny]=1;
            dfs(nx,ny,s+1);
        }
    }
}
inline int lowbit(int x){return x&-x;}

signed main(void){
    printf("ÇëÊäÈëÃÔ¹¬£º\n");
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;++i){
        for(int j = 1;j <= m;++j){
            scanf("%c",&mp[i][j]);
            mp[i][j]-='0';
        }
        getchar();
    }
    for(int i = 1;i <= n;++i){
        for(int j = 1;j <= m;++j){
            if(mp[i][j]==3)dfs(i,j,1);
        }
    }
    if(f)printf("ÕÒµ½Â·¾¶£¡");
    else printf("Î´ÕÒµ½£¬½áÊø¡­¡­");
    return 0;
}
