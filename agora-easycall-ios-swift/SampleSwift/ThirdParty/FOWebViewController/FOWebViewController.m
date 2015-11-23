//
//  FOWebViewController.m
//  Union App
//
//  Created by Shilong on 15/3/16.
//  Copyright (c) 2015年 FocusoneChina. All rights reserved.
//

#import "FOWebViewController.h"

@interface FOWebViewController ()

@end

@implementation FOWebViewController
{
    IBOutlet UIView *naviBarView;
    IBOutlet UILabel *titleLabel;
    NJKWebViewProgressView *_progressView;
    NJKWebViewProgress *_progressProxy;
    NSString *titleText_;
    NSString *_urlString;
}

- (id)initWithURL:(NSString *)urlString title:(NSString *)title
{
    self = [self init];
    if (self) {
        _urlString = urlString;
        titleText_ = title;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    naviBarView = self.navigationController.navigationBar;
    _progressProxy = [[NJKWebViewProgress alloc] init];
    _webView.delegate = _progressProxy;
    _progressProxy.webViewProxyDelegate = self;
    _progressProxy.progressDelegate = self;
    
    CGFloat progressBarHeight = 2.f;
    CGRect barFrame = CGRectMake(0, naviBarView.bounds.size.height - progressBarHeight, naviBarView.bounds.size.width, progressBarHeight);
    _progressView = [[NJKWebViewProgressView alloc] initWithFrame:barFrame];
    _progressView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleTopMargin;
    
    
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = NO;
    
    [naviBarView addSubview:_progressView];
    self.title = titleText_;
    
    [self startLoadWebView];
}

- (void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    // Remove progress view
    // because UINavigationBar is shared with other ViewControllers
    
    [_progressView removeFromSuperview];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)startLoadWebView
{
    NSURL *url = [NSURL URLWithString:_urlString];
    NSURLRequest *request =[NSURLRequest requestWithURL:url];
    [_webView loadRequest:request];
}

#pragma mark - NJKWebViewProgressDelegate
-(void)webViewProgress:(NJKWebViewProgress *)webViewProgress updateProgress:(float)progress
{
    [_progressView setProgress:progress animated:YES];
}

- (IBAction)click_btn_back:(id)sender {
    [self.navigationController popViewControllerAnimated:TRUE];
}

@end
