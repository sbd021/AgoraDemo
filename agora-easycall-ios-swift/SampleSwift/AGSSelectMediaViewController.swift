//
//  AGSSelectMediaViewController.swift
//  SampleSwift
//
//  Created by let on 10/28/15.
//  Copyright © 2015 Agora. All rights reserved.
//

public struct AGSKeys {
    static let channel = "Channel";
    static let vendorKey = "VendorKey";
    static let username = "Username";
}

public struct AGSSegueIdentifiers {
    static let select = "Select";
    static let chat = "Chat";
}

import UIKit
import AVFoundation

class AGSSelectMediaViewController: AGSBaseViewController, AGSAlertViewDelegate, AVAudioRecorderDelegate, AVAudioPlayerDelegate {
    
    @IBOutlet weak var roomNumberTextField: UITextField!
    @IBOutlet weak var echoTest: UIButton!
    @IBOutlet weak var videoLabel: UILabel!
    @IBOutlet weak var voiceLabel: UILabel!
    
    //
    lazy var alertView: AGSAlertView = {
        let view = AGSAlertView()
        view.delegate = self
        view.addStatusView(self.echoTestView)
        return view
    }()
    lazy var echoTestView: AGSEchoTestView = {
        let view: AGSEchoTestView = NSBundle.mainBundle().loadNibNamed("AGSEchoTestView", owner: self, options: nil).last as! AGSEchoTestView
        view.volumeView?.numberOfBars = 21
        view.volumeView?.barsColorMin = UIColor.greenColor()
        view.volumeView?.barsColorMax = UIColor.grayColor()
        view.volumeView?.volumenValue = 0
        return view
    }()
    
    //
    lazy var audioSession: AVAudioSession = {
        let session = AVAudioSession.sharedInstance()
        do { try session.setCategory(AVAudioSessionCategoryPlayAndRecord) } catch {}
        do { try session.setActive(true) } catch {}
        return session
    }()
    lazy var audioRecorder: AVAudioRecorder = {
        var settings: [String : AnyObject] = [AVFormatIDKey: NSNumber(unsignedInt: kAudioFormatLinearPCM), AVSampleRateKey: NSNumber(int: 8000), AVNumberOfChannelsKey: NSNumber(int: 1), AVLinearPCMBitDepthKey: NSNumber(int: 8), AVLinearPCMIsFloatKey: NSNumber(bool: true), AVLinearPCMIsBigEndianKey: NSNumber(bool: false)]
        var recorder: AVAudioRecorder!
        do {
            recorder = try AVAudioRecorder(URL: self.filePath(), settings: settings)
            recorder.delegate = self
            recorder.meteringEnabled = true
            
        } catch {}
        return recorder
    }()
    lazy var audioPlayer: AVAudioPlayer = {
        var player = AVAudioPlayer()
        do {
            player = try AVAudioPlayer(contentsOfURL: self.filePath())
            player.delegate = self
            player.numberOfLoops = 0
            player.meteringEnabled = true
            player.prepareToPlay()
        } catch {}
        return player
    }()
    
    var testing: Bool!
    var recorderTimer = NSTimer()
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        navigationController?.navigationBarHidden = false
        
        //
        title = NSLocalizedString("Agora Easy Call", comment: "")
        echoTest.setTitle(NSLocalizedString("Test", comment: ""), forState: UIControlState.Normal)
        roomNumberTextField.placeholder = NSLocalizedString("Enter Room No.", comment: "")
        videoLabel.text = NSLocalizedString("Join Video Call", comment: "")
        voiceLabel.text = NSLocalizedString("Join Voice Call", comment: "")
        
//        if DEBUG == 1 {
//            roomNumberTextField.text = "1024"
//        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // MARK: - Actions
    
    @IBAction func didClickShowEchoTestView(sender: AnyObject) {
        self.startTesting()
    }
    
    @IBAction func didClickMenuButton(sender: AnyObject) {
        frostedViewController.presentMenuViewController()
    }
    
    @IBAction func didClickChatButton(sender: AnyObject) {
        if isValidInput() {
            performSegueWithIdentifier(AGSSegueIdentifiers.chat, sender: sender)
        }
    }
    
    func isValidInput() -> Bool {
        view.endEditing(true)
        if roomNumberTextField.text?.characters.count > 0 {
            return true
        } else {
            UIAlertView(title: "", message: NSLocalizedString("Room No. can not be empty", comment: ""), delegate: nil, cancelButtonTitle: NSLocalizedString("Done", comment: "")).show()
            return false
        }
    }
    
    // MARK: - Start/Stop testing
    
    func startTesting() {
        view.endEditing(true)
        testing = true
        
        // Init and show
        setAlertViewStat(0)
        alertView.showAlertView()
    }
    
    func stopTesting() {
        alertView.hideAlertView()
        testing = false
        // Stop recording and playing
        recorderTimer.invalidate()
        
        audioRecorder.stop()
        audioPlayer.stop()
        do {
            try audioSession.setActive(false)
        } catch {
            
        }
        
    }
    
    // MARK: - Alert View Delegate
    func agsAlertView(alertView: AGSAlertView!, clickedButtonAtIndex buttonIndex: Int) {
        if buttonIndex == 0 {
            stopTesting()
        } else {
            startRecording()
        }
    }
    
