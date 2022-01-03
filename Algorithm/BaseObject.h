//
//  BaseObject.h
//  cplusplus_test_ios
//
//  Created by tianqi on 2020/4/29.
//  Copyright © 2020 tianqi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BaseObject : NSObject
//operators
+ (void)vector_operator_assign;
//vecotr functions
+ (void)vector_reserve;
+ (void)vector_resize;
+ (void)vector_shrink_to_fit;
+ (void)vector_begin_end;
+ (void)vector_at;
+ (void)vector_assign;
+ (void)vector_insert;
+ (void)vector_erase;
+ (void)vector_swap;
+ (void)vector_move;
+ (void)vector_simple_copy;
+ (void)vector_other;
//utility
+ (void)utility_rvalue;
+ (void)utility_forward;
//thread
+ (void)thread_condition_variable;
//move
+ (void)move_local_variable;
/*****************************************************
 *算法
 *****************************************************/
//快速排序
+ (void)algorithm_quick_sort;
/**
 NxN的棋盘，每个格子可以放一个车，有M个车，问：每个车放完后，棋盘还剩多少格子是所有车攻击范围外？
 */
+ (void)algorithm_colum_row;
/**
 . # . .
 . . . .
 .# . .
 #表示一堵墙，. 表示空隙，可以在墙或者空隙处安放炸弹，要求炸弹爆炸能够覆盖到所有的墙，如果找不到这样的位置，返回-1；否则返回安放炸弹的位置坐标。
 */
+ (void)algorithm_sortlink_merge;
/**
 两个单向链表h1，h2（没有环），判断是否有交叉，若无交叉，返回-1；若有交叉，返回家差点指针
 */
+ (void)algorithm_link_cross;

/**
 LRU算法
 */
+ (void)algorithm_lru;

/**
 求二进制数中1的个数
 */
+ (void)algorithm_bit_1_count;

@end

NS_ASSUME_NONNULL_END
