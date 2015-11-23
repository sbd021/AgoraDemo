//
//  AGSMenuPushSegue.swift
//  SampleSwift
//
//  Created by let on 10/29/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit

class AGSMenuPushSegue: UIStoryboardSegue {

    override func perform() {
        let menuViewController = sourceViewController as? AGSMenuViewController
        let nextViewController = destinationViewController
        let currentNavigationController = menuViewController?.frostedViewController.contentViewController as? UINavigationController
        
        menuViewController?.frostedViewController.hideMenuViewControllerWithCompletionHandler({ () -> Void in
            if currentNavigationController?.topViewController is AGSChatViewController {
                let chatViewController = currentNavigationController?.topViewController as? AGSChatViewController
                AGSAgoraKitManager.shareManager.callBackView.durationTime = Int((chatViewController?.duration)!)
                AGSAgoraKitManager.shareManager.callBackView.showCallBackView()
            }
            
            currentNavigationController?.pushViewController(nextViewController, animated: true)
        })
    }
}
