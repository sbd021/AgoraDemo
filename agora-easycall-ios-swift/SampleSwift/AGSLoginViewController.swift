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
        
        keyTextField.text = NSUserDefaults.standardUserDefaults().stringForKey(AGSKeys.vendorKey)
        usernameTextField.text = NSUserDefaults.standardUserDefaults().stringForKey(AGSKeys.username)
        
        //
        backButton.setTitle(NSLocalizedString("Return", comment: ""), forState: UIControlState.Normal)
        loginButton.setTitle(NSLocalizedString("Login", comment: ""), forState: UIControlState.Normal)
        agoraLabel.text = NSLocalizedString("Agora Easy Call", comment: "")
        keyTextField.placeholder = NSLocalizedString("Enter Vendor Key", comment: "");
        usernameTextField.placeholder = NSLocalizedString("User", comment: "");
        
        if DEBUG == 1 {
            keyTextField.text = "6D7A26A1D3554A54A9F43BE6797FE3E2";
            usernameTextField.text = "小明";
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
