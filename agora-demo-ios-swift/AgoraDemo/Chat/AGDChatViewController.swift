//
//  AGDChatViewController.swift
//  AgoraDemo
//
//  Created by apple on 15/9/23.
//
//

import UIKit

// key
let AGDKeySegueIdentifierChat = "Chat"
let AGDKeyChannel = "Channel"
let AGDKeyVendorKey = "VendorKey"
var AGDKeyStringExit = NSLocalizedString("exiting",comment:"Exiting...")

// type
enum AGDChatType {
    case Video
    case Audio
    case Default
}

class AGDChatViewController: UIViewController {
    
    
    @IBOutlet var speakerControlButtons: [UIButton]!
    @IBOutlet var audioMuteControlButtons: [UIButton]!
    @IBOutlet weak var cameraControlButton: UIButton!
    
    @IBOutlet weak var audioControlView: UIView!
    @IBOutlet weak var videoControlView: UIView!
    
    @IBOutlet weak var videoMainView: UIView!
    
    @IBOutlet weak var collectionView: UICollectionView!
    
    @IBOutlet weak var talkTimeLabel: UILabel!
    @IBOutlet weak var dataTrafficLabel: UILabel!
    @IBOutlet weak var alertLabel: UILabel!
    
    @IBOutlet weak var videoButton: UIButton!
    @IBOutlet weak var audioButton:UIButton!
    
    var dictionary = [:]
    var chatType: AGDChatType!
    
    var uids = [UInt]()
    var videoMuteForUids = [UInt:Bool]()
    
    lazy var channel: String = {
        let room = self.dictionary[AGDKeyChannel] as! String
        self.title = NSLocalizedString("room",comment:"Room") + " " + room
        return room
        }()
    
    lazy var vendorKey: String = {
        let key = self.dictionary[AGDKeyVendorKey] as! String
        return key
        }()
 
    lazy var agoraKit: AgoraRtcEngineKit = {
        let kit = AgoraRtcEngineKit.sharedEngineWithVendorKey(self.vendorKey) { errorCode -> Void in
            if errorCode == AgoraRtcErrorCode.Error_InvalidVendorKey {
                self.agoraKit.leaveChannel(nil)
                self.errorKeyAlert.show()
            }
        }
        
        self.setUpVideo(kit)
        self.setUpBlocks(kit)
        return kit
    }()
    
    lazy var errorKeyAlert: UIAlertView = {
        let alert = UIAlertView(title: nil, message: NSLocalizedString("wrong_key",comment:"Wrong Vendor Key"), delegate: nil, cancelButtonTitle: NSLocalizedString("done",comment:"Done"))
        return alert
    }()
    
    var type = AGDChatType.Default {
        willSet {
            if newValue == .Video {
                videoControlView.hidden = false
                audioControlView.hidden = true
                
                // Video/Audio switch button
                videoButton.selected = true
                audioButton.selected = false
                
                videoMainView.hidden = false
                
            } else if newValue == .Audio {
                videoControlView.hidden = true
                audioControlView.hidden = false
                
                // Video/Audio switch button
                videoButton.selected = false
                audioButton.selected = true
                
                videoMainView.hidden = true
            }
            collectionView.reloadData()
        }
    }
    
