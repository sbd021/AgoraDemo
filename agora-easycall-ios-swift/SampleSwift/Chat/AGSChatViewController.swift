//
//  AGSChatViewController.swift
//  SampleSwift
//
//  Created by let on 10/8/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit
import UIKit.UINavigationController
import Foundation

class AGSChatViewController:  UIViewController, UICollectionViewDelegate, UICollectionViewDataSource, AGSAlertViewDelegate, RatingBarDelegate, UITableViewDataSource, AGSChatCellDelegate, UIAlertViewDelegate {

    //
    var chatType = AGSChatType.Video // Swift only
    var duration: UInt = 0
    
    //
    var lastStat_ = AgoraRtcStats()
    var isErrorKey_ = false
    var fullscreenUid_: UInt!
    var localVideoCanvas_: AgoraRtcVideoCanvas!
    
    // IBOutlet
    //
    @IBOutlet weak var controlTitleMuteLabel: UILabel!
    @IBOutlet weak var controlTitleMuteAudioLabel: UILabel!
    @IBOutlet weak var controlTitleSpeakerLabel: UILabel!
    @IBOutlet weak var controlTitleSpeakerAudioLabel: UILabel!
    @IBOutlet weak var controlTitleSwitchLabel: UILabel!
    @IBOutlet weak var controlTitleCloseLabel: UILabel!
    
    //
    @IBOutlet var audioControlView: UIView!
    @IBOutlet var videoControlView: UIView!
    @IBOutlet var speakerControlButtons: [UIButton]!
    @IBOutlet var audioMuteControlButtons: [UIButton]!
    @IBOutlet var cameraControlButton: UIButton!
    
    @IBOutlet var videoMainView: UIView!
    
    @IBOutlet var collectionView: UICollectionView!
    
    @IBOutlet var statContrainerView: UIView!
    @IBOutlet var talkTimeLabel: UILabel!
    @IBOutlet var dataTrafficLabel: UILabel!
    @IBOutlet var alertLabel: UILabel!
    @IBOutlet var networkImageView: UIImageView!
    
    @IBOutlet var videoButton: UIButton!
    @IBOutlet var audioButton: UIButton!
    
    var agoraKit: AgoraRtcEngineKit!
    var uids: [UInt] = []
    var videoMuteForUids: [UInt: Bool] = [:]
    
    //
    var type: AGSChatType? {
        didSet {
            if type == AGSChatType.Video {
                videoControlView.hidden = false
                audioControlView.hidden = true
                
                videoButton.selected = true
                audioButton.selected = false
                
                self.videoMainView.hidden = false
            } else {
                videoControlView.hidden = true
                audioControlView.hidden = false
                
                videoButton.selected = false
                audioButton.selected = true
                
                self.videoMainView.hidden = true
            }
            collectionView.reloadData()
        }
    }
    var channel: String!
    var key: String!
    var agoraVideoEnabled: Bool!
    var durationTimer: NSTimer?
    
    //
    var callId: String!
    var rating: Float = 0
    var startDate: NSDate!
    var myUid: UInt!
    var firstJoinedUid: UInt = 0
    
    //
    var activityStrings: [String] = []
    @IBOutlet var tableView: UITableView!
    @IBOutlet var activityContrainerView: UIView!
    
    lazy var errorKeyAlert: UIAlertView = {
        var alert = UIAlertView.init(title: "", message: NSLocalizedString("Vendor key incorrect, please update user information", comment: ""), delegate: self, cancelButtonTitle: NSLocalizedString("Done", comment: ""))
        return alert
    }()
    
    
    func channel(channel: String) { // Replacment for "dictionary" in ObjC
        self.channel = channel
    }
    
    func type(type: AGSChatType) {
        chatType = type
    }
    
    
    // MARK: - View
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        key = NSUserDefaults.standardUserDefaults().stringForKey(AGSKeys.vendorKey)
        type = chatType
        
