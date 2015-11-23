//
//  AGSLaunchViewController.swift
//  SampleSwift
//
//  Created by let on 10/15/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit

class AGSLaunchViewController: UIViewController {
    
    @IBOutlet var useKeyButton: UIButton!
    @IBOutlet var noKeyButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Do any additional setup after loading the view.
    }

    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        navigationController?.navigationBarHidden = true
        
        useKeyButton.setTitle(NSLocalizedString("Login with Key", comment:""), forState:UIControlState.Normal)
        noKeyButton.setTitle(NSLocalizedString("Need a key? Click Here", comment:""), forState:UIControlState.Normal)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func didClickNoKeyButton(sender: AnyObject) {
        let controller = FOWebViewController(URL: "http://www.agora.io", title: "Agora");
        navigationController?.pushViewController(controller, animated: true)
    }
}
