//
//  AGSAgoraKitManager.swift
//  SampleSwift
//
//  Created by let on 10/30/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit

class AGSAgoraKitManager: NSObject, AGSCallBackViewDelegate {
    
    static let shareManager = AGSAgoraKitManager()
    
    var agoraKit: AgoraRtcEngineKit!
    var vendorKey: String!
    var errorCode: AgoraRtcErrorCode?
    var callBackView: AGSCallBackView!
    var delegate: AGSAgoraKitManagerDelegate?
    
    override init() {
        super.init()
        
        callBackView = AGSCallBackView()
        callBackView.delegate = self
    }
    
    func didHideCallBackView(view: AGSCallBackView) {
        delegate?.didBackChatViewAndHideCallBackView(view)
    }
    
    
}

protocol AGSAgoraKitManagerDelegate {
    func didBackChatViewAndHideCallBackView(view: AGSCallBackView)
}