        prepareAgoraKit()
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        let key = NSUserDefaults.standardUserDefaults().stringForKey(AGSKeys.vendorKey)
        if isErrorKey_ || (self.key != key) {
            self.key = key
            clearData()
            prepareAgoraKit()
        }
        
        //
        title = NSLocalizedString("Room", comment: "") + " " + channel
        
        controlTitleCloseLabel.text = NSLocalizedString("Camera Off", comment: "")
        controlTitleMuteAudioLabel.text = NSLocalizedString("Mute", comment: "")
        controlTitleMuteLabel.text = NSLocalizedString("Mute", comment: "")
        controlTitleSpeakerAudioLabel.text = NSLocalizedString("Speaker", comment: "")
        controlTitleSpeakerLabel.text = NSLocalizedString("Speaker", comment: "")
        controlTitleSwitchLabel.text = NSLocalizedString("Switch Camera", comment: "")
        
        videoButton.setTitle(NSLocalizedString("Video Call", comment: ""), forState:UIControlState.Normal)
        audioButton.setTitle(NSLocalizedString("Voice Call", comment: ""), forState:UIControlState.Normal)
        
        self.talkTimeLabel.text = NSLocalizedString("Total Time", comment: "")
        self.dataTrafficLabel.text = NSLocalizedString("Total Trafic", comment: "")
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // MARK: - Delegates
    
