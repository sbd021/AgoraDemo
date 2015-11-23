//
//  AGDSplashViewController.swift
//  AgoraDemo
//
//  Created by apple on 15/10/20.
//
//

import UIKit

class AGDSplashViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    override func viewDidAppear(animated: Bool) {
        super.viewDidAppear(animated)
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, Int64(3 * Double(NSEC_PER_SEC))), dispatch_get_main_queue()) {
            self.performSegueWithIdentifier("Splash", sender: nil)
        }
    }
}
