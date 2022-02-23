#pragma once

#include <Windows.h>
#include <iostream>

#define SINGLETON( x )                                           \
public:                                                          \
	static x& Get( void ) { static x _; return _; }              \
	x& operator=( x&& )      = delete;                           \
	x& operator=( const x& ) = delete;                           


#define D3D_CHECK( hr ) _d3d_check( hr )

inline void _d3d_check( HRESULT hr ) 
{
	if( ( FAILED( hr ) ) ) 
	{ 
		std::cout << "HResult Failed!\n"; 
		__debugbreak(); 
	}
}

#define SAFE_RELEASE( x ) if( ( x ) ) x->Release()