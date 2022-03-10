#include <stdio.h>
//非常裸的一道DFS
int mp[64][64];//存放矩阵
int n,m;//矩阵大小
int vis[64][64];//记录已经访问过的位置
int ans = 0;//最终答案
int dx[5] = {0,1,-1,0,0};//方向数组
int dy[5] = {0,0,0,-1,1};
void dfs(int x,int y){
    if(vis[x][y])return;//走过就不再走了
    vis[x][y] = 1;
    for (int i = 1; i <= 4; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(mp[x][y]==mp[nx][ny]&&!vis[nx][ny]&&nx>=1&&nx<=n&&ny>=1&&ny<=m){
            dfs(nx,ny);
        }
    }
    return;
}
int main(void){
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= n; i++){//输入mp
        for(int j = 1;j <= m; j++){
            scanf("%d",&mp[i][j]);
        }
    }
    for(int i = 1; i <= n; i++){//遍历mp
        for(int j = 1;j <= m; j++){
            if(!vis[i][j]){//如果该位置没被访问过，那么就dfs
                dfs(i,j);
                ans++;
            }
        }
    }
    printf("%d",ans);
    return 0;
}