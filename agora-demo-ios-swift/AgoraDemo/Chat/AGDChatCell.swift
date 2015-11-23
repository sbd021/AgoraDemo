//
//  AGDChatCell.swift
//  AgoraDemo
//
//  Created by apple on 15/9/23.
//
//

import UIKit

class AGDChatCell: UICollectionViewCell {
    
    @IBOutlet weak var videoView: UIView!
    @IBOutlet weak var audioView: UIView!
    @IBOutlet weak var nameLabel: UILabel!
    
    var type = AGDChatType.Default {
        willSet {
            if newValue == .Video {
                videoView.hidden = false
                audioView.hidden = true
            } else if newValue == .Audio {
                videoView.hidden = true
                audioView.hidden = false
            }
        }
    }
}
