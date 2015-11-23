//
//  AGSMenuViewController.m
//  AgoraSample
//
//  Created by Shilong on 9/16/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSMenuViewController.h"
#import "AGSSelectMediaViewController.h"

@implementation AGSResolution

+ (instancetype)resolutionWithType:(AGSResolutionType)type
{
    AGSResolution *re = [[self alloc] init];
    if (type == AGSResolutionTypeCIF) {
        re.width = @352;
        re.height = @288;
    } else if (type == AGSResolutionTypeLow) {
        re.width = @640;
        re.height = @480;
    } else if (type == AGSResolutionTypeMiddle) {
        re.width = @1280;
        re.height = @720;
    } else {
        re.width = @1920;
        re.height = @1080;
    }
    return re;
}

+ (NSString *)resolutionFormatWithType:(AGSResolutionType)type;
{
    NSString *string = @"";
    if (type == AGSResolutionTypeCIF) {
        string = @"CIF";
    } else if (type == AGSResolutionTypeLow) {
        string = @"480P";
    } else if (type == AGSResolutionTypeMiddle) {
        string = @"720P";
    } else {
        string = @"1080P";
    }
    return string;
}

@end


@interface AGSMenuViewController ()

//
@property (weak, nonatomic) IBOutlet UILabel *menuTitleHistory;
@property (weak, nonatomic) IBOutlet UILabel *menuTitleResolution;
@property (weak, nonatomic) IBOutlet UILabel *menuTitleMaxRate;
@property (weak, nonatomic) IBOutlet UILabel *menuTitleMaxFrame;
@property (weak, nonatomic) IBOutlet UILabel *menuTitleVolume;
@property (weak, nonatomic) IBOutlet UILabel *menuTitleRecording;
@property (weak, nonatomic) IBOutlet UILabel *menuTitleLogPath;
@property (weak, nonatomic) IBOutlet UILabel *menuTitleFloatWindow;
@property (weak, nonatomic) IBOutlet UILabel *menuTitleAbout;

@property (weak, nonatomic) IBOutlet UILabel *nameLabel;
@property (weak, nonatomic) IBOutlet UILabel *idLabel;

@property (weak, nonatomic) IBOutlet UISlider *resolutionSlider;
@property (weak, nonatomic) IBOutlet UILabel *resolutionLabel;

@property (weak, nonatomic) IBOutlet UISlider *rateSlider;
@property (weak, nonatomic) IBOutlet UILabel *rateLabel;

@property (weak, nonatomic) IBOutlet UISlider *frameSlider;
@property (weak, nonatomic) IBOutlet UILabel *frameLabel;

@property (weak, nonatomic) IBOutlet UISwitch *maxRateSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *recordingSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *floatSwitch;

@property (weak, nonatomic) IBOutlet UISlider *volumeSlider;

@property (weak, nonatomic) IBOutlet UILabel *logFilePathLabel;

//@property (nonatomic) NSUserDefaults *defaults;

@property (nonatomic) AGSResolutionType currentResolutionType;
@property (nonatomic) int currentRate;
@property (nonatomic) int currentFrame;
@property (nonatomic) BOOL currentValueFloatWindow;
@property (nonatomic) BOOL currentValueRecording;

@end

@implementation AGSMenuViewController

#pragma mark -

- (IBAction)didValueChangedResolutionSlider:(UISlider *)sender {
    AGSResolutionType type = AGSResolutionTypeHigh;
    
    if (sender.value <= 0.25) {
        type = AGSResolutionTypeCIF;
    } else if (sender.value <= 0.5) {
        type = AGSResolutionTypeLow;
    } else if (sender.value <= 0.75) {
        type = AGSResolutionTypeMiddle;
    } else {
        type = AGSResolutionTypeHigh;
    }
    
    if (type != self.currentResolutionType) {
        self.currentResolutionType = type;
        self.resolutionLabel.text = [AGSResolution resolutionFormatWithType:type];
        if (self.resolutionBlock) {
            self.resolutionBlock([AGSResolution resolutionWithType:type]);
        }
    }
}

