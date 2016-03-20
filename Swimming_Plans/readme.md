时间限制:10000ms

单点时限:1000ms

内存限制:256MB
#描述
Steven loves swimming! The swimming pool he goes to every afternoon consists of N parallel lanes which are number from 0 to N-1. Steven plans to swim for R rounds. Each round he chooses a lane and swim to the other side, spending exactly L units of time.

Since the weather is getting hotter, the swimming pool is very crowded. To prevent from accidents, the swimming pool manager asks everyone to submit their plans before swimming. A plan contains specific informations for a round, including t - the time he starts, l - the time he spends, n - the lane he chooses, d - the direction he swims(0 for swimming from west to east and 1 for swimming from east to west). Everyone starts at some integeral time and swims at a constant speed.

The plans should not conflict with each other: two swimmers are not allowed to meet in the middle of a lane (meeting at the sides is allowed).

Steven arrives at time T and gets Q plans of the other swimmers. So here's the question, what's the earliest time that Steven can finish his swimming plans?

Note that Steven starts from the west side and he moves from one side to the other only by swimming.

#输入
Input contains multiple testcases.

The first line is an integer TASKS, representing the number of testcases.

For each testcase, the first line contains five integers T, L, R, N and Q which are described above.

The following Q lines describe the plans, each line with four integers, t, l, n, d, which are described above.

For all testcases:

0 <= T, t <= 104

1 <= L, l <= 104

1 <= R <= 104

0 <= Q <= 104

1 <= N <= 103

#输出
The earliest time that Steven can finish his swimming plans.
##样例输入
2

0 1 3 1 2

1 1 0 0

3 2 0 0

1 1 2 2 4

0 3 0 0

3 3 0 0

0 3 1 1

3 3 1 1
##样例输出
4

4