    // Table view
    
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return activityStrings.count
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("ChatActivityCell", forIndexPath: indexPath) as! AGSChatActivityCell
        cell.titleLabel.text = activityStrings[indexPath.row]
        if indexPath.row == tableView.numberOfRowsInSection(0) - 1 {
            cell.titleLabel.textColor = UIColor.whiteColor()
        } else {
            cell.textLabel?.textColor = UIColor(white: 1, alpha: 0.6)
        }
        return cell
    }
    
    // Collection view
    
    func collectionView(collectionView: UICollectionView, didSelectItemAtIndexPath indexPath: NSIndexPath) {
        let cell = collectionView.cellForItemAtIndexPath(indexPath) as! AGSChatCell
        agoraKit.switchView(fullscreenUid_, andAnother: cell.uid)
        
        // Switch two UID
        let temp = cell.uid
        cell.uid = fullscreenUid_
        fullscreenUid_ = temp
    }
    
    func collectionView(collectionView: UICollectionView, cellForItemAtIndexPath indexPath: NSIndexPath) -> UICollectionViewCell {
        let cell = collectionView.dequeueReusableCellWithReuseIdentifier("CollectionViewCell", forIndexPath: indexPath) as! AGSChatCell
        cell.delegate = self
        
        // Get info
        let uid = uids[indexPath.row]
        let videoMute = videoMuteForUids[uid]

        if type == AGSChatType.Video {
            if (videoMute!) {
                cell.type = AGSChatType.Audio
            } else {
                cell.type = AGSChatType.Video
                cell.uid = uid
                agoraKit.setupRemoteVideo(cell.canvas)
            }
        } else {
            cell.type = AGSChatType.Audio
        }
        
        // Name
        cell.nameLabel.text = uid.description
        
        return cell
    }
    
    func collectionView(collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return self.uids.count
    }
    
    // Cell
    
    func cell(cell: AGSChatCell, didMuteAudio muted: Bool?) {
        print("make user: " + cell.uid.description + "audio" + (muted! ? "muted" : "unmuted"))
        agoraKit.muteAllRemoteAudioStreams(muted!)
    }
    
    // Rating
    
    func ratingChanged(newRating: Float) {
        self.rating = newRating
    }
    
    // App Alert
    
    func agsAlertView(alertView: AGSAlertView!, clickedButtonAtIndex buttonIndex: Int) {
        if buttonIndex == 1 {
            agoraKit.rate(self.callId, rating: Int(self.rating), description: nil)
        }
        
        alertView.hideAlertView()
        delay(0.5) { () -> () in
            self.navigationController?.popViewControllerAnimated(true)
        }
    }
    
    // Default Alert
    
    func alertView(alertView: UIAlertView, clickedButtonAtIndex buttonIndex: Int) {
        if alertView.isEqual(self.errorKeyAlert) {
            let controller = self.frostedViewController.menuViewController.storyboard?.instantiateViewControllerWithIdentifier("Profile")
            self.navigationController?.pushViewController(controller!, animated: true)
        }
    }

    // MARK: - Tool
    
    func prepareAgoraKit()
    {
        initAgoraKit()
        joinChannel()
    }
    
    func clearData() {
        uids.removeAll()
        videoMuteForUids.removeAll()
        activityStrings.removeAll()
        
        tableView.reloadData()
        collectionView.reloadData()
    }

    func initAgoraKit()
    {
        agoraKit = nil
        
        agoraKit = AgoraRtcEngineKit.sharedEngineWithVendorKey(key, error: { (errorCode: AgoraRtcErrorCode) -> Void in
            if errorCode == AgoraRtcErrorCode.Error_NoError {
                print("agora kit init successfully")
            } else {
                if errorCode == AgoraRtcErrorCode.Error_InvalidVendorKey {
                    self.isErrorKey_ = true
                    self.agoraKit.leaveChannel(nil)
                    self.errorKeyAlert.show()
                }
            }
        })

        AGSChatEncryptObserver.registerEncryptObserver(agoraKit)

        var filePath: String = NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory.DocumentDirectory, NSSearchPathDomainMask.UserDomainMask, true).first!
        filePath.appendContentsOf("/agora.log")
        agoraKit.setLogFile(filePath)
        agoraKit.setSpeakerphoneVolume(200)
        agoraKit.enableNetworkTest()
        
        setUpVideo()
        setUpBlocks()
        setUpMenuSettingBlocks()
    }
    
    func joinChannel()
    {
        agoraKit.joinChannelByKey(key, channelName: channel, info: nil, uid: 0) { (channel, uid, elapsed) -> Void in
            self.showAlertLabelWithString(NSLocalizedString("Waiting for attendees", comment: ""))
            self.isErrorKey_ = false
            
            if self.type == AGSChatType.Audio {
                self.agoraKit.disableVideo()
                self.agoraKit.setEnableSpeakerphone(true)
                self.selectSpeakerButtons(false)
            } else {
                self.agoraKit.setEnableSpeakerphone(true)
                self.selectSpeakerButtons(false)
            }
            
            //
            self.callId = self.agoraKit.getCallId()
            self.startDate = NSDate()
            self.myUid = uid
            
            //
            UIApplication.sharedApplication().idleTimerDisabled = true
        }
    }
    
    func setUpVideo() {
        agoraKit.enableVideo()
        localVideoCanvas_ = AgoraRtcVideoCanvas()
        localVideoCanvas_.uid = 0
        localVideoCanvas_.view = videoMainView
        localVideoCanvas_.renderMode = AgoraRtcRenderMode.Render_Hidden
        agoraKit.setupLocalVideo(localVideoCanvas_)
        
        fullscreenUid_ = 0
    }
    
    func updateActivityTableView() {
        let lastIndexPath = NSIndexPath(forRow: activityStrings.count-1, inSection: 0)
        tableView.insertRowsAtIndexPaths([lastIndexPath], withRowAnimation: UITableViewRowAnimation.None)
        tableView.reloadRowsAtIndexPaths([NSIndexPath(forRow: lastIndexPath.row-1, inSection: lastIndexPath.section)], withRowAnimation: UITableViewRowAnimation.Fade)
        tableView.scrollToRowAtIndexPath(lastIndexPath, atScrollPosition: UITableViewScrollPosition.Bottom, animated: true)
    }
    
    func setUpBlocks() {
        //
        // Network qulity of myself
        //
        self.agoraKit.networkQualityBlock { (quality: AgoraRtcQuality) -> Void in
            var imageName :String!
            switch quality {
            case .Quality_Down:
                imageName = "ic_room_signal_none"
            case .Quality_VBad, .Quality_Bad:
                imageName = "ic_room_signal_one"
            case .Quality_Good, .Quality_Poor:
                imageName = "ic_room_signal_two"
            case .Quality_Excellent:
                imageName = "ic_room_signal_three"
            default:
                imageName = "ic_room_signal_none"
            }
            self.networkImageView.image = UIImage(named: imageName)
        }
        
        //
        // Session status
        //
        self.agoraKit.rtcStatsBlock { (stat :AgoraRtcStats!) -> Void in
            // Update talk time
            if self.duration == 0 {
                self.talkTimeLabel.text = "00:00"
                self.durationTimer = NSTimer.scheduledTimerWithTimeInterval(1, target: self, selector: Selector("updateTalkTimeLabel"), userInfo: nil, repeats: true)
            }
            
            let traffic = (stat.txBytes + stat.rxBytes - self.lastStat_.txBytes - self.lastStat_.rxBytes) / 1024
            let speed = traffic / (stat.duration - self.lastStat_.duration)
            self.dataTrafficLabel.text = speed.description + "KB/s"
            
            self.lastStat_ = stat
        }
        
        //
        // User joined
        //
        agoraKit.userJoinedBlock { (uid, elapsed) -> Void in
            //
            if self.firstJoinedUid == 0 {
                self.firstJoinedUid = uid
            }
            
            //
            self.hideAlertLabel()
            self.uids.append(uid)
            
            self.videoMuteForUids.updateValue(false, forKey: uid) // Swift only
            
            self.collectionView.insertItemsAtIndexPaths([NSIndexPath(forRow: self.uids.count-1, inSection: 0)])
            
            //
            self.activityStrings.append(uid.description + " " + NSLocalizedString("joined room", comment: ""))
            self.updateActivityTableView()
        }
        
        //
        // User offline
        //
        agoraKit.userOfflineBlock { (uid) -> Void in
            if let index = self.uids.indexOf(uid) {
                
                if self.fullscreenUid_ == uid {
                    self.agoraKit.setupLocalVideo(self.localVideoCanvas_)
                    
                    self.agoraKit.disableVideo()
                    self.delay(0.3, closure: { () -> () in
                        self.agoraKit.enableVideo()
                    })
                    
                }
                
                self.uids.removeAtIndex(index)
                self.collectionView.deleteItemsAtIndexPaths([NSIndexPath(forRow: index, inSection: 0)])
            }
            
            self.activityStrings.append(uid.description + " " + NSLocalizedString("left room", comment: ""))
            self.updateActivityTableView()
        }
        
        //
        // Leave channel
        //
        agoraKit.leaveChannelBlock { (stat) -> Void in
            if self.isErrorKey_ {return}
            
            //
            self.durationTimer?.invalidate()
            
            // Rating view
            let view: AGSRatingView = NSBundle.mainBundle().loadNibNamed("AGSRatingView", owner: nil, options: nil).last as! AGSRatingView
            view.frame = CGRectMake(50, 200, 170, 61)
            view.delegate = self
            
            if (self.lastStat_.rxBytes > 0) {
                let traffic = Double(self.lastStat_.rxBytes + self.lastStat_.txBytes) / (1024.0 * 1024.0)
                view.dataTrafficLabel?.text = String(format: "%.2fMB", traffic)
            }
            if self.duration > 0 {
                view.talkTimeLabel?.text = self.talkTimeLabel.text
            }
            
            // Alert
            let alert = AGSAlertView()
            alert.delegate = self
            alert.addStatusView(view)
            alert.titleLabel?.text = NSLocalizedString("Please rate the call", comment: "")
            alert.subTitleLabel?.text = NSLocalizedString("Let's do better", comment: "")
            alert.subTitleLabel?.textColor = UIColor(red: 220/255.0, green: 186/255.0, blue: 117/255.0, alpha: 1)
            alert.leftButton?.setTitle(NSLocalizedString("Close", comment: ""), forState: UIControlState.Normal)
            alert.rightButton?.setTitle(NSLocalizedString("Rate", comment: ""), forState: UIControlState.Normal)
            
            alert.showAlertView()
            
            // Save record
            if self.firstJoinedUid != 0 {
//                let url = self.agoraKit.makeQualityReportUrl(self.callId, listenerUid: self.firstJoinedUid, speakerrUid: self.myUid, reportFormat: AgoraRtcQualityReportFormat.QualityReportFormat_Html)
//                AGSCoreDataManager.shareManager.saveRecord(self.callId, date: self.startDate, duration: self.duration, url: url)
            }
            
            //
            UIApplication.sharedApplication().idleTimerDisabled = true
        }
        
        //
        // Video
        //
        agoraKit.userMuteVideoBlock { (uid, muted) -> Void in
            print("user" + uid.description + "video" + (muted ? "muted" : "unmuted"))
        
            self.videoMuteForUids.updateValue(muted, forKey: uid)
            
            self.collectionView.reloadItemsAtIndexPaths([NSIndexPath(forRow: self.uids.indexOf(uid)!, inSection: 0)])
            
            if muted {
                self.activityStrings.append(uid.description + " " + NSLocalizedString("disabled camera", comment: ""))
            } else {
                self.activityStrings.append(uid.description + " " + NSLocalizedString("enabled camera", comment: ""))
            }
            self.updateActivityTableView()
        }
        
        //
        // Audio
        //
        agoraKit.userMuteAudioBlock { (uid, muted) -> Void in
            print("user" + uid.description + "audio" + (muted ? "muted" : "unmuted"))
            
            if muted {
                self.activityStrings.append(uid.description + " " + NSLocalizedString("disabled microphone", comment: ""))
            } else {
                self.activityStrings.append(uid.description + " " + NSLocalizedString("enabled microphone", comment: ""))
            }
            self.updateActivityTableView()
        }
        
        //
        // Connection lost
        //
        agoraKit.connectionLostBlock { () -> Void in
            self.showAlertLabelWithString(NSLocalizedString("No network connection, please check your network", comment: ""))
        }
        
        //
        // Qulity
        //
        agoraKit.audioQualityBlock { (uid, quality, delay, lost) -> Void in
            if let index = self.uids.indexOf(uid) {
                let cell = self.collectionView.cellForItemAtIndexPath(NSIndexPath(forRow: index, inSection: 0)) as! AGSChatCell
                cell.networkQulity = quality
            }
        }
        
        //
        // Exception for recording
        //
//        agoraKit.audioRecorderExceptionBlock { (elapsed) -> Void in
//            print("audio recorder exception")
//        }
        
        //
        // Local video
        //
        agoraKit.firstLocalVideoFrameBlock { (width, height, elapsed) -> Void in
            self.videoMainView.frame = (self.videoMainView.superview?.bounds)!
        }
    }
    
    func setUpMenuSettingBlocks() {
        let menu = self.frostedViewController.menuViewController as! AGSMenuViewController
        
        //
        // Resolution
        //
//        menu.resolutionChangedHandler =  { (resolution) -> Void in
//            self.agoraKit.setVideoResolution(resolution.width(), andHeight: resolution.height())
//        }
        
        //
        // Float window
        //
        menu.floatWindowChangedHandler =  { (floatWindow) -> Void in
            self.activityContrainerView.hidden = !floatWindow
            self.statContrainerView.backgroundColor = floatWindow ? UIColor.clearColor() : UIColor(white: 0, alpha: 0.4)
        }
        
        //
        // Recording
        //
        menu.recordingChangedHandler = { (recording) -> Void in
            if recording {
                var filePath: String = NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory.DocumentDirectory, NSSearchPathDomainMask.UserDomainMask, true).first!
                filePath.appendContentsOf("/recording")
                if !NSFileManager.defaultManager().fileExistsAtPath(filePath) {
                    do { try NSFileManager.defaultManager().createDirectoryAtPath(filePath, withIntermediateDirectories: false, attributes: nil) } catch { }
                }
                filePath.appendContentsOf(NSDate().timeIntervalSinceNow.description + ".wav")
                self.agoraKit .startAudioRecording(filePath)
            } else {
                self.agoraKit.stopAudioRecording()
            }
        }
        
        //
        // Video rate
        //
