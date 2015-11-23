//
//  AGSNavigationBar.swift
//  SampleSwift
//
//  Created by let on 10/19/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit

class AGSNavigationBar: UINavigationBar {

    /*
    // Only override drawRect: if you perform custom drawing.
    // An empty implementation adversely affects performance during animation.
    override func drawRect(rect: CGRect) {
        // Drawing code
    }
    */
    
    override func awakeFromNib() {
        barStyle = UIBarStyle.BlackTranslucent
        tintColor = UIColor.whiteColor()
        setBackgroundImage(UIImage(named: "ic_room_navi_bg_128"), forBarMetrics: UIBarMetrics.Default)
    }

}
