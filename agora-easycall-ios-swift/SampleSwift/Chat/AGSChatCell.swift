//
//  AGSChatCell.swift
//  
//
//  Created by let on 10/7/15.
//
//

import UIKit

enum AGSChatType {
    case Video
    case Audio
}

protocol AGSChatCellDelegate {
    func cell(cell:AGSChatCell, didMuteAudio:Bool?)
}

class AGSChatCell: UICollectionViewCell {
    
    @IBOutlet weak var videoView: UIView!
    @IBOutlet weak var nameLabel: UILabel!
    var type = AGSChatType.Video {
        didSet {
            if type == .Audio {
               videoView.hidden = true
               audioView.hidden = false
               uid = 0
            } else if type == .Video {
                videoView.hidden = false
                audioView.hidden = true
            } else {
                print("error: control type not correct")
            }
        }
    }
    
    var networkQulity = AgoraRtcQuality.Quality_Down {
        didSet {
            var imageName :String!
            switch networkQulity {
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
            
            let image = UIImage(named: imageName)
            self.qualityImageView.image = image
        }
    }
    
    var uid: UInt = 0 {
        didSet {
            canvas.uid = uid
        }
    }
    
    lazy var canvas: AgoraRtcVideoCanvas = {
        let _canvas = AgoraRtcVideoCanvas()
        _canvas.renderMode = AgoraRtcRenderMode.Render_Hidden
        _canvas.view = self.videoView
        return _canvas
    }()
    
    var delegate: AGSChatCellDelegate?
    
    @IBOutlet weak var audioView: UIView!
    @IBOutlet weak var audioMicButton: UIButton!
    @IBOutlet weak var videoMicButton: UIButton!
    @IBOutlet weak var qualityImageView: UIImageView!
    
    var audioMute: Bool! {
        didSet {
           audioMicButton.selected = audioMute
           videoMicButton.selected = audioMute
        }
    }
    
    @IBAction func didClickAudioMute(btn: UIButton) {
        audioMute = !self.audioMute
        delegate?.cell(self, didMuteAudio: self.audioMute)
    }
    
//    override func awakeFromNib() {
//        audioMute = false
//    }
}