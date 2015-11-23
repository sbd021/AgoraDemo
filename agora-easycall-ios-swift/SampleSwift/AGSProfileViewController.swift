//
//  AGSProfileViewController.swift
//  SampleSwift
//
//  Created by let on 10/29/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit

class AGSProfileViewController: UIViewController {

    @IBOutlet weak var key: UITextField!
    @IBOutlet weak var username: UITextField!
    
    @IBOutlet weak var modifyButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        //
        title = NSLocalizedString("Personal Info", comment: "")
        key.placeholder = NSLocalizedString("Enter Vendor Key", comment: "")
        username.placeholder = NSLocalizedString("User", comment: "")
        modifyButton.setTitle(NSLocalizedString("Update", comment: ""), forState: UIControlState.Normal)
        
        let defaults = NSUserDefaults.standardUserDefaults()
        key.text = defaults.objectForKey(AGSKeys.vendorKey) as? String
        username.text = defaults.objectForKey(AGSKeys.username) as? String
    }
    
    override func viewDidAppear(animated: Bool) {
        super.viewDidAppear(animated)
        
        key.becomeFirstResponder()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func didClickModifyButton(sender: AnyObject) {
        
        if key.text?.characters.count == 0 {
            let alert = UIAlertView(title: "", message: NSLocalizedString("Please Enter Vendor Key", comment: ""), delegate: nil, cancelButtonTitle: NSLocalizedString("Done", comment: ""))
            alert.show()
            return;
        }
        if username.text?.characters.count == 0 {
            let alert = UIAlertView(title: "", message: NSLocalizedString("Please Enter User Name", comment: ""), delegate: nil, cancelButtonTitle: NSLocalizedString("Done", comment: ""))
            alert.show()
            return;
        }
        
        let defaults = NSUserDefaults.standardUserDefaults()
        defaults.setObject(key.text, forKey: AGSKeys.vendorKey)
        defaults.setObject(username.text, forKey: AGSKeys.username)
        
        navigationController?.popViewControllerAnimated(true)
    }
}
