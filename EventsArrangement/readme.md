时间限制:20000ms

单点时限:1000ms

内存限制:256MB

#描述
There are n events in the parade. Each one can be performed for at most k times.

The parade will last for m minutes. The major will give a talk at the end, so you should make at least one minute idle.

Each events have three attributions, ai, bi, ci. If the parade have p minutes remaining when the i-th event begins, the excitement of the parade 

will increase by ai-(m-p)*bi and the event will last for ci minutes.

You should arrange the events to maximize excitement and guarantee at least one minute at the end will be free.

#输入
Three integers n, m ,k on the first line.

The following n lines, there are three integers ai, bi, ci, denoting the attributions of the events.

0 <= ai, bi, ci <= 10000

For 20% of the data, n<=5, m<=10, k<=5；

For 60% of the data, n<=200, m<=500, k<=50；

For 100% of the data, n<=1000, m<=5000, k<=1000
#输出
One integer on one line, denoting the answer.

#样例输入
2 5 1

4 1 1

5 2 4

#样例输出
5
