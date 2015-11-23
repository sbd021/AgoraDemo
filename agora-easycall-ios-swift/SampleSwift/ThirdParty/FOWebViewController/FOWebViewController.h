//
//  FOWebViewController.h
//  Union App
//
//  Created by Shilong on 15/3/16.
//  Copyright (c) 2015年 FocusoneChina. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NJKWebViewProgress.h"
#import "NJKWebViewProgressView.h"

@interface FOWebViewController : UIViewController <NJKWebViewProgressDelegate, UIWebViewDelegate>

@property (nonatomic, weak) IBOutlet UIWebView *webView;
- (id)initWithURL:(NSString *)urlString title:(NSString *)title;

@end
