//
//  ViewController.m
//  cplusplus_test_ios
//
//  Created by tianqi on 2020/2/3.
//  Copyright © 2020 tianqi. All rights reserved.
//

#import "ViewController.h"
#include "cplusplsu_vector.hpp"
#include "cplusplus_thread.hpp"
#import <QuartzCore/QuartzCore.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#import <AVFoundation/AVFoundation.h>
#include "BaseObject.h"

@interface ViewController ()<UITableViewDelegate, UITableViewDataSource>
//UI
@property (nonatomic, strong) UIButton *testButton;
@property (nonatomic, strong) UITableView *tableView;
//source
@property (nonatomic, strong) NSArray *dataArray;
@end

@implementation ViewController

#define Tableview_Title @"Title"
#define Tableview_Des @"Des"

- (void)viewDidLoad {
  [super viewDidLoad];
  _dataArray = @[@{Tableview_Title:@"vector", Tableview_Des:@"operator_assign"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"reserve"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"resize"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"shrink_to_fit"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"begin_end"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"at"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"assign"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"insert"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"erase"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"swap"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"move"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"move2"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"simple_copy"},
                 @{Tableview_Title:@"vector", Tableview_Des:@"other"},
                 @{Tableview_Title:@"utility", Tableview_Des:@"rvalue"},
                 @{Tableview_Title:@"utility", Tableview_Des:@"forward"},
                 @{Tableview_Title:@"thread", Tableview_Des:@"condition_variable"},
                 @{Tableview_Title:@"move", Tableview_Des:@"local_variable"},
                 @{Tableview_Title:@"algorithm", Tableview_Des:@"quick_sort"},
                 @{Tableview_Title:@"algorithm", Tableview_Des:@"colum_row"},
                 @{Tableview_Title:@"algorithm", Tableview_Des:@"sortlink_merge"},
                 @{Tableview_Title:@"algorithm", Tableview_Des:@"link_cross"},
                 @{Tableview_Title:@"algorithm", Tableview_Des:@"lru"},
                 @{Tableview_Title:@"algorithm", Tableview_Des:@"bit_1_count"}
  ];
  [self buildTableView];
}

- (void) buildTestButton {
  _testButton = [UIButton buttonWithType:UIButtonTypeSystem];
  _testButton.backgroundColor = [UIColor blueColor];
#define kTestWidth 100
#define kTestHeight 50
  [_testButton setFrame:CGRectMake((self.view.frame.size.width - kTestWidth)/2, (self.view.frame.size.height - kTestHeight)/2, kTestWidth, kTestHeight)];
  _testButton.layer.cornerRadius = kTestWidth/4;
  [_testButton.titleLabel setTextColor:[UIColor whiteColor]];
  [_testButton addTarget:self action:@selector(onClickTest) forControlEvents:UIControlEventTouchUpInside];
  [self.view addSubview:_testButton];
  [_testButton setTitle:@"Start" forState:UIControlStateNormal];
}

- (void) buildTableView {
  _tableView = [[UITableView alloc] initWithFrame:self.view.frame style:UITableViewStylePlain];
  _tableView.dataSource = self;
  _tableView.delegate = self;
  [self.view addSubview:_tableView];
}

#pragma mark -  UITableViewDatasource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
  return _dataArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
  UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"tableviewcell"];
  if (!cell) {
    cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"tableviewcell"];
  }
  if (_dataArray[indexPath.row][Tableview_Title]) {
    NSString *label = [NSString stringWithFormat:@"%@_%@",_dataArray[indexPath.row][Tableview_Title], _dataArray[indexPath.row][Tableview_Des]];
    [cell.textLabel setText:label];
    [cell.textLabel sizeToFit];
  }
  return cell;
}

#pragma mark - UITableViewDelegate

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
  return 50;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
  
  NSString *function = [NSString stringWithFormat:@"%@_%@",_dataArray[indexPath.row][Tableview_Title], _dataArray[indexPath.row][Tableview_Des]];
  SEL sel = NSSelectorFromString(function);
  if (sel && [BaseObject respondsToSelector:sel]) {
    [BaseObject performSelector:sel];
  }
}

#pragma mark - operations

- (void)onClickTest {
}

@end