    var durationTimer: NSTimer?
    var duration = 0
    
    
    var lastStat: AgoraRtcStats?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        type = chatType
    }
    
    override func viewDidAppear(animated: Bool) {
        super.viewDidAppear(animated)
        joinChannel(channel)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func joinChannel(channel: String) {
        showAlertLabelWithString(NSLocalizedString("wait_attendees",comment:"Waiting for attendees"))
        agoraKit.joinChannelByKey(nil, channelName: channel, info: nil, uid: 0) { (sid, uid, elapsed) -> Void in
            self.agoraKit.setEnableSpeakerphone(true)
            if self.type == .Audio {
                self.agoraKit.disableVideo()
            }
            UIApplication.sharedApplication().idleTimerDisabled = true
            
            let userDefaults = NSUserDefaults.standardUserDefaults()
            userDefaults.setObject(self.vendorKey, forKey: AGDKeyVendorKey)
        }
    }
    
    func setUpVideo(kit: AgoraRtcEngineKit) {
        kit.enableVideo()
        let videoCanvas = AgoraRtcVideoCanvas()
        videoCanvas.uid = 0
        videoCanvas.view = self.videoMainView
        videoCanvas.renderMode = AgoraRtcRenderMode.Render_Hidden
        kit.setupLocalVideo(videoCanvas)
    }
    
    func setUpBlocks(kit: AgoraRtcEngineKit) {
        
        kit.rtcStatsBlock { (stat) -> Void in
            if self.lastStat == nil {
                self.talkTimeLabel.text = "00:00"
                self.durationTimer = NSTimer.scheduledTimerWithTimeInterval(1, target: self, selector: Selector("updateTalkTimeLabel"), userInfo: nil, repeats: true)
            }
            
            var txBytes = (self.lastStat?.txBytes ?? 0)
            var rxBytes = (self.lastStat?.rxBytes ?? 0)
            var duration = (self.lastStat?.duration ?? 0)
            
            var traffic = (stat.txBytes + stat.rxBytes - txBytes - rxBytes) / 1024;
            var speed = traffic / (stat.duration - duration);
            var trafficString = String(speed) + "KB/s"
            self.dataTrafficLabel.text = trafficString;
            
            self.lastStat = stat;
        }
        
        kit.userJoinedBlock { (uid, elapsed) -> Void in
            self.hideAlertLabel()
            self.uids += [uid]
            self.videoMuteForUids.updateValue(false, forKey: uid)
            self.collectionView.insertItemsAtIndexPaths([NSIndexPath(forRow: self.uids.count - 1, inSection: 0)])
        }
        
        kit.userOfflineBlock { (uid) -> Void in
            
            if let index = self.uids.indexOf(uid) {
                self.uids.removeAtIndex(index)
                self.collectionView.deleteItemsAtIndexPaths([NSIndexPath(forRow: index, inSection: 0)])
            }
        }
        
        kit.leaveChannelBlock { (stat) -> Void in
            if self.durationTimer != nil{
                self.durationTimer!.invalidate()
            }
            
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, Int64(0.8 * Double(NSEC_PER_SEC))), dispatch_get_main_queue()) {
                self.navigationController!.popViewControllerAnimated(true)
            }
            UIApplication.sharedApplication().idleTimerDisabled = false
        }
        
        kit.connectionLostBlock { () -> Void in
            self.showAlertLabelWithString(NSLocalizedString("no_network",comment:"No network connection, please check your network"))
            self.videoMainView.hidden = false
            self.dataTrafficLabel.text = "0KB/s"
        }
        
        kit.userMuteVideoBlock { (uid, mute) -> Void in
            self.videoMuteForUids.updateValue(mute, forKey: uid)
            if let index = self.uids.indexOf(uid) {
                self.collectionView.reloadItemsAtIndexPaths([NSIndexPath(forRow: index, inSection: 0)])
            }
        }
        
        kit.firstLocalVideoFrameBlock { (width, height, elapsed) -> Void in
            self.videoMainView.frame = self.videoMainView.superview!.bounds
        }
    }
    
    func showAlertLabelWithString(text: String) {
        alertLabel.hidden = false
        alertLabel.text = text
    }
    
    func hideAlertLabel() {
        alertLabel.hidden = true
    }
    
    func updateTalkTimeLabel() {
        self.duration++
        let seconds = (duration % 60)
        let minutes = (duration - seconds)/60
        talkTimeLabel.text = String(format: "%02d:%02d", minutes, seconds)
    }
    
    @IBAction func didClickBcakView(sender: UIButton) {
        showAlertLabelWithString(AGDKeyStringExit)
        weak var weakSelf = self
        agoraKit.leaveChannel { (_) -> Void in
            if let strongSelf = weakSelf {
                strongSelf.durationTimer?.invalidate()
                strongSelf.navigationController?.popViewControllerAnimated(true)
                UIApplication.sharedApplication().idleTimerDisabled = false
            }
        }
        
        agoraKit.joinChannelByKey(nil, channelName: channel, info: nil, uid: 0) { (sid, uid, elapsed) -> Void in
            self.agoraKit.setEnableSpeakerphone(true)
            if self.type == .Audio {
                self.agoraKit.disableVideo()
            }
            UIApplication.sharedApplication().idleTimerDisabled = true
            
            let userDefaults = NSUserDefaults.standardUserDefaults()
            userDefaults.setObject(self.vendorKey, forKey: AGDKeyVendorKey)
        }
        
        
        
    }

    @IBAction func didClickHungUpButton(sender: UIButton){
        showAlertLabelWithString(AGDKeyStringExit)
        weak var weakSelf = self
        agoraKit.leaveChannel { (_) -> Void in
            if let strongSelf = weakSelf {
                strongSelf.durationTimer?.invalidate()
                strongSelf.navigationController?.popViewControllerAnimated(true)
                UIApplication.sharedApplication().idleTimerDisabled = false
            }
        }
    }
    
    @IBAction func didClickAudioMuteButton(sender: UIButton) {
        selectAudioMuteButtons(!sender.selected)
        agoraKit.muteLocalAudioStream(sender.selected)
    }
    
    @IBAction func didClickSpeakerButton(sender: UIButton) {
        agoraKit.setEnableSpeakerphone(!agoraKit.isSpeakerphoneEnabled())
        selectSpeakerButtons(!agoraKit.isSpeakerphoneEnabled())
    }
    
    @IBAction func didClickVideoMuteButton(sender: UIButton) {
        sender.selected = !sender.selected
        agoraKit.muteLocalVideoStream(sender.selected)
        videoMainView.hidden = sender.selected
    }
    
    @IBAction func didClickSwitchButton(sender: UIButton) {
        sender.selected = !sender.selected
        agoraKit.switchCamera()
    }
    
    @IBAction func didClickVideoButton(sender: UIButton) {
        agoraKit.enableVideo()
        type = .Video
        if (cameraControlButton.selected) {
            cameraControlButton.selected = false
        }
    }
    
    @IBAction func didClickAudioButton(sender: UIButton) {
        agoraKit.disableVideo()
        type = .Audio
    }
    
    func collectionView(collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return uids.count
    }
    
    func collectionView(collectionView: UICollectionView, cellForItemAtIndexPath indexPath: NSIndexPath) -> UICollectionViewCell {
        
        var cell = collectionView.dequeueReusableCellWithReuseIdentifier("cell", forIndexPath: indexPath) as! AGDChatCell
        
        // Video
        var uid = uids[indexPath.row]
        var mute = videoMuteForUids[uid]!
        
        if type == .Video {
            if mute {
                cell.type = .Audio
            } else {
                cell.type = .Video
                var videoCanvas = AgoraRtcVideoCanvas()
                videoCanvas.uid = uid
                videoCanvas.view = cell.videoView;
                videoCanvas.renderMode = AgoraRtcRenderMode.Render_Hidden
                agoraKit.setupRemoteVideo(videoCanvas)
            }
        } else {
            cell.type = .Audio
        }
        
        // Audio
        cell.nameLabel.text = String(uid)
        return cell;
    }
    
    func selectSpeakerButtons(selected: Bool) {
        for btn: UIButton in speakerControlButtons {
            btn.selected = selected
        }
    }
    
    func selectAudioMuteButtons(selected: Bool) {
        for btn: UIButton in audioMuteControlButtons {
            btn.selected = selected
        }
    }
}
