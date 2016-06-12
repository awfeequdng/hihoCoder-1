#include <iostream>
#include<cstring>
#include<cstdio>
using namespace std;

int M, N; // 行,列
int m[110][300]; // 原矩阵
int v[300];   // 压缩向量
bool zIndex[110]; // 标记全0行

// 函数
bool Clash( const int row )
{
	for( int i = 0; i < N; ++ i )
		if( v[i] == 1 && m[row][i] == 1 )
			return true; // 冲突
	return false;
}
void GetAllZeroRowIndex()
{
	memset( zIndex, false, sizeof(zIndex) );
	for( int i = 0; i < M; ++ i ) {
		bool flag = true;
		for( int j = 0; j < N; ++ j ) {
			if( m[i][j] == 1 ) {
				flag = false;
				break;
			}
		}
		if( flag ) zIndex[i] = true; // 标记全0行
	}
}
bool Full()
{
	for( int i = 0; i < N; ++ i )
		if( v[i] == 0 )
			return false; // 压缩向量未满
	return true;
}
bool DFS( const int row )
{
	// 该行可选
	if( !zIndex[row] && !::Clash(row) ) {
		for( int i = 0; i < N; ++ i )
			v[i] = v[i] | m[row][i];
		if( ::Full() )
			return true;
	}
	else // 该行不可选
		return false;

	// 深搜子问题
	for( int i = row + 1; i < M; ++ i )
		if( ::DFS(i) )
			return true;

	// 该行不可行
	for( int i = 0; i < N; ++ i )
		v[i] = v[i] ^ m[row][i];
	return false;
}
// 优化
bool HasColumnAllZero()
{
	for( int i = 0; i < N; ++ i ) {
		bool flag = true;
		for( int j = 0; j < M; ++ j ) {
			if( m[j][i] != 0 ) {
				flag = false;
				break;
			}
		}
		if( flag ) return true; // 存在全0列
	}
	return false;
}
bool HasRowAllOne()
{
	for( int i = 0; i < M; ++ i ) {
		bool flag = true;
		for( int j = 0; j < N; ++ j ) {
			if( m[i][j] != 1 ) {
				flag = false;
				break;
			}
		}
		if( flag ) return true; // 存在全1行
	}
	return false;
}

int main()
{
      int num;
      cin>>num;
	while( num-- ) {
            scanf( "%d%d", & M, & N ) ;
		for( int i = 0; i < M; ++ i )
			for( int j = 0; j < N; ++ j )
				scanf( "%d", & m[i][j] );

		bool succ = false;
		if( ::HasColumnAllZero() ) succ = false;
		else if( ::HasRowAllOne() ) succ = true;
		else {
			// 标记全0行
			::GetAllZeroRowIndex();
			memset( v, 0, sizeof(v) );
			for( int i = 0; i < M; ++ i )
				if( ::DFS(i) ) {
					succ = true;
					break;
				}
		}
		if( succ ) printf( "Yes\n" );
		else printf( "No\n" );
	}
	return 0;
}

