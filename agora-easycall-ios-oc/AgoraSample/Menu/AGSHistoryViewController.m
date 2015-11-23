//
//  AGSHistoryViewController.m
//  AgoraSample
//
//  Created by Shilong on 9/17/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSHistoryViewController.h"
#import "AGSCoreDataManager.h"
#import "AGSHistoryCell.h"
#import "NSDate+Helper.h"
#import "FOWebViewController.h"

@interface AGSHistoryViewController ()

@property (strong, nonatomic) NSMutableArray *records;
@property (weak, nonatomic) IBOutlet UITableView *tableView;

@end

@implementation AGSHistoryViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.records = [NSMutableArray array];
    [self.records addObjectsFromArray:[[AGSCoreDataManager shareManager] allRecords]];
    [self.tableView reloadData];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    self.title = NSLocalizedString(@"Conf. History", @"");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

#pragma mark -

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.records.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    AGSHistoryCell *cell = [tableView dequeueReusableCellWithIdentifier:@"HistoryCell" forIndexPath:indexPath];
    
    Record *record = [self.records objectAtIndex:indexPath.row];
    
    cell.dateLabel.text = [record.date dateWithFormat:@"YYYY-MM-dd"];
    cell.durationLabel.text = [NSDate formatStringWithDuration:record.duration.unsignedIntegerValue];
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 122.f;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    Record *record = [self.records objectAtIndex:indexPath.row];
    FOWebViewController *controller = [[FOWebViewController alloc] initWithURL:record.url title:NSLocalizedString(@"Conf. History", @"")];
    [self.navigationController pushViewController:controller animated:YES];
}

@end
