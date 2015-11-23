//
//  AGSMenuViewController.swift
//  SampleSwift
//
//  Created by let on 10/29/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit

enum AGSResolutionType {
    case CIF, Low, Middle, High
    
    func description() -> String {
        switch self {
        case .CIF:
            return "CIF"
        case .Low:
            return "480P"
        case .Middle:
            return "720P"
        case .High:
            return "1080P"
        }
    }
    
    func width() -> Int32 {
        switch self {
        case .CIF:
            return 352
        case .Low:
            return 640
        case .Middle:
            return 1280
        case .High:
            return 1920
        }
    }
    
    func height() -> Int32 {
        switch self {
        case .CIF:
            return 288
        case .Low:
            return 480
        case .Middle:
            return 720
        case .High:
            return 1080
        }
    }
}

class AGSMenuViewController: UITableViewController {
    
    // Closures
    var resolutionChangedHandler: ((AGSResolutionType) -> Void)!
    var frameChangedHandler: ((Int32) -> Void)!
    var rateChangedHandler: ((Int32) -> Void)!
    var volumeChangedHandler: ((Int32) -> Void)!
    
    var recordingChangedHandler: ((Bool) -> Void)!
    var floatWindowChangedHandler: ((Bool) -> Void)!
    
    // IB Outlets
    
    //
    @IBOutlet var menuTitleHistory: UILabel!
    @IBOutlet var menuTitleResolution: UILabel!
    @IBOutlet var menuTitleMaxRate: UILabel!
    @IBOutlet var menuTitleMaxFrame: UILabel!
    @IBOutlet var menuTitleVolume: UILabel!
    @IBOutlet var menuTitleRecording: UILabel!
    @IBOutlet var menuTitleLogPath: UILabel!
    @IBOutlet var menuTitleFloatWindow: UILabel!
    @IBOutlet var menuTitleAbout: UILabel!
    
    //
    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var idLabel: UILabel!
    @IBOutlet var resolutionSlider: UISlider!
    @IBOutlet var resolutionLabel: UILabel!
    @IBOutlet var rateSlider: UISlider!
    @IBOutlet var rateLabel: UILabel!
    @IBOutlet var frameSlider: UISlider!
    @IBOutlet var frameLabel: UILabel!
    @IBOutlet var recordingSwitch: UISwitch!
    @IBOutlet var floatSwitch: UISwitch!
    @IBOutlet var logFilePathLabel: UILabel!
    
    @IBOutlet var volumeSlider: UISlider!
    
    var currentResolutionType: AGSResolutionType?
    var currentRate: Int32?
    var currentFrame: Int32?
    var currentValueFloatWindow: Bool?
    var currentValueRecording: Bool?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        currentResolutionType = AGSResolutionType.Low
        resolutionLabel.text = currentResolutionType?.description()
        resolutionSlider.value = 0.3
        
        currentFrame = 30
        frameLabel.text = "30FPS"
        frameSlider.value = 0.8
        
        currentRate = 2014 * 1024
        rateLabel.text = "1Mbps"
        rateSlider.value = 4.0 * (1.0 / 7.0)
        
        volumeSlider.value = 100.0/255.0
    }

    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        let defaults = NSUserDefaults.standardUserDefaults()
        nameLabel.text = defaults.objectForKey(AGSKeys.username) as? String
        idLabel.text = defaults.objectForKey(AGSKeys.vendorKey) as? String
        
        //
        //
        menuTitleAbout.text = NSLocalizedString("About", comment:"");
        menuTitleFloatWindow.text = NSLocalizedString("Pop up", comment:"");
        menuTitleHistory.text = NSLocalizedString("Conf. History", comment:"");
        
        menuTitleLogPath.text = NSLocalizedString("Log Path", comment:"");
        menuTitleMaxFrame.text = NSLocalizedString("Max. Framerate", comment:"");
        menuTitleMaxRate.text = NSLocalizedString("Max. Bitrate", comment:"");
        
        menuTitleRecording.text = NSLocalizedString("Recording", comment:"");
        menuTitleResolution.text = NSLocalizedString("Video Resolution", comment:"");
        menuTitleVolume.text = NSLocalizedString("Speaker Volume", comment:"");
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // MARK: - IB Actions
    
    @IBAction func didValueChangedResolutionSlider(sender: UISlider) {
        var type: AGSResolutionType!
        
        if sender.value <= 0.25 {
            type = AGSResolutionType.CIF;
        } else if sender.value <= 0.5 {
            type = AGSResolutionType.Low;
        } else if sender.value <= 0.75 {
            type = AGSResolutionType.Middle;
        } else {
            type = AGSResolutionType.High;
        }
        
        if (type != currentResolutionType) {
            currentResolutionType = type
            resolutionLabel.text = type.description()
            if resolutionChangedHandler != nil {
                resolutionChangedHandler(type)
            }
        }
    }
    
    @IBAction func didValueChangedRateSlider(sender: UISlider) {
        let d: Float = 1.0/7.0
        var rate: Int32 = 0
        var string :String
        if sender.value <= d {
            rate = 150 * 1024
            string = "150K";
        } else if (sender.value <= d * 2.0) {
            rate = 500 * 1024;
            string = "500K";
        } else if (sender.value <= d * 3.0) {
            rate = 800 * 1024;
            string = "800K";
        } else if (sender.value <= d * 4.0) {
            rate = 1024 * 1024;
            string = "1M";
        } else if (sender.value <= d * 5.0) {
            rate = 2 * 1024 * 1024;
            string = "2M";
        } else if (sender.value <= d * 6.0) {
            rate = 5 * 1024 * 1024;
            string = "5M";
        } else {
            rate = 10 * 1024 * 1024;
            string = "10M";
        }
        
        if rate != currentRate {
            currentRate = rate
            rateLabel.text = string + "bps"
            if rateChangedHandler != nil {
                rateChangedHandler(currentRate!)
            }
        }
    }
    
    @IBAction func didValueChangedFrameSlider(sender: UISlider) {
        var frame: Int32 = 0
        if sender.value <= 0.2 {
            frame = 15;
        } else if sender.value <= 0.4 {
            frame = 20;
        } else if sender.value <= 0.6 {
            frame = 24;
        } else if sender.value <= 0.8 {
            frame = 30;
        } else {
            frame = 60;
        }
        
        if frame != currentFrame {
            currentFrame = frame
            frameLabel.text = frame.description + "FPS"
            if frameChangedHandler != nil {
                frameChangedHandler(currentFrame!)
            }
        }
    }

    @IBAction func didValueChangedVolumeSlider(sender: UISlider) {
        let volume = 255.0 * sender.value
        
        if volumeChangedHandler != nil {
            volumeChangedHandler(Int32(volume))
        }
    }
    
    @IBAction func didValueChangedRecordingSwitch(sender: UISwitch) {
        if recordingChangedHandler != nil {
            recordingChangedHandler(sender.on)
        }
    }
    
    @IBAction func didValueChangedFloatSwitch(sender: UISwitch) {
        if floatWindowChangedHandler != nil {
            floatWindowChangedHandler(sender.on)
        }
    }
    
//    func resolutionChanged(closure: (AGSResolutionType) -> Void) {
//        
//    }
//    
//    func frameChanged(closure: (Int) -> Void) {
//        
//    }
//    
//    func rateChanged(closure: (Int) -> Void) {
//        
//    }
//    
//    func recordingChanged(closure: (Bool) -> Void) {
//        
//    }
//    
//    func floatWindowChanged(closure: (Bool) -> Void) {
//        
//    }
    
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