- (IBAction)didValueChangedRateSlider:(UISlider *)sender {
    float d = 1.0/7.0;
    int rate = 0;
    NSString *string = nil;
    if (sender.value <= d) {
        rate = 150 * 1024;
        string = @"150K";
    } else if (sender.value <= d * 2.0) {
        rate = 500 * 1024;
        string = @"500K";
    } else if (sender.value <= d * 3.0) {
        rate = 800 * 1024;
        string = @"800K";
    } else if (sender.value <= d * 4.0) {
        rate = 1024 * 1024;
        string = @"1M";
    } else if (sender.value <= d * 5.0) {
        rate = 2 * 1024 * 1024;
        string = @"2M";
    } else if (sender.value <= d * 6.0) {
        rate = 5 * 1024 * 1024;
        string = @"5M";
    } else {
        rate = 10 * 1024 *1024;
        string = @"10M";
    }
    
    if (rate != self.currentRate) {
        self.currentRate = rate;
        self.rateLabel.text = [NSString stringWithFormat:@"%@bps", string];
        if (self.rateBlock) {
            self.rateBlock(self.currentRate);
        }
    }
}

- (IBAction)didValueChangedFrameSlider:(UISlider *)sender {
    int frame = 0;
    if (sender.value <= 0.2) {
        frame = 15;
    } else if (sender.value <= 0.4) {
        frame = 20;
    } else if (sender.value <= 0.6) {
        frame = 24;
    } else if (sender.value <= 0.8) {
        frame = 30;
    } else {
        frame = 60;
    }
    
    if (frame != self.currentFrame) {
        self.currentFrame = frame;
        self.frameLabel.text = [NSString stringWithFormat:@"%dFPS", frame];
        if (self.frameBlock) {
            self.frameBlock(self.currentFrame);
        }
    }
}

- (IBAction)didValueChangedVolumeSlider:(UISlider *)sender {
    int volume = 255 * sender.value;
    
    if (self.volumeBlock) {
        self.volumeBlock(volume);
    }
    
}

- (IBAction)didValueChangedRecordingSwitch:(UISwitch *)sender {
    if (self.recordingBlock) {
        self.recordingBlock(sender.on);
    }
}

- (IBAction)didValueChangedFloatSwitch:(UISwitch *)sender {
    if (self.floatWindowBlock) {
        self.floatWindowBlock(sender.on);
    }
}

#pragma mark -

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.currentResolutionType = AGSResolutionTypeLow;
    self.resolutionLabel.text = @"480P";
    self.resolutionSlider.value = 0.3;
    
    self.currentFrame = 30;
    self.frameLabel.text = @"30FPS";
    self.frameSlider.value = 0.8;
    
    self.currentRate = 1024 * 1024;
    self.rateSlider.value = 4.0 * (1.0/7.0);
    self.rateLabel.text = @"1Mbps";
    
    self.volumeSlider.value = 100.0/255.0;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    self.nameLabel.text = [userDefaults objectForKey:AGSKeyUsername];
    self.idLabel.text = [userDefaults objectForKey:AGSKeyVendorKey];
    
    //
    self.menuTitleAbout.text = NSLocalizedString(@"About", @"");
    self.menuTitleFloatWindow.text = NSLocalizedString(@"Pop up", @"");
    self.menuTitleHistory.text = NSLocalizedString(@"Conf. History", @"");
    
    self.menuTitleLogPath.text = NSLocalizedString(@"Log Path", @"");
    self.menuTitleMaxFrame.text = NSLocalizedString(@"Max. Framerate", @"");
    self.menuTitleMaxRate.text = NSLocalizedString(@"Max. Bitrate", @"");
    
    self.menuTitleRecording.text = NSLocalizedString(@"Recording", @"");
    self.menuTitleResolution.text = NSLocalizedString(@"Video Resolution", @"");
    self.menuTitleVolume.text = NSLocalizedString(@"Speaker Volume", @"");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