    func startRecording() {
        setAlertViewStat(1)
        do { try audioSession.setCategory(AVAudioSessionCategoryRecord) } catch { }
        
        audioRecorder.record()
        // Volume
        NSTimer.scheduledTimerWithTimeInterval(0.1, target: self, selector: Selector("audioRecordPowerChange:"), userInfo: nil, repeats: true)
        // Stop recording
        recorderTimer = NSTimer.scheduledTimerWithTimeInterval(5, target: self, selector: Selector("stopRecording"), userInfo: nil, repeats: false)
    }
    
    func stopRecording() {
        audioRecorder.stop()
    }
    
    // MARK: - Audio Recorder/Player Delegate
    
    func audioRecorderDidFinishRecording(recorder: AVAudioRecorder, successfully flag: Bool) {
        if !testing {
            return;
        }
        
        setAlertViewStat(4)
        
        do { try audioSession.setCategory(AVAudioSessionCategoryPlayback) } catch {}
        audioPlayer.play()
        NSTimer.scheduledTimerWithTimeInterval(0.1, target: self, selector: Selector("audioPlayerPowerChange:"), userInfo: nil, repeats: true)
    }
    
    func audioRecorderEncodeErrorDidOccur(recorder: AVAudioRecorder, error: NSError?) {
        setAlertViewStat(3)
    }
    
    // Player
    
    func audioPlayerDidFinishPlaying(player: AVAudioPlayer, successfully flag: Bool) {
        setAlertViewStat(2)
    }
    
    func audioPlayerDecodeErrorDidOccur(player: AVAudioPlayer, error: NSError?) {
        setAlertViewStat(3)
    }
    
    // MARK: - Others
    
    func audioRecordPowerChange(timer: NSTimer) {
        if audioRecorder.recording {
            audioRecorder.updateMeters()
            let power = audioRecorder.averagePowerForChannel(0)
            let progress = (power + 160) / 160.0
            echoTestView.volumeView?.volumenValue = progress
        } else {
            timer.invalidate()
        }
    }
    
    func audioPlayerPowerChange(timer: NSTimer) {
        if audioPlayer.playing {
            audioPlayer.updateMeters()
            let power = audioPlayer.averagePowerForChannel(0)
            let progress = (power + 160) / 160.0
            echoTestView.volumeView?.volumenValue = progress
        } else {
            timer.invalidate()
        }
    }
    
    func setAlertViewStat(stat: Int) {
        switch (stat) {
        case 0:
            echoTestView.volumeView?.volumenValue = 0
            alertView.titleLabel?.text = NSLocalizedString("Echo Test", comment:"");
            alertView.setSubTitle(NSLocalizedString("Click Test to Start", comment:""), color: UIColor(hexString: "B7B7B7"))
            alertView.setRightButtonText(NSLocalizedString("Echo Test", comment:""), color: UIColor(hexString: "1677CB"))
            alertView.leftButton?.setTitle(NSLocalizedString("Cancel", comment:""), forState: UIControlState.Normal)
            alertView.setButtonEnabled(true)
            
        case 1:
            alertView.setButtonEnabled(false)
            alertView.setSubTitle(NSLocalizedString("Please speak to the phone", comment: ""), color: UIColor(hexString: "B7B7B7"))
            alertView.setRightButtonText(NSLocalizedString("In Testing", comment: ""), color: UIColor(hexString: "999999"))
            alertView.leftButton?.setTitle(NSLocalizedString("Cancel", comment: ""), forState: UIControlState.Normal)

            
        case 2:
            alertView.setButtonEnabled(true)
            alertView.setSubTitle(NSLocalizedString("Click Test to Start", comment:""), color: UIColor(hexString: "B7B7B7"))
            alertView.setRightButtonText(NSLocalizedString("Test Again", comment: ""), color: UIColor(hexString: "1677CB"))
            alertView.leftButton?.setTitle(NSLocalizedString("Done", comment: ""), forState: UIControlState.Normal)
            
        case 3:
            alertView.setButtonEnabled(true)
            alertView.setSubTitle(NSLocalizedString("Click Test to Start", comment:""), color: UIColor(hexString: "B7B7B7"))
            alertView.setRightButtonText(NSLocalizedString("Test Again", comment: ""), color: UIColor(hexString: "1677CB"))
            
        case 4:
            alertView.setSubTitle(NSLocalizedString("Detecting", comment:""), color: UIColor(hexString: "B7B7B7"))
        default:
            break
        }
        
    }
    
    // MARK: -
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
        
        if segue.identifier == AGSSegueIdentifiers.chat {
            let chatViewController: AGSChatViewController = segue.destinationViewController as! AGSChatViewController
            chatViewController.channel(roomNumberTextField.text!)
            
            let button = sender as! UIButton
            if button.tag == 0 {
                chatViewController.type(AGSChatType.Video)
            } else {
                chatViewController.type(AGSChatType.Audio)
            }
        }
    }
    
    // MARK: - Testing Config
    func filePath() -> NSURL {
        var urlStr: String = NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory.DocumentDirectory, NSSearchPathDomainMask.UserDomainMask, true).last!
        urlStr.appendContentsOf("/textRecord.caf")
        return NSURL(fileURLWithPath: urlStr)
    }

}
