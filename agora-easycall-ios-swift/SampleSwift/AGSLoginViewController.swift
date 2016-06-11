//
//  AGSLoginViewController.swift
//  SampleSwift
//
//  Created by let on 10/19/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit
import Foundation

class AGSLoginViewController: AGSBaseViewController { //:base

    // Outlet
    
    @IBOutlet weak var keyTextField: UITextField!
    @IBOutlet weak var usernameTextField: UITextField!
    @IBOutlet weak var backButton: UIButton!
    @IBOutlet weak var agoraLabel: UILabel!
    @IBOutlet weak var loginButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
//        keyTextField.text = NSUserDefaults.standardUserDefaults().stringForKey(AGSKeys.vendorKey)
        usernameTextField.text = NSUserDefaults.standardUserDefaults().stringForKey(AGSKeys.username)
        
        //
        backButton.setTitle(NSLocalizedString("Return", comment: ""), forState: UIControlState.Normal)
        loginButton.setTitle(NSLocalizedString("Login", comment: ""), forState: UIControlState.Normal)
        agoraLabel.text = NSLocalizedString("Agora Easy Call", comment: "")
        keyTextField.placeholder = NSLocalizedString("Enter Vendor Key", comment: "");
        usernameTextField.placeholder = NSLocalizedString("User", comment: "");
        
        let vendorKey = NSUserDefaults.standardUserDefaults().stringForKey(AGSKeys.vendorKey)
        if vendorKey != nil {
            keyTextField.text = vendorKey
        } else {
            let innerKeyUrl = NSURL(string: "http://192.168.99.253:8970/agora.inner.test.key.txt")
            if let jsonData: NSData = NSData(contentsOfURL: innerKeyUrl!) {
                let innerVendorKey = NSString(data: jsonData, encoding: NSUTF8StringEncoding)
                self.keyTextField.text = innerVendorKey!.stringByReplacingOccurrencesOfString("\n", withString: "") // Please use your own key. The inner test key is just invalid in public.
            }

        }
     
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    func isValidateInput() -> Bool {
        view.endEditing(true)
        
        if keyTextField.text?.characters.count == 0 {
            let alert = UIAlertView(title: "", message: NSLocalizedString("Vendor key can not be empty", comment: ""), delegate: nil, cancelButtonTitle: NSLocalizedString("Done", comment: ""))
            alert.show()
            return false;
        }
        if usernameTextField.text?.characters.count == 0 {
            let alert = UIAlertView(title: "", message: NSLocalizedString("User name can not be empty", comment: ""), delegate: nil, cancelButtonTitle: NSLocalizedString("Done", comment: ""))
            alert.show()
            return false;
        }
        return true
    }
    
    @IBAction func didClickEnterChatRoom(sender: AnyObject) {
        if isValidateInput() {
            performSegueWithIdentifier(AGSSegueIdentifiers.select, sender: self)
            let defualts = NSUserDefaults.standardUserDefaults()
            defualts.setObject(keyTextField.text, forKey: AGSKeys.vendorKey)
            defualts.setObject(usernameTextField.text, forKey: AGSKeys.username)
        }
    }
    
}
