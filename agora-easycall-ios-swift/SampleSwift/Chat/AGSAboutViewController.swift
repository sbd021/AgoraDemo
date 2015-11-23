//
//  AGSAboutViewController.swift
//  SampleSwift
//
//  Created by let on 10/29/15.
//  Copyright © 2015 Agora. All rights reserved.
//

import UIKit

class AGSAboutViewController: UIViewController {
    
    @IBOutlet weak var faqLabel: UILabel!
    @IBOutlet weak var updateLabel: UILabel!
    @IBOutlet weak var AgoraLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        //
        title = NSLocalizedString("About", comment: "")
        AgoraLabel.text = NSLocalizedString("Agora Conf.", comment: "")
        updateLabel.text = NSLocalizedString("Update", comment: "")
        faqLabel.text = NSLocalizedString("FAQ", comment: "")
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    @IBAction func didTapFAQView(sender: AnyObject) {
        let web = FOWebViewController(URL: "http://www.agora.io/faq", title: NSLocalizedString("FAQ", comment: ""))
        navigationController?.pushViewController(web, animated: true)
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
