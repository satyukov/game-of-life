#ifndef __GAME_OF_LIFE_COMMON_H__
#define __GAME_OF_LIFE_COMMON_H__

#include <cstdint>

using int32 = std::int32_t;
using int64 = std::int64_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

void CheckInternal(bool expr, const char* file, int line, const char* function);

#define CHECK(expr) CheckInternal((expr), __FILE__, __LINE__, __FUNCTION__)
#define CHECK_NE(expr1, expr2) CheckInternal((expr1) != (expr2), __FILE__, __LINE__, __FUNCTION__)
#define CHECK_EQ(expr1, expr2) CheckInternal((expr1) == (expr2), __FILE__, __LINE__, __FUNCTION__)
#define CHECK_LE(expr1, expr2) CheckInternal((expr1) <= (expr2), __FILE__, __LINE__, __FUNCTION__)
#define CHECK_LT(expr1, expr2) CheckInternal((expr1) < (expr2), __FILE__, __LINE__, __FUNCTION__)
#define CHECK_GE(expr1, expr2) CheckInternal((expr1) >= (expr2), __FILE__, __LINE__, __FUNCTION__)
#define CHECK_GT(expr1, expr2) CheckInternal((expr1) > (expr2), __FILE__, __LINE__, __FUNCTION__)

#endif /*__GAME_OF_LIFE_COMMON_H__*/
