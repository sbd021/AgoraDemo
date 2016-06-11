//
//  AGDLoginViewController.swift
//  AgoraDemo
//
//  Created by apple on 15/9/23.
//
//

import UIKit

class AGDLoginViewController: UIViewController {
    
    @IBOutlet weak var keyTextField: UITextField!
    @IBOutlet weak var roomNumberTextField: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        navigationController!.navigationBarHidden = true
        
        let userDefaults = NSUserDefaults.standardUserDefaults()
        let vendorKey = userDefaults.objectForKey(AGDKeyVendorKey)
        if vendorKey != nil {
            keyTextField.text = vendorKey as? String
        } else {
            // remove these code, and it's just for inner test
            let innerKeyUrl = NSURL(string: "http://192.168.99.253:8970/agora.inner.test.key.txt")
            if let jsonData: NSData = NSData(contentsOfURL: innerKeyUrl!) {
                let innerVendorKey = NSString(data: jsonData, encoding: NSUTF8StringEncoding)
                self.keyTextField.text = innerVendorKey!.stringByReplacingOccurrencesOfString("\n", withString: "") // Please use your own key. The inner test key is just invalid in public.
            }
        }
    }
    
    override func viewWillDisappear(animated: Bool) {
        super.viewWillDisappear(animated)
        navigationController!.navigationBarHidden = false
    }
    
    @IBAction func didTapHideKeyboard(sender: UITapGestureRecognizer) {
        view.endEditing(true)
    }
    
    @IBAction func didClickPushChatViewController(sender: UIButton) {
        
        view.endEditing(true)
        if isValidInput() {
            performSegueWithIdentifier(AGDKeySegueIdentifierChat, sender: sender)
        }
    }
    
    func isValidInput() -> Bool {
        
        if keyTextField.text!.isEmpty || roomNumberTextField.text!.isEmpty {
            var alertView = UIAlertView(title: nil, message:NSLocalizedString("enter_key_room",comment:"Please Enter Vendor Key and Room No.") , delegate: nil, cancelButtonTitle: NSLocalizedString("done",comment:"Done"))
            alertView.show()
            
            return false
        } else {
            return true
        }
    }
   
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        
        if segue.identifier == AGDKeySegueIdentifierChat {
            var chatViewController = segue.destinationViewController as! AGDChatViewController
            chatViewController.dictionary = [AGDKeyVendorKey:keyTextField.text!,AGDKeyChannel:roomNumberTextField.text!]
            
            var button = sender as! UIButton
            if button.tag == 1 {
                chatViewController.chatType = .Video
            } else {
                chatViewController.chatType = .Audio
            }
        }
    }
}
