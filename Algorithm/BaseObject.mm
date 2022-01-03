//
//  BaseObject.m
//  cplusplus_test_ios
//
//  Created by tianqi on 2020/4/29.
//  Copyright © 2020 tianqi. All rights reserved.
//

#import "BaseObject.h"
#include "cplusplus_thread.hpp"
#include "cplusplsu_vector.hpp"
#include "cplusplus_utility.hpp"
#include "cplusplus_move.hpp"
#include "algorithm.hpp"

@implementation BaseObject

+ (void)vector_operator_assign {
  vector_operator_assign();
}

+ (void)vector_reserve {
  vector_reserve();
}

+ (void)vector_resize {
  vector_resize();
}

+ (void)vector_shrink_to_fit {
  vector_shrink_to_fit();
}

+ (void)vector_begin_end {
  vector_begin_end();
}

+ (void)vector_at {
  vector_at();
}

+ (void)vector_assign {
  vector_assign();
}

+ (void)vector_insert {
  vector_insert();
}

+ (void)vector_erase {
  vector_erase();
}

+ (void)vector_swap {
  vector_swap();
}

+ (void)vector_move {
  vector_move();
}

+ (void)vector_move2 {
  vector_move2();
}

+ (void)vector_simple_copy {
  vector_simple_copy();
}

+ (void)vector_other {
  vector_other();
}

+ (void)utility_rvalue {
  utility_rvalue();
}

+ (void)utility_forward {
  utility_forward();
}

+ (void)thread_condition_variable {
  thread_condition_variable();
}

+ (void)move_local_variable {
  move_local_variable();
}

+ (void)algorithm_quick_sort {
    algorithm_quick_sort();
}

+ (void)algorithm_colum_row {
    algorithm_colum_row();
}

+ (void)algorithm_sortlink_merge {
    algorithm_sortlink_merge();
}

+ (void)algorithm_link_cross {
    algorithm_link_cross();
}

+ (void)algorithm_lru {
    algorithm_lru();
}

+ (void)algorithm_bit_1_count {
    algorithm_bit_1_count();
}

@end
