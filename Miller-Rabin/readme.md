时间限制:10000ms

单点时限:1000ms

内存限制:256MB

# 描述

小Hi和小Ho最近突然对密码学产生了兴趣，其中有个叫RSA的公钥密码算法。RSA算法的计算过程中，需要找一些很大的质数。

小Ho：要如何来找出足够大的质数呢？

小Hi：我倒是有一个想法，我们可以先随机一个特别大的初始奇数，然后检查它是不是质数，如果不是就找比它大2的数，一直重复，直到找到一个质数为止。

小Ho：这样好像可行，那我就这么办吧。

过了一会儿，小Ho拿来了一张写满数字的纸条。

小Ho：我用程序随机生成了一些初始数字，但是要求解它们是不是质数太花时间了。

小Hi：你是怎么做的啊？

说着小Hi接过了小Ho的纸条。

小Ho：比如说我要检测数字n是不是质数吧，我就从2开始枚举，一直到sqrt(n)，看能否被n整除。

小Hi：那就对了。你看纸条上很多数字都是在15、16位左右，就算开方之后，也有7、8位的数字。对于这样大一个数字的循环，显然会很花费时间。

小Ho：那有什么更快速的方法么？

小Hi：当然有了，有一种叫做Miller-Rabin质数测试的算法，可以很快的判定一个大数是否是质数。

# 输入

第1行：1个正整数t，表示数字的个数，10≤t≤50

第2..t+1行：每行1个正整数，第i+1行表示正整数a[i]，2≤a[i]≤10^18

# 输出

第1..t行：每行1个字符串，若a[i]为质数，第i行输出"Yes"，否则输出"No"

# 样例输入
3

3

7

9

# 样例输出
Yes

Yes

No