//        menu.rateChangedHandler = {
//            self.agoraKit.setVideoMaxBitrate($0)
//        }
        
        //
        // Video frame
        //
//        menu.frameChangedHandler = {
//            self.agoraKit.setVideoMaxFrameRate($0)
//        }
    }
    
    func showAlertLabelWithString(text: String) {
        alertLabel.hidden = false
        alertLabel.text = text
    }
    
    func hideAlertLabel() {
        alertLabel.hidden = true
    }
    
    func updateTalkTimeLabel() {
        duration++
        let seconds = duration % 60
        let minutes = (duration - seconds) / 60
        talkTimeLabel.text = String(format: "%02d:%02d", minutes, seconds)
    }
    
    func selectSpeakerButtons(selected:Bool)
    {
        for btn in speakerControlButtons {
            btn.selected = selected
        }
    }
    
    func selectAudioMuteButtons(selected: Bool) {
        for btn in audioMuteControlButtons {
            btn.selected = selected
        }
    }
    
    func delay(delay:Double, closure:()->()) {
        dispatch_after(
            dispatch_time(
                DISPATCH_TIME_NOW,
                Int64(delay * Double(NSEC_PER_SEC))
            ),
            dispatch_get_main_queue(), closure)
    }
    
    // MARK: - IB Action
    
    @IBAction func didClickBcakView(sender: AnyObject) {
        showAlertLabelWithString(NSLocalizedString("Exiting", comment: ""))
        if isErrorKey_ {
            navigationController?.popViewControllerAnimated(true)
        } else {
            weak var weakSelf = self
            agoraKit.leaveChannel { (_) -> Void in
                if let strongSelf = weakSelf {
                    strongSelf.durationTimer?.invalidate()
                    strongSelf.navigationController?.popViewControllerAnimated(true)
                    UIApplication.sharedApplication().idleTimerDisabled = false
                }
            }
        }
    }
    
    @IBAction func didClickAudioMuteButton(btn: UIButton) {
        selectAudioMuteButtons(!btn.selected)
        agoraKit.muteLocalAudioStream(btn.selected)
    }
    
    @IBAction func didClickSpeakerButton(btn: UIButton) {
        agoraKit.setEnableSpeakerphone(!agoraKit.isSpeakerphoneEnabled())
        selectSpeakerButtons(!agoraKit.isSpeakerphoneEnabled())
    }
    
    @IBAction func didClickVideoMuteButton(btn: UIButton) {
        btn.selected = !btn.selected
        agoraKit.muteLocalVideoStream(btn.selected)
        videoMainView.hidden = btn.selected
    }
    
    @IBAction func didClickSwitchButton(btn: UIButton) {
        btn.selected = !btn.selected
        agoraKit.switchCamera()
    }
    
    @IBAction func didClickHungUpButton(btn: UIButton) {
        showAlertLabelWithString(NSLocalizedString("Exiting", comment: ""))
        weak var weakSelf = self
        agoraKit.leaveChannel { (_) -> Void in
            if let strongSelf = weakSelf {
                strongSelf.durationTimer?.invalidate()
                strongSelf.navigationController?.popViewControllerAnimated(true)
                UIApplication.sharedApplication().idleTimerDisabled = false
            }
        }
    }
    
    @IBAction func didClickAudioButton(btn: UIButton) {
        // Swith to audio chat
        type = AGSChatType.Audio
        agoraKit.disableVideo()
    }
    
    @IBAction func didClickVideoButton(btn: UIButton) {
        // Swith to video chat
        type = AGSChatType.Video
        agoraKit.enableVideo()
        if cameraControlButton.selected {
            cameraControlButton.selected = false
        }
    }
    
    @IBAction func didClickMenuButton(btn: UIButton) {
        frostedViewController.presentMenuViewController()
    }
    
}
