# 为了尽可能贴近C语言的风格，这里很多写法都比较憨
# 大家可以由C入门python,快速get用法
mp = [[] for i in range(64)]# 创建二维数组
vis = [[0 for i in range(64)] for i in range(64)] ## 创建二维数组，并都置0
n = m = ans = 0
dx = [1,-1,0,0]# 方向列表
dy = [0,0,-1,1]

def dfs(x,y,t):
    if vis[x][y]:# 如果访问过就返回
        return
    vis[x][y]=1
    for i in range(4):
        nx = x+dx[i]
        ny = y+dy[i]
        if nx>=0 and nx<n and ny>=0 and ny<m and mp[x][y]==mp[nx][ny] and vis[nx][ny]==0:
            dfs(nx,ny,t+1)

    return


if __name__ == "__main__":
    n,m = map(lambda x:int(x),input("").split())
    for i in range(n):
        mp[i] = list(map(lambda x:int(x),input("").split()))
    for i in range(n):
        for j in range(m):
            if vis[i][j]==0:
                dfs(i,j,0)
                ans+=1
    print(ans,end='')

