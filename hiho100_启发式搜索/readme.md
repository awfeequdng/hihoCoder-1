### 题目1 : 搜索三·启发式搜索

时间限制:10000ms

单点时限:1000ms

内存限制:256MB

### 描述

在小Ho的手机上有一款叫做八数码的游戏，小Ho在坐车或者等人的时候经常使用这个游戏来打发时间。

游戏的棋盘被分割成3x3的区域，上面放着标记有1~8八个数字的方形棋子，剩下一个区域为空。
游戏过程中，小Ho只能移动棋子到相邻的空区域上。当小Ho将8个棋子都移动到如下图所示的位置时，游戏就结束了。
小Hi：小Ho，你觉得如果用计算机来玩这个游戏应该怎么做？

小Ho：用计算机来玩么？我觉得应该是搜索吧，让我想一想。

提示：启发式搜索

### 输入

第1行：1个正整数t，表示数据组数。1≤t≤8。

接下来有t组数据，每组数据有3行，每行3个整数，包含0~8，每个数字只出现一次，其中0表示空位。

### 输出

第1..t行：每行1个整数，表示该组数据解的步数。若无解输出"No Solution!"

### 样例输入
```
3
1 2 3
4 5 6
7 8 0
1 2 3
4 5 6
8 7 0
8 0 1
5 7 4
3 6 2
```

### 样例输出
```
0
No Solution!
25
```