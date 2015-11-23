//
//  AGSSplashSegue.swift
//  SampleSwift
//
//  Created by let on 11/2/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit

class AGSSplashSegue: UIStoryboardSegue {
    
    override func perform() {
        UIApplication.sharedApplication().keyWindow?.rootViewController = destinationViewController
    }
    
}
